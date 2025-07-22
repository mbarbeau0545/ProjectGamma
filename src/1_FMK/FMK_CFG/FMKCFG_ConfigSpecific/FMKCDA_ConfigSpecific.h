/*********************************************************************
 * @file        FMKCDA_ConfigSpecific.h
 * @brief       Template_BriefDescription.
 * @details     TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef FMKCDA_CONFIGSPECIFIC_H_INCLUDED
#define FMKCDA_CONFIGSPECIFIC_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "../FMKCFG_ConfigFiles/FMKIO_ConfigPublic.h"
    #include "../FMKCFG_ConfigFiles/FMKTIM_ConfigPublic.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************

    // ********************************************************************
    // *                      Types
    // ********************************************************************

	//-----------------------------ENUM TYPES-----------------------------//

	//-----------------------------STRUCT TYPES---------------------------//

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
    /**
 *
 *	@brief      Function to get the bsp channel based on the value of f_channel_e.\n
 *
 *	@param[in]  f_channel_e           : enum adc channel, value from @ref t_eFMKCDA_AdcChannel
 *	@param[in]  f_bspChannel_32       : bsp adc channel uint32
 *
 *  @retval RC_OK                             @ref RC_OK
 *  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
 *  @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NULL
 *  @retval RC_ERROR_PARAM_NOT_SUPPORTED      @ref RC_ERROR_PARAM_NOT_SUPPORTED
 *
 */
t_eReturnCode FMKCDA_Get_BspChannel(t_eFMKCDA_AdcChannel f_channel_e, t_uint32 *f_bspChannel_32);
#endif // FMKCDA_CONFIGSPECIFIC_H_INCLUDED           
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
