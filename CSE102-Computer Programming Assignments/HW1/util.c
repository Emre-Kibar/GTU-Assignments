#include <stdio.h>
#include "util.h"

void Part1(){
	//num1 and num2 are input variables.
	int num1,num2,remainder,GCD;
	
	printf("Enter two numbers:");
	scanf("%d %d",&num1,&num2); //The input values are taken and assigned to num1 and num2.
	
	// With this two if statement,I am turning negative numbers into positive numbers.
	//So that,I can find GCD of negative numbers because the greatest factor of each negative number is its positive form. 
	if(num1 < 0){
		num1 = num1 * -1;       	
	}
	if(num2 < 0){
		num2 = num2 * -1;
    }
	
	//According to the Euclidean algorithm GCD(num1,num2) = GCD(num2,(num1%num2)).
	//When (num1 % num2)=0,then GCD has to be num1 because 0 is a factor of every number.
	//Until remainder equals to 0,the loop will continue and remainder will be 0 for every case at the end.   
	while(num2 != 0){
		
		remainder = num1 % num2;
		num1 = num2;
		num2 = remainder;
			
		}
	
	GCD = num1; // After we equalized the num2(reaminder of inputs) to 0, num1 will be GCD.

	printf("The greatest common divisor of the inputs is %d\n",GCD);

}


void Part2(){
	//num1 and num2 are input variables.
	int num1,num2;
	
	printf("Enter two positive numbers that must be at most 4 digits:");
	scanf("%d %d",&num1,&num2); // The inputs are taken and assigned to num1 and num2 variables.
	
	//User must enter positive and at most four digits inputs to perform operation.
	if(num1 > 9999 || num2 > 9999 || num1 < 0 || num2 < 0){
		
		printf("ERROR.The inputs must be at most four digits and positive.\n");
	
	}else{
	
	int sum = num1 + num2; // The result of addition operation.
	
	printf("-------Addition Operation-------\n");
	printf("%7d\n",num1);
	printf("%7d\n",num2);
	printf("+\n-------\n");
	printf("%7d\n",sum); 
	//This operation's digit width equals to 7 as in the output example at HW1.pdf.
    // I can write eveything in one printf function but I seperated them to prevent confusion.
 
    }
}


void Part3(){
	//num1 and num2 are the input variables.
	int num1,num2;
	
	printf("Enter two positive numbers that must be at most 3 digits:");
	scanf("%d %d",&num1,&num2); // The inputs are taken and assigned to num1 and num2 variables.
	
	//User must enter positive and at most three digits inputs to perform operation.
	if(num1 > 999 || num2 > 999  || num1 < 0 || num2 < 0){   
		
		printf("ERROR.The inputs must be at most three digits and positive.\n");
		
    }else{
	// multiplication_digit = Selected digit during the middle multiplication.
	// mid_multiplication = The answer calculated during the middle multiplication.
	int multiplication_digit,mid_multiplication;
	
	int digit_width = 10; //This is the max digit width.Later,during the digit-by-digit multiplication,it will be lowered for each step.(line 109).
	int result = num1 * num2;  // The result of multiplication operation
	int temp = num2;  // I used temp variable not to lose initial num2 value.   
	
	printf("-------Multiplication Operation-------\n");
	printf("%10d\n",num1); 
	printf("%10d\n",num2);
	printf("*\n----------\n");
	
	// As a special case,if second number is 0,then it doesn't enter the loop 
	//and directly printed 0 for mid_multiplications.
	if(num2 == 0){
		
		printf("%10d\n",(num1*num2));
		
	}
	
	while(temp > 0){
		
		multiplication_digit = temp % 10; // multiplication_digit equals to rightmost digit of temp(=num2) value. 
		mid_multiplication = num1 * multiplication_digit; // mid_multiplication equals to (number that is above * selected digit)  
		
		// After finding mid_ multiplication's result,it is printed according to determined digit_width.
		printf("%*d\n",digit_width,mid_multiplication);
		
		temp = temp / 10; // By dividing the temp to 10,I discard the rightmost digit that we use at line 102.
		digit_width--; // digit_width decrased for each step of loop to shift the next mid_multiplication's result to the left.
	}
	
	printf("+\n----------\n");
	printf("%10d\n",result); //Finally,result will be printed.
	
	//This operation's digit width equals to 10 as in the output example at HW1.pdf.
  }
}


void Part4(){
	////num is the input variable.
	int num;
	
	printf("Enter an integer between 1-10:");
	scanf("%d",&num); // The input taken and assigned to the num variable.
	
	//After the taken input matched one of the if-else condition,necessary text will be printed. 
	if(num > 5 && num <= 10){
		printf("The integer you entered is greater than 5\n");
	}else if(num <= 5 && num >= 1){
		printf("The integer you entered is less than or equal to 5\n");
	}else if(num < 1 || num > 10){
		printf("Invalid Input\n");
	}
		
}
