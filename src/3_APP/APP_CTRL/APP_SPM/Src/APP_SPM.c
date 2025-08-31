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
#include "APP_CTRL/APP_SYS/Src/APP_SYS.h"
#ifdef APPSYS_MODULE_APP_SPM_ENABLE
#include "./APP_SPM.h"
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
    t_uAPPSPM_PrmValType value_u;
    t_sAPPSPM_ItemPrmCfg * prmCfg_ps;
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

///@brief flag to know the parameter are load
static t_bool g_FlagParamInit_b = FALSE;
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
/**
*
*	@brief  Call driver cyclic function
*
*/
static void s_APPSPM_AppSigMsgRcvCallback(t_eAPPSIG_Signal f_prmSignal_e, t_float32 f_value_f32);
/**
*
*	@brief  Call driver cyclic function
*
*/
static t_eReturnCode s_APPSPM_EncodePrmValue(   t_sAPPSPM_ItemPrmInfo * f_prmInfo_ps, 
                                                void * f_value_pv);
/**
*
*	@brief  Call driver cyclic function
*
*/
static t_eReturnCode s_APPSPM_GetVoidFromFloat32(t_float32 f_prmvalue_f32,
                                                 t_eAPPSPM_PrmType f_prmType_e,
                                                 void * f_value_pv);
//****************************************************************************
//                      Public functions - Implementation
//********************************************************************************
/*********************************
 * APPSPM_Init
 *********************************/
