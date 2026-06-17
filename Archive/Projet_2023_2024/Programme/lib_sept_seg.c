/*
 * File:   lib_sept_seg.c
 * Author: romain
 *
 * Created on 6 juin 2024, 08:47
 */


#include "lib_sept_seg.h"
uint8_t int_to_bin(uint8_t sept_seg_int) {
    switch(sept_seg_int) {
        case 0:
            return 0b01111101;
        case 1:
            return 0b01001000;
        case 2:
            return 0b00111110;
        case 3:
            return 0b01101100;
        case 4:
            return 0b01001011;
        case 5:
            return 0b01100111;
        case 6:
            return 0b01110111;
        case 7:
            return 0b01001100;
        case 8:
            return 0b01111111;
        case 9:
            return 0b01101111;
        default:
            return 0;
    }
}