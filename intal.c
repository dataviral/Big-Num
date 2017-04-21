#include "intal.h"

intal *create_intal(char *str){
  long int  len = strlen(str);

  intal *new_intal = (intal *)malloc(sizeof(intal));
  if( new_intal == NULL ) {
    return NULL;
  }


  new_intal->num = (char *)malloc(sizeof(char) * (len ));
  if(new_intal == NULL) {
    return NULL;
  }

  strcpy(new_intal->num, str+1);
  new_intal->sign = str[0];


  new_intal->length = len - 1;

  return new_intal;

}

void print_intal(intal* i){
	if(i == NULL) {
		return; //no intal to print
	}

	if(i->num != NULL) {
    remove_pad(i);
    printf("%c%s\n\n", i->sign,i->num);
	}
	return;
}

void delete_intal(intal **i){
  if (i == NULL) {
		return;
	}

	if (*i == NULL) {
		return;
	}

	if( (*i)->num != NULL ) {
		free( (*i)->num );
	}

	free(*i);
	*i = NULL;
	return;
}

intal *cpy_intal(intal *x){
  intal *cpy = (intal *)malloc(sizeof(intal) );

  cpy->length = x->length;
  cpy->num = (char *)malloc(sizeof(char)*cpy->length + 1);
  strcpy(cpy->num, x->num);
  cpy->sign = x->sign;

  return cpy;
}

long int max(long int a, long int b){
   return a > b ? a : b;
 }

intal *add(intal *num1, intal *num2){
  pad_same(num1, num2);

  long int i = num1->length-1;
  long int j = num2->length-1;
  int x, c=0;
  long int m = max(num1->length, num2->length);
  temp_str2[m+1] = 0;

  while( (i >= 0) && (j >= 0) ) {

    x = num1->num[i] - '0' + num2->num[j] - '0' + c;
    temp_str2[m] = x%10 + '0';

    if(x > 9){
      c=1;
    } else {
      c=0;
    }

    i--;j--;m--;

  }

  while(i>=0) {

    x = num1->num[i] - '0' + c;
    temp_str2[m] = x%10 + '0';
    if(x > 9){
      c=1;
    } else {
      c=0;
    }
    i--;m--;
  }

  while(j>=0) {

    x = num2->num[j] - '0' + c;
    temp_str2[m] = x%10 + '0';
    if(x > 9){
      c=1;
    } else {
      c=0;
    }
    j--;m--;

  }

  if(num1->sign == '+' || num2->sign == '+'){
    temp_str[0] = '+';
  } else if(num1->sign == '-' || num2->sign == '-') {
    temp_str[0] = '-';
  } else {
    temp_str[0] = '0';
  }

  temp_str2[0] = c + '0';
  temp_str[1] = '\0';

  strcat(temp_str, temp_str2);



  return create_intal(temp_str);
}

intal *sub(intal *num1, intal *num2){
  pad_same(num1, num2);

  long int i,j;

  char sign = 0;

  if(num1->length > num2->length){
    sign = '+';
  } else if(num1->length < num2->length){
    sign = '-';
  } else {
      i = 0;
      while( (i < num1->length) ){

        if( num1->num[i] > num2->num[i] ){
          sign = '+';
          break;
        } else if( num1->num[i] < num2->num[i]) {
          sign = '-';
          break;
        } else {

        }
        i++;
      }
      if(sign == 0){
        return create_intal("00");
      }
  }



    intal *big_num, *small_num;
    if( sign == '+'){
      big_num = num1;
      small_num = num2;
    } else if( sign == '-'){
      big_num = num2;
      small_num = num1;
    }

    i = big_num->length - 1;
    j = small_num->length - 1;
    long int x, b=0;
    temp_str2[i+1] = 0;

    while(i>=0){
      if(j >= 0){
        x = big_num->num[i] -'0' - (small_num->num[j] - '0') - b;
        j--;
      } else {
        x = big_num->num[i] -'0' -b;
      }
      if(x<0) {
        b=1;
      } else {
        b=0;
      }

      temp_str2[i] = b*10 + x + '0';

      i--;
    }

    temp_str2[big_num->length] = '\0';
    temp_str[0] = sign;
    temp_str[1] = '\0';

    strcat(temp_str, temp_str2);
    return create_intal(temp_str);
}

