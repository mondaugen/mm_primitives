#include <stdlib.h> 
#include <stdio.h>
#include "mm_seq.h"
#include <pthread.h> 
#include <unistd.h>
#include <string.h> 
#include "mm_heap.h" 

typedef struct __MMTestEvent MMTestEvent;
typedef struct __ThreadInfo ThreadInfo;

struct __MMTestEvent {
    MMEvent eventHead;
    char *msg;
};

struct __ThreadInfo {
    int exit;
    MMSeq *sequence;
};

void MMTestEvent_happen(MMEvent *event)
{
    printf("%s\n",((MMTestEvent*)event)->msg);
    free(event);
}

MMTestEvent *MMTestEvent_new(void)
{
    return (MMTestEvent*)malloc(sizeof(MMTestEvent));
}

void MMTestEvent_init(MMTestEvent *event, char *str)
{
    event->msg = str;
    MMEvent_init((MMEvent*)event, MMTestEvent_happen);
}

void *tick(void *threadinfo)
{
    while (!(((ThreadInfo*)threadinfo)->exit)) {
        MMSeq_doAllCurrentEvents((((ThreadInfo*)threadinfo)->sequence));
        if (MMSeq_checkIfEmpty((((ThreadInfo*)threadinfo)->sequence))) {
            ((ThreadInfo*)threadinfo)->exit = 1;
            continue;
        }
        MMSeq_tick((((ThreadInfo*)threadinfo)->sequence));
        usleep(1000);
    }
    pthread_exit(NULL);
}

int main (void) 
{
    int rc;
    pthread_t thread;
    ThreadInfo threadinfo;
    char *strs[] = {
        "why",
        "you",
        "got",
        "to",
        "be",
        "sooo",
        "crazed",
        NULL
    };

    threadinfo.exit = 0;
    threadinfo.sequence = MMSeq_new();
    MMSeq_init(threadinfo.sequence,0);
    char **ptr = strs;
    MMTime time = 0;
    while (*ptr) {
        MMTestEvent *event = MMTestEvent_new();
        MMTestEvent_init(event,*ptr);
        ptr++;
        MMSeq_scheduleEvent(threadinfo.sequence,(MMEvent*)event,time);
        time += 500;
    }
    rc = pthread_create(&thread, NULL, tick, (void*)&threadinfo);
    if (rc) {
        fprintf(stderr, "Error %d creating thread\n", rc);
        exit(-1);
    }
    while (!threadinfo.exit)
        ; /* Just leave it running */
    MMSeq_free(threadinfo.sequence);
    pthread_exit(NULL);
    return 0;
}
