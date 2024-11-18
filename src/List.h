#ifndef LIST_H
#define LIST_H


//====================================================================================================================//
#define LIST_DEBUG                                                                                                  //
//====================================================================================================================//

#include "ColorPrintFile.h"

typedef int list_t;

struct list {
    list_t *data;
    size_t *next; //the null-index element points to the first logical item 
    size_t *prev; //the null-index element points to the last  logical item
    size_t curr_size;
    size_t free;
};

int ListCtor  (list *Lst, size_t size);
int ListDtor  (list *Lst);
int ListBack  (list *Lst, list_t num);
int ListInsert(list *Lst, list_t num, size_t index);
int ListPop   (list *Lst, size_t index);

const size_t STACK_SIZE = 8;
const size_t  LIST_SIZE = 10;

const list_t POISON_VAL = -666;

// ============== DSL ==============


#endif /* LIST_H */