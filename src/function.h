#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef char DATA;
struct linked_list {
    DATA d;
    unsigned long long int digit, dot, cnt;
    struct linked_list* next, * prev, * next_top, *next_rear;
};
typedef struct linked_list ELEMENT;
typedef ELEMENT* LINK;


LINK char_to_list(char s); // 데이터가 char인 헤드 주소
unsigned long long int count(LINK head); // LINK 길이
void print_list(LINK head); // 연결리스트 출력
void print_list_test(LINK head); //[손댄부분] 테스트 출력용
void erase(LINK head); // 소수점 아래 필요없는 0 제거
void print_answer(LINK head); // Linked list 깔끔하게 출력
void digit_matching_list(LINK head); //[손댄부분] 자릿수 세팅
void connect(LINK a, LINK b); // a에 b 붙이기
LINK insert(LINK p1, char x);  // p1 뒤에 x 끼워넣기
void del_link(LINK p); // p 삭제 (head는 불가능)
LINK copy_link(LINK b); // b 복사 후 반환
char compare(LINK x, LINK y); // 두 수 비교,  1:a가 더 큼 , 2:b가 더 큼,  3:같음
LINK small_fill(LINK x, LINK y); // 작은 수의 앞자리에 0 채워서 큰 수와 자릿수 맞추기
void downzero(LINK x, LINK y); // 소수점 자리 0 채워서 맞춰주기
LINK last_link(LINK head); // Linked list의 맨 마지막 주소 반환
void free_all(LINK a); // Linked list 데이터 전부 free
