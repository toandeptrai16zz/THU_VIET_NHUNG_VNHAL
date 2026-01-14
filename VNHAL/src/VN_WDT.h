#ifndef VN_WDT_H
#define VN_WDT_H
#include "VN_Common.h"

// --- BỘ GIÁM SÁT HỆ THỐNG (WATCHDOG TIMER) ---

// Khởi tạo WDT với thời gian chờ (ms)
// Nếu hệ thống bị treo quá thời gian này, chip sẽ tự khởi động lại
void WDT_KhoiTao(u32 thoi_gian_ms);

// Làm mới bộ đếm (Tương đương "Feed the dog")
// Phải gọi hàm này liên tục trong vòng lặp để báo là hệ thống vẫn sống
void WDT_LamMoi(void);

// Vô hiệu hóa WDT (Tắt giám sát)
// Cảnh báo: Nếu tắt, khi chip treo sẽ không ai reset hộ
void WDT_VoHieuHoa(void);

#endif