/*********************************************************************
 * @file        FMKHRT_ConfigPublic.h
 * @brief       High Resolution Timer Interface Mode.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      mba
 * @date        02/03/2025
 * @version     1.0
 */
  
#ifndef FMKHRT_CONFIGPUBLIC_H_INCLUDED
#define FMKHRT_CONFIGPUBLIC_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "TypeCommon.h"
    #include "FMKCPU_ConfigPublic.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    
    // ********************************************************************
    // *                      Types
    // ********************************************************************
    /**
    * @brief Frequency Range to Help User (there is also Excel)
    */
   typedef enum 
    {
        FMKHRT_CPU_64MHZ_FREQRANGE_250_15600_HZ = 0x00,     /**< Div 4 */
        FMKHRT_CPU_64MHZ_FREQRANGE_500_31200_HZ,            /**< Div 2 */
        FMKHRT_CPU_64MHZ_FREQRANGE_1000_62500_HZ,           /**< Div 1 */
        FMKHRT_CPU_64MHZ_FREQRANGE_2000_125000_HZ,          /**< Mul 2 */
        FMKHRT_CPU_64MHZ_FREQRANGE_4000_250000_HZ,          /**< Mul 4 */
        FMKHRT_CPU_64MHZ_FREQRANGE_8000_500000_HZ,          /**< Mul 8 */
        FMKHRT_CPU_64MHZ_FREQRANGE_16000_1000000_HZ,        /**< Mul 16 */
        FMKHRT_CPU_64MHZ_FREQRANGE_32000_2000000_HZ         /**< Mul 32 */
    } t_eFMKHRT_FreqRangeCpu64MHz;
    typedef enum 
    {
        FMKHRT_CPU_80MHZ_FREQRANGE_320_19500_HZ = 0x00,
        FMKHRT_CPU_80MHZ_FREQRANGE_650_39000_HZ,
        FMKHRT_CPU_80MHZ_FREQRANGE_1250_78125_HZ,
        FMKHRT_CPU_80MHZ_FREQRANGE_2500_156250_HZ,
        FMKHRT_CPU_80MHZ_FREQRANGE_5000_312500_HZ,
        FMKHRT_CPU_80MHZ_FREQRANGE_10000_625000_HZ,
        FMKHRT_CPU_80MHZ_FREQRANGE_20000_1250000_HZ,
        FMKHRT_CPU_80MHZ_FREQRANGE_40000_2500000_HZ,
    } t_eFMKHRT_FreqRangeCpu80MHz;
    typedef enum 
    {
        FMKHRT_CPU_96MHZ_FREQRANGE_400_23400_HZ = 0x00,
        FMKHRT_CPU_96MHZ_FREQRANGE_750_46800_HZ,
        FMKHRT_CPU_96MHZ_FREQRANGE_1500_93700_HZ,
        FMKHRT_CPU_96MHZ_FREQRANGE_3000_187000_HZ,
        FMKHRT_CPU_96MHZ_FREQRANGE_6000_375000_HZ,
        FMKHRT_CPU_96MHZ_FREQRANGE_12000_750000_HZ,
        FMKHRT_CPU_96MHZ_FREQRANGE_24000_1500000_HZ,
        FMKHRT_CPU_96MHZ_FREQRANGE_48000_3000000_HZ,
    } t_eFMKHRT_FreqRangeCpu96MHz;
    typedef enum 
    {
        FMKHRT_CPU_128MHZ_FREQRANGE_500_30000_HZ = 0x00,  
        FMKHRT_CPU_128MHZ_FREQRANGE_1000_60000_HZ,       
        FMKHRT_CPU_128MHZ_FREQRANGE_2000_120000_HZ,       
        FMKHRT_CPU_128MHZ_FREQRANGE_4000_250000_HZ,      
        FMKHRT_CPU_128MHZ_FREQRANGE_8000_500000_HZ,
        FMKHRT_CPU_128MHZ_FREQRANGE_16000_1000000_HZ,
        FMKHRT_CPU_128MHZ_FREQRANGE_32000_2000000_HZ,
        FMKHRT_CPU_128MHZ_FREQRANGE_64000_4000000_HZ,
    } t_eFMKHRT_FreqRangeCpu128MHz;
    typedef enum 
    {
        FMKHRT_CPU_168MHZ_FREQRANGE_660_41000_HZ = 0x00,  
        FMKHRT_CPU_168MHZ_FREQRANGE_1312_82000_HZ,       
        FMKHRT_CPU_168MHZ_FREQRANGE_2625_164000_HZ,       
        FMKHRT_CPU_168MHZ_FREQRANGE_5250_328100_HZ,      
        FMKHRT_CPU_168MHZ_FREQRANGE_10500_656200_HZ,
        FMKHRT_CPU_168MHZ_FREQRANGE_21000_1312000_HZ,
        FMKHRT_CPU_168MHZ_FREQRANGE_42000_2625000_HZ,
        FMKHRT_CPU_168MHZ_FREQRANGE_84000_5250000_HZ,
    } t_eFMKHRT_FreqRangeCpu168MHz;
    //-----------------------------ENUM TYPES-----------------------------//

    /* CAUTION : Automatic generated code section for Enum: Start */
    /**
    * @brief High Resolution Line Avaiblable on CPU.
    */
    typedef enum
    {
        FMKHRT_HR_LINE_1 = 0,                  /**< Reference to HRTIM1, Timer Slave A, Channel 1 */
        FMKHRT_HR_LINE_2,                        /**< Reference to HRTIM1, Timer Slave A, Channel 2 */
        FMKHRT_HR_LINE_3,                        /**< Reference to HRTIM1, Timer Slave B, Channel 1 */
        FMKHRT_HR_LINE_4,                        /**< Reference to HRTIM1, Timer Slave B, Channel 2 */
        FMKHRT_HR_LINE_5,                        /**< Reference to HRTIM1, Timer Slave C, Channel 1 */
        FMKHRT_HR_LINE_6,                        /**< Reference to HRTIM1, Timer Slave C, Channel 2 */
        FMKHRT_HR_LINE_7,                        /**< Reference to HRTIM1, Timer Slave D, Channel 1 */
        FMKHRT_HR_LINE_8,                        /**< Reference to HRTIM1, Timer Slave D, Channel 2 */
        FMKHRT_HR_LINE_9,                        /**< Reference to HRTIM1, Timer Slave E, Channel 1 */
        FMKHRT_HR_LINE_10,                       /**< Reference to HRTIM1, Timer Slave E, Channel 2 */
        FMKHRT_HR_LINE_11,                       /**< Reference to HRTIM1, Timer Slave F, Channel 1 */
        FMKHRT_HR_LINE_12,                       /**< Reference to HRTIM1, Timer Slave F, Channel 2 */
    
        FMKHRT_HR_LINE_NB,
    } t_eFMKHRT_HighResLine;

    /* CAUTION : Automatic generated code section for Enum: End */
  
    
    //-----------------------------TYPEDEF TYPES---------------------------//
    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // ********************************************************************

    //********************************************************************************
    //                      Public functions - Prototyupes
    //********************************************************************************

#endif // FMKHRT_CONFIGPUBLIC_H_INCLUDED           
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
