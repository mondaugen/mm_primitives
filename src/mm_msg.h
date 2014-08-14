#ifndef MM_MSG_H
#define MM_MSG_H 

/* An abstract message "class" */
typedef struct __MMMsg MMMsg;

struct __MMMsg {
    void (*call)(MMMsg *,void *);
};

#endif /* MM_MSG_H */
