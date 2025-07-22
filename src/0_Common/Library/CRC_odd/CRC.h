/*********************************************************************
 * @file        CRC.h
 * @brief       Compute CRC Number
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
 #ifndef CRC_H_INCLUDED 
 #define CRC_H_INCLUDED 
 
 
 
 
 
    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "TypeCommon.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    #define CRC8B_POLYNOME_STD            ((t_uint8)0x07)     // x⁸ + x⁴ + x³ + x² + 1
    #define CRC8B_POLYNOME_ANSI           ((t_uint8)0x1D)     // x⁸ + x⁷ + x⁶ + x³ + x² + x + 1
    #define CRC8B_POLYNOME_ITU            ((t_uint8)0x83)     // x⁸ + x⁷ + x + 1

    #define CRC16B_POLYNOME_STD           ((t_uint16)0x8005)     // x¹⁶ + x¹⁵ + x² + 1
    #define CRC16B_POLYNOME_ANSI          ((t_uint16)0x11021)    // x¹⁶ + x¹² + x⁵ + 1
    #define CRC16B_POLYNOME_ITU           ((t_uint16)0x1021)     // x¹⁶ + x¹² + x⁵ + 1

    #define CRC32B_POLYNOME_ETH_ZIP_PNG   ((t_uint32)0xEDB88320) // reverse x³² + x²⁶ + x²³ + x²² + x¹⁶ + x¹² + x¹¹ + x¹⁰ + x⁸ + x⁷ + x⁵ + x⁴ + x² + x + 1
    #define CRC32B_POLYNOME_CASTAGNOLI    ((t_uint32)0x1EDC6F41) // x³² + x²⁸ + x²⁷ + x²⁶ + x²⁵ + x²³ + x²² + x²¹ + x²⁰ + x¹⁹ + x¹⁸ + x¹⁴ + x¹³ + x¹¹ + x¹⁰ + x⁹ + x⁸ + x⁷ + x⁵ + x⁴ + x² + x  + 1
    #define CRC32B_POLYNOME_KOOPMAN       ((t_uint32)0x741B8CD7) // x³² + x³¹ + x²⁹ + x²⁸ + x²⁷ + x²⁵ + x²³ + x²² + x²¹ + x¹⁹ + x¹⁷ + x¹⁶ + x¹⁵ + x¹³ + x¹² + x¹⁰ + x⁸ + x⁷ + x⁴ + x² + x + 1

    #define CRC8B_STARTVALUE_STD          ((t_uint8)0xFF)     
    #define CRC8B_STARTVALUE_ANSI         ((t_uint8)0xFF)     
    #define CRC8B_STARTVALUE_ITU          ((t_uint8)0xFF)     

    #define CRC16B_STARTVALUE_STD         ((t_uint16)0xFFFF)     
    #define CRC16B_STARTVALUE_ANSI        ((t_uint16)0xFFFF)    
    #define CRC16BSTARTVALUE_ITU          ((t_uint16)0xFFFF)     

    #define CRC32B_STARTVALUE_ETH_ZIP_PNG ((t_uint32)0xFFFFFFFF) 
    #define CRC32B_STARTVALUE_CASTAGNOLI  ((t_uint32)0xFFFFFFFF) 
    #define CRC32B_STARTVALUE_KOOPMAN     ((t_uint32)0xFFFFFFFF) 
    // ********************************************************************
    // *                      Types
    // ********************************************************************

    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // ********************************************************************


    //********************************************************************************
    //                      Public functions - Prototyupes
    //********************************************************************************
    /**
    *
    *	@brief
    *	@note   
    *
    *
    *	@param[in] 
    *
    */
    t_eReturnCode LIBCRC_ComputeCrc8Bits(  const t_uint8 * f_data_pu8,
                                        t_uint16 f_sizeData_u16,
                                        t_uint8 f_polynomial_u8,
                                        t_uint8 f_initVal_u8,
                                        t_uint8 * f_crcCompute_pu8);
    /**
    *
    *	@brief
    *	@note   
    *
    *
    *	@param[in] 
    *
    */
    t_eReturnCode LIBCRC_ComputeCrc16Bits( const t_uint8 * f_data_pu8,
                                        t_uint16 f_sizeData_u16,
                                        t_uint16 f_polynomial_u16,
                                        t_uint16 f_initVal_u16,
                                        t_uint16 * f_crcCompute_pu16);
    /**
    *
    *	@brief
    *	@note   
    *
    *
    *	@param[in] 
    *
    */
    t_eReturnCode LIBCRC_ComputeCrc32Bits( const t_uint8 * f_data_pu8,
                                        t_uint16 f_sizeData_u16,
                                        t_uint32 f_polynomial_u32,
                                        t_uint32 f_initVal_u32,
                                        t_uint32 * f_crcCompute_pu32);
 #endif // FILE_CONFIGPRIVATE_H_INCLUDED           
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
 