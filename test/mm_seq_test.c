#include <stdlib.h> 
#include <stdio.h>
#include "mm_seq.h"
#include <pthread.h> 
#include <unistd.h>
#include <string.h> 

typedef struct __MMTestEvent MMTestEvent;
typedef struct __ThreadInfo ThreadInfo;

struct __MMTestEvent {
    MMEvent eventHead;
    char *msg;
};

struct __ThreadInfo {
    int exit;
    MMSeq sequence;
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
        MMSeq_doAllCurrentEvents(&(((ThreadInfo*)threadinfo)->sequence));
        if (MMSeq_checkIfEmpty(&(((ThreadInfo*)threadinfo)->sequence))) {
            ((ThreadInfo*)threadinfo)->exit = 1;
            continue;
        }
        MMSeq_tick(&(((ThreadInfo*)threadinfo)->sequence));
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
    MMSeq_init(&(threadinfo.sequence),0);
    char **ptr = strs;
    MMTime_Tick time = 0;
    while (*ptr) {
        MMTestEvent *event = MMTestEvent_new();
        MMTestEvent_init(event,*ptr);
        ptr++;
        MMHeap_Node *hn = (MMHeap_Node*)malloc(sizeof(MMHeap_Node));
        memset(hn,0,sizeof(MMHeap_Node));
        hn->key = time;
        hn->data = (void*)event;
        MMHeap_Manager_insertMinHeapNode(&(threadinfo.sequence.heapManager),hn);
        time += 500;
    }
    rc = pthread_create(&thread, NULL, tick, (void*)&threadinfo);
    if (rc) {
        fprintf(stderr, "Error %d creating thread\n", rc);
        exit(-1);
    }
    while (!threadinfo.exit)
        ; /* Just leave it running */
    pthread_exit(NULL);
}
