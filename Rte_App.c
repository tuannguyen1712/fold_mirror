TASK (ASWTask_20ms) {
    VAR(EventMaskType, AUTOMATIC) Event;

    while( 1 )
    {
        (VAR(void, AUTOMATIC))WaitEvent( OsEvent_ASW_20ms );
        Event = 0U;
        (VAR(void, AUTOMATIC))GetEvent( OsTask_ASWTask_20ms, &Event );

        if( (Rte_status == RTE_STATUS_RUN) && (Rte_partition_status_EcucPartition_0 == RTE_PARTITION_STATUS_RUNNING) && (SchM_status == SCHM_STATUS_RUN) ) {
            if( (Event & OsEvent_ASW_20ms) > 0U ) {
                (VAR(void, AUTOMATIC))ClearEvent( OsEvent_ASW_20ms );

                if ( Rte_periodically_event_activation == TRUE ) {
                    if( Rte_DisableEventList[3] == 0U ) {
                        Rte_App_ComTxRx();
                    }
                }
                if ( Rte_periodically_event_activation == TRUE ) {
                    if( Rte_DisableEventList[12] == 0U ) {
                        Rte_AppDiag_20ms();
                    }
                }
                if ( Rte_periodically_event_activation == TRUE ) {
                    if( Rte_DisableEventList[36] == 0U ) {
                        Rte_AppWdgM_20ms();
                    }
                }
            } else {
              /* No treatment */
            }
        } else {
            (VAR(void, AUTOMATIC))ClearEvent( Event );
        }
    }
}