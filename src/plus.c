#include "plus.h"

LINK plus(LINK a, LINK b) {
    LINK ans;
    LINK num_copy;
    LINK num1;
    LINK num2;
    char buho; //부호 (+,- : 1,0)
    char big_num; //비교값 (1,2,3)
    unsigned long long int point_count = 0; //점의 위치(0~)
    char now = 0; // 계산파트에서의 현재값
    char up = 0; // 계산파트에서의 올림값

    big_num = compare(a, b);

    if (big_num == 2) { // b가 더 크면 b가 a로 이동
        num_copy = a;
        a = b;
        b = num_copy;
    }

    buho = a->d == '+' ? 1 : 0;  // +면 1, -면 0

    num1 = a->next; num1->prev = NULL; free(a);
    num2 = b->next; num2->prev = NULL; free(b);

    num2 = small_fill(num1, num2);

    downzero(num1, num2);

    a = last_link(num1);
    b = num2;
    for (; a->d != '.'; a = a->prev) point_count++; del_link(a);
    for (; b->d != '.'; b = b->next); del_link(b);

    a = last_link(num1);
    b = last_link(num2);

    while (b != NULL) {
        char number1 = a->d - '0';
        char number2 = b->d - '0';
        char check = 0;
        if (number1 + number2 + up >= 10) { check = 1; };
        now = number1 + number2 + up;
        now = check ? now % 10 : now;
        up = check ? 1 : 0;
        a->d = now + '0';
        a = a->prev != NULL ? a->prev : a;
        b = b->prev;
    }
    if (up) {
        b = char_to_list('1');
        connect(b, a);
        num1 = b;
    }

    ans = copy_link(num1);

    free_all(num1); free_all(num2);

    a = last_link(ans);
    for (int _ = point_count; _ > 0; _--) a = a->prev; //[손댄부분] point_count를 기억하기 위해서
    insert(a, '.');

    ans->dot = point_count;
    erase(ans);
    point_count = ans->dot;

    a = ans;
    ans = char_to_list(buho ? '+' : '-');
    connect(ans, a);

    a = ans->next;
    for (; a->next->d != '.' && a->d == '0'; a = a->next) del_link(ans->next);

    ans->cnt = count(ans);
    ans->dot = ans->cnt - point_count;
    digit_matching_list(ans);
    return ans;
}