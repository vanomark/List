#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "ListDump.h"
#include "List.h"

#ifdef LIST_DEBUG
    #define ON_DEBUG(code) code 
#else
    #define ON_DEBUG(code)
#endif /* LIST_DEBUG */


int ListCtor(list *list, size_t size)
{   
    assert(list);

    list->data = (list_t *) calloc(size, sizeof(list_t));
    list->next = (size_t *) calloc(size, sizeof(size_t));
    list->prev = (size_t *) calloc(size, sizeof(size_t));

    list->next[0] = 0; 
    list->prev[0] = 0;

    for (size_t i = 1; i < LIST_SIZE; i++) {
        list->data[i] = POISON_VAL;
    }

    return 0;
}

int ListDtor(list *list) 
{   
    assert(list);

    free(list->data); list->data = NULL;
    free(list->next); list->next = NULL;
    free(list->prev); list->prev = NULL;

    return 0;
}

////====================================================================================================================

int ListInsert(list *list, list_t num, size_t index)
{
    assert(list);
    assert(list->data);
    assert(list->prev);
    assert(list->next);

    list->curr_size++;

    if (index >= list->curr_size) {
        RED_PRINT_LOG(stderr, "Insert index larger than list size\n");
        RED_PRINT_LOG(stderr, "The item will be pushed to the end of the list\n");
        index = list->curr_size;
    }

    if (index == 0) {
        RED_PRINT_LOG(stderr, "Insert index cannot be null\n");
        RED_PRINT_LOG(stderr, "The item will be pushed to the beginning of the list");
        index = 1;
    }
    
    list->data[list->curr_size] = num; //add elem to the end of the list
    
    list->prev[list->next[index - 1]] = list->curr_size;
    list->prev[list->curr_size] = index - 1;
    
    list->next[list->curr_size] = list->next[index - 1];
    list->next[index - 1]       = list->curr_size;
    
    ON_DEBUG(ListDump(list, "Graf.dot"));

    return 0;
}

int ListBack(list *list, list_t num) //func same as ListInsert but index = current size
{
    assert(list);
    assert(list->next);
    assert(list->prev);
    assert(list->data);

    list->curr_size++;

    list->data[list->curr_size] = num; //add elem to the end of the data array
    
    list->prev[list->next[list->curr_size - 1]] = list->curr_size;
    list->prev[list->curr_size]                 = list->curr_size - 1;
    
    list->next[list->curr_size]     = list->next[list->curr_size - 1];
    list->next[list->curr_size - 1] = list->curr_size;

    ON_DEBUG(ListDump(list, "Graf.dot"));

    return 0;
}

int ListPop(list *list, size_t index)
{
    assert(list);
    assert(list->data);
    assert(list->next);
    assert(list->prev);

    if (index >= list->curr_size) {
        RED_PRINT_LOG(stderr, "Remove index larger than list size\n");
        RED_PRINT_LOG(stderr, "The last list item will be removed\n");
        index = list->curr_size;
    }

    list->curr_size--;

    list->data[index] = POISON_VAL; //delete element

    list->prev[list->next[index]] = list->prev[index]; 

    list->next[list->prev[index]] = list->next[index];
    list->next[index] = 0;

    list->prev[list->next[index]] = index;
    list->prev[index] = 0;

    list->prev[0]--;

    ON_DEBUG(ListDump(list, "Graf.dot"));

    return 0;
}

