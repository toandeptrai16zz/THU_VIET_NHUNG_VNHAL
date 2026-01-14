#include "VN_Time.h"

// Xung nhịp CPU mặc định của ESP32 là 240MHz (240 triệu xung/giây)
// Tức là 1 micro-giây (us) có 240 xung.
#define CPU_FREQ_MHZ  240

// Hàm Assembly đọc thanh ghi CCOUNT (Cycle Count) của CPU
static inline u32 lay_xung_nhip_cpu(void) {
    u32 ccount;
    asm volatile("rsr %0, ccount" : "=a" (ccount));
    return ccount;
}

void ThoiGian_KhoiTao(void) {
    // Không cần làm gì vì ESP32 tự đếm khi bật nguồn
}

void Tre_micro_giay(u32 us) {
    u32 bat_dau = lay_xung_nhip_cpu();
    u32 so_xung_can_doi = us * CPU_FREQ_MHZ;
    
    // Vòng lặp chờ đến khi đủ số xung
    while ((lay_xung_nhip_cpu() - bat_dau) < so_xung_can_doi) {
        asm volatile("nop"); // Nghỉ ngơi 1 nhịp
    }
}

void Tre_mili_giay(u32 ms) {
    // Gọi hàm delay us để đỡ phải viết lại logic
    Tre_micro_giay(ms * 1000);
}

u32 LayThoiGian_ms(void) {
    // Chuyển đổi từ số xung sang mili-giây
    return lay_xung_nhip_cpu() / (CPU_FREQ_MHZ * 1000);
}