#include <stdlib.h> 
#include <stdio.h>
#include "mm_seq.h"
#include <pthread.h> 
#include <unistd.h>
#include <string.h> 
#include "mm_heap.h"
#include <ctype.h> 

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
    free(event->msg);
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
        MMSeq_tick((((ThreadInfo*)threadinfo)->sequence));
        usleep(1000);
    }
    pthread_exit(NULL);
}

/* parses commands of the form "time" "string", returns a pointer to the start
 * of the string and puts the time in ptime. The string returned cannot be
 * freed, but you can copy it if you want to store it. */
char *parseCommand(char *str,MMTime_Tick *time)
{
    while (isspace(*str)) {
        str++;
    }
    if (!isdigit(*str)) {
        return NULL;
    }
    *time = (MMTime_Tick)strtol(str,&str,10);
    while (isspace(*str)) {
        str++;
    }
    char *tmp;
    for (tmp = str; *tmp != '\0'; tmp++) {
        if (*tmp == '\n') {
            *tmp = '\0';
            break;
        }
    }
    return str;
}

int main (void) 
{
    int rc;
    pthread_t thread;
    ThreadInfo threadinfo;
    threadinfo.exit = 0;
    threadinfo.sequence = MMSeq_new();
    MMSeq_init(threadinfo.sequence,0);
    MMTime_Tick time = 0;
    char buf[100];

    rc = pthread_create(&thread, NULL, tick, (void*)&threadinfo);
    if (rc) {
        fprintf(stderr, "Error %d creating thread\n", rc);
        exit(-1);
    }
    while (!threadinfo.exit) {
        fgets(buf,100,stdin);
        char *str;
        if (strncmp(buf,"exit",4) == 0) {
            threadinfo.exit = 1;
        } else if (!(str = parseCommand(buf,&time))) {
            fprintf(stderr,"Bad command.\n");
        } else {
            char *tmp = (char*)malloc(strlen(str));
            strcpy(tmp,str);
            MMTestEvent *event = MMTestEvent_new();
            MMTestEvent_init(event,tmp);
            MMSeq_scheduleEvent(threadinfo.sequence,(MMEvent*)event,
                    MMSeq_getCurrentTime(threadinfo.sequence) + time);
        }
    }
    MMSeq_free(threadinfo.sequence);
    pthread_exit(NULL);
    return 0;
}
