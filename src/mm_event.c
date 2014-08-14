#include <stdlib.h> 
#include "mm_event.h" 

void MMEvent_init(MMEventHandle *eventHandle, MMEvent_Time_t time, MMEvent_CB_t cb)
{
    *eventHandle = (MMEventHandle)malloc(sizeof(MMEvent));
    ((MMEventHandle)*eventHandle)->time = time;
    ((MMEventHandle)*eventHandle)->onTimeReached = cb;
}
