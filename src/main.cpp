#include <stdio.h>
#include <stdlib.h>

#include "List.h"
#include "ListDump.h"


int main()
{   
    list Lst = {};
    ListCtor(&Lst, LIST_SIZE);

    ListDump(&Lst, "Graf.dot");

    ListInsert(&Lst, 18, 100);
    ListInsert(&Lst, 69, 100);
    ListInsert(&Lst, 228, 100);
    ListInsert(&Lst, 34, 2);
    ListInsert(&Lst, 1488, 100);
    ListInsert(&Lst, 7, 2);
    ListInsert(&Lst, 1234, 100);

    ListPop(&Lst, 4U);
    ListPop(&Lst, 3U);

    ListDtor(&Lst);
                                
    #ifdef LIST_DEBUG                      //!!!!!!!!/
    FILE* FP = fopen("Graf.dot", "a");     //!DANGER!//
    fprintf(FP, "}");                      //! VERY !//
    fclose(FP);                            //!STUPID!// 
    system("dot Graf.dot -Tsvg -o Graf.svg");//!!!!!/!
    #endif

    system("rm Graf.dot");

    return 0;
}