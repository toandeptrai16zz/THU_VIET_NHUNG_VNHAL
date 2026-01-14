#include "VN_PWM.h"

// --- ĐỊNH NGHĨA THANH GHI LEDC (LED CONTROL) ---
#define LEDC_BASE_ADDR      0x3FF59000

// Cấu hình Timer (High Speed Timer 0)
#define LEDC_HSTIMER0_CONF  *((volatile u32 *)(LEDC_BASE_ADDR + 0x500))
#define LEDC_HSTIMER0_VAL   *((volatile u32 *)(LEDC_BASE_ADDR + 0x504))

// Cấu hình Kênh 0 (High Speed Channel 0)
#define LEDC_HSCH0_CONF0    *((volatile u32 *)(LEDC_BASE_ADDR + 0x00))
#define LEDC_HSCH0_HPOINT   *((volatile u32 *)(LEDC_BASE_ADDR + 0x04))
#define LEDC_HSCH0_DUTY     *((volatile u32 *)(LEDC_BASE_ADDR + 0x08))
#define LEDC_HSCH0_CONF1    *((volatile u32 *)(LEDC_BASE_ADDR + 0x0C))
#define LEDC_HSCH0_DUTY_R   *((volatile u32 *)(LEDC_BASE_ADDR + 0x10))
typedef uint64_t u64; 
// GPIO Matrix (Để nối PWM ra chân)
#define GPIO_FUNC_OUT_SEL_CFG_REG  0x3FF44530 

void PWM_KhoiTao(byte chan, byte kenh, u32 tan_so_hz) {
    // 1. Cấu hình Timer 0 (High Speed)
    // Bit 0-3: Duty resolution (13 bit = 13)
    // Bit 10-27: Clock divider (Tính toán: 80MHz / tan_so / 2^13)
    // Để đơn giản ta dùng nguồn xung APB_CLK 80MHz
    
    // Tính Divider (Dạng Fixed Point 8-bit thập phân)
    // Div = (80.000.000 << 8) / 8192 / tan_so
    u64 clk_div = ((u64)80000000 << 8) / 8192 / tan_so_hz;
    
    // Ghi vào thanh ghi Timer Config
    // Bit 25: Tick Select (1=APB)
    u32 conf = (1 << 25) | (13 << 0); // APB Clock, 13 bit resolution
    conf |= (clk_div << 4); // Nhét Divider vào bit 4-21
    
    LEDC_HSTIMER0_CONF = conf;
    // Reset Timer
    LEDC_HSTIMER0_CONF |= (1 << 31); // Bit RST
    LEDC_HSTIMER0_CONF &= ~(1 << 31);

    // 2. Cấu hình Kênh (Channel 0)
    // Bit 0-1: Timer Sel (00 = Timer 0)
    LEDC_HSCH0_CONF0 = (0 << 0); 
    LEDC_HSCH0_HPOINT = 0; // Bắt đầu từ 0
    LEDC_HSCH0_DUTY = 0;   // Duty ban đầu = 0
    
    // Cập nhật cấu hình
    LEDC_HSCH0_CONF1 = (1 << 31); // Start bit

    // 3. Gắn chân (GPIO Matrix)
    // Cái này hơi khoai, phải nối tín hiệu LEDC_HS_SIG_OUT0 (idx 140) ra chân GPIO
    // Địa chỉ thanh ghi Config chân: 0x3FF44530 + (chan * 4)
    volatile u32* gpio_func_reg = (volatile u32*)(GPIO_FUNC_OUT_SEL_CFG_REG + (chan * 4));
    *gpio_func_reg = 140; // 140 là index của LEDC High Speed Channel 0
    
    // Bật Output cho chân đó
    CauHinhChan(chan, RA);
}

void PWM_GhiGiaTri(byte kenh, u32 gia_tri) {
    // Chỉ hỗ trợ kênh 0 cho code gọn (Muốn thêm kênh thì switch case địa chỉ)
    if (kenh != 0) return;

    // Ghi giá trị Duty mới
    LEDC_HSCH0_DUTY = (gia_tri << 4); // Shift 4 bit vì phần cứng yêu cầu
    
    // Kích hoạt cập nhật (Update bit)
    LEDC_HSCH0_CONF1 |= (1 << 31);
}