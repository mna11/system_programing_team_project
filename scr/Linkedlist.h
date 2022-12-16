#include <stdio.h>
#include "polynomial.h"

LinkedList    *minus(LinkedList *aList, LinkedList *bList) // 다항식의 뺏셈
{
    LinkedList    *newList = createPolynomialList();
    alloc_calc_node(newList, aList, 0);
    alloc_calc_node(newList, bList, 1);
    return (newList);
}

#include "polynomial.h"

void alloc_calc_node(LinkedList *new_list, LinkedList *base_list, int flag)
{
    ListNode    *base_head;
    ListNode    *new_node;
    int            baseidx = base_list->currentElementCount; // 연산을 위해 base list node 갯수를 저장한다.

    base_head = base_list->headerNode.pRLink;
    new_node = malloc(sizeof(ListNode));
    while(baseidx--) {
        new_node->degree = base_head->degree;
        if (flag)
            new_node->coef = -(base_head->coef);
        else
            new_node->coef = base_head->coef;
        addPLElement(new_list, *new_node); // node를 새로운 list에 할당한다.
        base_head = base_head->pRLink;
    }
    free(new_node);
    new_node = NULL;
    deletePolynomialList(base_list);
    base_list = NULL;
}
