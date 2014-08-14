#include <stdlib.h> 
#include "mm_list.h"


/* Appends all the way at the end of the head list */
void MMList_append(MMList *head, MMList *tail)
{
    while (head->next) {
        head = head->next;
    }
    head->next = tail;
}

void MMList_init(MMList *head)
{
    head->next = NULL;
}

void MMList_free(MMList *head)
{
    MMList *next;
    while (head) {
        next = head->next;
        free(head);
        head = next;
    }
}
