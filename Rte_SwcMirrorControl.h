#ifndef RTE_SWCMIRRORCONTROL_H
#define RTE_SWCMIRRORCONTROL_H

#include "Rte_Type.h"
#include "Rte_SwcAdjuster.h"

FUNC(void, RTE_CODE_EcucPartition_0) GetParram(void);
FUNC(void, RTE_CODE_EcucPartition_0) UpdatePossition(void);
FUNC(Std_ReturnType, AUTOMATIC) Rte_Read_RP_Setting_ButtonArray( P2VAR(buttonValues, AUTOMATIC, RTE_APPL_DATA) button );

#endif