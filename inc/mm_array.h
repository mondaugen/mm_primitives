#ifndef MM_ARRAY_H
#define MM_ARRAY_H 

#include <stdlib.h> 
#include <stddef.h>  

typedef struct __MMArray MMArray;

struct __MMArray {
    size_t length;
    void    *data;
};

/* array needs to be a pointer to an array */
#define MMArray_get(array,type,index) ((type *)(((MMArray*)array)->data))[index]
#define MMArray_set(array,type,index,value) MMArray_get(array,type,index) = value 
#define MMArray_set_data(a,d) ((MMArray*)a)->data = d 
#define MMArray_set_length(a,l) ((MMArray*)a)->length = l
#define MMArray_get_data(a) ((MMArray*)a)->data
#define MMArray_get_length(a) ((MMArray*)a)->length

static inline MMArray *MMArray_new(size_t length, size_t typeSize)
{
    MMArray *result = (MMArray*)malloc(sizeof(MMArray));
    result->data = malloc(typeSize * length);
    result->length = length;
    return result;
}

/* Accepts a pointer to an array and initializes the data with enough memory to
 * store "length" of your type. Pass the size of your datatype */
#define MMArray_init(array,length,typeSize) do { \
    ((MMArray*)array)->data = malloc(typeSize * length); \
    ((MMArray*)array)->length = length; \
} while (0)

#endif /* MM_ARRAY_H */
