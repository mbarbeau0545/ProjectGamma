/**
 * @file        FMK_MAC.c
 * @brief       Framework Memory Access Control module.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      mba
 * @date        15/09/2024
 * @version     1.0
 */






// ********************************************************************
// *                      Includes
// ********************************************************************
#include "./SafeMem.h"
#include "string.h"
// ********************************************************************
// *                      Defines
// ********************************************************************
#define SAFEMEM_MAX_ATTEMPT_OPE ((t_uint8)10)
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

//********************************************************************************
//                      Public functions - Implementation
//********************************************************************************
//**************************
// SMB_SecureBlockInit
//***************************
t_eReturnCode SMB_SecureBlockInit(  t_sSafeMem_BlockInfo * f_secBlockInfo_ps, 
                                        const void * f_SecureArea_pv,
                                        const t_uint16 f_sizeSecArea_u16,
                                        t_uint8 f_maxAttemptOpe_u8)
{
    t_eReturnCode Ret_e = RC_OK;

    if((f_secBlockInfo_ps == (t_sSafeMem_BlockInfo *)NULL)
    || (f_SecureArea_pv == (const void *)NULL))
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        if(f_maxAttemptOpe_u8 > SAFEMEM_MAX_ATTEMPT_OPE)
        {
            f_maxAttemptOpe_u8 = SAFEMEM_MAX_ATTEMPT_OPE;
        }
        //---- Initialisation de la structure ----//
        f_secBlockInfo_ps->flag_s.isCorrupted_b = (t_bool)False;
        f_secBlockInfo_ps->flag_s.isRead_b      = (t_bool)False;
        f_secBlockInfo_ps->flag_s.isWrite_b     = (t_bool)False; 
        f_secBlockInfo_ps->maxAttemptOpe_u8     = f_maxAttemptOpe_u8;
        f_secBlockInfo_ps->blockArea_pv         = (void *)f_SecureArea_pv;
        f_secBlockInfo_ps->sizeBlock_u16        = f_sizeSecArea_u16;
        f_secBlockInfo_ps->isConfigured_b       = (t_bool)True;
    }

    return Ret_e;
}

//**************************
// SMB_Read
//***************************
t_eReturnCode SMB_Read( t_sSafeMem_BlockInfo * f_secBlockInfo_ps,
                                         void * f_dataContainer_pv)
{
    t_eReturnCode Ret_e = RC_OK;
    t_sSafeMem_FlagBlock * flag_ps;
    t_uint8 cntAttemptOpe_u8 = 0;

    if(f_secBlockInfo_ps == NULL)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        flag_ps = (t_sSafeMem_FlagBlock *)(&f_secBlockInfo_ps->flag_s);

        //---- Vérifie si une écriture est en cours ----//
        if(flag_ps->isWrite_b == (t_bool)True)
        {
            Ret_e =  RC_WARNING_BUSY;
        }
        else 
        {       
            //---- Boucle de tentative de lecture ----//
            while(cntAttemptOpe_u8 < f_secBlockInfo_ps->maxAttemptOpe_u8
            &&   (cntAttemptOpe_u8 < SAFEMEM_MAX_ATTEMPT_OPE))
            {    
                //---- Met à jour le flag de lecture ----//
                flag_ps->isRead_b = (t_bool)True;
                Ret_e = SafeMem_memcpy( f_dataContainer_pv, 
                                        f_secBlockInfo_ps->blockArea_pv,
                                        f_secBlockInfo_ps->sizeBlock_u16);
                //---- Réinitialise le flag de lecture ----//
                flag_ps->isRead_b = (t_bool)False;
                
                //----- Vérifie si le flag de corruption a été activé ou si l'opération a échoué ----//
                if((flag_ps->isCorrupted_b == (t_bool)True) 
                || (Ret_e != RC_OK))
                {
                    //---- Remise à zéro du flag de corruption et incrémentation du compteur de tentatives ----//
                    flag_ps->isCorrupted_b = (t_bool)False;
                    cntAttemptOpe_u8++;
                    continue;
                }
                // Si la copie s'est déroulée correctement, on sort de la boucle
                break;
            }
            
            if(cntAttemptOpe_u8 >= f_secBlockInfo_ps->maxAttemptOpe_u8)
            {
                Ret_e = RC_WARNING_BUSY;
            }
        }
    }
    
    return Ret_e;
}