intal *mul(intal *num1, intal *num2){


  char result[10000];
  long long n1, n2;
  char sign;

  sscanf(num1->num, "%Ld", &n1);
  sscanf(num2->num, "%Ld", &n2);

  if(n1==0 || n2==0){
    return create_intal("00");
  }

  if(num1->sign == '+' && num2->sign == '-'){
    sign = '-';
  } else if(num1->sign == '-' && num2->sign == '+'){
    sign = '-';
  } else {
    sign = '+';
  }

  sprintf(result, "%Ld", n1*n2);

  temp_str[0] = sign;
  temp_str[1] = '\0';

  strcat(temp_str, result);

  return create_intal(temp_str);
}

intal *div_rep_sub(intal *num1, intal *num2){

  remove_pad(num1);
  remove_pad(num2);

  if(num2->length > num1->length){
    return create_intal("00");
  }

  intal *qt = create_intal("00");
  intal *a = create_intal("+1");
  intal *divd = cpy_intal(num1);
  intal *divr = cpy_intal(num2);

  divd->sign = '+';
  divr->sign = '+';

  divd=sub_intal(divd, divr);
  qt = add_intal(qt, a);

  while(divd->sign == '+') {
    // printf("%c %s %c\n",divd->sign, divd->num, divr->sign   );
    divd=sub_intal(divd, divr);
    if(divd->sign != '-'){
      qt = add_intal(qt, a);
    }
    remove_pad(a);
    remove_pad(qt);

  }

  if( (divd->sign != '0') || qt->length >= 1 ){

    if( (num1->sign == '-' && num2->sign == '-') || (num1->sign == '+' && num2->sign == '+') ){
      qt->sign = '+';
    } else {
      qt->sign = '-';
    }
  } else {

    qt->sign = '0';
  }

  delete_intal(&a);
  delete_intal(&divd);
  delete_intal(&divr);

  return qt;

}

int cmp_num(char *s1, char *s2){
  long int i = strlen(s1);
  long int j = strlen(s2);
  if(i>j){
    return 1;
  } else if(i<j){
    return -1;
  } else {
    int k=0;
    while(k<i){
      if(s1[k] > s2[k]){
        return 1;
      } else if(s1[k]< s2[k]) {
        return -1;
      } else {

      }
      k++;
    }
  }
}

intal *div_intal(intal *num1, intal *num2){

  remove_pad(num1);
  remove_pad(num2);

  if(num2->length > num1->length){
    return create_intal("00");
  }

  intal *qt = create_intal("00");
  intal *p_1;
  intal *carry = create_intal("+");
  intal *m;


  char *x = (char *)malloc(sizeof(char) * (num1->length + 10));
  char *result = (char *) malloc(sizeof(char) * num1->length + 2);

  long int i,j,l;

  result[0] = '+';
  result[1] = '\0';

  x[0] = '+';
  x[1] = '\0';

  strncpy(x+1, num1->num, num2->length);
  int flg;
  i = num2->length - 1 ;

  while( i < num1->length ) {

    if( i >= num2->length  ){

      memset(x, 0, (num1->length + 10) );
      x[0] = '+';
      x[1] = '\0';

      if(carry->num[0] == '0'){
        l=0;
        while(1){
          carry->num[l] = carry->num[l+1];
          if(carry->num[l] == '\0'){
            break;
          }
          l++;
        }
        carry->length--;
      }

      strcat(x, carry->num);
    }

    flg=0;
    j=strlen(x);

    while( cmp_num(x+1,num2->num) != 1 && i < num1->length){

      x[j] = num1->num[i];
      x[j+1] = '\0';
      i++;
      j++;
      flg++;
    }

    while(flg >= 1){
      if(flg>1){
        strcat(result, "0");
        i++;
      }
      flg--;
      i--;
    }

    p_1 = create_intal(x);
    qt = div_rep_sub(p_1, num2);

    m = mul_intal(qt, num2);
    carry = sub_intal(m, p_1);

    remove_pad(carry);
    remove_pad(qt);



    if(qt->num[0] == '0' && qt->length != 1 ){
      strcat(result, qt->num+1);
    } else {
      strcat(result, qt->num);
    }

    i++;
  }

  if(qt->sign != '0'){
    if( (num1->sign == '-' && num2->sign == '-') || (num1->sign == '+' && num2->sign == '+') ){
      result[0] = '+';
    } else {
      result[0] = '-';
    }
  } else {
    result[0] = '0';
  }


  delete_intal(&qt);
  delete_intal(&p_1);
  delete_intal(&carry);
  delete_intal(&m);

  return create_intal(result);

}

