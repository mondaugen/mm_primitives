#ifndef MM_SEQ_H
#define MM_SEQ_H 
#endif /* MM_SEQ_H */

#include "mm_time.h" 

#define  MM_HEAP_KEY_TYPE MMTime_Tick;

#include "mm_heap.h" 

typedef struct __MMSeq MMSeq;

struct __MMSeq {
    MMHeap_Manager   heapManager;
    MMTime_Tick      currentTime;
    MMStaticQueue *pendingEvents;
};





