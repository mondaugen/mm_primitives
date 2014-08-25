#include <stdlib.h> 
#include "mm_event.h" 


MMEvent *MMEvent_new()
{
    return (MMEvent*)malloc(sizeof(MMEvent));
}

void MMEvent_init(MMEvent *event, MMEvent_CB_t cb)
{
    event->happen = cb;
}
