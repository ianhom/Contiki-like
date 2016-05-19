static void do_event(void)
{
    static process_event_t ev;
    static process_data_t data;
    static struct process *receiver;
    static struct process *p;
  
  /*
   * If there are any events in the queue, take the first one and walk
   * through the list of processes to see if the event should be
   * delivered to any of them. If so, we call the event handler
   * function for the process. We only process one event at a time and
   * call the poll handlers inbetween.
   */

    if(nevents > 0) 
    {
    
        /* There are events that we should deliver. */
        ev = events[fevent].ev;
    
        data = events[fevent].data;
        receiver = events[fevent].p;

        /* Since we have seen the new event, we move pointer upwards and decrease the number of events. */
        fevent = (fevent + 1) % PROCESS_CONF_NUMEVENTS;
        --nevents;

        /* If this is a broadcast event, we deliver it to all events, in order of their priority. */
        if(receiver == PROCESS_BROADCAST) 
        {
            for(p = process_list; p != NULL; p = p->next) 
            {
	            /* If we have been requested to poll a process, we do this in between processing the broadcast event. */
	            if(poll_requested) 
	            {
	                do_poll();
	            }
	            call_process(p, ev, data);
            }
        } 
        else 
        {
            /* This is not a broadcast event, so we deliver it to the specified process. */
            /* If the event was an INIT event, we should also update the state of the process. */
            if(ev == PROCESS_EVENT_INIT) 
            {
	            receiver->state = PROCESS_STATE_RUNNING;
            }
        
            /* Make sure that the process actually is running. */
            call_process(receiver, ev, data);
        }
    }
}


int process_run(void)
{
    /* Process poll events. */
    if(poll_requested) 
    {
        do_poll();
    }

    /* Process one event from the queue */
    do_event();
    
    return nevents + poll_requested;
}
