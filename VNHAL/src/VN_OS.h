#ifndef VN_OS_H
#define VN_OS_H
#include "VN_Common.h"

// Số lượng tác vụ tối đa (Tùy chỉnh)
#define MAX_TAC_VU 10

// Định nghĩa cấu trúc một Tác vụ
typedef struct {
    void (*ham_thuc_thi)(void); // Con trỏ hàm
    u32 chu_ky_ms;              // Bao lâu chạy 1 lần (0 = chạy liên tục)
    u32 thoi_gian_truoc_do;     // Để tính giờ
    byte dang_chay;             // Cờ bật/tắt
} TacVu_t;

// --- API QUẢN LÝ TÁC VỤ ---

// Khởi tạo hệ thống lập lịch
void OS_KhoiTao(void);

// Tạo tác vụ mới
// - ham: Tên hàm cần chạy
// - chu_ky_ms: Cách bao nhiêu ms thì chạy lại hàm này 1 lần
void TaoTacVu(void (*ham)(void), u32 chu_ky_ms);

// Chạy hệ điều hành (Hàm này sẽ chiếm quyền CPU vĩnh viễn)
void OS_Chay(void);

#endif