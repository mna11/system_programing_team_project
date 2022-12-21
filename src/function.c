#include "function.h"

LINK char_to_list(char s) { // 데이터가 char인 헤드 주소
    LINK head;
    head = malloc(sizeof(ELEMENT));
    head->d = s;
    head->next = NULL;
    head->prev = NULL;

    //[손댄부분]
    head->cnt = 0;
    head->digit = 0;
    head->dot = -1;
    head->next_top = 0;
    head->next_rear = 0;

    return head;
}

unsigned long long int count(LINK head) { // LINK 길이
    unsigned long long int cnt = 0; //[손댄부분] 변수명이 없었음, double int 형이길래 double 지웠습니다.
    for (; head != NULL; head = head->next)
        cnt++;
    return cnt;
}

void digit_matching_list(LINK head) { //[손댄부분] 자릿수 세팅을 위해 추가했습니다.
    int cnt = head->cnt = count(head);
    int dot = head->dot = head->dot != -1 ? head->dot : cnt; //점이 없을 경우 그냥 뒤집어주는 것임
    int n = 3; //부호는 카운트하지 않는다는 점을 고려해서 적절한 값을 넣음
    for (LINK p = head; p != NULL; p = p->next) {
        if (isdigit(p->d) || p->d == '.') {
            p->digit = dot - n++; // 식은 cnt - (cnt - dot) - n이다. 예시를 들면 123.12의 cnt = 5, dot = 3이므로 1의 자릿수는 5 - (5 - 3) - 1 = 2이다. 그러므로 123.12의 수의 각각 자릿수는 2 1 0 -1 -1 -2이다.  
            if (p->d == '.') n--; //소수점 아래 첫번째 수가 자릿수가 -1이어야 하므로
        }
        else {
            p->digit = 0;
        }
    }
}

void print_list_test(LINK head) // [손댄부분] 테스트 출력용
{
    printf("[%lld %lld] ", head->cnt, head->dot);
    for (LINK p = head; p != NULL; p = p->next) { //리스트 끝까지 출력함
        printf("%c[%lld] <-> ", p->d, p->digit);
    }
    printf("NULL \n");
}

void print_list(LINK head) { // 연결리스트 출력
    if (head == NULL);
    else { printf("%c", head->d); print_list(head->next); }
}

void erase(LINK head) { // 소수점 아래 필요없는 0 제거
    LINK header = head; //[손댄부분]
    head = last_link(head);
    while (head->d != '.' && head->d == '0') {
        header->dot--; //[손댄부분] 설명은 minus.c의 "뒤 0 없애기" 파트
        LINK store = head->prev;
        del_link(head);
        head = store;
    }
}

void print_answer(LINK head) {// Linked list 깔끔하게 출력
    for (; head != NULL; head = head->next) {
        if (head->d == '+')
            continue;
        if (head->d == '.' && head->next == NULL)
            break;
        printf("%c", head->d);
    }
}

void connect(LINK a, LINK b) { // a에 b 붙이기
    if (a->next == NULL) {
        a->next = b;
        b->prev = a;
    }
    else {
        connect(a->next, b); //[손댄부분] concatenate(a->next, b)인데 오타라고 생각해 수정했습니다, 오타가 아닐시 고쳐주시면 감사합니다.
    }
}

LINK insert(LINK p1, char x) {  // p1 뒤에 x 끼워넣기
    LINK q = char_to_list(x);
    if (p1->next == NULL) {
        p1->next = q;
        q->prev = p1;
    }
    else {
        q->next = p1->next;
        p1->next->prev = q;
        p1->next = q;
        q->prev = p1;
    }
    return q; //[손댄부분] 끼워넣고 반환하게 만들었습니다.
}

void del_link(LINK p) { // p 삭제 (head는 불가능)
    if (p->next == NULL) {
        p->prev->next = NULL;
        free(p);
    }
    else {
        p->prev->next = p->next;
        p->next->prev = p->prev;
        free(p);
    }
}

LINK copy_link(LINK b) { // b 복사 후 반환
    LINK a = char_to_list(b->d);
    LINK p = a;
    b = b->next;
    for (; b != NULL; b = b->next) {
        insert(p, b->d);
        p = p->next;
    }
    return a;
}

char compare(LINK x, LINK y) { // 두 수 비교,  1:a가 더 큼 , 2:b가 더 큼,  3:같음
    LINK a = x->next;
    LINK b = y->next;

    while ((a != NULL && b != NULL) && (a->d != '.' || b->d != '.')) {
        if (a->d == '.')
            return 2;
        if (b->d == '.')
            return 1;
        a = a->next;
        b = b->next;
    }

    a = x->next;
    b = y->next;
    while (a != NULL && b != NULL) {
        if (a == NULL)
            return 2;

        if (b == NULL)
            return 1;

        if (a->d > b->d)
            return 1;

        if (a->d < b->d)
            return 2;

        a = a->next;
        b = b->next;
    }
    return 3;
}

LINK small_fill(LINK x, LINK y) {   // 작은 수의 앞자리에 0 채워서 큰 수와 자릿수 맞추기
    LINK first = x;
    LINK second = y;

    unsigned long long len1, len2;
    len1 = len2 = 0;

    for (; first->d != '.'; first = first->next) // [손댄부분] first가 아니라 a라 적혀있길래 고침
        len1++;

    for (; second->d != '.'; second = second->next)
        len2++;

    if (len1 == len2)
        return y;

    unsigned long long len = len1 - len2;

    LINK zero = char_to_list('0');
    while (len-- > 0) {
        zero = insert(zero, '0'); //[손댄 부분]
    }

    connect(zero, y);
    return zero;
}

void downzero(LINK x, LINK y) { // 소수점 자리 0 채워서 맞춰주기
    LINK a = last_link(x);
    LINK b = last_link(y);
    for (; a->d != '.'; a = a->prev);
    for (; b->d != '.'; b = b->prev);
    while (a != NULL || b != NULL) {
        if (a->next != NULL && b->next == NULL)
            insert(b, '0');
        if (a->next == NULL && b->next != NULL)
            insert(a, '0');
        a = a->next; b = b->next;
    }
}

LINK last_link(LINK head) {  // Linked list의 맨 마지막 주소 반환
    for (; head->next != NULL; head = head->next);
    return head;
}


void free_all(LINK a) { // Linked list 데이터 전부 free
    if (a == NULL) return;
    free_all(a->next);
    free(a);
}