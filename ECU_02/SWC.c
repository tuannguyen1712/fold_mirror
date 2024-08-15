#include "Rte_MotorLeft.h"
#include "DataType.h"
#include "SWC.h"


FUNC(void, RTE_CODE_EcucPartition_2) ChangeLeft(void) {
    Angles_t Angles;
    VAR(Std_ReturnType, AUTOMATIC) ret_val = Rte_Read_RP_ChangeLeftAngle_Angles(&Angles);
    if (ret_val == RTE_E_INVALID) {
        /* ERROR */
        return;
    }
    Rte_Call_WdgMCheckpointReached(SE_MA_FnO, CP_ID_1);
    Rte_Call_RP_IO_Hwab_MotorControl(ID_MOTOR_FOLD, Angles.Fold); /* Control Fold */
    Rte_Call_WdgMCheckpointReached(SE_MA_FnO, CP_ID_2);

    Rte_Call_WdgMCheckpointReached(SE_MA_LnR, CP_ID_3);
    Rte_Call_RP_IO_Hwab_MotorControl(ID_MOTOR_YAW, Angles.Yaw); /* Control Yaw */
    Rte_Call_WdgMCheckpointReached(SE_MA_LnR, CP_ID_4);

    Rte_Call_WdgMCheckpointReached(SE_MA_UnD, CP_ID_5);
    Rte_Call_RP_IO_Hwab_MotorControl(ID_MOTOR_PITCH, Angle.Pitch); /* Control Pitch */
    Rte_Call_WdgMCheckpointReached(SE_MA_UnD, CP_ID_6);
}