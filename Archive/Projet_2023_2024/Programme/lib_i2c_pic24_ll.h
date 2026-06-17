/**
 * @file    lib_i2c_pic24_ll.h 
 * @author 	Alexis ROLLAND
 * @date	2022/02
 * @brief 	Low level library for I2C / PIC24 (PIC24FJ128GA010 fully tested) - Header file
 *          V2 - 05/2024 
 */

#ifndef	__LIB_I2C_PIC24_LL_H__
#define	__LIB_I2C_PIC24_LL_H__
#include <xc.h>

#ifndef REG_ADDR_TYPE
#define REG_ADDR_TYPE
typedef uint16_t*    regAddr;       /**<    Alias to uint16_t*  */
#endif

/**
 * Defines for classical BRG Values
 */
#define KHZ100_MHZ16    157     /**<    100 kHz with Osc 32 MHz     */
#define KHZ100_MHZ8     78      /**<    100 kHz with Osc 16 MHz     */ 
#define KHZ100_MHZ4     39      /**<    100 kHz with Osc 8 MHz      */
#define KHZ400_MHZ16    37      /**<    400 kHz with Osc 32 MHz     */
#define KHZ400_MHZ8     18      /**<    400 kHz with Osc 16 MHz     */
#define KHZ400_MHZ4     9       /**<    400 kHz with Osc 8 MHz      */
#define KHZ400_MHZ2     4       /**<    400 kHz with Osc 4 MHz      */

/** 
 * Masks for I2CxCON registers
 */
#define I2CEN_MASK  (0x0001 << 15)  /**< I2CEN bit  */
#define ACKDT_MASK  (0x0001 << 5)   /**< ACKDT bit  */
#define ACKEN_MASK  (0x0001 << 4)   /**< ACKEN bit  */
#define RCEN_MASK   (0x0001 << 3)   /**< RCEN bit  */
#define PEN_MASK    (0x0001 << 2)   /**< PEN bit - Stop Condition  */
#define RSEN_MASK   (0x0001 << 1)   /**< RSEN bit - Restart Condition  */
#define SEN_MASK    (0x0001 << 0)   /**< SEN bit - Start Condition  */

/**
 * Masks for I2CxSTAT registers
 */
#define ACKSTAT_MASK    (0x0001 << 15)  /**< ACKSTAT bit    */
/** 
 * Masks for IFSx Registers
 */
#define I2C1IF_MASK (0x0001 << 1)   /**  IFS1[1]   */
#define I2C2IF_MASK (0x0001 << 2)   /**  IFS3[2]   */

/**
 * Few Macros...
 */
#define ClrIFS()    {*(pi2c->pIFSREG) &= ~pi2c->IFS_MASK;}  /**< Clears the IFS bit */
#define WaitIFS()   {while(!(*(pi2c->pIFSREG) & pi2c->IFS_MASK));}  /**< Wait for the IFS bit to be set (end of action) */

typedef enum    {   
    _I2C1,      /**< Value for I2C1 module */
    _I2C2       /**< Value for I2C2 module */
} i2c_id_t;
                
typedef enum    {   
    I2C_SET_ACK = 0,        /**< Set ACK after receiving byte */
    I2C_SET_NO_ACK = 1      /**< Set NO ACK after receiving byte */
} set_ack_t;
                    
typedef enum    {   
    I2C_OK,                 /**< Succes value                   */
    I2C_ERROR,              /**< Non Specific Error             */
    I2C_UNKNOWN_MODULE,     /**< The I2C Module ID is unknown   */
    I2C_NO_ACK,             /**< No ack received from slave     */
    I2C_BAD_ADDRESS         /**< Address is not I2C             */
 } i2c_err_t; 
                    
/** 
 * Type i2c_config_t
 */
typedef struct{ 
    uint16_t    i2cBRG_value;   /**< Only BRG value is needed to configure bitrate  */
} i2c_config_t;
                    
/** 
 * Type i2c_desc_t 
 */
typedef struct {
    i2c_id_t    i2cID;          /**< ID of the I2C Module (_I2C1 or _I2C2)  */
    regAddr     pI2CxBRG;       /**< Address of the real I2CxBRG register  */
    regAddr     pI2CxCON;       /**< Address of the real I2CxCON register  */
    regAddr     pI2CxSTAT;      /**< Address of the real I2CxSTAT register  */
    regAddr     pI2CxTRN;       /**< Address of the real I2CxTRN register  */
    regAddr     pI2CxRCV;       /**< Address of the real I2CxRCV register  */
    regAddr     pIFSREG;        /**< Address of the real IFS register */
    uint16_t    IFS_MASK;       /**< Mask for the MI2CxIF bit   */
} i2c_desc_t;            
                            
