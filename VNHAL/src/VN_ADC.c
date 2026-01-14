#include "VN_ADC.h"

// --- ĐỊNH NGHĨA THANH GHI SENS / SARADC ---
#define SENS_BASE           0x3FF48800
#define SENS_SAR_READ_CTRL  *((volatile u32 *)(SENS_BASE + 0x00))
#define SENS_SAR_ATTEN1     *((volatile u32 *)(SENS_BASE + 0x04)) // Atten cho ADC1
#define SENS_SAR_MEAS_START1 *((volatile u32 *)(SENS_BASE + 0x2C)) // Lệnh đo

// Thanh ghi cấu hình GPIO thành Analog (RTC_IO)
#define RTC_IO_BASE         0x3FF48400
// (Cần map từng chân RTC pad, ở đây demo ngắn gọn)

void ADC_KhoiTao(void) {
    u32 ctrl = SENS_SAR_READ_CTRL;
    ctrl &= ~(0xFF << 19); // Xóa cũ
    ctrl |= (3 << 19);     // Set 12 bit (0-4095)
    SENS_SAR_READ_CTRL = ctrl;
}

u16 ADC_DocGiaTri(byte chan) {
    // Mapping GPIO sang ADC Channel (Chỉ hỗ trợ vài chân cơ bản)
    byte adc_channel = 0;
    if (chan == 36) adc_channel = 0;
    else if (chan == 39) adc_channel = 3;
    else return 0; // Chưa hỗ trợ chân khác

    // 1. Cấu hình Attenuation (Suy hao) để đo được 3.3V
    // Mỗi kênh 2 bit trong thanh ghi SENS_SAR_ATTEN1
    // Set mức 3 (11dB) -> Full range
    u32 atten = SENS_SAR_ATTEN1;
    atten |= (3 << (adc_channel * 2));
    SENS_SAR_ATTEN1 = atten;

    // 2. Ra lệnh đo (Start Force)
    // Nguyên lý: Ghi vào MEAS_START1, sau đó chờ bit DONE
    SENS_SAR_MEAS_START1 = (1 << 31) | ((adc_channel) << 16); 
    
    volatile u32* sar_data_reg = (volatile u32*)(0x3FF4884C);    
    return 0; // Placeholder
}