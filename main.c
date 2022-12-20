#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <stdio.h>

typedef struct big_integer{
    int is_minus;
    char * INT_VAL;
    char * FLOAT_VAL;
}BigInteger;

BigInteger create(char * int_val, char * float_val){
    BigInteger i;
    i.INT_VAL = (char *)malloc((int)strlen(int_val));
    strcpy(i.INT_VAL, int_val);
    i.FLOAT_VAL = (char *)malloc((int)strlen(float_val));
    strcpy(i.FLOAT_VAL, float_val);
    return i;
}

BigInteger create2(char * val){
    BigInteger i;
    i.FLOAT_VAL = (char *)malloc(1);
    i.FLOAT_VAL[0] = '0';
    i.INT_VAL = NULL;
    int is_first = 0;
    char *copied = strdup(val);
    char *ptr = strtok(copied, ".");
    while (ptr != NULL)
    {
        if(is_first == 0){
            i.INT_VAL = (char *)malloc((int)strlen(ptr));
            strcpy(i.INT_VAL, ptr);
            is_first = 1;
        }else{
            i.FLOAT_VAL = (char *)malloc((int)strlen(ptr));
            strcpy(i.FLOAT_VAL, ptr);
            is_first = 2;
        }
        ptr = strtok(NULL, ".");
    }
    return i;
}

BigInteger createPlus(BigInteger *left, BigInteger * right){
    BigInteger res;
    int max = strlen(left->INT_VAL);
    if(strlen(right->INT_VAL) > max){
        max =strlen(right->INT_VAL);
    }
    res.INT_VAL =(char *)malloc(max + 1);
    res.FLOAT_VAL = NULL;
    max = strlen(left->FLOAT_VAL);
    if(strlen(right->FLOAT_VAL) > max){
        max =strlen(right->FLOAT_VAL);
    }
    res.FLOAT_VAL =(char *)malloc(max + 1);
    return res;
}

BigInteger createMul(BigInteger *left, BigInteger * right){
    BigInteger res;
    int max = strlen(left->INT_VAL);
    if(strlen(right->INT_VAL) > max){
        max =strlen(right->INT_VAL);
    }
    res.INT_VAL =(char *)malloc(max*2);
    res.FLOAT_VAL = NULL;
    max = strlen(left->FLOAT_VAL);
    if(strlen(right->FLOAT_VAL) > max){
        max =strlen(right->FLOAT_VAL);
    }
    res.FLOAT_VAL =(char *)malloc(max*2);
    return res;
}

void test(char * c){
    BigInteger d = create2(c);
    printf("%s.%s\n",d.INT_VAL,d.FLOAT_VAL);
}

int main(int argc, const char * argv[]) {
    BigInteger b = create("123123123123123123123123123123", "123123123123123123123123123123123");
    printf("%s.%s\n",b.INT_VAL,b.FLOAT_VAL);
    test("123123123123123123123123123123.123123123123123123123123123123123");
    test("0.2");
    test("2");
    return 0;
}
