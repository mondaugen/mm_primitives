#include "mm_seq.h"
#include <stdlib.h> 

#define MM_HEAP_KEY_TYPE MMTime_Tick

#include "mm_heap__static.h" 

struct __MMSeq {
    MMHeap_Manager   heapManager;
    MMTime_Tick      currentTime;
    MMStaticQueue *pendingEvents;
};

MMSeq *MMSeq_new(void)
{
    return (MMSeq*)malloc(sizeof(MMSeq));
}

void MMSeq_init(MMSeq *seq, size_t maxPendingItems)
{
    MMHeap_Manager_init(&(seq->heapManager));
    seq->currentTime = 0;
    if (maxPendingItems) {
        seq->pendingEvents = MMStaticQueue_new(maxPendingItems);
    } else {
        seq->pendingEvents = NULL;
    }
}

void MMSeq_free(MMSeq *seq)
{
    MMHeap_freeAll(seq->heapManager.top);
    free(seq->pendingEvents);
    free(seq);
}

void MMSeq_tick(MMSeq *seq)
{
    (seq->currentTime)++;
}

/* If the current time is greater or equal to a time of an event in the
 * sequence, it removes this event from the sequence and returns a pointer to
 * the event. Otherwise it returns NULL. This can be used to pop all the events
 * that are scheduled to happen at the current time. */
MMEvent *MMSeq_getCurrentEvent(MMSeq *seq)
{
    if (seq->heapManager.top && (seq->heapManager.top->key <= seq->currentTime)) {
        MMHeap_Node *minNode = MMHeap_Manager_removeMin(&(seq->heapManager));
        MMEvent *result = (MMEvent*)minNode->data;
        free(minNode);
        return result;
    }
    return NULL;
}

/* Check if the sequencer is empty */
int MMSeq_checkIfEmpty(MMSeq *seq)
{
    return (seq->heapManager.top) ? 0 : 1;
}

/* Don't queue up the events, instead just do them all */
void MMSeq_doAllCurrentEvents(MMSeq *seq)
{
    MMEvent *current;
    while ((current = MMSeq_getCurrentEvent(seq))) {
        MMEvent_happen(current);
    }
}

void MMSeq_loadCurrentEvents(MMSeq *seq)
{
    while (1) {
        MMEvent *event = MMSeq_getCurrentEvent(seq);
        if (!event) {
            return;
        }
        if (MMStaticQueue_push(seq->pendingEvents,(void*)event)) {
            /* queue full, just discard event (what a shame...) */
            free(event);
            /* we could instead reschedule... */
        }
    }
}

void MMSeq_scheduleEvent(MMSeq *seq, MMEvent *ev, MMTime_Tick time)
{
    MMHeap_Node *hn = (MMHeap_Node*)malloc(sizeof(MMHeap_Node));
    memset(hn,0,sizeof(MMHeap_Node));
    hn->key = time;
    hn->data = (void*)ev;
    MMHeap_Manager_insertMinHeapNode(&(seq->heapManager),hn);
}

MMTime_Tick MMSeq_getCurrentTime(MMSeq *seq)
{
    return seq->currentTime;
}

/* TODO: Make a function that does queued events... maybe not needed */

