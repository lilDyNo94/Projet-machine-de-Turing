/**
 * @file    lib_i2c_pic24_ll.c
 * @author 	Alexis ROLLAND
 * @date	2022-03
 * @brief 	Low level library for I2C / PIC24 (PIC24FJ128GA010 fully tested)
 */

#include "lib_i2c_pic24_ll.h" // 

/* Directives de compilation - Macros		*/

/* Déclarations des variables globales 	*/

/*	Implémentation du code */
i2c_err_t   i2c_init(i2c_id_t i2c_id, i2c_config_t* pI2cCFG, i2c_desc_t *pI2c)
{
    uint16_t    tmpReg;
    
    switch(i2c_id){
        case _I2C1:
            pI2c->pI2CxBRG = (regAddr)&I2C1BRG;
            pI2c->pI2CxCON = (regAddr)&I2C1CON;
            pI2c->pI2CxSTAT = (regAddr)&I2C1STAT;
            pI2c->pI2CxTRN = (regAddr)&I2C1TRN;
            pI2c->pI2CxRCV = (regAddr)&I2C1RCV;
            pI2c->pIFSREG = (regAddr)&IFS1;
            pI2c->IFS_MASK = I2C1IF_MASK;
            break;
        case _I2C2:
            pI2c->pI2CxBRG = (regAddr)&I2C2BRG;
            pI2c->pI2CxCON = (regAddr)&I2C2CON;
            pI2c->pI2CxSTAT = (regAddr)&I2C2STAT;
            pI2c->pI2CxTRN = (regAddr)&I2C2TRN;
            pI2c->pI2CxRCV = (regAddr)&I2C2RCV;
            pI2c->pIFSREG = (regAddr)&IFS3;
            pI2c->IFS_MASK = I2C2IF_MASK;
            break;
        default:
            return I2C_UNKNOWN_MODULE;
            break;
    }
    
    pI2c->i2cID = i2c_id;
    
    /**
     *  I2CBRG Register
     */ 
    *(pI2c->pI2CxBRG) = pI2cCFG->i2cBRG_value;
    
    /**
     * I2CCON Register
     */
    tmpReg = 0x0000;
    tmpReg |= I2CEN_MASK;       /**<     I2CEN  */
    *(pI2c->pI2CxCON) = tmpReg;
    
    /**
     * I2CSTAT Register
     */
    tmpReg = 0x0000;
    *(pI2c->pI2CxSTAT) = tmpReg;
    
    return I2C_OK;
}
//----------------------------------------------------------------------------
i2c_err_t   i2c_write(i2c_desc_t *pi2c, uint8_t i2c_Addr,const uint8_t *pByte,uint8_t NbBytes){
    i2c_err_t   Res;
    uint8_t     i;
    
    Res = I2C_Start(pi2c);
    if (Res != I2C_OK) return Res;
    
    // Emission adresse en écriture
    Res = I2C_PutByte(pi2c, ((i2c_Addr<<1) & 0xFE));
    if (Res != I2C_OK){
        I2C_Stop(pi2c);
        return I2C_NO_ACK;
    }
    
    for (i=0;i<NbBytes;i++){
        Res = I2C_PutByte(pi2c, pByte[i]);
        if (Res != I2C_OK){
            I2C_Stop(pi2c);
            return I2C_NO_ACK;
        }
    }
    I2C_Stop(pi2c);
    return I2C_OK;
}
//----------------------------------------------------------------------------
i2c_err_t   i2c_read(i2c_desc_t *pi2c, uint8_t i2c_Addr,uint8_t *pByte,uint8_t NbBytes){
    i2c_err_t   Res;
    uint8_t     Index;
    
    Res = I2C_Start(pi2c);
    if (Res != I2C_OK) return Res;
    
    Res = I2C_PutByte(pi2c, ((i2c_Addr<<1) | 0x01));
    if (Res != I2C_OK){
        I2C_Stop(pi2c);
        return I2C_NO_ACK;
    }

    Index = 0;
    while(Index < (NbBytes - 1)){
        Res = I2C_GetByte(pi2c, &pByte[Index],I2C_SET_ACK);
        Index++;
        if (Res != I2C_OK){
            I2C_Stop(pi2c);
            return Res;  // Réception ACK ?
            }
        }
    
    Res = I2C_GetByte(pi2c,&pByte[Index],I2C_SET_NO_ACK);    // Dernier octet lu sans ACQ 
    if (Res != I2C_OK){
        I2C_Stop(pi2c);
        return Res;  // Réception ACK ?
    }

    I2C_Stop(pi2c);
    
    return I2C_OK;
}
//----------------------------------------------------------------------------
i2c_err_t  i2c_write_then_read(i2c_desc_t *pi2c, uint8_t i2c_Addr,const uint8_t *pByteWR,uint8_t NbBytes2WR,uint8_t *pByteRD,uint8_t NbBytes2RD){
    i2c_err_t   Res;    
    uint8_t     Index;

    Res = I2C_Start(pi2c);
    if (Res != I2C_OK) return Res;
    
    // Emission adresse en écriture
    Res = I2C_PutByte(pi2c, ((i2c_Addr<<1) & 0xFE));
    if (Res != I2C_OK){
        I2C_Stop(pi2c);
        return I2C_NO_ACK;
        }
    
    for (Index=0;Index<NbBytes2WR;Index++){
        Res = I2C_PutByte(pi2c, pByteWR[Index]);
        if (Res != I2C_OK){
            I2C_Stop(pi2c);
            return I2C_NO_ACK;
            }
    }
    
    I2C_ReStart(pi2c);    
    
    Res = I2C_PutByte(pi2c, ((i2c_Addr << 1) | 0x01));
    if (Res != I2C_OK){
        I2C_Stop(pi2c);
        return I2C_NO_ACK;
        }

    Index = 0;
    while(Index < (NbBytes2RD - 1)){
        Res = I2C_GetByte(pi2c, &pByteRD[Index],I2C_SET_ACK);
        Index++;
        if (Res != I2C_OK){
            I2C_Stop(pi2c);
            return Res;  // Réception ACK ?
            }
        }
    
    Res = I2C_GetByte(pi2c,&pByteRD[Index],I2C_SET_NO_ACK);    // Dernier octet lu sans ACQ (cf doc))
    if (Res != I2C_OK){
        I2C_Stop(pi2c);
        return Res;  // Réception ACK ?
        }

    I2C_Stop(pi2c);
    
    return I2C_OK;
}
//----------------------------------------------------------------------------
i2c_err_t  I2C_PutByte(i2c_desc_t *pi2c, uint8_t Byte){
    *(pi2c->pI2CxTRN) = Byte;       /**<    Chargement registre d'émission  */
     
    WaitIFS();                                              /**<     Attente fin émission   */
    if ((*(pi2c->pI2CxSTAT) & ACKSTAT_MASK) != 0){          /**<     Check ACK  */                                    
                I2C_Stop(pi2c);
                return I2C_NO_ACK;
    }
    ClrIFS();                                               /**<    Raz Flag    */
    
    return I2C_OK;
    
}
//----------------------------------------------------------------------------
i2c_err_t  I2C_GetByte(i2c_desc_t *pi2c, uint8_t *pByte, set_ack_t EtatACK){
    if (EtatACK == I2C_SET_ACK) (*(pi2c->pI2CxCON) &= ~ACKDT_MASK);     /**< Set ACK to be generated  */
    else                        (*(pi2c->pI2CxCON) |= ACKDT_MASK);      /**< Set NACK to be generated  */
    
    *(pi2c->pI2CxCON) |= RCEN_MASK;                                     /**< Start Reading  */
    WaitIFS();                                                          /**< Wait until end of reception    */
    *pByte = *(pi2c->pI2CxRCV);                                         /**< Get received byte from Rx Register */
    
    WaitIFS();                                                          /**< Wait for ? */
    ClrIFS();                                                           /**< Raz Flag   */
    
    *(pi2c->pI2CxCON) |= ACKEN_MASK;                                    /**< Start ACK/NACK generation  */
    WaitIFS();                                                          /**< Wait for complete generation   */
    ClrIFS();                                                           /**< RAZ flag   */
         
    return I2C_OK;
}
//----------------------------------------------------------------------------
i2c_err_t   I2C_Start(const i2c_desc_t *pi2c){
    *pi2c->pI2CxCON |= SEN_MASK;                    /**< Generate START condition    */
    WaitIFS();                                      /**< Wait end of START condition */
    ClrIFS();                                       /**< Clear IFS bit  */
    return I2C_OK;
}
//------------------------------------------------------------------------------        
i2c_err_t   I2C_Stop(const i2c_desc_t *pi2c){
    *pi2c->pI2CxCON |= PEN_MASK;                    /**< Generate STOP condition    */
    WaitIFS();                                      /**< Wait end of STOP condition */
    ClrIFS();                                       /**< Clear IFS bit  */
    return I2C_OK;
}
//------------------------------------------------------------------------------
i2c_err_t   I2C_ReStart(const i2c_desc_t *pi2c){
    *pi2c->pI2CxCON |= RSEN_MASK;                   /**< Generate RESTART condition    */
    WaitIFS();                                      /**< Wait end of RESTART condition */
    ClrIFS();                                       /**< Clear IFS bit  */
    return I2C_OK;
}
//------------------------------------------------------------------------------

