/*********************************************************************
 * @file        APPSPM.c
 * @brief       System Paramters Managment.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  





// ********************************************************************
// *                      Includes
// ********************************************************************
#include "./APP_SPM.h"
#ifdef APPSYS_MODULE_APP_SPM_ENABLE
#include "APP_CFG/ConfigFiles/APPSPM_ConfigPrivate.h"
// ********************************************************************
// *                      Defines
// ********************************************************************

// ********************************************************************
// *                      Types
// ********************************************************************
enum
{
    APPSPM_PRMSTATE_BIT_NO_OPE = 0,
};
/* CAUTION : Automatic generated code section for Enum: Start */

/* CAUTION : Automatic generated code section for Enum: End */
//-----------------------------ENUM TYPES-----------------------------//


/* CAUTION : Automatic generated code section for Structure: Start */

/* CAUTION : Automatic generated code section for Structure: End */
//-----------------------------STRUCT TYPES---------------------------//
typedef struct 
{
    t_uint8 status_u8;
    t_uint16 value_u16;
    t_sAPPSPM_ItemPrmCfg * rawInfo_ps;
} t_sAPPSPM_ItemPrmInfo;
/* CAUTION : Automatic generated code section : Start */

/* CAUTION : Automatic generated code section : End */
//-----------------------------TYPEDEF TYPES---------------------------//
// ********************************************************************
// *                      Prototypes
// ********************************************************************
	
// ********************************************************************
// *                      Variables
// ********************************************************************
/**
 * @brief Container for Parameter Information 
 */
static t_sAPPSPM_ItemPrmInfo g_ItemPrmInfo_as[APPSPM_PRM_NB];
/**
 * @brief Container for Module State Machine
 */
static t_eCyclicModState g_APPSM_ModState_e = STATE_CYCLIC_CFG;
//********************************************************************************
//                      Local functions - Prototypes
//********************************************************************************
/**
 *
 *	@brief      Perform preOperationnal action.\n
 *  @note       Call driver init function.\n
 *              Set the actuator configuration (5 per cycle).\n
 *              If one of the configuration is not set the Module Cyclic 
 *              retry indefinitely.\n
 *              
 * 
 *  @retval RC_OK                             @ref RC_OK
 *  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
 *  @retval RC_ERROR_WRONG_STATE              @ref RC_ERROR_WRONG_STATE

 */
static t_eReturnCode s_APPSM_ConfigurationState(void);
/**
*
*	@brief  Call driver cyclic function
*
*/
static t_eReturnCode s_APPSM_Operational(void);
//****************************************************************************
//                      Public functions - Implementation
//********************************************************************************
/*********************************
 * APPSPM_Init
 *********************************/
t_eReturnCode APPSPM_Init(void)
{
    t_uint8 idxPrm_u8;

    for(idxPrm_u8 = (t_uint8)0 ; idxPrm_u8 < APPSPM_PRM_NB ; idxPrm_u8++)
    {
        SETBIT_8B(g_ItemPrmInfo_as[idxPrm_u8].status_u8, APPSPM_PRMSTATE_BIT_NO_OPE);
        g_ItemPrmInfo_as[idxPrm_u8].value_u16 = (t_uint16)0;
        g_ItemPrmInfo_as[idxPrm_u8].rawInfo_ps = (t_sAPPSPM_ItemPrmCfg *)(&c_AppSpm_ItemPrmInfo_as[idxPrm_u8]);
    }
    return RC_OK;
}

/*********************************
 * APPSPM_Cyclic
 *********************************/
t_eReturnCode APPSPM_Cyclic(void)
{
    t_eReturnCode Ret_e = RC_OK;

    switch (g_APPSM_ModState_e)
    {
    case STATE_CYCLIC_CFG:
    {
        Ret_e = s_APPSM_ConfigurationState();
        if(Ret_e == RC_OK)
        {
            g_APPSM_ModState_e = STATE_CYCLIC_WAITING;
        }   
        break;
    }
    case STATE_CYCLIC_WAITING:
    {
        // nothing to do, just wait all module are Ope
        break;
    }
    case STATE_CYCLIC_PREOPE:
    {
        g_APPSM_ModState_e = STATE_CYCLIC_OPE;
        // nothing to do, just wait all module are Ope
        break;
    }
    case STATE_CYCLIC_OPE:
    {
        Ret_e = s_APPSM_Operational();
        break;
    }
    case STATE_CYCLIC_ERROR:
    {
        break;
    }
    case STATE_CYCLIC_BUSY:
    default:
        Ret_e = RC_OK;
        break;
    }
    return Ret_e;
}

/*********************************
 * APPSPM_GetState
 *********************************/
t_eReturnCode APPSPM_GetState(t_eCyclicModState *f_State_pe)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_State_pe == (t_eCyclicModState *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        *f_State_pe = g_APPSM_ModState_e;
    }
    return Ret_e;
}

