#include <stdio.h>
#include <math.h>
#include "util.h"

void Part1(){
	
	printf("******PART1******\n");
	
	//Leap year algorithm:A leap year should be divided by 4 without remainder
	//if a year is divided by 100 without remainder but divided by 400 with remainder,that year isn't a leap year
	//also if a year is divided by 4000 without remainder,that year isn't a leap year.
	
	int year;
	int flag = 0;
	// year is the input variable,I used flag variable to check the condition. 
	
	printf("Enter a year: ");
	scanf("%d",&year); // I took the year as input from user and assigned to year variable.
	
	if(year % 4 == 0){  
		
		flag = 1;  //If the year is divided by 4 without remainder,the flag is 1 that means the year is a leap year.
		
		if(year % 100 == 0 && year % 400 != 0 ){
		//If the year enters this condition,that means this year isn't a leap year.So,flag is 0.	
			flag = 0;
		
		}else if(year % 4000 == 0){
		//If the year enters this condition,that means this year isn't a leap year.So,flag is 0.	
			flag = 0;
		}
	}
	
	//According to the flag's conditions,I printed the appropriate text.
	if(flag == 1){
		
		printf("%d is a leap year.\n\n",year);
	
	}else if(flag == 0){
		
		printf("%d is not a leap year.\n\n",year);
	}
		
}


//Part2

void Part2(){
	
	printf("******PART2******\n");
	
	char format_output,operation; //format_output is an iput value(S || I),Operation is used for operator.
	int m,n,i; // m is the number of total digits and n is the number of digits after the point.i used as counter.
	int exponential,digit; 
	// exponential is used for hold the exponential part of result in Scientific format.
	// digit is used for hold the number of int_part's digit. 
	long long int int_part; // int_part is used for hold the integer part of result and to hold greater values,selected as long long int.
	double first_operand,second_operand,result; 
	
	printf("Enter the format of output(S or I):");
	scanf(" %c",&format_output); //To determine format_output,taking input value from user. 
	
	if(format_output == 'S'){
		
		printf("Enter m and n values:");
		scanf("%d %d",&m,&n);  //If the format output is S(scientific),taking the m and n values for digit numbers.
    }
    
	printf("Enter the operation(+,-,/,*,%%,!,^):");
    scanf(" %c",&operation); //Taking input for operator and assigned to operation.
    
    if(operation == '+'||operation == '-'|| operation == '/'|| operation == '*'|| operation == '%'|| operation == '^'){
		
		printf("Enter the first operand:");
		scanf("%lf",&first_operand);
		printf("Enter the second operand:");
		scanf("%lf",&second_operand);
		
	}else if(operation == '!'){
		
		printf("Enter the operand:");
		scanf("%lf",&first_operand);
	//If operation is '!',taking 1 operand value,otherwise,taking 2 input values. 
	}
    
	
	//According to the operator,necessary calculation is made.
	//I used if-else statements for operations according to the format output and if format_output is 'I',I typecasted operands 
	//because if I make calculation without typecasting the operands,the result might be different for some situations.
	//Such as, first_operand=2.4 , second_operand=3 ,result =7.2 and while printing,it will be "2 * 3 =7"    
	switch(operation){
		case '+':
			    if(format_output == 'I'){
				    result= (int)first_operand + (int)second_operand; 
				}else if(format_output == 'S'){
				    result = first_operand + second_operand;
				}
			    break;
			    
		case '-':
			    if(format_output == 'I'){
				    result= (int)first_operand - (int)second_operand; 
				}else if(format_output == 'S'){
				    result = first_operand - second_operand;
			    }  
			    break;
			    
		case '/':
			    if(format_output == 'I'){
				    result= (int)first_operand / (int)second_operand; 
				}else if(format_output == 'S'){
				    result = first_operand / second_operand;
				}
			    break;
			    
		case '*':
			    if(format_output == 'I'){
				    result= (int)first_operand * (int)second_operand; 
				}else if(format_output == 'S'){
				    result = first_operand * second_operand;
				}
			    break;
			    
		case '%':
		//I made typecasting the operand values to take mod because I cant find the mod of 2 double value with % operator. 
			    result = (int)first_operand % (int)second_operand;
			    break;
			    
		case '!':
		//To calculate factorial,I used loop and firstly,equalized result to 1 and later,multiply the result from 1 to operand value.
			    result =1;
			    
			    for(i=1 ; i <= first_operand ; i++){
			    	
			    	result = result * i;
				}
			    
				break;
			    
		case '^':
			    if(format_output == 'I'){
				    result = pow((int)first_operand,(int)second_operand); 
				}else if(format_output == 'S'){
				    result = pow(first_operand,second_operand);
				}
			    break;
		//To calculate power of a number,I used pow() function for math.h library.  
		default :
		        printf("ERROR!Invalid Operator.\n");
				break;
		//If user enters another character except of selected operators,an error message printed.													    
		}
		
    
    if(format_output == 'I'){
          
	    if(operation == '+'||operation == '-'|| operation == '/'|| operation == '*'|| operation == '%'|| operation == '^'){
		
		printf("%d %c %d = %lld \n",(int)first_operand,operation,(int)second_operand,(long long)result);
		
		//If the operator is not factorial,printing the two operands and result with operator by making typecasting.
		//I typecasted result as long long integer to prevent from overflowing as possible as I can.
	    }else if(operation == '!'){
		
		printf("%d! = %lld \n",(int)first_operand,(long long)result);
	    //If the operator is factorial,printing the operand and result with operator by making typecasting.
        }
	
	
    }else if(format_output == 'S' && m > n){
    	
    	exponential = 0;  
    	digit = 0; // initialized the number of digits of int_part and exponential to 0.
		int_part = (long long)result;
	    //By typecasting the result from double to long long integer,I can find digit number of integer part.
	    //To hold greater values,I used long long integer. 
		
		while(int_part != 0){
			
			int_part = int_part / 10.0;
			digit++; 
		//Until int_part equalized to 0,I divided to int_part to 10 to find number of digits of integer part.	
		}

		
		if(digit < (m-n)){
			
			while(digit != (m-n)){
				
				result = result * 10.0;
				digit++;
				exponential--;
				
			}
		//If digit number is lower than 'total digit input-decimal digit input',I multplied the result with 10 to move left the result.
		
			
		}else if(digit > (m-n)){
			
			while(digit != (m-n)){
				
				result = result / 10.0;
				digit--;
				exponential++;
				
			}
        }
    	//If digit number is greater than 'total digit input-decimal digit input',I divided the result to 10 to move right the result.
    	
    	
    	if(operation == '+'||operation == '-'|| operation == '/'|| operation == '*'|| operation == '%'|| operation == '^'){
		
		
		printf("%f %c %f = ",first_operand,operation,second_operand);
		printf("%0*.*fe%d  \n",m+1,n,result,exponential);
		
		//Firstly,printing the operands and operator,later printing the result and exponential part.
		
	    }else if(operation == '!'){	
		
		printf("%f%c = ",first_operand,operation);
	    printf("%0*.*fe%d  \n",m+1,n,result,exponential);
	    
	    //Firstly,printing the operand and factorial operator,later printing the result and exponential part.
	
        }
    
	  		
	}else if(format_output != 'S' || format_output != 'I'){
	//If user enter except of 'S' or 'I' for format output,giving a error message.	
		printf("ERROR! Invalid format output.\n");
	
	}else if(n >= m){
	//If number of total digits is greater than number of digits after the point,giving an error message.	
		printf("ERROR! n value cannot be greater than m value.\n");
    }
}


