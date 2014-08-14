#ifndef MM_EVENTLIST_H
#define MM_EVENTLIST_H 

#include "mm_list.h" 
#include "mm_event.h"

typedef struct __MMEventList MMEventList;

struct __MMEventList {
    MMList base;
    MMEventHandle eventHandle;
};

void MMEventList_init(MMEventList *head, MMEventHandle eventHandle);
MMEventList *MMEventList_new(void);

#endif /* MM_EVENTLIST_H */
