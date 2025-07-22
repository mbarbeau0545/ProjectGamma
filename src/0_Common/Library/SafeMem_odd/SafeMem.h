/**
 * @file        FMK_MAC.h
 * @brief       Memomry access control for DMA & user access\n.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef SAFEMEM_H_INCLUDED
#define SAFEMEM_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "TypeCommon.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    

    // ********************************************************************
    // *                      Types
    // ********************************************************************

    //-----------------------------ENUM TYPES-----------------------------//

    /* CAUTION : Automatic generated code section for Enum: Start */

    /* CAUTION : Automatic generated code section for Enum: End */
   
    //-----------------------------STRUCT TYPES---------------------------//

    /* CAUTION : Automatic generated code section for Structure: Start */

    /* CAUTION : Automatic generated code section for Structure: End */
    /**
     * @brief Strcture for flag to R/W block
     */
    typedef struct
    {
        t_bool isRead_b;
        t_bool isWrite_b;
        t_bool isCorrupted_b;
    } t_sSafeMem_FlagBlock;
    
    /**
     * @brief Block Info
     */
    typedef struct
    {
        t_uint8 maxAttemptOpe_u8;           /**< Container for the max operation when read/write ope failed */
        t_uint16 sizeBlock_u16;             /**< Size of the secure Area Block*/
        void * blockArea_pv;                /**< Pointor to the secure area block */
        t_sSafeMem_FlagBlock flag_s;        /**< Flag Info */
        t_bool isConfigured_b;
    } t_sSafeMem_BlockInfo;
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
     * @brief Performs a secure memory Init.
     * @param[in] f_secBlockInfo_ps Structure that contains information for the scure block.
     * @param[in] f_SecureArea_pv Pointer to the source buffer.
     * @param[in] f_sizeSecArea_u16 Size of the data to copy (in bytes).
     * @param[in] f_maxAttemptOpe_u8 the max operation when read/write ope failed, max is SAFEMEM_MAX_ATTEMPT_OPE
     * @return t_eReturnCode Return code indicating success or failure.
     */
    t_eReturnCode SMB_SecureBlockInit(  t_sSafeMem_BlockInfo * f_secBlockInfo_ps, 
                                            const void * f_SecureArea_pv,
                                            const t_uint16 f_sizeSecArea_u16,
                                            t_uint8 f_maxAttemptOpe_u8);
    
    /**
     * @brief Performs a secure memory Read of a secure block.
     * @param[in] f_secBlockInfo_ps Structure that contains information for the scure block.
     * @param[in] f_dataContainer_pv Pointer to the reception buffer.
     * @return t_eReturnCode Return code indicating success or failure.
     */
    t_eReturnCode SMB_Read(  t_sSafeMem_BlockInfo * f_secBlockInfo_ps,
                                            void * f_dataContainer_pv);
    /**
     * @brief Performs a secure memory Read of a secure block.
     * @param[in] f_secBlockInfo_ps Structure that contains information for the scure block.
     * @param[in] f_dataContainer_pv Pointer to the reception buffer.
     * @return t_eReturnCode Return code indicating success or failure.
     */
    t_eReturnCode SMB_Write( t_sSafeMem_BlockInfo * f_secBlockInfo_ps,
                                            void * f_dataContainer_pv);
    /**
     * @brief Performs a secure memory copy.
     * @param[in] f_destination_pv Pointer to the destination buffer.
     * @param[in] f_src_pv Pointer to the source buffer.
     * @param[in] f_size_u16 Size of the data to copy (in bytes).
     * @return t_eReturnCode Return code indicating success or failure.
     */
    t_eReturnCode SafeMem_memcpy(void *f_destination_pv, const void *f_src_pv, t_uint16 f_size_u16);

    /**
     * @brief Initializes a memory region with a given value.
     * @param[in] f_destination_pv Pointer to the memory to initialize.
     * @param[in] f_value_i Value to write to the memory.
     * @param[in] f_size_u16 Size of the memory to initialize (in bytes).
     * @return t_eReturnCode Return code indicating success or failure.
     */
    t_eReturnCode SafeMem_memset(void *f_destination_pv, t_uint16 f_value_u16, t_uint16 f_size_u16);

    /**
     * @brief Moves a memory region safely (supports overlapping regions).
     * @param[in] f_destination_pv Pointer to the destination buffer.
     * @param[in] f_src_pv Pointer to the source buffer.
     * @param[in] f_size_u16 Size of the data to move (in bytes).
     * @return t_eReturnCode Return code indicating success or failure.
     */
    t_eReturnCode SafeMem_memmove(void *f_destination_pv, const void *f_src_pv, t_uint16 f_size_u16);

    /**
     * @brief Compares two memory regions.
     * @param[in] f_buffer1_pv Pointer to the first buffer.
     * @param[in] f_buffer2_pv Pointer to the second buffer.
     * @param[in] f_size_u16 Size of the data to compare (in bytes).
     * @param[out] f_result_pi Result of the comparison (-1, 0, 1).
     * @return t_eReturnCode Return code indicating success or failure.
     */
    t_eReturnCode SafeMem_memcmp(const void *f_buffer1_pv, const void *f_buffer2_pv, t_uint16 f_size_u16);

    /**
     * @brief Clears a memory region securely (useful for sensitive data).
     * @param[in] f_buffer_pv Pointer to the memory to clear.
     * @param[in] f_size_u16 Size of the memory to clear (in bytes).
     * @return t_eReturnCode Return code indicating success or failure.
     */
    t_eReturnCode SafeMem_memclear(void *f_buffer_pv, t_uint16 f_size_u16);
#endif // SAFEMEM_H_INCLUDED           
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
