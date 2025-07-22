/*********************************************************************
 * @file        item.h
 * @brief       Template_BriefDescription.
 * @details     TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */






// ********************************************************************
// *                      Includes
// ********************************************************************
#include "./CRC.h"
// ********************************************************************
// *                      Defines
// ********************************************************************

// ********************************************************************
// *                      Types
// ********************************************************************
/* CAUTION : Automatic generated code section for Enum: Start */

/* CAUTION : Automatic generated code section for Enum: End */
//-----------------------------ENUM TYPES-----------------------------//


/* CAUTION : Automatic generated code section for Structure: Start */

/* CAUTION : Automatic generated code section for Structure: End */
//-----------------------------STRUCT TYPES---------------------------//
/* CAUTION : Automatic generated code section : Start */

/* CAUTION : Automatic generated code section : End */
//-----------------------------TYPEDEF TYPES---------------------------//
// ********************************************************************
// *                      Prototypes
// ********************************************************************
	
// ********************************************************************
// *                      Variables
// ********************************************************************

//********************************************************************************
//                      Local functions - Prototypes
//********************************************************************************

//****************************************************************************
//                      Public functions - Implementation
//********************************************************************************
t_eReturnCode LIBCRC_ComputeCrc8Bits(  const t_uint8 * f_data_pu8,
                                    t_uint16 f_sizeData_u16,
                                    t_uint8 f_polynomial_u8,
                                    t_uint8 f_initVal_u8,
                                    t_uint8 * f_crcCompute_pu8)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 crcCompute_u8 = f_initVal_u8;
    t_uint8 LLI_u8;
    const t_uint8 * dataVal_pu8;

    if((f_data_pu8 == (t_uint8 *)NULL)
    || f_crcCompute_pu8 == (t_uint8 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        dataVal_pu8 = (const t_uint8 *)f_data_pu8;
        while(f_sizeData_u16--)
        {
            crcCompute_u8 ^= (*dataVal_pu8++);

            for(LLI_u8 = (t_uint8)0 ;LLI_u8 < 8 ; LLI_u8++)
            {
                crcCompute_u8 = (crcCompute_u8 & 0x80) ? 
                        (crcCompute_u8 << 1) ^ f_polynomial_u8 : (crcCompute_u8 << 1);
            }
        }
        *f_crcCompute_pu8 = (t_uint8)crcCompute_u8;
    }   

    return Ret_e;
}

t_eReturnCode LIBCRC_ComputeCrc16Bits( const t_uint8 * f_data_pu8,
                                        t_uint16 f_sizeData_u16,
                                        t_uint16 f_polynomial_u16,
                                        t_uint16 f_initVal_u16,
                                        t_uint16 * f_crcCompute_pu16)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint16 crcCompute_u16 = f_initVal_u16;
    t_uint8 LLI_u8;
    const t_uint8 * dataVal_pu8;

    if((f_data_pu8 == (t_uint8 *)NULL) 
    || (f_crcCompute_pu16 == (t_uint16 *)NULL))
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        dataVal_pu8 = f_data_pu8;
        while(f_sizeData_u16--)
        {
            // Intégrer le prochain octet dans les 8 bits de poids fort
            crcCompute_u16 ^= ((t_uint16)(*dataVal_pu8++)) << 8;
            for(LLI_u8 = 0; LLI_u8 < 8; LLI_u8++)
            {
                crcCompute_u16 = (crcCompute_u16 & 0x8000) ?
                                  (crcCompute_u16 << 1) ^ f_polynomial_u16 :
                                  (crcCompute_u16 << 1);
            }
        }
        *f_crcCompute_pu16 = (t_uint16)crcCompute_u16;
    }

    return Ret_e;
}

t_eReturnCode LIBCRC_ComputeCrc32Bits( const t_uint8 * f_data_pu8,
                                    t_uint16 f_sizeData_u16,
                                    t_uint32 f_polynomial_u32,
                                    t_uint32 f_initVal_u32,
                                    t_uint32 * f_crcCompute_pu32)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint32 crcCompute_u32 = f_initVal_u32;
    t_uint8 LLI_u8;
    const t_uint8 * dataVal_pu8;

    if((f_data_pu8 == (t_uint8 *)NULL) || (f_crcCompute_pu32 == (t_uint32 *)NULL))
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        dataVal_pu8 = f_data_pu8;
        while(f_sizeData_u16--)
        {
            crcCompute_u32 ^= ((t_uint32)(*dataVal_pu8++));
            for(LLI_u8 = 0; LLI_u8 < 8; LLI_u8++)
            {
                crcCompute_u32 = (crcCompute_u32 & 1) ?
                                  (crcCompute_u32 >> 1) ^ f_polynomial_u32 :
                                  (crcCompute_u32 >> 1);
            }
        }
        *f_crcCompute_pu32 = ~crcCompute_u32; // Inversion finale du CRC pour obtenir la valeur correcte
    }

    return Ret_e;
}
//********************************************************************************
//                      Local functions - Implementation
//********************************************************************************
           
//************************************************************************************
// End of File
//************************************************************************************

/**
 *
 *	@brief
 *	@note
 *
 *
 *	@param[in] 
 *	@param[out]
 *	 
 *
 *
 */
