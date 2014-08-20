#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 
#include "ne_tester.h"
#include "mm_dllist.h" 

typedef struct __MMDLList_Tester MMDLList_Tester;

struct __MMDLList_Tester {
    NETester testHead;
    MMDLList list;
};

int MMDLList_insertAfter_test(NETester *t)
{
    int result = 1;
    MMDLList *newList = (MMDLList*)malloc(sizeof(MMDLList));
    memset(newList,0,sizeof(MMDLList));
    result = (MMDLList_insertAfter(((MMDLList_Tester*)t)->list.next, newList)
            == NULL) && result;
    NETester_progPrint(result,stdout);
    result = (MMDLList_insertAfter(&(((MMDLList_Tester*)t)->list), newList)
            == &(((MMDLList_Tester*)t)->list)) && result;
    NETester_progPrint(result,stdout);
    result = (((MMDLList_Tester*)t)->list.next == newList) && result;
    NETester_progPrint(result,stdout);
    result = (((MMDLList_Tester*)t)->list.next->prev == &(((MMDLList_Tester*)t)->list))
            && result;
    NETester_progPrint(result,stdout);
    result = (((MMDLList_Tester*)t)->list.next->next == NULL) && result;
    NETester_progPrint(result,stdout);
    newList = MMDLList_remove(((MMDLList_Tester*)t)->list.next);
    result = (((MMDLList_Tester*)t)->list.next == NULL) && result;
    NETester_progPrint(result,stdout);
    free(newList);
    return result;
}

int MMDLList_insertBefore_test(NETester *t)
{
    int result = 1;
    MMDLList *newList = (MMDLList*)malloc(sizeof(MMDLList));
    memset(newList,0,sizeof(MMDLList));
    result = (MMDLList_insertBefore(((MMDLList_Tester*)t)->list.next, newList)
            == NULL) && result;
    NETester_progPrint(result,stdout);
    result = (MMDLList_insertBefore(&(((MMDLList_Tester*)t)->list), newList)
            == &(((MMDLList_Tester*)t)->list)) && result;
    NETester_progPrint(result,stdout);
    result = (((MMDLList_Tester*)t)->list.prev == newList) && result;
    NETester_progPrint(result,stdout);
    result = (((MMDLList_Tester*)t)->list.prev->next == &(((MMDLList_Tester*)t)->list))
            && result;
    NETester_progPrint(result,stdout);
    result = (((MMDLList_Tester*)t)->list.prev->prev == NULL) && result;
    NETester_progPrint(result,stdout);
    newList = MMDLList_remove(((MMDLList_Tester*)t)->list.prev);
    result = (((MMDLList_Tester*)t)->list.prev == NULL) && result;
    NETester_progPrint(result,stdout);
    free(newList);
    return result;
}

int MMDLList_addAfterTail_test(NETester *t)
{
    int result = 1;
    MMDLList *listHead = &(((MMDLList_Tester*)t)->list);
    MMDLList *newList1 = (MMDLList*)malloc(sizeof(MMDLList));
    memset(newList1,0,sizeof(MMDLList));
    MMDLList *newList2 = (MMDLList*)malloc(sizeof(MMDLList));
    memset(newList2,0,sizeof(MMDLList));
    MMDLList_addAfterTail(listHead,newList1);
    result = (listHead->next == newList1) && result;
    NETester_progPrint(result,stdout);
    result = (listHead->next->prev == listHead) && result;
    NETester_progPrint(result,stdout);
    result = (listHead->next->next == NULL) && result;
    NETester_progPrint(result,stdout);
    MMDLList_addAfterTail(listHead,newList2);
    result = (listHead->next->next == newList2) && result;
    NETester_progPrint(result,stdout);
    newList1 = MMDLList_remove(listHead->next);
    free(newList1);
    result = (listHead->next == newList2) && result;
    NETester_progPrint(result,stdout);
    newList2 = MMDLList_remove(listHead->next);
    free(newList2);
    result = (listHead->next == NULL) && result;
    NETester_progPrint(result,stdout);
    return result;
}

int MMDLList_addBeforeHead_test(NETester *t)
{
    int result = 1;
    MMDLList *listHead = &(((MMDLList_Tester*)t)->list);
    MMDLList *newList1 = (MMDLList*)malloc(sizeof(MMDLList));
    memset(newList1,0,sizeof(MMDLList));
    MMDLList *newList2 = (MMDLList*)malloc(sizeof(MMDLList));
    memset(newList2,0,sizeof(MMDLList));
    MMDLList_addBeforeHead(listHead,newList1);
    result = (listHead->prev == newList1) && result;
    NETester_progPrint(result,stdout);
    result = (listHead->prev->next == listHead) && result;
    NETester_progPrint(result,stdout);
    result = (listHead->prev->prev == NULL) && result;
    NETester_progPrint(result,stdout);
    MMDLList_addBeforeHead(listHead,newList2);
    result = (listHead->prev->prev == newList2) && result;
    NETester_progPrint(result,stdout);
    newList1 = MMDLList_remove(listHead->prev);
    free(newList1);
    result = (listHead->prev == newList2) && result;
    NETester_progPrint(result,stdout);
    newList2 = MMDLList_remove(listHead->prev);
    free(newList2);
    result = (listHead->prev == NULL) && result;
    NETester_progPrint(result,stdout);
    return result;
}

int main(void)
{
    NETester_Test tests[] = {
        MMDLList_insertAfter_test,
        MMDLList_insertBefore_test,
        MMDLList_addAfterTail_test,
        MMDLList_addBeforeHead_test,
        NULL
    };

    MMDLList_Tester dllt;
    memset(&dllt,0,sizeof(MMDLList_Tester));
    ((NETester*)&dllt)->tests = tests;
    if (NETester_doTests((NETester*)&dllt)) {
        return 0;
    } else {
        return 1; /* Tests failed. */
    }
}
    



