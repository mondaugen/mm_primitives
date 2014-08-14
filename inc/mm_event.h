#ifndef MM_EVENT_H
#define MM_EVENT_H 

#include <stdint.h> 

#define MMEvent_MEMBERS 
typedef struct __MMEvent MMEvent;
typedef MMEvent * MMEventHandle;
typedef uint64_t MMEvent_Time_t;
typedef void (*MMEvent_CB_t)(MMEventHandle);

struct __MMEvent {
    MMEvent_Time_t time;
    MMEvent_CB_t   onTimeReached;
};

void MMEvent_init(MMEventHandle *eventHandle, MMEvent_Time_t time, MMEvent_CB_t cb);

#endif /* MM_EVENT_H */
