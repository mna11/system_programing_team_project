#include "minus.h"

LINK minus(LINK a, LINK b) {
    LINK answer;
    LINK num_copy;
    LINK num1;
    LINK num2;
    char sign = 1; //부호 (+,- : 1,0)
    char big; 
    unsigned long long int point_count = 0; //'.'위치 계산
    char now = 0; //  현재값
    char down = 0; //  내림값

    // a =[절대값 큰 경우]
    big = compare(a, b);
    if (big == 3) { // 둘의 절대값이 같을 때
        answer = char_to_list('+');
        insert(answer, '.');
        insert(answer, '0');
        free_all(a); free_all(b);
        answer->cnt = count(answer);
        return answer;
    }

    if (big == 2) { // b->a (b>a)
        num_copy = a;
        a = b;
        b = num_copy;
        sign = 0;
    }
    
    //절대값으로 구현
    num1 = a->next; num1->prev = NULL; free(a);
    num2 = b->next; num2->prev = NULL; free(b);

    //자릿수 정수부 맞추기
    num2 = small_fill(num1, num2);


    //자릿수 소수부분 맞추기
    downzero(num1, num2);

    //소수점 자릿수 세기 및 제거
    a = last_link(num1);
    b = num2;
    for (; a->d != '.'; a = a->prev) point_count++; del_link(a);
    for (; b->d != '.'; b = b->next); del_link(b);

    //계산 코드
    a = last_link(num1);
    b = last_link(num2);

    while (a != NULL) { 
        char number1 = a->d - '0';
        char number2 = b->d - '0';
        char check = 0;
        if (number2 - down > number1) { number1 += 10; check = 1; };
        now = number1 - number2 + down;
        down = check ? -1 : 0;
        a->d = now + '0';
        a = a->prev;
        b = b->prev;
    }

    answer = copy_link(num1);
    free_all(num1); free_all(num2);

    //점 붙이기
    a = last_link(answer);
    for (int _ = point_count; _ > 0; _--) a = a->prev; // point_count를 기억하기 위해서
    insert(a, '.');


    //뒤 0 없애기
    answer->dot = point_count; //소수점 자리 세팅을 위해 추가함
    erase(answer); //erase() 내부에서 반복문 한번 돌때마다 ans->dot--
    point_count = answer->dot; 

    //부호 붙이기
    a = answer;
    answer = char_to_list(sign ? '+' : '-');
    connect(answer, a);

    //앞 0 없애기
    a = answer->next;
    for (; a->next->d != '.' && a->d == '0'; a = a->next) del_link(answer->next);

    // 헤드파트 설정 
    answer->cnt = count(answer);
    answer->dot = answer->cnt - point_count;
    digit_matching_list(answer);
    return answer;
}
