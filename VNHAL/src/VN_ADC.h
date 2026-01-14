#ifndef VN_ADC_H
#define VN_ADC_H
#include "VN_Common.h"

// Khởi tạo ADC (Độ phân giải 12-bit: 0-4095)
void ADC_KhoiTao(void);

// Đọc giá trị từ một chân (Trả về 0 -> 4095)
// Lưu ý: ESP32 chỉ hỗ trợ ADC1 trên các chân GPIO 32-39 khi dùng WiFi
u16 ADC_DocGiaTri(byte chan);

// Đổi sang điện áp (mV) cho dễ dùng
u16 ADC_DocDienAp(byte chan);

#endif