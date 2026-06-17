/**
 * @file    
 * @author 	
 * @date	
 * @brief 	
 */

#ifndef	__LIB_MCP23017_H__
#define	__LIB_MCP23017_H__
#include <xc.h>

#include "lib_i2c_pic24_ll.h"

// Default I2C address (for 8 pins devices)
#define MCP23017_7_SEG   0b0100001
#define MCP23017_BP      0b0100010
#define MCP23017_GENERAL 0b0100011

// internal regs
#define REG_IOCONA   0x0A
#define REG_IOCONB   0x0B
#define REG_GPIOA    0x12
#define REG_GPIOB    0x13
#define REG_OLATA    0x14
#define REG_OLATB    0x15
/*
 Masks and reg values
 */

typedef enum    {   
    MCP23017_OK,     /**< Success Value          */
    MCP23017_ERROR,  /**< Non specific error     */
} mcp23017_err_t;
                    
typedef enum    {   
    INIT_WITH_I2C1,     /**< Initialize the PCA9633 and I2C1 module    */
    INIT_WITH_I2C2,     /**< Initialize the PCA9633 and I2C2 module    */
    INIT_ALREADY_DONE   /**< Initialize the PCA9633 but don't touch I2C module config */
} mcp23017_i2c_init_type_t;

#define BUF_SIZE    16  // Max I2C (Tx/Rx) buffer size                    

typedef struct {
    i2c_desc_t  *pi2c;                      /**< I2C descriptor initialized or not    */
    mcp23017_i2c_init_type_t    initType;   /**< Initializing scheme (with I2C1, with I2C2 or init already done) */
    uint8_t i2c_Address;                    /**< I2C (7bits) Adrress of the PCA9633 device          */
} mcp23017_config_t;                    

typedef struct  {
    i2c_desc_t  *pi2c;          /**< Fully intialized I2C descriptor    */
    uint8_t     i2c_Address;    /**< Real (7 bits) address of the used PCA9633  */
} mcp23017_desc_t; 
   
/**
 * @brief       Initializes the PCA9633 device descriptor
 *              Init state is osc PCA9633 Powered on, no SUB or ALL calls, 
 *              Dimming group control, Output logic state not inverted, 
 *              output drivers are open drain.
 *              LED driver x individual brightness can be controlled through 
 *              its PWMx register.
 * 
 * @param[out]  pPca9633        Address of the PCA9633 device descriptor
 * @param[in]   pPca9633CFG     Address of the PCA9633 init structure	
 * 
 * @return      PCA9633_OK on success
 * @return      PCA9633_ERROR on error
 */
 mcp23017_err_t mcp23017_init (mcp23017_desc_t *pMPC23017, const mcp23017_config_t *pMPC23017config);
 
 //-----------------------------------------------------------------------------
 //-----------------------------------------------------------------------------
 
 /**
  * Low level functions - Not part of the API 
  */
  
/**
 * @brief       Writes a byte into a PCA9633 register   
 * 
 * @param[in]   pPca9633        Address of the PCA9633 device descriptor
 * @param       RegAddr         Address of the PCA9633 target register
 * @param       RegValue        Value of the byte to be written in the target register
 * 
 * @return      PCA9633_OK on success
 * @return      PCA9633_ERROR on error 
 * 
 * @Attention Low Level Function - Should not be used by app 
 *
 */
 mcp23017_err_t mcp23017_write_reg(const mcp23017_desc_t *pMPC23017,uint8_t RegAddr, uint8_t RegValue);
 
 /**
 * @brief       Reads a byte from a PCA9633 register   
 * 
 * @param[in]   pPca9633        Address of the PCA9633 device descriptor
 * @param       RegAddr         Address of the PCA9633 target register
 * @param[out]  pRegValue       Address of the byte receiving the register value
 * 
 * @return      PCA9633_OK on success
 * @return      PCA9633_ERROR on error 
 * 
 * @Attention Low Level Function - Should not be used by app 
 *
 */
 mcp23017_err_t mcp23017_read_reg(const mcp23017_desc_t *pMPC23017,uint8_t RegAddr, uint8_t *pRegValue);
 
#endif //__LIB_MPC23017_H__