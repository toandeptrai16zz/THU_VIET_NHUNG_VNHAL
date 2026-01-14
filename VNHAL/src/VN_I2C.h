#ifndef VN_I2C_H
#define VN_I2C_H
#include "VN_Common.h"

// Định nghĩa chân I2C (Sửa ở đây nếu muốn đổi chân)
#define I2C_SDA_PIN  21
#define I2C_SCL_PIN  22

// Các hàm giao tiếp cơ bản
void I2C_KhoiTao(void);
void I2C_BatDau(void);              // Start Condition
void I2C_KetThuc(void);             // Stop Condition
void I2C_GhiByte(byte data);        // Gửi 1 byte
byte I2C_DocByte(byte ack);         // Đọc 1 byte (1=Gửi ACK, 0=NACK)
byte I2C_KiemTraThietBi(byte dia_chi); // Quét xem thiết bị có sống không

#endif