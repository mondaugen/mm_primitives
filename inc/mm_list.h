#ifndef MM_LIST_H
#define MM_LIST_H

#define MMList_getNext(pmml) (((MMList*)pmml)->next) 

typedef struct __MMList MMList;

struct __MMList {
    MMList *next;
};

void MMList_append(MMList *head, MMList *tail);
void MMList_init(MMList *head);
void MMList_free(MMList *head);
#endif /* MM_LIST_H */
