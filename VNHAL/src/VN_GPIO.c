#include "VN_GPIO.h"

// --- ĐỊNH NGHĨA ĐỊA CHỈ PHẦN CỨNG (ESP32 WROOM) ---
#define GPIO_BASE       0x3FF44000
#define GPIO_OUT_REG    *((volatile u32 *)(GPIO_BASE + 0x04))
#define GPIO_ENABLE_REG *((volatile u32 *)(GPIO_BASE + 0x20))
#define GPIO_IN_REG     *((volatile u32 *)(GPIO_BASE + 0x3C))

void CauHinhChan(byte chan, byte che_do) {
    if (chan > 33) return; // Bảo vệ
    if (che_do == RA) SET_BIT(GPIO_ENABLE_REG, chan);
    else              CLEAR_BIT(GPIO_ENABLE_REG, chan);
}

void GhiDien(byte chan, byte muc) {
    if (chan > 33) return;
    if (muc == CAO) SET_BIT(GPIO_OUT_REG, chan);
    else            CLEAR_BIT(GPIO_OUT_REG, chan);
}

byte DocDien(byte chan) {
    if (chan > 33) return 0;
    return READ_BIT(GPIO_IN_REG, chan);
}

void DaoTrangThai(byte chan) {
    if (chan > 33) return;
    TOGGLE_BIT(GPIO_OUT_REG, chan);
}