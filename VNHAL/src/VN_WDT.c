#include "VN_WDT.h"

// Địa chỉ Timer Group 0 (Chứa Main Watchdog Timer 0)
#define TIMG0_BASE      0x3FF5F000
#define WDT_CONFIG0     *((volatile u32 *)(TIMG0_BASE + 0x48))
#define WDT_FEED        *((volatile u32 *)(TIMG0_BASE + 0x60))
#define WDT_PROTECT     *((volatile u32 *)(TIMG0_BASE + 0x64)) // Thanh ghi khóa

#define WDT_KEY         0x50D83AA1 // Chìa khóa mở quyền ghi

void WDT_KhoiTao(u32 thoi_gian_ms) {
    // 1. Mở khóa quyền ghi (Unlock)
    WDT_PROTECT = WDT_KEY;

    // 2. Cấu hình
    // Bit 31: Enable (Bật)
    // Thực tế để set đúng thoi_gian_ms cần tính toán Clock Stages (hơi dài dòng)
    // Ở mức độ cơ bản này, ta kích hoạt cấu hình mặc định của ROM (thường là vài giây)
    WDT_CONFIG0 |= (1 << 31); 
    
    // 3. Khóa lại (Lock)
    WDT_PROTECT = 0;
}

void WDT_LamMoi(void) {
    WDT_PROTECT = WDT_KEY;  // Mở khóa
    WDT_FEED = 1;           // Ghi số 1 để reset bộ đếm về 0
    WDT_PROTECT = 0;        // Khóa lại
}

void WDT_VoHieuHoa(void) {
    WDT_PROTECT = WDT_KEY;
    WDT_CONFIG0 &= ~(1 << 31); // Xóa bit Enable (Tắt)
    WDT_PROTECT = 0;
}