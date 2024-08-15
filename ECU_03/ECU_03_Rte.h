#ifndef __ECU_02_RTE_H__
#define __ECU_02_RTE_H__

#include <stdint.h>

FUNC(void, RTE_CODE_EcucPartition_3) Rte_Read_RP_Angle(uint8_t* ArrayAngle);
FUNC(void, RTE_CODE_EcucPartition_3) Rte_Call_Motor_Control(VAR(uint8, AUTOMATIC) id, VAR(uint8, AUTOMATIC, RTE_APPL_DATA) angle);

#endif