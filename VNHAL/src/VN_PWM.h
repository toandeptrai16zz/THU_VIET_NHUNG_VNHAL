#ifndef VN_PWM_H
#define VN_PWM_H
#include "VN_Common.h"

// Cấu hình PWM cho một chân
// kenh: 0-15 (ESP32 có 16 kênh PWM)
// tan_so_hz: VD 5000Hz (cho LED), 50Hz (cho Servo)
void PWM_KhoiTao(byte chan, byte kenh, u32 tan_so_hz);

// Ghi giá trị (Duty Cycle)
// gia_tri: 0 -> 8191 (Độ phân giải 13 bit)
void PWM_GhiGiaTri(byte kenh, u32 gia_tri);

#endif