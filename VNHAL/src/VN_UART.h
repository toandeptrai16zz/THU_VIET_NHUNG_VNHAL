#ifndef VN_UART_H
#define VN_UART_H
#include "VN_Common.h"

void UART_KhoiTao(u32 toc_do_baud);
void UART_GhiKyTu(char c);
void UART_GhiChuoi(const char* str);
void UART_XuongDong(void);

// Hàm in số (Thay thế Serial.print)
void UART_InSoNguyen(long num);
void UART_InSoThuc(float num, byte so_chu_so_thap_phan);

#endif