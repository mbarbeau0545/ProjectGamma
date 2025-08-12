/*********************************************************************
 * @file        APPSPM.h
 * @brief       System Paramters Managment.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef APP_PRM_H_INCLUDED 
#define APP_PRM_H_INCLUDED 





	// ********************************************************************
	// *                      Includes
	// ********************************************************************
    #ifdef APPSYS_MODULE_APP_SPM_ENABLE
	#include "TypeCommon.h"
	#include "APP_CFG/ConfigFiles/APPSPM_ConfigPublic.h"
	// ********************************************************************
	// *                      Defines
	// ********************************************************************

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
    *	@brief      Perform all Init action for this module.\n
    *
    */
   t_eReturnCode APPSPM_Init(void);
   /**
   *
   *	@brief      Perform all Cyclic action for this module.\n
   *   @note       In preOpe mode -> If one of the configuration is not set the Module Cyclic 
   *               retry indefinitely and the module state doesn't change until all 
   *               actuator configuration are set
   *               In Ope mode -> call driver cyclic
   *
   */
   t_eReturnCode APPSPM_Cyclic(void);
   /**
   *
   *	@brief Function to know the module state.\n 
   *
   *	@param[in]  f_State_pe : store the value, value from @ref t_eCyclicModState
   *
   *   @retval RC_OK                             @ref RC_OK
   *   @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NUL
   */
   t_eReturnCode APPSPM_GetState(t_eCyclicModState *f_State_pe);
   /**
   *
   *	@brief Function to update the module state.\n
   *
   *	@param[in]  f_State_e : the new value, value from @ref t_eCyclicModState
   *
   *   @retval RC_OK                             @ref RC_OK
   */
   t_eReturnCode APPSPM_SetState(t_eCyclicModState f_State_e);
   /**
   *
   *	@brief Get the Parameter value
   *
   *	@param[in]  f_itemId_e : the item parameter id, value from @ref t_eAPPSPM_ItemPrm
   *	@param[in]  f_prmValue_pu16 : Container for parameter value 
   *
   *   @retval RC_OK                             @ref RC_OK
   */
	t_eReturnCode APPSPM_GetParam(t_eAPPSPM_ItemPrm f_itemId_e, t_uint16 * f_prmValue_pu16);
    /** 
    *	@brief Set the Parameter value
    *
    *	@param[in]  f_itemId_e : the item parameter id, value from @ref t_eAPPSPM_ItemPrm
    *	@param[in]  f_prmValue_u16 : New Parameter Value 
    *
    *   @retval RC_OK                             @ref RC_OK
    */
	t_eReturnCode APPSPM_SetParam(t_eAPPSPM_ItemPrm f_itemId_e, t_uint16 f_prmValue_u16);
    /**
     *
     *	@brief Get the Parameter Information
    *
    *	@param[in]  f_itemId_e : the item parameter id, value from @ref t_eAPPSPM_ItemPrm
    *	@param[in]  f_prmValue_pu16 : Container for parameter value 
    *
    *   @retval RC_OK                             @ref RC_OK
    */
	t_eReturnCode APPSPM_GetParamInfo(	t_eAPPSPM_ItemPrm f_itemId_e, 
                                        t_uint16 * f_prmMinValue_pu16,
                                        t_uint16 * f_prmMaxValue_pu16,
                                        t_uint16 * f_prmDefaultValue_pu16);
    #endif // APPSYS_MODULE_APP_SPM_ENABLE
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