//Part3


void Part3(){
	
	printf("\n\n******PART3******\n");
	
	//exam1,exam2,exam3,assignment1,assignment2 are the inputs taken from the user.
	//final_grade is the average of exam and assignment grades
	float exam1,exam2,exam3,assignment1,assignment2,final_grade;
	
	printf("Enter 3 exam grades of student: ");
	scanf("%f %f %f",&exam1,&exam2,&exam3); //Exam inputs are taken and assigned to variable. 
	
	printf("Enter 2 assignment grades of student: ");
	scanf("%f %f",&assignment1,&assignment2); //Assignment inputs are taken and assigned to variable. 
	
	if(exam1 > 100 || exam2 > 100 || exam3 > 100 || assignment1 > 100 || assignment2 > 100 ){
	//If user enters any input values greater than 100 for exams or assignments.That cause an error.
		printf("ERROR!The grades cannot be greater than 100.\n");
	
	}else{
	//final_grade will be calculated.
	final_grade = (exam1 + exam2 + exam3) / 3 * 0.6 + (assignment1 + assignment2) / 2 * 0.4;
	
	//According to the final_grade's conditions,I printed the appropriate text.
	if(final_grade >= 60){
		
		printf("Your final grade is %.2f.Passed!\n",final_grade);
	
	}else if(final_grade < 60){
		
		printf("Your final grade is %.2f.Failed!\n",final_grade);
	}
	
    }

}
