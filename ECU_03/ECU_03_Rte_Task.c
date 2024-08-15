TASK (TASK_MIRROR_RIGHT) {
    VAR(EventMaskType, AUTOMATIC) Event;

    while(1)
    {
        (VAR(void, AUTOMATIC))WaitEvent(OSEvent_ChangeRight);
        Event = 0U;
        (VAR(void, AUTOMATIC))GetEvent(TASK_MIRROR_RIGHT, &Event);

        if( (Event & OSEvent_ChangeRight) > 0U ) {
            (VAR(void, AUTOMATIC))ClearEvent(OSEvent_ChangeRight);
            Rte_ChangeRight();
        } 
    }
}