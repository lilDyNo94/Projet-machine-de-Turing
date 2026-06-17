/**
 * @file 
 * @author 	
 * @date	
 * @brief 	
 */
#include "lib_mcp23017.h"

uint8_t     TxBuffer[BUF_SIZE];
uint8_t     RxBuffer[BUF_SIZE];

mcp23017_err_t mcp23017_init (mcp23017_desc_t *pMPC23017, const mcp23017_config_t *pMPC23017config){
    i2c_config_t i2cCfg;
    i2c_err_t   Res;
    
    if(pMPC23017config->initType != INIT_ALREADY_DONE) {
        switch(pMPC23017config->initType){
            case INIT_WITH_I2C1:
                i2c_init(_I2C1, &i2cCfg, pMPC23017config->pi2c);
                break;
            case INIT_WITH_I2C2:
                i2c_init(_I2C2, &i2cCfg, pMPC23017config->pi2c);
                break;
            default: break;
            }
    }
    pMPC23017->pi2c = pMPC23017config->pi2c;
    pMPC23017->i2c_Address = pMPC23017config->i2c_Address;
    
    //TODO les registres
    
    return MCP23017_OK;
}

mcp23017_err_t mcp23017_write_reg(const mcp23017_desc_t *pMCP23017,uint8_t RegAddr, uint8_t RegValue){
    mcp23017_err_t   Res;
    TxBuffer[0] = RegAddr;   // Clear all auto-increment features
    TxBuffer[1] = RegValue;
     
    Res = i2c_write(pMCP23017->pi2c, pMCP23017->i2c_Address,TxBuffer,2);
    if (Res != I2C_OK) return MCP23017_ERROR;
    
    return MCP23017_OK;
}
//------------------------------------------------------------------------------        
mcp23017_err_t mcp230173_read_reg(const mcp23017_desc_t *pMCP23017,uint8_t RegAddr, uint8_t *pRegValue){
    i2c_err_t   Res;
    TxBuffer[0] = RegAddr & 0x0F;   // Clear all auto-increment features
    
    Res = i2c_write_then_read(pMCP23017->pi2c, pMCP23017->i2c_Address, TxBuffer, 1, pRegValue,1);
    if (Res != I2C_OK) return MCP23017_ERROR;
        
    return MCP23017_OK;
}