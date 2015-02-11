#ifndef MM_SEQ_H
#define MM_SEQ_H 

#include "mm_staticqueue.h" 
#include "mm_event.h" 
#include "mm_time.h" 

/* NOTE: Because we forward declare the structure (the user shouldn't know or
 * care what's inside of it), you can only declare pointers to it, never the
 * structure proper. */
struct __MMSeq;

typedef struct __MMSeq MMSeq;

MMSeq *MMSeq_new(void);
void MMSeq_init(MMSeq *seq, size_t maxPendingItems);
void MMSeq_free(MMSeq *seq);
void MMSeq_tick(MMSeq *seq);
MMEvent *MMSeq_getCurrentEvent(MMSeq *seq);
int MMSeq_checkIfEmpty(MMSeq *seq);
void MMSeq_doAllCurrentEvents(MMSeq *seq);
void MMSeq_loadCurrentEvents(MMSeq *seq);
void MMSeq_scheduleEvent(MMSeq *seq, MMEvent *ev, MMTime time);
MMTime MMSeq_getCurrentTime(MMSeq *seq);

#endif /* MM_SEQ_H */
