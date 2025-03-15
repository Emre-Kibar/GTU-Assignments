#include <stdio.h>
#include "util.h"

int main() {

    int num1, den1;
    int num2, den2;
    int num3, den3;
    
	printf("Enter first fractional number's nominator and denominator in order:");
	scanf("%d %d",&num1,&den1);
	printf("Enter second fractional number's nominator and denominator in order:");
    scanf("%d %d",&num2,&den2);

    printf("First number: ");
    fraction_print(num1, den1);
    printf("\n");

    printf("Second number: ");
    fraction_print(num2, den2);
    printf("\n");

    printf("Addition: ");
    fraction_add(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");

    printf("Subtraction: ");
    fraction_sub(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");

    printf("Multiplication: ");
    fraction_mul(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");

    printf("Division: ");
    fraction_div(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");


    return(0);
}
