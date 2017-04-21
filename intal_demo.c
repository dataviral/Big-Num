#include "intal.h"

int main(){

  intal *num1 = create_intal("-3");
  intal *num6 = create_intal("-110320");
  intal *num2 = create_intal("+158722983991960578329999999999999");
  intal *num3 = create_intal("-150272567550413613089999999999999");
  intal *num4 = create_intal("+500");
  intal *num5 = create_intal("+1263622236");
  intal *res;

  // ADDITION
  printf("ADDITION of : %c%s + %c%s\n Result: \n",num2->sign, num2->num, num3->sign,num3->num );
  res = add_intal(num2, num3);
  print_intal(res);

  // SUBTRACTION
  printf("SUBTRACTION of : %c%s - %c%s\n Result: \n",num3->sign,num3->num, num5->sign,num5->num );
  res = sub_intal(num3, num5);
  print_intal(res);

  // MULTIPLICATION
  printf("MULTIPLICATION of : %c%s * %c%s\n Result: \n",num2->sign, num2->num, num3->sign,num3->num );
  res = mul_intal(num2, num3);
  print_intal(res);

  // DIVISION
  remove_pad(num5);
  printf("DIVISION of : %c%s / %c%s\n Result: \n",num5->sign, num5->num, num6->sign, num6->num );
  res = div_intal(num5, num6);
  print_intal(res);

  // EXPONENTAITION
  printf("EXPONENTAITION of : %c%s ^ ( %c%s )\n Result: \n",num1->sign, num1->num, num4->sign, num4->num );
  res = pow_intal(num1, num4);
  print_intal(res);


  delete_intal(&num1);
  delete_intal(&num2);
  delete_intal(&num3);
  delete_intal(&num4);
  delete_intal(&num5);
  delete_intal(&num6);
  delete_intal(&res);

  return 0;
}
