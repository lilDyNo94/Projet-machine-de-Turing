/**
 * @file    lib_i2c_pic24_ll.h 
 * @author 	Alexis ROLLAND
 * @date	2022/02
 * @brief 	Low level library for I2C / PIC24 (PIC24FJ128GA010 fully tested) - Header file
 *          V2 - 05/2024 
 */

#ifndef	__LIB_MACHINE_DE_TURING_H__
#define	__LIB_MACHINE_DE_TURING_H__

#include <xc.h>
#include <p24FJ64GA002.h>

#include "lib_i2c_pic24_ll.h"
#include "lib_mcp23017.h"
#include "lib_calculs.h"
#include "lib_sept_seg.h"
#include "lib_sk9822.h"

typedef enum {
    MANUAL_MODE,
    AUTOMATIC_MODE
} working_mode_t;

typedef enum {
    RED,
    GREEN,
    LIGHT_BLUE,
    YELLOW,
    PURPLE,
    DARK_BLUE,
    ORANGE
} mtu_colors_t;

typedef enum {
    LEFT,
    RIGHT,
    STILL
} mtu_move_t;

void Initialiser();
void MainTask();
void error_handler();
void valid(void);
#endif //__LIB_MACHINE_DE_TURING_H__