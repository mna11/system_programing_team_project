#include "multiply.h"

bool sign;
LINK answer;
LINK num_copy;
LINK cal1;
LINK cal2;
LINK next_num1 = copy_link(num1->next);
LINK next_num2 = copy_link(num2->next);
LINK zero_link;
LINK save;
LINK input;

// 계산 값 부호 결정 
sign = (num1->d == num2->d); //'+'=true, '-'=false

// 소수점 위치
unsigned long long point1 = 0;
unsigned long long point2 = 0;

num_copy = last_link(num1); //마지막에서 탐색 시작
while(num_copy->d != '.'){
    num_copy = num_copy->prev;
    point1++;
}

num_copy = last_link(num2);
while(num_copy->d != '.'){
    num_copy = num_copy->prev;
    point2++;
}
point = point1 + point2; //최종 소수점 위치 구함

// 점 빼기
num_copy = next_num1;
while(num_copy->d != '.')
    num_copy->next;
del_link(num_copy);

num_copy = next_num2;
while(num_copy->d != '.'){
    num_copy->next;
del_link(num_copy);


// 계산 (손계산 원리 참조)
cal1 = last_link(next_num1); //다시 역으로 만들어 처음처럼 만들어준다
unsigned long long int zero = 0; 
for (; cal1 != NULL; cal1 = cal1->prev) {
    cal2 = last_link(next_num2);
    char down = (cal1->d - '0') * (cal2->d - '0'); 
    char up = down / 10; //올림수
    down % 10 = down; //나머지 그대로

    input = char_to_list(down + '0');

    num_copy = input;

    cal2 = cal2->prev;
    for (; cal2 != NULL; cal2 = cal2->prev) {
        down = (cal1->d - '0') * (cal2->d - '0') + up;
        up = down / 10; 
        down % 10 = down;
        insert(num_copy, down + '0');
        num_copy = num_copy->next;
    }
    if (up != 0) insert(num_copy, up + '0'); //올림수가 존재할 경우
    num_copy = last_link(input);

    for (; num_copy->prev != NULL; num_copy = num_copy->prev) {
        if (num_copy->d != '0')
            break;
    }

    //필요없는 '0'값 지우기
    num_copy = last_link(input);
    while (1) {
        if (num_copy->prev == NULL || num_copy->d != '0')
            break;

        LINK save = num_copy->prev;
        del_link(num_copy);
        num_copy = save;
    }

    if (zero > 0) {
        zero_link = char_to_list('0');
        for (unsigned long long i = 1; i < zero; i++) {
            insert(zero_link, '0');
        }
        connect(zero_link, input);
        input = zero_link; //자리수 추가
    }

    //곱하기 결과들 덧셈
    if (!zero) 
        answer = copy_link(input);

    else {
        unsigned long long len1 = count(answer);
        unsigned long long len2 = count(input);
        if (len2 > len1) {
            num_copy = answer;
            answer = input;
            input = num_copy;
        }
        save = answer;
        num_copy = input;
        down = 0;
        up = 0;
        for (; num_copy != NULL; num_copy = num_copy->next) {
            down = num_copy->d - '0' + save->d - '0' + up;
            up = down / 10;
            down = down % 10;
            save->d = down + '0';
            save = save->next;
        }
        for (; up && save != NULL; save = save->next) {
            down = save->d - '0' + up;
            up = down / 10;
            down = down % 10;
            save->d = down + '0';
        }
        if (up) {
            save = last_link(answer);
            insert(save, '1');
        }
    }
    free_all(input);
    zero++;
}

unsigned long long answerlen = count(answer); //부호 및 '.'추가 파트
if (answerlen > point) { //도출값이 point 보다 클 때(정수부 존재)
    num_copy = answer;
    save = answer;

    if (sign) //부호가 같을 경우 '+' 넣기
        answer = char_to_list('+');
    else
        answer = char_to_list('-');

    for (; num_copy != NULL; num_copy = num_copy->next) {
        insert(answer, num_copy->d);
    }
    free_all(save);

    num_copy = last_link(answer); //다시 뒤집고 '.'추가
    while (point--) num_copy = num_copy->prev;
    insert(num_copy, '.');
}
else { //소수부분만 
    num_copy = answer;
    if (sign)
        answer = char_to_list('+');
    else
        answer = char_to_list('-');

    save = answer;
    insert(save, '0');
    save = save->next; insert(save, '.');
    save = save->next;
    point -= answerlen;

    while (point--) {
        insert(save, '0');
        save = save->next;
    }
    for (; num_copy != NULL; num_copy = num_copy->next) {
        insert(save, num_copy->d);
    }
}
answer->cnt = answerlen;

erase(answer);

free_all(num1);
free_all(num2);
free_all(next_num1);
free_all(next_num2);

return answer;
}
