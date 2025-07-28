/*********************************************************************
 * @file        FMKCDA_ConfigSpecific.h
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
#include "./FMKCDA_ConfigSpecific.h"
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
//                      Local functions - Prototypes
//********************************************************************************

//****************************************************************************
//                      Public functions - Implementation
//********************************************************************************
/*********************************
 * FMKCDA_Get_BspChannel
 *********************************/
t_eReturnCode FMKCDA_Get_BspChannel(t_eFMKCDA_Adc f_Adc_e,
                                    t_eFMKCDA_AdcChannel f_channel_e, 
                                    t_uint32 *f_bspChannel_32)
{
    t_eReturnCode Ret_e = RC_OK;

    if (f_channel_e >= FMKCDA_ADC_CHANNEL_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if (f_bspChannel_32 == (t_uint32 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if (Ret_e == RC_OK)
    {
        switch (f_channel_e)
        {
            /* CAUTION : Automatic generated code section for switch_case ADC channel: Start */
            case FMKCDA_ADC_CHANNEL_0:
                *f_bspChannel_32 = ADC_CHANNEL_0;
                break;
            case FMKCDA_ADC_CHANNEL_1:
                *f_bspChannel_32 = ADC_CHANNEL_1;
                break;
            case FMKCDA_ADC_CHANNEL_2:
                *f_bspChannel_32 = ADC_CHANNEL_2;
                break;
            case FMKCDA_ADC_CHANNEL_3:
                *f_bspChannel_32 = ADC_CHANNEL_3;
                break;
            case FMKCDA_ADC_CHANNEL_4:
                *f_bspChannel_32 = ADC_CHANNEL_4;
                break;
            case FMKCDA_ADC_CHANNEL_5:
                *f_bspChannel_32 = ADC_CHANNEL_5;
                break;
            case FMKCDA_ADC_CHANNEL_6:
                *f_bspChannel_32 = ADC_CHANNEL_6;
                break;
            case FMKCDA_ADC_CHANNEL_7:
                *f_bspChannel_32 = ADC_CHANNEL_7;
                break;
            case FMKCDA_ADC_CHANNEL_8:
                *f_bspChannel_32 = ADC_CHANNEL_8;
                break;
            case FMKCDA_ADC_CHANNEL_9:
                *f_bspChannel_32 = ADC_CHANNEL_9;
                break;
            case FMKCDA_ADC_CHANNEL_10:
                *f_bspChannel_32 = ADC_CHANNEL_10;
                break;
            case FMKCDA_ADC_CHANNEL_11:
                *f_bspChannel_32 = ADC_CHANNEL_11;
                break;
            case FMKCDA_ADC_CHANNEL_12:
                *f_bspChannel_32 = ADC_CHANNEL_12;
                break;
            case FMKCDA_ADC_CHANNEL_13:
                *f_bspChannel_32 = ADC_CHANNEL_13;
                break;
            case FMKCDA_ADC_CHANNEL_14:
                *f_bspChannel_32 = ADC_CHANNEL_14;
                break;
            case FMKCDA_ADC_CHANNEL_15:
                *f_bspChannel_32 = ADC_CHANNEL_15;
                break;
            case FMKCDA_ADC_CHANNEL_16:
                *f_bspChannel_32 = ADC_CHANNEL_16;
                break;
            case FMKCDA_ADC_CHANNEL_17:
                *f_bspChannel_32 = ADC_CHANNEL_17;
                break;
            case FMKCDA_ADC_CHANNEL_18:
                *f_bspChannel_32 = ADC_CHANNEL_18;
                break;
            /* CAUTION : Automatic generated code section for switch_case ADC channel: End */
            case FMKCDA_ADC_CHANNEL_NB:
            default:
                Ret_e = RC_ERROR_PARAM_NOT_SUPPORTED;
        }
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