intal *add_intal(intal *num1, intal *num2){
  intal *sum;
  if (num1->sign == '+' && num2->sign == '+') {
    sum = add(num1, num2);
    sum->sign = '+';
  } else if(num1->sign == '+' && num2->sign == '-') {
    sum = sub(num1, num2);
  } else if(num1->sign == '-' && num2->sign == '+') {
    sum = sub(num2, num1);
  } else if(num1->sign == '-' && num2->sign == '-') {
    sum = add(num2, num1);
    sum->sign = '-';
  } else{
    sum = add(num1, num2);
  }
  return sum;

}

intal *sub_intal(intal *num1, intal *num2){
  intal *sum;
  if (num1->sign == '+' && num2->sign == '+') {
    sum =  sub(num1, num2);
  } else if(num1->sign == '+' && num2->sign == '-') {
    sum = add(num1, num2);
    sum->sign = '+';
  } else if(num1->sign == '-' && num2->sign == '+') {
    sum = add(num2, num1);
    sum->sign = '-';
  } else if(num1->sign == '-' && num2->sign == '-') {
    sum = sub(num2, num1);
  } else {
    sum = sub(num1, num2);
  }

  return sum;

}

intal *mul_intal(intal *num1, intal *num2){
  return karatsuba(num1, num2);
}

void pad_same(intal *s1, intal *s2){

  if(s1->length > s2->length){

    long int i,  x = s1->length - s2->length;

    temp_str[0] = 0;
    strcpy(temp_str, s2->num);
    temp_str[s2->length] = 0;
    free(s2->num);
    s2->num = (char *)malloc(sizeof(char) * (s2->length +x +100));

    for(i=0; i<x; i++){
      temp_str2[i] = '0';
    }
    temp_str2[x] = '\0';


    strcpy(s2->num, temp_str2);
    strcat(s2->num, temp_str);

    s2->length =strlen(s2->num);

  } else if(s2->length > s1->length) {

    long int i, x = s2->length - s1->length;

    temp_str[0] = 0;
    strcpy(temp_str, s1->num);
    temp_str[s1->length] = 0;

    free(s1->num);
    s1->num = (char *)malloc(sizeof(char) * (s1->length +x+100));

    for(i=0; i<x; i++){
      temp_str2[i] = '0';
    }
    temp_str2[x] = '\0';

    strcpy(s1->num, temp_str2);
    strcat(s1->num, temp_str);

    s1->length =strlen(s1->num);

  }

  else{

  }

  if(s1->length %2 !=0 && s1->length > 3){


    temp_str2[0] = '0';
    temp_str2[1] = '\0';

    temp_str[0] = 0;
    strcpy(temp_str, s1->num);
    temp_str[s1->length] = 0;
    free(s1->num);
    s1->num = (char *)malloc(sizeof(char) * (s1->length +2));
    strcpy(s1->num, temp_str2);
    strcat(s1->num, temp_str);

    temp_str[0] = 0;
    strcpy(temp_str, s2->num);
    temp_str[s2->length] = 0;
    free(s2->num);
    s2->num = (char *)malloc(sizeof(char) * (s2->length +2));
    strcpy(s2->num, temp_str2);
    strcat(s2->num, temp_str);

    s1->length =strlen(s1->num);
    s2->length =strlen(s2->num);
  }


}

