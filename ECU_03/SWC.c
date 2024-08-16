#include "Rte_MotorRight.h"
#include "DataType.h"
#include "SWC.h"

/******************************************************************************/
/* ModuleID    :                                                              */
/* ServiceID   :                                                              */
/* Name        : ChangeRight                                                   */
/* Param       :                                                              */
/* Return      :                                                              */
/* Contents    :                                                              */
/* Author      : Autosar_Group_02                                             */
/* Note        : This is Runnable which has the function of reading data,     */
/*               processing data and sending corresponding control to         */
/*               the motor                                                    */
/******************************************************************************/
FUNC(void, RTE_CODE_EcucPartition_3) ChangeRight(void) {
    angles_t angles;
    adc_values_t adc_values;
    VAR(Std_ReturnType, AUTOMATIC) ret_val = Rte_Read_RP_ChangeRightAngle_Angles(&angles);
    if (ret_val == RTE_E_INVALID) {
        /* ERROR */
        return;
    }

    adc_values.fold_adc_value  = (angles.fold  / RANGE_FOLD_ANGLE)  * RANGE_FOLD_ADC;
    adc_values.yaw_adc_value   = (angles.yaw   / RANGE_YAW_ANGLE)   * RANGE_YAW_ADC;
    adc_values.pitch_adc_value = (angles.pitch / RANGE_PITCH_ANGLE) * RANGE_PITCH_ADC;

    Rte_Call_WdgMCheckpointReached(SE_MA_FnO, CP_ID_1);
    Rte_Call_RP_IO_Hwab_MotorControl(ID_MOTOR_FOLD, adc_values.fold_adc_value);     /* Control Fold Motor */
    Rte_Call_WdgMCheckpointReached(SE_MA_FnO, CP_ID_2);

    Rte_Call_WdgMCheckpointReached(SE_MA_LnR, CP_ID_3);
    Rte_Call_RP_IO_Hwab_MotorControl(ID_MOTOR_YAW, adc_values.yaw_adc_value);       /* Control Yaw Motor*/
    Rte_Call_WdgMCheckpointReached(SE_MA_LnR, CP_ID_4);

    Rte_Call_WdgMCheckpointReached(SE_MA_UnD, CP_ID_5);
    Rte_Call_RP_IO_Hwab_MotorControl(ID_MOTOR_PITCH, adc_values.pitch_adc_value);   /* Control Pitch Motor*/
    Rte_Call_WdgMCheckpointReached(SE_MA_UnD, CP_ID_6);
}