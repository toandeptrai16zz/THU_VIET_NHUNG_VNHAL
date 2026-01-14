# VNHAL - THƯ VIỆN LẬP TRÌNH NHÚNG ESP32 ( VIỆT HÓA, TỐI ƯU) V1.0

## Giới thiệu
Chào anh em, đây là bộ thư viện tôi tự viết từ A-Z, chọc thẳng vào thanh ghi, KHÔNG phụ thuộc Arduino, KHÔNG phụ thuộc framework lằng nhằng.
Mục tiêu: Code chạy nhanh hơn, dễ hiểu, toàn bộ hàm bằng Tiếng Việt.

## Tính năng
- **GPIO:** Bật tắt chân siêu tốc (nhanh gấp 50 lần digitalWrite).
- **Time:** Delay chuẩn từng micro-giây.
- **UART:** In log ra màn hình máy tính.
- **PWM:** Điều khiển độ sáng LED (Bare-metal).
- **OS:** Tích hợp FreeRTOS đa nhiệm (Việt hóa).

## Cách dùng (Cho anh em PlatformIO)
1. Tải thư mục `src` về.
2. Ném vào thư mục `src` dự án của anh em.
3. Trong `main.cpp` thêm `#include "VNHAL.h"`.
4. Gọi `VNHAL_KhoiTao()` trong setup.
5. Chiến thôi!

#### 2. Tạo file nén `VNHAL_v1.0.zip`
Nén toàn bộ thư mục lại.
## Cách cài đặt (PlatformIO)
Thêm vào `platformio.ini`:
```ini
lib_deps = 
    https://github.com/toandeptrai16zz/THU_VIET_NHUNG_VNHAL.git
```    
---

## Ví dụ
```cpp
#include "VNHAL.h"
void setup() {
    VNHAL_KhoiTao();
    CauHinhChan(2, RA);
}
void loop() {
    DaoTrangThai(2);
    Tre_mili_giay(500);
}