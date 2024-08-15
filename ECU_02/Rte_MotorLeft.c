#include "Rte_MotorLeft.h"

static Angles_t Rte_Angles;

FUNC(void, RTE_CODE_EcucPartition_2) Rte_ChangeLeft( VAR(void, AUTOMATIC) ) {
    ChangeLeft();
}

FUNC(void, RTE_CODE_EcucPartition_2) Rte_COMCbk_ComISignal_HS_CAN1_SetAngle(void) {

    (void)Com_ReceiveSignalGroup(ComConf_ComSignalGroup_ComISignal_HS_CAN1_SetAngle);

    (void)Com_ReceiveSignal(ComConf_ComGroupSignal_ComISignal_HS_CAN1_SetAngle_Fold, &Rte_Angles.Fold);          /*angle_Fold*/
    (void)Com_ReceiveSignal(ComConf_ComGroupSignal_ComISignal_HS_CAN1_SetAngle_LeftYaw, &Rte_Angles.Yaw);        /*angle_Yaw*/
    (void)Com_ReceiveSignal(ComConf_ComGroupSignal_ComISignal_HS_CAN1_SetAngle_LeftPitch, &Rte_Angles.Pitch);    /*angle_Pitch*/

    (void)SetEvent(TASK_MIRROR_LEFT, Rte_DRE_ChangeLeft);
}

FUNC(Std_ReturnType, RTE_CODE_EcucPartition_2) Rte_Read_RP_ChangeLeftAngle_Angles(Angles_t* Angles) {
    VAR(Std_ReturnType, AUTOMATIC) ret_val = RTE_E_OK;
    if (Angles == Null) {
        ret_val =  RTE_E_INVALID;
        return ret_val;
    }
    Angles->Fold = Rte_Angles.Fold;
    Angles->Yaw = Rte_Angles.Yaw;
    Angles->Pitch = Rte_Angles.Pitch;
    return ret_val;
}

FUNC(Std_ReturnType, RTE_CODE_EcucPartition_2) Rte_Call_RP_IO_Hwab_MotorControl(VAR(uint8, AUTOMATIC) id, VAR(uint8, AUTOMATIC) angle) {
    VAR(Std_ReturnType, AUTOMATIC) ret_val;
    ret_val = Hwab_MotorControl(id, angle);
    return ret_val;
}
