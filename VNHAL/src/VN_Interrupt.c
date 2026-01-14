#include "VN_Interrupt.h"
#include "VN_GPIO.h"
// Thư viện hệ thống bắt buộc của ESP32 để can thiệp Vector Table
#include "esp32/rom/ets_sys.h" 
#include "driver/gpio.h" 

// Địa chỉ thanh ghi cấu hình chân (để set kiểu trigger)
#define GPIO_BASE           0x3FF44000
#define GPIO_PIN_REG(n)     *((volatile u32 *)(GPIO_BASE + 0x88 + (n)*4))

void Ngat_DangKy(byte chan, byte kieu_kich_hoat, TrinhPhucVuNgat_t trinh_phuc_vu) {
    if(chan > 33) return;

    // 1. Cấu hình chân là ĐẦU VÀO (INPUT)
    CauHinhChan(chan, VAO);

    // 2. Cấu hình kiểu kích hoạt (Trigger Type) bằng Thanh ghi
    // Bit 7-9 trong GPIO_PIN_REG quyết định kiểu ngắt
    // 1: PosEdge (Sườn dương), 2: NegEdge (Sườn âm), 3: AnyEdge
    u32 config = GPIO_PIN_REG(chan);
    config &= ~(0x07 << 7); // Xóa cấu hình cũ (3 bit tại vị trí 7)
    config |= (kieu_kich_hoat << 7); // Ghi cấu hình mới
    GPIO_PIN_REG(chan) = config;

    // 3. Đăng ký ISR vào Core (Dùng SDK ESP-IDF)
    // Cài đặt dịch vụ ISR mặc định (nếu chưa có)
    gpio_install_isr_service(0); 
    // Gắn hàm của người dùng vào danh sách xử lý
    gpio_isr_handler_add((gpio_num_t)chan, trinh_phuc_vu, (void*)chan);
}

void Ngat_VoHieuHoaToanCuc(void) {
    ETS_GPIO_INTR_DISABLE(); // Lệnh Assembly tắt ngắt CPU
}

void Ngat_ChoPhepToanCuc(void) {
    ETS_GPIO_INTR_ENABLE(); // Lệnh Assembly bật lại ngắt
}