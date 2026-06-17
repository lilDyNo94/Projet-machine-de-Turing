/*
 * File:   lib_calculs.c
 * Author: romain
 *
 * Created on 21 juin 2024, 21:44
 */


#include "lib_calculs.h"

uint8_t generate_general_reg_value(uint8_t symbol, uint8_t next_symbol, uint8_t next_move) {
    
}

void get_next_transition(machine_de_turing_desc_t *mtu) {
    switch(mtu->state) {
        case 1:
            if(mtu->symbol == RED) {
                mtu->next_symbol = GREEN;
                mtu->next_state = 2;
                mtu->next_move = LEFT;
            }
            if(mtu->symbol == GREEN) {
                mtu->next_symbol = RED;
                mtu->next_state = 2;
                mtu->next_move = LEFT;
            }
            if(mtu->symbol == LIGHT_BLUE) {
                mtu->next_symbol = LIGHT_BLUE;
                mtu->next_state = 1;
                mtu->next_move = LEFT;
            }
            break;
        case 2:
            if(mtu->symbol == RED) {
                mtu->next_symbol = RED;
                mtu->next_state = 2;
                mtu->next_move = LEFT;
            }
            if(mtu->symbol == GREEN) {
                mtu->next_symbol = GREEN;
                mtu->next_state = 2;
                mtu->next_move = LEFT;
            }
            if(mtu->symbol == LIGHT_BLUE) {
                mtu->next_symbol = LIGHT_BLUE;
                mtu->next_state = 3;
                mtu->next_move = LEFT;
            }
            break;
        case 3:
            if(mtu->symbol == RED) {
                mtu->next_symbol = GREEN;
                mtu->next_state = 3;
                mtu->next_move = LEFT;
            }
            if(mtu->symbol == GREEN) {
                mtu->next_symbol = RED;
                mtu->next_state = 4;
                mtu->next_move = RIGHT;
            }
            if(mtu->symbol == LIGHT_BLUE) {
                mtu->next_symbol = RED;
                mtu->next_state = 4;
                mtu->next_move = RIGHT;
            }
            break;
        case 4:
            if(mtu->symbol == RED) {
                mtu->next_symbol = RED;
                mtu->next_state = 4;
                mtu->next_move = RIGHT;
            }
            if(mtu->symbol == GREEN) {
                mtu->next_symbol = GREEN;
                mtu->next_state = 4;
                mtu->next_move = RIGHT;
            }
            if(mtu->symbol == LIGHT_BLUE) {
                mtu->next_symbol = LIGHT_BLUE;
                mtu->next_state = 5;
                mtu->next_move = RIGHT;
            }
            break;
        case 5:
            if(mtu->symbol == RED) {
                mtu->next_symbol = RED;
                mtu->next_state = 6;
                mtu->next_move = RIGHT;
            }
            if(mtu->symbol == GREEN) {
                mtu->next_symbol = GREEN;
                mtu->next_state = 5;
                mtu->next_move = RIGHT;
            }
            if(mtu->symbol == LIGHT_BLUE) {
                mtu->next_symbol = LIGHT_BLUE;
                mtu->next_state = 5;
                mtu->next_move = STILL;
                mtu->accept = 1;
            }
            break;
        case 6:
            if(mtu->symbol == RED) {
                mtu->next_symbol = RED;
                mtu->next_state = 6;
                mtu->next_move = RIGHT;
            }
            if(mtu->symbol == GREEN) {
                mtu->next_symbol = GREEN;
                mtu->next_state = 6;
                mtu->next_move = RIGHT;
            }
            if(mtu->symbol == LIGHT_BLUE) {
                mtu->next_symbol = LIGHT_BLUE;
                mtu->next_state = 1;
                mtu->next_move = LEFT;
            }
            break;
        default:
            error_handler();
            break;
    }
}