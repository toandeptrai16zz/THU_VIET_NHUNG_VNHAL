#ifndef VN_TIME_H
#define VN_TIME_H
#include "VN_Common.h"

// Khởi tạo bộ đếm (thực ra ESP32 tự chạy, hàm này để clear nếu cần)
void ThoiGian_KhoiTao(void);

// Delay chính xác
void Tre_mili_giay(u32 ms);
void Tre_micro_giay(u32 us);

// Lấy thời gian từ lúc khởi động
u32 LayThoiGian_ms(void);

#endif