/*********************************
 * APPSPM_SetState
 *********************************/
t_eReturnCode APPSPM_SetState(t_eCyclicModState f_State_e)
{
    g_APPSM_ModState_e = f_State_e;
    return RC_OK;
}
//********************************************************************************
//                      Local functions - Implementation
//********************************************************************************
/*********************************
 * s_APPSM_ConfigurationState
 *********************************/
static t_eReturnCode s_APPSM_ConfigurationState(void)
{
    t_uint8 idxParm_u8;

    //---- for now, no EEPROM so we take the default value instead ----//
    for(idxParm_u8 = (t_uint8)0 ; idxParm_u8 < APPSPM_PRM_NB ; idxParm_u8++)
    {
        g_ItemPrmInfo_as[idxParm_u8].value_u16 = g_ItemPrmInfo_as[idxParm_u8].rawInfo_ps->DefaultItemVal_u16;
    }
    
    return RC_OK;
}      

/*********************************
 * s_APPSM_Operational
 *********************************/
static t_eReturnCode s_APPSM_Operational(void)
{
    return RC_OK;
}

/*********************************
 * APPSPM_GetParam
 *********************************/
t_eReturnCode APPSPM_GetParam(t_eAPPSPM_ItemPrm f_itemId_e, t_uint16 * f_prmValue_pu16)
{
    t_eReturnCode Ret_e;

    if(f_itemId_e > APPSPM_PRM_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    else if(f_prmValue_pu16 == (t_uint16 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else if(g_APPSM_ModState_e != STATE_CYCLIC_OPE)
    {
        Ret_e = RC_WARNING_BUSY;
    }
    else 
    {
        *f_prmValue_pu16 = g_ItemPrmInfo_as[f_itemId_e].value_u16;
        Ret_e = RC_OK;
    }

    return Ret_e;
}

/*********************************
 * APPSPM_SetParam
 *********************************/
t_eReturnCode APPSPM_SetParam(t_eAPPSPM_ItemPrm f_itemId_e, t_uint16 f_prmValue_u16)
{
    t_eReturnCode Ret_e;
    t_sAPPSPM_ItemPrmInfo * itemPrmInfo_ps;

    if(f_itemId_e > APPSPM_PRM_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    else if(g_APPSM_ModState_e != STATE_CYCLIC_OPE)
    {
        Ret_e = RC_WARNING_BUSY;
    }
    else 
    {
        itemPrmInfo_ps = (t_sAPPSPM_ItemPrmInfo *)(&g_ItemPrmInfo_as[f_itemId_e]);

        if((f_prmValue_u16 > itemPrmInfo_ps->rawInfo_ps->minItemVal_u16)
        && (f_prmValue_u16 < itemPrmInfo_ps->rawInfo_ps->maxItemVal_u16))
        {
            itemPrmInfo_ps->value_u16 = f_prmValue_u16;
            Ret_e = RC_OK;
        }
        else 
        {
            Ret_e = RC_ERROR_PARAM_INVALID;
        }
    }

    return Ret_e;
}

/*********************************
 * APPSPM_GetParam
 *********************************/
t_eReturnCode APPSPM_GetParamInfo(	t_eAPPSPM_ItemPrm f_itemId_e, 
                                    t_uint16 * f_prmMinValue_pu16,
                                    t_uint16 * f_prmMaxValue_pu16,
                                    t_uint16 * f_prmDefaultValue_pu16)
{
    t_eReturnCode Ret_e;
    t_sAPPSPM_ItemPrmInfo * itemPrmInfo_ps;

    if(f_itemId_e > APPSPM_PRM_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    else if(    (f_prmMinValue_pu16 == (t_uint16 *)NULL)
            ||  (f_prmMaxValue_pu16 == (t_uint16 *)NULL)
            ||  (f_prmDefaultValue_pu16 == (t_uint16 *)NULL))
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else if(g_APPSM_ModState_e != STATE_CYCLIC_OPE)
    {
        Ret_e = RC_WARNING_BUSY;
    }
    else 
    {
        itemPrmInfo_ps = (t_sAPPSPM_ItemPrmInfo *)(&g_ItemPrmInfo_as[f_itemId_e]);

        *f_prmDefaultValue_pu16 = itemPrmInfo_ps->rawInfo_ps->DefaultItemVal_u16;
        *f_prmMaxValue_pu16 = itemPrmInfo_ps->rawInfo_ps->maxItemVal_u16;
        *f_prmMinValue_pu16 = itemPrmInfo_ps->rawInfo_ps->minItemVal_u16;
        Ret_e = RC_OK;
    }

    return Ret_e;
}

#endif // APPSYS_MODULE_APP_SPM_ENABLE
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
