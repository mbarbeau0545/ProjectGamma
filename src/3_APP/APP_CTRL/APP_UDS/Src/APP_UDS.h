/**
 * @file        .h
 * @brief       Memomry access control for DMA & user access\n.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
 #ifndef APP_UDS_H_INCLUDED
 #define APP_UDS_H_INCLUDED
 
    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "TypeCommon.h"
    #include "FMK_HAL/FMK_SRL/Src/FMK_SRL.h"
    #include "Library/CRC/CRC.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    #define APPUDS_SERIAL_LINE FMKSRL_SERIAL_LINE_2

    #define APPUDS_CRC32B_POLYNOME_USED (CRC32B_POLYNOME_ETH_ZIP_PNG)
    #define APPUDS_CRC32B_STARTVALUE    (CRC32B_STARTVALUE_ETH_ZIP_PNG)
    #define APPUDS_CRC8B_POLYNOME_USED  (CRC8B_POLYNOME_STD)
    #define APPUDS_CRC8B_STARTVALUE     (CRC8B_STARTVALUE_STD)
    // ********************************************************************
    // *                      Types
    // ********************************************************************

    //-----------------------------ENUM TYPES-----------------------------//
    /* CAUTION : Automatic generated code section for Enum: Start */

    /* CAUTION : Automatic generated code section for Enum: End */

    //-----------------------------STRUCT TYPES---------------------------//

    /* CAUTION : Automatic generated code section for Structure: Start */

    /* CAUTION : Automatic generated code section for Structure: End */

    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // ********************************************************************
    /**
     *	@brief
    *	@note   
    *
    */
    t_eReturnCode APPUDS_Init(void);
    /**
     *	@brief
    *	@note   
    *
    *
    */
    t_eReturnCode APPUDS_Cyclic(void);
    /**
    *
    *	@brief
    *	@note   
    *
    *
    *	@param[in] 
    *
    */
    t_eReturnCode APPUDS_GetState(t_eCyclicModState *f_State_pe);
    /**
    *
    *	@brief
    *	@note   
    *
    *
    *	@param[in] 
    *
    */
    t_eReturnCode APPUDS_SetState(t_eCyclicModState f_State_e);
     //********************************************************************************
     //                      Public functions - Prototyupes
     //********************************************************************************
     
 #endif // LIBRAMP_H_INCLUDED
 //************************************************************************************
 // End of File
 //************************************************************************************
 
 /**
  *	@brief
  *	@note   
  *
  *
  *	@param[in] 
  *	@param[in]
  *	 
  *
  *
  */
 