//**************************
// SMB_Write
//***************************
t_eReturnCode SMB_Write( t_sSafeMem_BlockInfo * f_secBlockInfo_ps,
                                          void * f_dataContainer_pv)
{
    t_eReturnCode Ret_e = RC_OK;
    t_sSafeMem_FlagBlock * flag_ps;

    if(f_secBlockInfo_ps == NULL)
    {
        return RC_ERROR_PARAM_INVALID;
    }
    
    flag_ps = &f_secBlockInfo_ps->flag_s;

    //---- Si une lecture est en cours, on marque le bloc comme corrompu ----//
    if(flag_ps->isRead_b == (t_bool)True)
    {
        flag_ps->isCorrupted_b = (t_bool)True;
    }

    //---- Met à jour le flag d'écriture ----//
    flag_ps->isWrite_b = (t_bool)True;
    Ret_e = SafeMem_memcpy( f_secBlockInfo_ps->blockArea_pv,
                            f_dataContainer_pv, 
                            f_secBlockInfo_ps->sizeBlock_u16);
    flag_ps->isWrite_b = (t_bool)False;
    
    return Ret_e;
}
//**********************
// SafeMem_memcpy
//**********************
t_eReturnCode SafeMem_memcpy(void *f_destination_pv, const void *f_src_pv, t_uint16 f_size_u16)
{
    t_eReturnCode Ret_e = RC_OK;
    void * memcpy_pv = NULL;
    // Vérification des pointeurs NULL
    if (f_destination_pv == NULL || f_src_pv == NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else
    {
        // Effectuer la copie avec memcpy
        memcpy_pv = memcpy(f_destination_pv, f_src_pv, f_size_u16);
        if(Ret_e == RC_OK)
        {
            // Vérification que memcpy renvoie bien le pointeur destination
            if(memcpy_pv != f_destination_pv)
            {
                Ret_e = RC_WARNING_MEM_FAILED;
            }
        }
    }

    return Ret_e;
}

//**********************
// SafeMem_memset
//**********************
t_eReturnCode SafeMem_memset(void *f_destination_pv, t_uint16 f_value_u16, t_uint16 f_size_u16)
{
    t_eReturnCode Ret_e = RC_OK;

    // Vérification du pointeur NULL
    if (f_destination_pv == NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else
    {
        // Effectuer l'opération avec memset
        void *memset_pv = memset(f_destination_pv, f_value_u16, (size_t)f_size_u16);

        // Vérification que memset renvoie bien le pointeur destination
        if (memset_pv != f_destination_pv)
        {
            Ret_e = RC_WARNING_MEM_FAILED;
        }
    }

    return Ret_e;
}

//**********************
// SafeMem_memmove
//**********************
t_eReturnCode SafeMem_memmove(void *f_destination_pv, const void *f_src_pv, t_uint16 f_size_u16)
{
    t_eReturnCode Ret_e = RC_OK;

    // Vérification des pointeurs NULL
    if (f_destination_pv == NULL || f_src_pv == NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else
    {
        // Effectuer l'opération avec memmove
        void *memmove_pv = memmove(f_destination_pv, f_src_pv, (size_t)f_size_u16);

        // Vérification que memmove renvoie bien le pointeur destination
        if (memmove_pv != f_destination_pv)
        {
            Ret_e = RC_WARNING_MEM_FAILED;
        }
    }

    return Ret_e;
}

//**********************
// SafeMem_memcmp
//**********************
t_eReturnCode SafeMem_memcmp(const void *f_buffer1_pv, const void *f_buffer2_pv, t_uint16 f_size_u16)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint32 result_u32;
    // Vérification des pointeurs NULL
    if (f_buffer1_pv == NULL || f_buffer2_pv == NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else
    {
        // Comparaison avec memcmp
        result_u32 = memcmp(f_buffer1_pv, f_buffer2_pv, (size_t)f_size_u16);

        // Vérification du résultat
        if (result_u32 != 0)
        {
            Ret_e = RC_WARNING_MEM_FAILED;
        }
    }

    return Ret_e;
}

//**********************
// SafeMem_memclear
//**********************
t_eReturnCode SafeMem_memclear(void *f_buffer_pv, t_uint16 f_size_u16)
{
    t_eReturnCode Ret_e = RC_OK;
    volatile unsigned char *ptr = NULL;

    // Vérification du pointeur NULL
    if (f_buffer_pv == NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else
    {
        // Effacer la mémoire
        ptr = (volatile unsigned char *)f_buffer_pv;
        while (f_size_u16--)
        {
            *ptr++ = 0;
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
