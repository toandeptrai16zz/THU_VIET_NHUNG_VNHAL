#ifndef VN_COMMON_H
#define VN_COMMON_H

#include <stdint.h> // Thư viện chuẩn C (uint8_t, uint32_t...)

// --- KIỂU DỮ LIỆU THUẦN VIỆT ---
typedef uint8_t  byte;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64 ;
typedef uint8_t byte;

// --- HẰNG SỐ TRẠNG THÁI ---
#define VAO         0   // Input
#define RA          1   // Output
#define THAP        0   // Low
#define CAO         1   // High
#define DUNG        1   // True
#define SAI         0   // False

// --- BỘ DAO MỔ BITWISE (Macro tối ưu) ---
// inline để trình biên dịch thay thế code trực tiếp, không tốn thời gian gọi hàm
#define SET_BIT(REG, n)     ((REG) |= (1U << (n)))
#define CLEAR_BIT(REG, n)   ((REG) &= ~(1U << (n)))
#define TOGGLE_BIT(REG, n)  ((REG) ^= (1U << (n)))
#define READ_BIT(REG, n)    (((REG) >> (n)) & 1U)
#define WRITE_BIT(REG, n, val) ((val) ? SET_BIT(REG, n) : CLEAR_BIT(REG, n))

#endif