/*
  Ví dụ: Nháy LED sử dụng thư viện VNHAL
  Tác giả: Hà Quang Chương
*/

#include <VNHAL.h> // Chỉ cần gọi file tổng

#define LED_PIN 2

void setup() {
  // Cấu hình chân số 2 là ĐẦU RA (OUTPUT)
  CauHinhChan(LED_PIN, RA);
}

void loop() {
  GhiDien(LED_PIN, CAO);  // Bật đèn
  delay(500);             // Đợi 0.5s
  GhiDien(LED_PIN, THAP); // Tắt đèn
  delay(500);             // Đợi 0.5s
}