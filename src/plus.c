#include "plus.h"

LINK plus(LINK a, LINK b) {
    LINK ans;
    LINK num_copy;
    LINK num1;
    LINK num2;
    char buho; //��ȣ (+,- : 1,0)
    char big_num; //�񱳰� (1,2,3)
    unsigned long long int point_count = 0; //���� ��ġ(0~)
    char now = 0; // �����Ʈ������ ���簪
    char down = 0; // �����Ʈ������ ������

    big_num = compare(a, b);

    if (big_num == 3) { // ���� ���밪�� ���� ��
        ans = char_to_list('+');
        insert(ans, '.');
        insert(ans, '0');
        free_all(a); free_all(b);
        return ans;
    }

    if (big_num == 2) { // b�� �� ũ�� b�� a�� �̵�
        num_copy = a;
        a = b;
        b = num_copy;
    }

    buho = a->d == '+' ? 1 : 0;  // +�� 1, -�� 0

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

    while (a != NULL) {
        char number1 = a->d - '0';
        char number2 = b->d - '0';
        char check = 0;
        if (number2 - down > number1) { number1 += 10; check = 1; };
        now = number1 + number2 + down;
        down = check ? -1 : 0;
        a->d = now + '0';
        a = a->prev;
        b = b->prev;
    }

    ans = copy_link(num1);
    free_all(num1); free_all(num2);

    a = last_link(ans);
    for (int _ = point_count; _ > 0; _--) a = a->prev; //[�մ��κ�] point_count�� ����ϱ� ���ؼ�
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