/**
 * @brief   Initializes the I2C module     
 * 
 * @param       i2c_id  ID of the target I2C module (_I2C1 or _I2C2)
 * @param[in]   pI2cCFG Address of the fully completed i2c_config_t structure
 * @param[out]  pI2c    Address of the I2c module descriptor (fully completed by the function)  
 * 
 * @return  I2C_OK  on success
 * @return  I2C_UNKNOWN_MODULE if I2C module is unknown   
 */
i2c_err_t   i2c_init(i2c_id_t i2c_id, i2c_config_t* pI2cCFG, i2c_desc_t *pI2c);
    
  /**
 * @brief       Sends NbBytes on the I2Cbus
 * 
 * @param[in]   pi2c        Address of an initialized I2C descriptor
 * @param       i2c_Addr    I2C address of the slave (7 bits)
 * @param[in]   pByte       Address of the Tx buffer 
 * @param       NbBytes     Number of Bytes to send	
 * 
 * @return      I2C_OK on success
 * @return      I2C_NO_ACK on no ack error
 * @return      I2C_UNKNOWN_MODULE if I2C module is unknown
 *  
 * @attention   7bits address must be passed 
 *
 */
i2c_err_t   i2c_write(i2c_desc_t *pi2c, uint8_t i2c_Addr,const uint8_t *pByte,uint8_t NbBytes);
 
 /**
 * @brief       Reads NbBytes on the I2Cbus
 * 
 * @param[in]   pi2c        Address of an initialized I2C descriptor
 * @param       i2c_Addr    I2C address of the slave (7 bits)
 * @param[out]  pByte       Address of the rx buffer 
 * @param       NbBytes     Number of Bytes to read
 * 
 * @return      I2C_OK on success
 * @return      I2C_NO_ACK on no ack error
 * @return      I2C_UNKNOWN_MODULE if I2C module is unknown
 *  
 * @attention   7bits address must be passed 
 *
 */
i2c_err_t   i2c_read(i2c_desc_t *pi2c, uint8_t i2c_Addr,uint8_t *pByte,uint8_t NbBytes);
 
 /**
 * @brief       Write sequence, followed by a read sequence. 
 *              Restart condition is issued between the sequences.  
 * 
 * @param[in]   pi2c        Address of an initialized I2C descriptor
 * @param       i2c_Addr    I2C address of the slave (7 bits)
 * @param[in]   pByteWR     Address of the Tx buffer 
 * @param       NbBytes2WR  Number of Bytes to Write
 * @param[out]  pByteRD     Address of the Rx buffer 
 * @param       NbBytes2RD  Number of Bytes to Read
 * 
 * @return      I2C_OK on success
 * @return      I2C_NO_ACK on no ack error  
 *  
 * @attention   7bits address must be passed 
 *
 */
 i2c_err_t  i2c_write_then_read(i2c_desc_t *pi2c, uint8_t i2c_Addr,const uint8_t *pByteWR,uint8_t NbBytes2WR,uint8_t *pByteRD,uint8_t NbBytes2RD);
 
 //-----------------------------------------------------------------------------
 // The following functions are low level functions, not intended to be used 
 // as "public" API functions.
 //-----------------------------------------------------------------------------
 
 /**
 * @brief       Reads a raw byte from the bus.
 * 
 * @param[in]   pi2c        Address of an initialized I2C descriptor
 * @param[out]  pByte       Address where to put the received byte value	
 * @param       EtatACK     ACK level to put on th line after the byte reception  
 * 
 * @return      I2C_OK 
 */
 i2c_err_t  I2C_GetByte(i2c_desc_t *pi2c, uint8_t *pByte, set_ack_t EtatACK);
 
 /**
 * @brief       Raw sending of a byte on the bus.
 * 
 * @param[in]   pi2c        Address of an initialized I2C descriptor
 * @param       Byte        Byte to send	
 * 
 * @return      I2C_OK on success
 * @return      I2C_NO_ACK on no ack error
 */
 i2c_err_t  I2C_PutByte(i2c_desc_t *pi2c, uint8_t Byte);

 //-----------------------------------------------------------------------------
 /**
 * @brief       Very Low level I2C functions, used to generate START, STOP and RESTART conditions
 * 
 * @param[in]	pi2c    Address of an initialized I2C descriptor 
 * 
 * @return      I2C_OK
 */
i2c_err_t   I2C_Start(const i2c_desc_t *pi2c);
i2c_err_t   I2C_Stop(const i2c_desc_t *pi2c);
i2c_err_t   I2C_ReStart(const i2c_desc_t *pi2c);





#endif


