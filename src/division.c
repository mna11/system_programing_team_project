#include "division.h"

/*
LINK division(LINK a, LINK b) {
    char check; // ũ�� ��
    char buho; // +�̸� 1, -�̸� 0:

    LINK num1;
    LINK num2;

    // case 1. b = 0
    if (b->next->d == '0' && b->next->next->d == '.' && b->next->next->next == NULL) {
        printf("error");
        free_all(a); free_all(b);
        break;
    }

    // case 2. a���� b�� �� ū�� Ȯ��
    check = compare(a, b);
    if (check == 2) {
        LINK quo = char_to_list('+'); insert(quo, '0');
        LINK remain = //���� �κ� �״�� ����?
            free_all(a); free_all(b);
        return quo;   //b�� �� ũ�� 0�� �������� �״�� ��ȯ
    }

    //��ȣ ���� �� ��ȣ ����
    buho = a->d == b->d ? 1 : 0;

    if (check == 3) {
        LINK quo = char_to_list(buho ? '+' : '-'); insert(quo, '1');
        free_all(a); free_all(b);
        return quo;  //a�� b�� ���� ��.
    }

    else { //case 3. a�� �� Ŭ ��.
        LINK quo = minus(LINK a, LINK b)
            while (compare(a, b) != 1) {
                LINK quo = minus(LINK quo, LINK b);
                if (quo ��ȣ�� - �� ��) {
                    LINK quo = plus(LINK quo, LINK b);
                    LINK remain = LINK insert(LINK quo, / );
                    LINK remain = LINK insert(LINK remain, b);
                    break;
                }
                LINK remain = LINK insert(LINK quo, / );
                LINK remain = LINK insert(LINK remain, b);
            }
        LINK quo = char_to_list(buho ? '+' : '-'); insert(quo, '+'); insert(quo, remain);

        num1 = a->next;
        num2 = b->next;
        free(a); free(b);
}
*/