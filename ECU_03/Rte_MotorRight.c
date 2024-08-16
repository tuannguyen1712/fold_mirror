#include "Rte_MotorRight.h"

static angles_t rte_angles;

extern Hwab_MotorControl(VAR(uint8_t, AUTOMATIC), VAR(uint8_t, AUTOMATIC));
/******************************************************************************/
/* ModuleID    :                                                              */
/* ServiceID   :                                                              */
/* Name        : Rte_ChangeRight                                              */
/* Param       : void                                                         */
/* Return      : void                                                         */
/* Contents    :                                                              */
/* Author      : Autosar_Group_02                                             */
/* Note        : Rte_ChangeRight call ChangeRight runnable                    */
/******************************************************************************/
FUNC(void, RTE_CODE_EcucPartition_3) Rte_ChangeRight(VAR(void, AUTOMATIC)) 
{
    ChangeRight();
}

/******************************************************************************/
/* ModuleID    :                                                              */
/* ServiceID   :                                                              */
/* Name        : Rte_COMCbk_ComISignal_HS_CAN1_SetAngle                       */
/* Param       : void                                                         */
/* Return      : void                                                         */
/* Contents    :                                                              */
/* Author      : Autosar_Group_02                                             */
/* Note        : Rte_COMCbk is called when new data becomes available.        */ 
/*               Rte_COMCbk will update new data from the shadow buffer to    */
/*               the RTE global variable then set OSevent                     */
/******************************************************************************/
FUNC(void, RTE_CODE_EcucPartition_3) Rte_COMCbk_ComISignal_HS_CAN1_SetAngle(void) 
{

    (void)Com_ReceiveSignalGroup(ComConf_ComSignalGroup_ComISignal_HS_CAN1_SetAngle);

    (void)Com_ReceiveSignal(ComConf_ComGroupSignal_ComISignal_HS_CAN1_SetAngle_Fold, &rte_angles.fold);          /*angle_Fold*/
    (void)Com_ReceiveSignal(ComConf_ComGroupSignal_ComISignal_HS_CAN1_SetAngle_RightYaw, &rte_angles.yaw);        /*angle_Yaw*/
    (void)Com_ReceiveSignal(ComConf_ComGroupSignal_ComISignal_HS_CAN1_SetAngle_RightPitch, &rte_angles.pitch);    /*angle_Pitch*/

    (void)SetEvent(TASK_MIRROR_RIGHT, Rte_DRE_ChangeRight);
}

/******************************************************************************/
/* ModuleID    :                                                              */
/* ServiceID   :                                                              */
/* Name        : Rte_Read_RP_ChangeRightAngle_Angles                          */
/* Param       : a pointer of struct (angles)                                 */
/* Return      : Std_ReturnType                                               */
/* Contents    :                                                              */
/* Author      : Autosar_Group_02                                             */
/* Note        : This API will copy data from RTE global variable to SWC      */
/*               variable                                                     */
/******************************************************************************/
FUNC(Std_ReturnType, RTE_CODE_EcucPartition_3) Rte_Read_RP_ChangeRightAngle_Angles(angles_t* angles) 
{
    VAR(Std_ReturnType, AUTOMATIC) ret_val = RTE_E_OK;
    if (Angles == Null) {
        ret_val =  RTE_E_INVALID;
        return ret_val;
    }
    angles->fold  = rte_angles.fold;
    angles->yaw   = rte_angles.yaw;
    angles->pitch = rte_angles.pitch;
    return ret_val;
}

/******************************************************************************/
/* ModuleID    :                                                              */
/* ServiceID   :                                                              */
/* Name        : Rte_Call_RP_IO_Hwab_MotorControl                             */
/* Param       : id , adc_value                                               */
/* Return      : Std_ReturnType                                               */
/* Contents    :                                                              */
/* Author      : Autosar_Group_02                                             */
/* Note        : This API call hardware abstraction layer to request service  */
/******************************************************************************/
FUNC(Std_ReturnType, RTE_CODE_EcucPartition_3) Rte_Call_RP_IO_Hwab_MotorControl(VAR(uint8_t, AUTOMATIC) id, VAR(uint8_t, AUTOMATIC) adc_value) 
{
    VAR(Std_ReturnType, AUTOMATIC) ret_val;
    ret_val = Hwab_MotorControl(id, adc_value);
    return ret_val;
}