void remove_pad(intal *n){

  long int i=0;
  while(n->num[i] == '0' && i<n->length-2){
    i++;
  }
  temp_str[0] = 0;
  strcpy(temp_str, n->num+i);
  temp_str[n->length -i ] = 0;
  memset(n->num, 0, n->length);
  n->length -= i;
  strcpy(n->num, temp_str);

}

intal *split_intal(intal *sp, long int l, long int r){

  temp_str[0] = 0;

  intal *splited = (intal *)malloc(sizeof(intal));
  strncpy(temp_str, sp->num+l, r-l);
  temp_str[r-l] = '\0';

  long int len = strlen(temp_str);
  splited->num = (char *)malloc(sizeof(char) + len);

  strcpy(splited->num, temp_str);
  splited->length = len;
  splited->sign = sp->sign;

  return splited;
}

intal *karatsuba(intal *num1, intal *num2){


  if( num1->length <= 3 && num2->length <= 3){
    return mul(num1, num2);
  }

  pad_same(num1, num2);

  long int m = num1->length/2;

  intal *a1, *a2, *b1, *b2, *p1, *p2, *p3;

  a1 = split_intal(num1, 0, m);
  a2 = split_intal(num1, m, num1->length);
  b1 = split_intal(num2, 0, m);
  b2 = split_intal(num2, m, num2->length);

  p1 = karatsuba(a1, b1);

  p2 = karatsuba(a2, b2);

  intal * add1 = add_intal(a1,a2);
  intal * add2 = add_intal(b1, b2);

  p3 = karatsuba(add1, add2);

  delete_intal(&add1);
  delete_intal(&add2);
  delete_intal(&a1);
  delete_intal(&a2);
  delete_intal(&b1);
  delete_intal(&b2);

  return karat(p1, p2, p3,   num1->length);

}

intal *karat(intal *p1, intal *p2, intal *p3, long int m){

  intal *mid = sub_intal(p3, add_intal(p1,p2));

  long int i;
  for(i=0; i<m; i++){
    temp_str2[i] = '0';
  }
  temp_str2[i] = '\0';

  temp_str[0] = p1->sign;
  temp_str[1] = '\0';
  strcat(temp_str, p1->num);
  strcat(temp_str, temp_str2);
  intal *high = create_intal(temp_str);

  for(i=0; i<m/2; i++){
    temp_str2[i] = '0';
  }
  temp_str2[i] = '\0';

  if(mid->sign == 0){
    temp_str[0] = '0';
  }

  temp_str[0] = mid->sign;
  temp_str[1] = '\0';
  strcat(temp_str, mid->num);
  strcat(temp_str, temp_str2);
  delete_intal(&mid);
  mid = create_intal(temp_str);

  delete_intal(&p1);
  delete_intal(&p3);

  intal *res2 = add_intal(high, mid);
  intal *res = add_intal(res2, p2);


  delete_intal(&p2);
  delete_intal(&res2);
  delete_intal(&high);
  delete_intal(&mid);

  return res;

}

intal *pow_intal(intal *p1, intal *p2){

  intal *cnt = cpy_intal(p2);
  intal *num = cpy_intal(p1);
  intal *s = create_intal("+1");
  intal *res = create_intal("+1");
  cnt->sign = num->sign = '+';

  while(cnt->sign == '+'){
    res = mul_intal(res, num);
    cnt = sub_intal(cnt, s);
    remove_pad(res);
  }

  res->sign = p1->sign;

  delete_intal(&cnt);
  delete_intal(&s);
  delete_intal(&num);

  return res;
}
