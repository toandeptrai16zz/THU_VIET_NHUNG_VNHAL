#ifndef VNHAL_H
#define VNHAL_H

#include "VN_Common.h"
#include "VN_GPIO.h"
#include "VN_Time.h"
#include "VN_UART.h"
#include "VN_I2C.h"
#include "VN_WDT.h"      
#include "VN_Interrupt.h" 
#include "VN_OS.h"
#include "VN_ADC.h"
#include "VN_PWM.h"

static inline void VNHAL_KhoiTao(void) {
    ThoiGian_KhoiTao();
    UART_KhoiTao(115200);
    I2C_KhoiTao(); 
}

#endif