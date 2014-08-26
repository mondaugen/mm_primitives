#ifndef MM_SEQ_H
#define MM_SEQ_H 

#include "mm_staticqueue.h" 
#include "mm_time.h" 
#include "mm_event.h" 

#define MM_HEAP_KEY_TYPE MMTime_Tick

#include "mm_heap__static.h" 

typedef struct __MMSeq MMSeq;

struct __MMSeq {
    MMHeap_Manager   heapManager;
    MMTime_Tick      currentTime;
    MMStaticQueue *pendingEvents;
};

MMSeq *MMSeq_new(void);
void MMSeq_init(MMSeq *seq, size_t maxPendingItems);
void MMSeq_free(MMSeq *seq);
void MMSeq_tick(MMSeq *seq);
MMEvent *MMSeq_getCurrentEvent(MMSeq *seq);
int MMSeq_checkIfEmpty(MMSeq *seq);
void MMSeq_doAllCurrentEvents(MMSeq *seq);
void MMSeq_loadCurrentEvents(MMSeq *seq);

#endif /* MM_SEQ_H */
