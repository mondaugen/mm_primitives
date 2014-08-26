#ifndef MM_EVENT_H
#define MM_EVENT_H 

#include <stdint.h> 

typedef struct __MMEvent MMEvent;
typedef MMEvent * MMEventHandle;
typedef void (*MMEvent_CB_t)(MMEventHandle);

struct __MMEvent {
    MMEvent_CB_t   happen;
};

#define MMEvent_happen(event) (((MMEvent*)event)->happen((MMEvent*)event)) 

MMEvent *MMEvent_new();
void MMEvent_init(MMEvent *event, MMEvent_CB_t cb);

#endif /* MM_EVENT_H */
