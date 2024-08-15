TASK (TASK_MIRROR_LEFT) {
    VAR(EventMaskType, AUTOMATIC) Event;

    while(1)
    {
        (VAR(void, AUTOMATIC))WaitEvent(OSEvent_ChangeLeft);
        Event = 0U;
        (VAR(void, AUTOMATIC))GetEvent(TASK_MIRROR_LEFT, &Event);

        if( (Event & OSEvent_ChangeLeft) > 0U ) {
            (VAR(void, AUTOMATIC))ClearEvent(OSEvent_ChangeLeft);
            Rte_ChangeLeft();
        } 
    }
}