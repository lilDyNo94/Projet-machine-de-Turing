/**
 * @file    machine_de _turing_main.c
 * @author 	Romain BROUARD
 * @date	2024/05
 * @brief 	main programm of the machine de turing project
 */

#include "lib_machine_de_turing.h"

#ifndef FCY
#define FCY 400000UL
#endif

mcp23017_desc_t mcp23017_7_seg;
mcp23017_desc_t mcp23017_bp;
mcp23017_desc_t mcp23017_general;
i2c_desc_t I2CModule;
sk9822_desc_t sk9822_symbol;
sk9822_desc_t sk9822_rw_head;
machine_de_turing_desc_t *mtu;
uint8_t next_step = 1;

    
led_color_t red;
led_color_t green;
led_color_t lblue;

void Initialiser() {
    mcp23017_err_t   Res;
    mcp23017_config_t    mcpCfg;
    
    TRISB = 0x0000;
    LATB = 0;
  
    mcpCfg.pi2c = &I2CModule;
    mcpCfg.initType = INIT_WITH_I2C1;
    
    // MCP23017 7 segs
    mcpCfg.i2c_Address = MCP23017_7_SEG;
    Res = mcp23017_init(&mcp23017_7_seg,&mcpCfg);
    if (Res != MCP23017_OK) error_handler();
    
    if(mcp23017_write_reg(&mcp23017_7_seg, REG_IOCONA, 0x00) == MCP23017_ERROR) {
        error_handler();
    }
    
    // MCP23017 BP
    mcpCfg.i2c_Address = MCP23017_BP;
    Res = mcp23017_init(&mcp23017_bp,&mcpCfg);
    if (Res != MCP23017_OK) error_handler();
    if(mcp23017_write_reg(&mcp23017_bp, REG_IOCONA, 0x00) == MCP23017_ERROR) {
        error_handler();
    }
    
    // MCP23017 GENERAL
    mcpCfg.i2c_Address = MCP23017_GENERAL;
    Res = mcp23017_init(&mcp23017_general,&mcpCfg);
    if (Res != MCP23017_OK) error_handler();
    if(mcp23017_write_reg(&mcp23017_general, REG_IOCONA, 0x00) == MCP23017_ERROR) {
        error_handler();
    }
    
    red.brightness = 0xFF;
    red.blue = 0;
    red.green = 0;
    red.red = 0xFF;
    
    green.brightness = 0xFF;
    green.blue = 0;
    green.green = 0xFF;
    green.red = 0;
    
    lblue.brightness = 0xFF;
    lblue.blue = 0xE6;
    lblue.green = 0xD8;
    lblue.red = 0xAD;
    
    for(uint8_t i = 0; i<3; i++) {
        sk9822_symbol.led_strip_buff[i] = lblue;
    }
    
    for(uint8_t i = 14; i<N_LED; i++) {
        sk9822_symbol.led_strip_buff[i] = lblue;
    }
    
    sk9822_symbol.led_strip_buff[4] = red;
    sk9822_symbol.led_strip_buff[6] = red;
    sk9822_symbol.led_strip_buff[8] = red;
    sk9822_symbol.led_strip_buff[12] = red;
    sk9822_symbol.led_strip_buff[13] = red;
    sk9822_symbol.led_strip_buff[5] = green;
    sk9822_symbol.led_strip_buff[7] = green;
    sk9822_symbol.led_strip_buff[10] = green;
    sk9822_symbol.led_strip_buff[11] = green;
    
    for(uint8_t i = 0; i<N_LED; i++) {
        sk9822_rw_head.led_strip_buff[i] = lblue;
    }
    sk9822_rw_head.led_strip_buff[13] = red;
    
    mtu->accept = 0;
    mtu->state = 1;
    mtu->next_symbol = RED;
    mtu->position = 12;
}

void MainTask() {
    uint8_t working_mode;
    uint8_t segValue;
    uint8_t genValue;
    if(mcp23017_read_reg(&mcp23017_bp, REG_GPIOA, &working_mode) == MCP23017_ERROR) {
        working_mode = MANUAL_MODE;
    }
    
    while(!mtu->accept) {
        get_next_transition(mtu);
        
        segValue = int_to_bin(mtu->state);
        if(mcp23017_write_reg(&mcp23017_7_seg, REG_OLATB, segValue) == MCP23017_ERROR) {
            error_handler();
        }
        segValue = int_to_bin(mtu->next_state);
        if(mcp23017_write_reg(&mcp23017_7_seg, REG_OLATA, segValue) == MCP23017_ERROR) {
            error_handler();
        }
        
        genValue = generate_general_reg_value(mtu->symbol, mtu->next_symbol, mtu->next_move);
        if(mcp23017_write_reg(&mcp23017_7_seg, REG_OLATB, segValue) == MCP23017_ERROR) {
            error_handler();
        }
        
        sk9822_rw_head.led_strip_buff[mtu->position] = lblue;
        sk9822_rw_head.led_strip_buff[mtu->next_move] = red;
        mtu->state = mtu->next_state;
        mtu->position = mtu->next_move;
        mtu->symbol = mtu->next_symbol;
        
        if(!working_mode) {
            while(next_step);
        }
        
    }
}

void error_handler(void){
    LATBbits.LATB15 = 1;
    __delay_ms(500);
}