t_eReturnCode APPSPM_Init(void)
{
    t_uint16 idxPrm_u16;

    for(idxPrm_u16 = (t_uint8)0 ; idxPrm_u16 < APPSPM_PRM_NB ; idxPrm_u16++)
    {
        SETBIT_8B(g_ItemPrmInfo_as[idxPrm_u16].status_u8, APPSPM_PRMSTATE_BIT_NO_OPE);
        g_ItemPrmInfo_as[idxPrm_u16].value_u.prmVal_u32 = (t_uint32)0;
        g_ItemPrmInfo_as[idxPrm_u16].prmCfg_ps = (t_sAPPSPM_ItemPrmCfg *)(&c_AppSpm_ItemPrmInfo_as[idxPrm_u16]);
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

/*********************************
 * APPSPM_GetParam
 *********************************/
t_eReturnCode APPSPM_GetParam(t_eAPPSPM_ItemPrm f_itemId_e, t_uAPPSPM_PrmValType * f_prmValue_pu)
{
    t_eReturnCode Ret_e;

    if(f_itemId_e > APPSPM_PRM_NB)
    {
        ASSERT((t_uint16)0);
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    else if(f_prmValue_pu == NULL)
    {
        ASSERT((t_uint16)0);
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else if(g_FlagParamInit_b == FALSE)
    {
        Ret_e = RC_WARNING_BUSY;
    }
    else 
    {
        *f_prmValue_pu = g_ItemPrmInfo_as[f_itemId_e].value_u;
        Ret_e = RC_OK;
    }

    return Ret_e;
}

/*********************************
 * APPSPM_SetParam
 *********************************/
t_eReturnCode APPSPM_SetParam(t_eAPPSPM_ItemPrm f_itemId_e, t_uAPPSPM_PrmValType f_prmVal_u)
{
    t_eReturnCode Ret_e;
    t_sAPPSPM_ItemPrmInfo * itemPrmInfo_ps;

    if(f_itemId_e > APPSPM_PRM_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    else if(g_FlagParamInit_b == FALSE)
    {
        Ret_e = RC_WARNING_BUSY;
    }
    else 
    {
        itemPrmInfo_ps = (t_sAPPSPM_ItemPrmInfo *)(&g_ItemPrmInfo_as[f_itemId_e]);

        Ret_e = s_APPSPM_EncodePrmValue(itemPrmInfo_ps,
                                        (void *)(&f_prmVal_u));
    }

    return Ret_e;
}

/*********************************
 * APPSPM_GetParam
 *********************************/
t_eReturnCode APPSPM_GetParamInfo(	t_eAPPSPM_ItemPrm f_itemId_e, 
                                    t_float32 * f_prmMinValue_pf32,
                                    t_float32 * f_prmMaxValue_pf32,
                                    t_float32 * f_prmDefaultValue_pf32)
{
    t_eReturnCode Ret_e;
    t_sAPPSPM_ItemPrmInfo * itemPrmInfo_ps;

    if(f_itemId_e > APPSPM_PRM_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    else if(    (f_prmMinValue_pf32 == NULL)
            ||  (f_prmMaxValue_pf32 == NULL)
            ||  (f_prmDefaultValue_pf32 == NULL))
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

        *f_prmDefaultValue_pf32 = itemPrmInfo_ps->prmCfg_ps->DefaultItemVal_f32;
        *f_prmMaxValue_pf32 = itemPrmInfo_ps->prmCfg_ps->maxItemVal_f32;
        *f_prmMinValue_pf32 = itemPrmInfo_ps->prmCfg_ps->minItemVal_f32;
        Ret_e = RC_OK;
    }

    return Ret_e;
}


//********************************************************************************
//                      Local functions - Implementation
//********************************************************************************
/*********************************
 * s_APPSM_ConfigurationState
 *********************************/
static t_eReturnCode s_APPSM_ConfigurationState(void)
{
    t_eReturnCode Ret_e = RC_OK;
    t_eAPPSPM_ItemPrm idxParm_e;
    t_sAPPSPM_ItemPrmInfo * prmInfo_ps;

    //---- for now, no EEPROM so we take the default value instead ----//
    for(idxParm_e = 0 ; (idxParm_e < APPSPM_PRM_NB) && (Ret_e == RC_OK) ; idxParm_e++)
    {
        prmInfo_ps = &g_ItemPrmInfo_as[idxParm_e];
        if(c_AppSpm_ItemPrmInfo_as[idxParm_e].signal_e < APPSIG_SIGNAL_NB)
        {
            Ret_e = APPSIG_AddRcvMsgCallback(   c_AppSpm_ItemPrmInfo_as[idxParm_e].signal_e,
                                                s_APPSPM_AppSigMsgRcvCallback);
        }

        switch(prmInfo_ps->prmCfg_ps->prmType_e)
        {
            case APPSPM_PRM_TYPE_UINT8:
                prmInfo_ps->value_u.prmVal_u8 = (t_uint8)prmInfo_ps->prmCfg_ps->DefaultItemVal_f32;
            break;
            case APPSPM_PRM_TYPE_UINT16:
                prmInfo_ps->value_u.prmVal_u16 = (t_uint16)prmInfo_ps->prmCfg_ps->DefaultItemVal_f32;
            break;
            case APPSPM_PRM_TYPE_UINT32:
                prmInfo_ps->value_u.prmVal_u32 = (t_uint32)prmInfo_ps->prmCfg_ps->DefaultItemVal_f32;
            break;
            case APPSPM_PRM_TYPE_SINT8:
                prmInfo_ps->value_u.prmVal_s8 = (t_sint8)prmInfo_ps->prmCfg_ps->DefaultItemVal_f32;
            break;
            case APPSPM_PRM_TYPE_SINT16:
                prmInfo_ps->value_u.prmVal_s16 = (t_sint16)prmInfo_ps->prmCfg_ps->DefaultItemVal_f32;
            break;
            case APPSPM_PRM_TYPE_SINT32:
                prmInfo_ps->value_u.prmVal_s32 = (t_sint32)prmInfo_ps->prmCfg_ps->DefaultItemVal_f32;
            break;
            case APPSPM_PRM_TYPE_FLOAT32:
                prmInfo_ps->value_u.prmVal_f32 = (t_float32)prmInfo_ps->prmCfg_ps->DefaultItemVal_f32;
            break;  
            case APPSPM_PRM_TYPE_NB:
            default:
                Ret_e = RC_ERROR_WRONG_STATE;
            break; 
        }
    }

    g_FlagParamInit_b = (t_bool)TRUE;
    
    return Ret_e;
}      

/*********************************
 * s_APPSM_Operational
 *********************************/
static t_eReturnCode s_APPSM_Operational(void)
{  
    return RC_OK;
}

/*********************************
 * s_APPSPM_AppSigMsgRcvCallback
 *********************************/
static void s_APPSPM_AppSigMsgRcvCallback(t_eAPPSIG_Signal f_prmSignal_e, t_float32 f_value_f32)
{
    t_eReturnCode Ret_e;
    t_uint16 idxParam_u16;
    t_bool msgInfoFound_b = FALSE;
    t_uint32 tmpValue_u32;

    if(f_prmSignal_e >= APPSIG_SIGNAL_NB)
    {
        ASSERT((t_uint16)0);
    }
    else
    {
        for(idxParam_u16 = (t_uint16)0 ; 
        (idxParam_u16 < (t_uint16)APPSPM_PRM_NB) && (msgInfoFound_b == FALSE) ; 
        idxParam_u16++)
        {
            //---- the value f_value_f32 will be always be an unsigned value 
            //      but apppsig module used float32 ----//
            if(f_prmSignal_e == c_AppSpm_ItemPrmInfo_as[idxParam_u16].signal_e)
            {
                msgInfoFound_b = TRUE;
                Ret_e = s_APPSPM_GetVoidFromFloat32(f_value_f32,
                                                    g_ItemPrmInfo_as[idxParam_u16].prmCfg_ps->prmType_e,
                                                    &tmpValue_u32);
                                                    
                if(Ret_e == RC_OK)
                {
                    //---- apply offset and factor ----//

                    Ret_e = s_APPSPM_EncodePrmValue(&g_ItemPrmInfo_as[idxParam_u16],
                                                    (void *)&tmpValue_u32);
                }
                //--- set flag for eeprom, once there will be one ----//
            }
        }
        if(msgInfoFound_b == FALSE)
        {
            ASSERT((t_uint16)f_prmSignal_e);
        }
    }   

    return;
}

/*********************************
 * s_APPSPM_EncodePrmValue
 *********************************/
static t_eReturnCode s_APPSPM_EncodePrmValue(   t_sAPPSPM_ItemPrmInfo * f_prmInfo_ps, 
                                                void * f_value_pv)
{
    t_eReturnCode Ret_e = RC_OK;
    t_float32 scaledValue_f32;

    if (f_value_pv == NULL)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
        ASSERT((t_uint16)0);
    }
    else 
    {
        switch (f_prmInfo_ps->prmCfg_ps->prmType_e)
        {
            case APPSPM_PRM_TYPE_UINT8:
                scaledValue_f32 = (t_float32)(*((t_uint8 *)f_value_pv));
                scaledValue_f32 = scaledValue_f32 * f_prmInfo_ps->prmCfg_ps->factor_f32
                                                + f_prmInfo_ps->prmCfg_ps->offset_s16;
                if ((scaledValue_f32 > f_prmInfo_ps->prmCfg_ps->maxItemVal_f32)
                ||  (scaledValue_f32 < f_prmInfo_ps->prmCfg_ps->minItemVal_f32))
                {
                    Ret_e = RC_ERROR_LIMIT_REACHED;
                    f_prmInfo_ps->value_u.prmVal_u8 = (t_uint8)0;
                }
                else
                {
                    f_prmInfo_ps->value_u.prmVal_u8 = (t_uint8)scaledValue_f32;
                }
                break;

            case APPSPM_PRM_TYPE_UINT16:
                scaledValue_f32 = (t_float32)(*((t_uint16 *)f_value_pv));
                scaledValue_f32 = scaledValue_f32 * f_prmInfo_ps->prmCfg_ps->factor_f32
                                                + f_prmInfo_ps->prmCfg_ps->offset_s16;
                if ((scaledValue_f32 > f_prmInfo_ps->prmCfg_ps->maxItemVal_f32)
                ||  (scaledValue_f32 < f_prmInfo_ps->prmCfg_ps->minItemVal_f32))
                {
                    Ret_e = RC_ERROR_LIMIT_REACHED;
                    f_prmInfo_ps->value_u.prmVal_u16 = (t_uint16)0;
                }
                else
                {
                    f_prmInfo_ps->value_u.prmVal_u16 = (t_uint16)scaledValue_f32;
                }
                break;

            case APPSPM_PRM_TYPE_UINT32:
                scaledValue_f32 = (t_float32)(*((t_uint32 *)f_value_pv));
                scaledValue_f32 = scaledValue_f32 * f_prmInfo_ps->prmCfg_ps->factor_f32
                                                + f_prmInfo_ps->prmCfg_ps->offset_s16;
                if ((scaledValue_f32 > f_prmInfo_ps->prmCfg_ps->maxItemVal_f32)
                ||  (scaledValue_f32 < f_prmInfo_ps->prmCfg_ps->minItemVal_f32))
                {
                    Ret_e = RC_ERROR_LIMIT_REACHED;
                    f_prmInfo_ps->value_u.prmVal_u32 = (t_uint32)0;
                }
                else
                {
                    f_prmInfo_ps->value_u.prmVal_u32 = (t_uint32)scaledValue_f32;
                }
                break;

            case APPSPM_PRM_TYPE_SINT8:
                scaledValue_f32 = (t_float32)(*((t_sint8 *)f_value_pv));
                scaledValue_f32 = scaledValue_f32 * f_prmInfo_ps->prmCfg_ps->factor_f32
                                                + f_prmInfo_ps->prmCfg_ps->offset_s16;
                if ((scaledValue_f32 > f_prmInfo_ps->prmCfg_ps->maxItemVal_f32)
                ||  (scaledValue_f32 < f_prmInfo_ps->prmCfg_ps->minItemVal_f32))
                {
                    Ret_e = RC_ERROR_LIMIT_REACHED;
                    f_prmInfo_ps->value_u.prmVal_s8 = (t_sint8)0;
                }
                else
                {
                    f_prmInfo_ps->value_u.prmVal_s8 = (t_sint8)scaledValue_f32;
                }
                break;

            case APPSPM_PRM_TYPE_SINT16:
                scaledValue_f32 = (t_float32)(*((t_sint16 *)f_value_pv));
                scaledValue_f32 = scaledValue_f32 * f_prmInfo_ps->prmCfg_ps->factor_f32
                                                + f_prmInfo_ps->prmCfg_ps->offset_s16;
                if ((scaledValue_f32 > f_prmInfo_ps->prmCfg_ps->maxItemVal_f32)
                ||  (scaledValue_f32 < f_prmInfo_ps->prmCfg_ps->minItemVal_f32))
                {
                    Ret_e = RC_ERROR_LIMIT_REACHED;
                    f_prmInfo_ps->value_u.prmVal_s16 = (t_sint16)0;
                }
                else
                {
                    f_prmInfo_ps->value_u.prmVal_s16 = (t_sint16)scaledValue_f32;
                }
                break;

            case APPSPM_PRM_TYPE_SINT32:
                scaledValue_f32 = (t_float32)(*((t_sint32 *)f_value_pv));
                scaledValue_f32 = scaledValue_f32 * f_prmInfo_ps->prmCfg_ps->factor_f32
                                                + f_prmInfo_ps->prmCfg_ps->offset_s16;
                if ((scaledValue_f32 > f_prmInfo_ps->prmCfg_ps->maxItemVal_f32)
                ||  (scaledValue_f32 < f_prmInfo_ps->prmCfg_ps->minItemVal_f32))
                {
                    Ret_e = RC_ERROR_LIMIT_REACHED;
                    f_prmInfo_ps->value_u.prmVal_s32 = (t_sint32)0;
                }
                else
                {
                    f_prmInfo_ps->value_u.prmVal_s32 = (t_sint32)scaledValue_f32;
                }
                break;

            case APPSPM_PRM_TYPE_FLOAT32:
                scaledValue_f32 = *((t_float32 *)f_value_pv);
                scaledValue_f32 = scaledValue_f32 * f_prmInfo_ps->prmCfg_ps->factor_f32
                                                + f_prmInfo_ps->prmCfg_ps->offset_s16;
                if ((scaledValue_f32 > f_prmInfo_ps->prmCfg_ps->maxItemVal_f32)
                ||  (scaledValue_f32 < f_prmInfo_ps->prmCfg_ps->minItemVal_f32))
                {
                    Ret_e = RC_ERROR_LIMIT_REACHED;
                    f_prmInfo_ps->value_u.prmVal_f32 = (t_float32)0.0f;
                }
                else
                {
                    f_prmInfo_ps->value_u.prmVal_f32 = scaledValue_f32;
                }
                break;

            case APPSPM_PRM_TYPE_NB:
            default:
                Ret_e = RC_ERROR_PARAM_INVALID;
                ASSERT((t_uint16)0);
                break;

        }
    }

    return Ret_e;
}

/*********************************
 * s_APPSPM_GetVoidFromFloat32
 *********************************/
static t_eReturnCode s_APPSPM_GetVoidFromFloat32(t_float32 f_prmvalue_f32,
                                                 t_eAPPSPM_PrmType f_prmType_e,
                                                 void * f_value_pv)
{
    t_eReturnCode Ret_e = RC_OK;

    if ((f_value_pv == NULL) || (f_prmType_e >= APPSPM_PRM_TYPE_NB))
    {
        return RC_ERROR_PARAM_INVALID;
    }

    switch (f_prmType_e)
    {
        case APPSPM_PRM_TYPE_UINT8:
            *((t_uint8 *)f_value_pv) = (t_uint8)f_prmvalue_f32;
            break;

        case APPSPM_PRM_TYPE_UINT16:
            *((t_uint16 *)f_value_pv) = (t_uint16)f_prmvalue_f32;
            break;

        case APPSPM_PRM_TYPE_UINT32:
            *((t_uint32 *)f_value_pv) = (t_uint32)f_prmvalue_f32;
            break;

        case APPSPM_PRM_TYPE_SINT8:
            *((t_sint8 *)f_value_pv) = (t_sint8)f_prmvalue_f32;
            break;

        case APPSPM_PRM_TYPE_SINT16:
            *((t_sint16 *)f_value_pv) = (t_sint16)f_prmvalue_f32;
            break;

        case APPSPM_PRM_TYPE_SINT32:
            *((t_sint32 *)f_value_pv) = (t_sint32)f_prmvalue_f32;
            break;

        case APPSPM_PRM_TYPE_FLOAT32:
            *((t_float32 *)f_value_pv) = f_prmvalue_f32;
            break;

        default:
            Ret_e = RC_ERROR_PARAM_INVALID;
            break;
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
