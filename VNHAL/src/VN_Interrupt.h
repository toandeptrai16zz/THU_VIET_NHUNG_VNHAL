#include "VN_Interrupt.h"
#include "VN_GPIO.h"

#include "esp32/rom/ets_sys.h" 
#include "driver/gpio.h" 

// --- ĐỊNH NGHĨA THANH GHI CẤU HÌNH NGẮT (BARE-METAL) ---
#define GPIO_BASE_ADDR      0x3FF44000
#define GPIO_PIN_REG(n)     *((volatile u32 *)(GPIO_BASE_ADDR + 0x88 + (n)*4))
#define GPIO_STATUS_W1TC    *((volatile u32 *)(GPIO_BASE_ADDR + 0x4C)) // Xóa cờ ngắt

static byte da_cai_dat_dich_vu = SAI;

void ISR_DangKy(byte chan, byte kieu_kich, ISR_Handler_t ham_xu_ly) {
    if(chan > 33) return; // Bảo vệ

    CauHinhChan(chan, VAO);

    if (da_cai_dat_dich_vu == SAI) {
        gpio_install_isr_service(0); // Cờ 0: Mặc định
        da_cai_dat_dich_vu = DUNG;
    }

    u32 val = GPIO_PIN_REG(chan);
    val &= ~(0x07 << 7);        // Xóa 3 bit cũ (Mask 111 dịch 7)
    val |= (kieu_kich << 7);    // Ghi kiểu mới
    GPIO_PIN_REG(chan) = val;

    // 4. Móc hàm vào Vector Table
    // Hàm này sẽ tự động Bật ngắt (Int Enable) cho chân đó
    gpio_isr_handler_add((gpio_num_t)chan, ham_xu_ly, (void*)chan);
}

void ISR_KhoaToanCuc(void) {
    ETS_GPIO_INTR_DISABLE(); // Lệnh Assembly: RSIL (Read Set Interrupt Level)
}

void ISR_MoToanCuc(void) {
    ETS_GPIO_INTR_ENABLE();
}

void ISR_GoBo(byte chan) {
    if(chan > 33) return;
    // Xóa handler
    gpio_isr_handler_remove((gpio_num_t)chan);
    // Tắt ngắt trong thanh ghi cấu hình (Về 0)
    u32 val = GPIO_PIN_REG(chan);
    val &= ~(0x07 << 7);
    GPIO_PIN_REG(chan) = val;
}