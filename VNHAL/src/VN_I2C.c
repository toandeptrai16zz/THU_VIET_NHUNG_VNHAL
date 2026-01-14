#include "VN_I2C.h"
#include "VN_GPIO.h"
#include "VN_Time.h"

// Thời gian trễ để tạo xung (I2C 100kHz -> chu kỳ 10us -> nửa chu kỳ 5us)
// Dùng bit-banging nên ta delay tầm 2-4us là an toàn.
#define I2C_DELAY  4 

// Macro thao tác chân cho gọn code
#define SDA_CAO()   GhiDien(I2C_SDA_PIN, CAO)
#define SDA_THAP()  GhiDien(I2C_SDA_PIN, THAP)
#define SCL_CAO()   GhiDien(I2C_SCL_PIN, CAO)
#define SCL_THAP()  GhiDien(I2C_SCL_PIN, THAP)
#define DOC_SDA()   DocDien(I2C_SDA_PIN)

void I2C_KhoiTao(void) {
    // I2C Open-Drain: Bình thường thả nổi (Input/High), Kéo xuống là Low
    // Nhưng để đơn giản ta cấu hình Output Push-Pull + Delay
    CauHinhChan(I2C_SDA_PIN, RA);
    CauHinhChan(I2C_SCL_PIN, RA);
    
    SDA_CAO();
    SCL_CAO();
    Tre_micro_giay(I2C_DELAY);
}

void I2C_BatDau(void) {
    // Khi SCL đang CAO, kéo SDA từ CAO xuống THAP
    SDA_CAO();
    SCL_CAO();
    Tre_micro_giay(I2C_DELAY);
    SDA_THAP();
    Tre_micro_giay(I2C_DELAY);
    SCL_THAP(); // Giữ SCL thấp để chuẩn bị truyền
}

void I2C_KetThuc(void) {
    // Khi SCL đang CAO, kéo SDA từ THAP lên CAO
    SCL_THAP();
    SDA_THAP();
    Tre_micro_giay(I2C_DELAY);
    
    SCL_CAO();
    Tre_micro_giay(I2C_DELAY);
    SDA_CAO();
    Tre_micro_giay(I2C_DELAY);
}

void I2C_GhiByte(byte data) {
    for(byte i = 0; i < 8; i++) {
        // Ghi từng bit từ MSB đến LSB
        if ((data & 0x80) != 0) SDA_CAO();
        else                    SDA_THAP();
        
        data <<= 1; // Dịch trái để lấy bit tiếp theo
        
        // Tạo xung Clock
        Tre_micro_giay(I2C_DELAY);
        SCL_CAO();
        Tre_micro_giay(I2C_DELAY);
        SCL_THAP();
    }
    
    // --- Đọc ACK từ thiết bị ---
    // Thả SDA ra để làm Input (hoặc set High nếu là giả lập)
    SDA_CAO(); 
    CauHinhChan(I2C_SDA_PIN, VAO); // Chuyển sang Input để nghe
    
    Tre_micro_giay(I2C_DELAY);
    SCL_CAO(); // Kéo Clock lên để đọc
    Tre_micro_giay(I2C_DELAY);
    
    // Nếu thiết bị kéo SDA xuống thấp -> Có ACK
    // (Ta có thể return giá trị này nếu muốn kiểm tra lỗi)
    // byte ack = DOC_SDA(); 
    
    SCL_THAP(); // Kết thúc xung ACK
    CauHinhChan(I2C_SDA_PIN, RA); // Trả lại quyền Output
}

byte I2C_DocByte(byte ack) {
    byte data = 0;
    CauHinhChan(I2C_SDA_PIN, VAO); // Chuyển SDA sang Input
    
    for(byte i = 0; i < 8; i++) {
        data <<= 1;
        Tre_micro_giay(I2C_DELAY);
        SCL_CAO();
        Tre_micro_giay(I2C_DELAY);
        
        if(DOC_SDA()) data |= 1;
        
        SCL_THAP();
    }
    
    // --- Gửi ACK/NACK cho thiết bị ---
    CauHinhChan(I2C_SDA_PIN, RA);
    if(ack) SDA_THAP(); // Gửi ACK (muốn nhận tiếp)
    else    SDA_CAO();  // Gửi NACK (dừng nhận)
    
    Tre_micro_giay(I2C_DELAY);
    SCL_CAO();
    Tre_micro_giay(I2C_DELAY);
    SCL_THAP();
    
    return data;
}

byte I2C_KiemTraThietBi(byte dia_chi) {
    // Logic: Gửi Start -> Gửi Địa chỉ + Write bit -> Đọc ACK -> Stop
    I2C_BatDau();
    
    // Gửi 7 bit địa chỉ + bit 0 (Write)
    byte byte_gui = (dia_chi << 1); 
    
    // Copy logic GhiByte nhưng có trả về ACK để check
    for(byte i = 0; i < 8; i++) {
        if ((byte_gui & 0x80) != 0) SDA_CAO();
        else                        SDA_THAP();
        byte_gui <<= 1;
        Tre_micro_giay(I2C_DELAY);
        SCL_CAO();
        Tre_micro_giay(I2C_DELAY);
        SCL_THAP();
    }
    
    // Check ACK
    SDA_CAO();
    CauHinhChan(I2C_SDA_PIN, VAO);
    Tre_micro_giay(I2C_DELAY);
    SCL_CAO();
    Tre_micro_giay(I2C_DELAY);
    
    byte phan_hoi = DOC_SDA(); // 0 là có thiết bị, 1 là không có
    
    SCL_THAP();
    CauHinhChan(I2C_SDA_PIN, RA);
    
    I2C_KetThuc();
    
    return (phan_hoi == 0); // Trả về DUNG nếu tìm thấy
}