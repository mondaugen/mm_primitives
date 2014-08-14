#include <stdlib.h>
#include <stdio.h> 
#include <time.h> 
#include "mm_eventlist.h"

#define NUM_EVENTS 100 

void MMTest_eventCB(MMEventHandle event)
{
    printf("Event at time %llu\n", event->time);
}

void initWithEvent(MMEventList *el)
{
    MMEventList_init(el,NULL);
    MMEvent_init(&(el->eventHandle),rand(),&MMTest_eventCB);
}


void appendSomeEvent(MMEventList *el)
{
    MMEventList *new;
    new = MMEventList_new();
    initWithEvent(new);
    MMList_append((MMList*)el,(MMList*)new);
}

int main (void)
{
    srand(time(NULL));
    MMEventList *el;
    el = MMEventList_new();
    initWithEvent(el);
    size_t i;
    for (i = 0; i < NUM_EVENTS; i++) {
        appendSomeEvent(el);
    }
    for (  ; el != NULL; el = (MMEventList*)MMList_getNext(el)) {
        (el->eventHandle->onTimeReached)(el->eventHandle);
        free(el->eventHandle);
    }
    MMList_free((MMList*)el);
    return 0;
}


