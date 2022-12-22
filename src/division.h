 LINK division(LINK a, LINK b){  
    char check; // 크기 비교
    boolean sign; // +이면 1, -이면 0:
    sign = (num1->d == num2->d);
   
    // case 1. b = 0
    if(b->next->d == '0' && b->next->next->d == '.' && b->next->next->next==NULL){
        printf("error"); 
        free_all(a); free_all(b);
        break;
    }
    
    // case 2. a보다 b가 더 큰지 확인
    check = compare(a,b);
    if(check == 2){
        LINK quo = char_to_list('+'); insert(quo,'0');
        LINK remain = //남은 부분 그대로 리턴?
        free_all(a); free_all(b);
        return quo;   //b가 더 크면 0과 나머지를 그대로 반환
    }

    //부호 연산 및 부호 제거

    if(check == 3){
        LINK quo = char_to_list(buho?'+':'-'); insert(quo,'1');
        free_all(a); free_all(b);
        return quo;  //a와 b가 같을 때.
    }

   else{ //case 3. a가 더 클 때.
        LINK quo = minus(LINK a, LINK b);
        unsigned long long int i = 0;
        while (compare(a,b) != 1 ){
	        LINK quo = minus(LINK quo, LINK b);
            i++;
}
	   
        if (sign)
            LINK quo = char_to_list('+'); insert(quo);
        else
            LINK quo = char_to_list('-'); Insert(quo, i);
        return quo;

    free(a); free(b);

  
