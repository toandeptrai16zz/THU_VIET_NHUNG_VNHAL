#include "VN_UART.h"
#include <stdio.h> // Cần cho hàm sprintf xử lý số thực

// Địa chỉ UART0
#define UART0_BASE      0x3FF40000
#define UART_FIFO       *((volatile u32 *)(UART0_BASE + 0x00))
#define UART_STATUS     *((volatile u32 *)(UART0_BASE + 0x1C))
#define UART_CLKDIV     *((volatile u32 *)(UART0_BASE + 0x14))

void UART_KhoiTao(u32 toc_do_baud) {
    u32 apb_clk = 80000000; // 80MHz
    u32 clk_div = (apb_clk << 4) / toc_do_baud;
    UART_CLKDIV = clk_div;
}

void UART_GhiKyTu(char c) {
    // Chờ FIFO rỗng (Bit 16-23 < 120)
    while (((UART_STATUS >> 16) & 0xFF) >= 120);
    UART_FIFO = c;
}

void UART_GhiChuoi(const char* str) {
    while (*str) UART_GhiKyTu(*str++);
}

void UART_XuongDong(void) {
    UART_GhiKyTu('\r');
    UART_GhiKyTu('\n');
}

void UART_InSoNguyen(long num) {
    char buf[32];
    sprintf(buf, "%ld", num); // Dùng thư viện C chuẩn để convert cho nhanh
    UART_GhiChuoi(buf);
}

void UART_InSoThuc(float num, byte so_chu_so_thap_phan) {
    char buf[32];
    // Xử lý thủ công một chút vì %f trong embedded đôi khi bị cắt giảm
    long phan_nguyen = (long)num;
    UART_InSoNguyen(phan_nguyen);
    UART_GhiKyTu('.');
    
    float phan_thap_phan = num - phan_nguyen;
    if(phan_thap_phan < 0) phan_thap_phan = -phan_thap_phan;

    for(byte i=0; i<so_chu_so_thap_phan; i++) {
        phan_thap_phan *= 10;
        UART_GhiKyTu(((long)phan_thap_phan % 10) + '0');
    }
}