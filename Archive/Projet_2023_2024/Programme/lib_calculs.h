/* 
 * File:   
 * Author: romain
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef _LIB_CALCULS_H_
#define	_LIB_CALCULS_H_

#include <xc.h>

typedef struct {
    uint8_t state;
    uint8_t symbol;
    uint8_t position;
    uint8_t next_state;
    uint8_t next_symbol;
    uint8_t next_move;
    uint8_t accept;
} machine_de_turing_desc_t;

uint8_t generate_general_reg_value(uint8_t symbol, uint8_t next_symbol, uint8_t next_move);
void get_next_transition(machine_de_turing_desc_t *mtu);

#endif	// _LIB_CALCULS_H_

