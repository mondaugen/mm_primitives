#include <stdlib.h> 
#include "mm_eventlist.h"

void MMEventList_init(MMEventList *head, MMEventHandle eventHandle)
{
    MMList_init((MMList *)head);
    head->eventHandle = eventHandle;
}

MMEventList *MMEventList_new(void)
{
    MMEventList *result;
    result = (MMEventList *)malloc(sizeof(MMEventList));
    return result;
}

