#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

typedef struct intal{
  char *num; // the number
  long int length; // no of digits
  char sign;  // sign of integer
}intal;

char temp_str[100000000];
char temp_str2[100000000];

long int max( long int , long int );
void reset();
void remove_pad(intal *);
void pad_same(intal *, intal *);
void delete_intal(intal **);
void print_intal(intal *);
intal *pow_intal(intal *, intal *);
intal *split_intal(intal *, long int , long int );
intal *create_intal(char *);
intal *cpy_intal(intal *);
intal *add(intal *, intal *);
intal *mul(intal *, intal *);
intal *sub(intal *, intal *);
intal *div_rep_sub(intal *, intal *);
intal *add_intal(intal *, intal *);
intal *sub_intal(intal *, intal *);
intal *mul_intal(intal *, intal *);
intal *div_intal(intal *, intal *);
intal *karatsuba(intal *, intal *);
intal *karat(intal *, intal *, intal *, long int );
