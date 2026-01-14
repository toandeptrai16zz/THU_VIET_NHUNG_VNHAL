#include "VN_OS.h"
#include "VN_Time.h" 

// Mảng lưu danh sách các tác vụ
static TacVu_t danh_sach_tac_vu[MAX_TAC_VU];
static byte so_luong_tac_vu = 0;

void OS_KhoiTao(void) {
    so_luong_tac_vu = 0;
    // Xóa sạch danh sách
    for(int i=0; i<MAX_TAC_VU; i++) {
        danh_sach_tac_vu[i].dang_chay = SAI;
    }
}

void TaoTacVu(void (*ham)(void), u32 chu_ky_ms) {
    if (so_luong_tac_vu >= MAX_TAC_VU) return; // Đầy bộ nhớ rồi

    // Gán thông tin vào danh sách
    danh_sach_tac_vu[so_luong_tac_vu].ham_thuc_thi = ham;
    danh_sach_tac_vu[so_luong_tac_vu].chu_ky_ms = chu_ky_ms;
    danh_sach_tac_vu[so_luong_tac_vu].thoi_gian_truoc_do = 0; // Chạy ngay lần đầu
    danh_sach_tac_vu[so_luong_tac_vu].dang_chay = DUNG;
    
    so_luong_tac_vu++;
}

void OS_Chay(void) {
    while(1) {
        u32 thoi_gian_hien_tai = LayThoiGian_ms();

        // Duyệt qua tất cả các tác vụ đã đăng ký
        for(int i = 0; i < so_luong_tac_vu; i++) {
            // Nếu tác vụ đang được phép chạy
            if (danh_sach_tac_vu[i].dang_chay == DUNG) {
                
                // Kiểm tra xem đã đến giờ chưa
                // (Hiện tại - Quá khứ >= Chu kỳ)
                if ((thoi_gian_hien_tai - danh_sach_tac_vu[i].thoi_gian_truoc_do) >= danh_sach_tac_vu[i].chu_ky_ms) {
                    
                    // Cập nhật lại thời gian
                    danh_sach_tac_vu[i].thoi_gian_truoc_do = thoi_gian_hien_tai;
                    
                    // CHẠY HÀM CỦA NGƯỜI DÙNG
                    danh_sach_tac_vu[i].ham_thuc_thi();
                }
            }
        }
        
        
    }
}