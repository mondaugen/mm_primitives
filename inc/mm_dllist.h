#ifndef MM_DLLIST_H
#define MM_DLLIST_H 

typedef struct __MMDLList MMDLList;

struct __MMDLList {
    MMDLList *prev;
    MMDLList *next;
};

/* Insert who after whom and update pointers of who to point to previous
 * pointers of whom. */
static inline MMDLList *MMDLList_insertAfter(MMDLList *whom, MMDLList *who)
{
    if (!whom) {
        return NULL;
    }
    if (who) {
        who->next = whom->next;
        who->prev = whom;
    }
    whom->next = who;
    return whom;
}

/* Insert who before whom and update pointers of who to point to previous
 * pointers of whom. */
static inline MMDLList *MMDLList_insertBefore(MMDLList *whom, MMDLList *who)
{
    if (!whom) {
        return NULL;
    }
    if (who) {
        who->next = whom;
        who->prev = whom->prev;
    }
    whom->prev = who;
    return whom;
}

/* remove the item at address of who and return the address to it. The pointers
 * of who are still as they were before the removal (they still point to its
 * previous "prev" and "next" nodes. */
static inline MMDLList *MMDLList_remove(MMDLList *who)
{
    if (!who) {
        return NULL;
    }
    if (who->prev) {
        who->prev->next = who->next;
    }
    if (who->next) {
        who->next->prev = who->prev;
    }
    return who;
}

/* Insert who after whose's last node. */
static inline void MMDLList_addAfterTail(MMDLList *whose, MMDLList *who)
{
    while (whose->next) {
        whose = whose->next;
    }
    MMDLList_insertAfter(whose,who);
}
/* Insert who before whose's first node. */
static inline void MMDLList_addBeforeHead(MMDLList *whose, MMDLList *who)
{
    while (whose->prev) {
        whose = whose->prev;
    }
    MMDLList_insertBefore(whose,who);
}

#endif /* MM_DLLIST_H */