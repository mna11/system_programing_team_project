#include "division.h"

/*
LINK division(LINK a, LINK b) {
    char check; // 크기 비교
    char buho; // +이면 1, -이면 0:

    LINK num1;
    LINK num2;

    // case 1. b = 0
    if (b->next->d == '0' && b->next->next->d == '.' && b->next->next->next == NULL) {
        printf("error");
        free_all(a); free_all(b);
        break;
    }

    // case 2. a보다 b가 더 큰지 확인
    check = compare(a, b);
    if (check == 2) {
        LINK quo = char_to_list('+'); insert(quo, '0');
        LINK remain = //남은 부분 그대로 리턴?
            free_all(a); free_all(b);
        return quo;   //b가 더 크면 0과 나머지를 그대로 반환
    }

    //부호 연산 및 부호 제거
    buho = a->d == b->d ? 1 : 0;

    if (check == 3) {
        LINK quo = char_to_list(buho ? '+' : '-'); insert(quo, '1');
        free_all(a); free_all(b);
        return quo;  //a와 b가 같을 때.
    }

    else { //case 3. a가 더 클 때.
        LINK quo = minus(LINK a, LINK b)
            while (compare(a, b) != 1) {
                LINK quo = minus(LINK quo, LINK b);
                if (quo 부호가 - 일 때) {
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