#include "list.h"

//각 함수별 용도 설명은 헤더파일에 있음

FC* head_insert(FC* head, char value) {
	head->data = value;
	return head;
}

FC* insertVal(FC* pre, char value) {
	FC* p = (FC*)malloc(sizeof(FC));
	p->data = value;
	pre->next = p; //새로 다음 리스트 공간을 만들고 이어 붙임 
	return p; // 이어 붙인 리스트 공간을 반환함 
}


void print_list(FC* head)
{
	for (FC* p = head; p != NULL; p = p->next) //리스트 끝까지 출력함
		printf("%c -> ", p->data);
	printf("NULL \n");
}