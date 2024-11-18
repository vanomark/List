#include <assert.h>
#include <stdio.h>

#include "ListDump.h"
#include "List.h"


int ListDump(list *list, const char* DumpFile) 
{   
    assert(list);
    assert(DumpFile);
//!====================================================================//
    static size_t num_of_func_calls = 0;                      //!DANGER//
    num_of_func_calls++;                                      // !ZONE //  
//!====================================================================//
    fprintf(stderr, "data: ");
    for (size_t i = 0; i < LIST_SIZE; i++) {
        fprintf(stderr, "%d ", list->data[i]); 
    }

    fprintf(stderr, "\nnext: ");
    for (size_t i = 0; i < LIST_SIZE; i++) {
        fprintf(stderr, "%lu ", list->next[i]); 
    }

    fprintf(stderr, "\nprev: ");
    for (size_t i = 0; i < LIST_SIZE; i++) {
        fprintf(stderr, "%lu ", list->prev[i]); 
    }

    GREEN_PRINT_LOG(stderr, "prev[0] = %lu\n", list->prev[0]); 

    FILE* Graf = fopen(DumpFile, "a");
    assert(Graf);

    if (num_of_func_calls == 1)
        fprintf(Graf, "digraph G{\n");
    
    fprintf(Graf, "\trankdir=LR;\n"
                  "\tedge[color=\"#1e2460\"];\n"
                  "\tsubgraph cluster%lu {\n"
                  "\t\tstyle = filled;\n"
		          "\t\tcolor = \"#ebd1d7\";\n", num_of_func_calls);
    
    for (size_t i = 0; i < LIST_SIZE; i++) {
        
        if (list->data[i] != POISON_VAL) 
            fprintf(Graf, "\t\t_%lu%lu -> _%lu%lu;\n", i,             num_of_func_calls, 
                                                       list->next[i], num_of_func_calls);

        fprintf(Graf, "\t\t_%lu%lu [shape=record,label=\"  %lu|data = %d|next = %lu|prev = %lu \", style=filled," 
                      "color=\"#050505\", fontcolor=\"#0a2033\", fillcolor=\"#6c4675\" ];\n",
                      i, num_of_func_calls, i, list->data[i], list->next[i], list->prev[i]);
    }

    fprintf(Graf, "\t\tedge[color=\"#960018\"]\n");

    for (size_t i = 0; i < LIST_SIZE; i++) {
        if (list->data[i] != POISON_VAL) 
            fprintf(Graf, "\t\t_%lu%lu -> _%lu%lu;\n", list->prev[i], num_of_func_calls, 
                                                                   i, num_of_func_calls);
    }
    fprintf(Graf, "\t\tedge[color=\"#ebd1d7\", arrowhead = none];\n");
    
    for (size_t i = 1; i < LIST_SIZE; i++) {
        fprintf(Graf, "\t\t_%lu%lu -> _%lu%lu [weight = 1000, arrowsize = 0];\n", i - 1, num_of_func_calls, 
                                                                                i,     num_of_func_calls);
    }

    fprintf(Graf, "\t}\n");

    fclose(Graf);

    // if (strcmp(DumpFile, "Graf.dot") == 0) {
    //     fprintf(stderr, "\nInputting system command\n");
    //     system("echo dot Graf.dot -Tsvg -o Graf.svg");
    //     system("dot Graf.dot -Tsvg -o Graf.svg");
    // } else {
    //     fprintf(stderr, "Unexpected dot file was given\n");
    // }

    WHITE_PRINT("\nListDump has ended, press [ENTER] to continue\n");
    getchar();


    return 0;
}

int ListVerf(list *list)
{
    if (!list) {
        fprintf(stderr, "ERROR = %d\n", 1);
        return 1;
    }

    if (!list->data || !list->next || !list->prev) {
        fprintf(stderr, "ERROR = %d\n", 2);
        return 2;
    }

    if (list->next[0] >= LIST_SIZE || list->prev[0] >= LIST_SIZE) {
        fprintf(stderr, "ERROR = %d\n", 4);
        return 4;
    }

    return 0;
}