#include <stdio.h>
#include "util.h"

void fraction_print(int numerator, int denominator) {	
	printf("%d//%d", numerator, denominator);

}  /* end fraction_print */

void fraction_add(int n1, int d1, int n2, int d2, int * n3, int * d3) {
    *n3 = n1*d2 + n2*d1;
    *d3 = d1*d2;
    fraction_simplify(n3, d3);
} /* end fraction_add */

void fraction_sub(int n1, int d1, int n2, int d2, int * n3, int * d3) {
    *n3 = n1*d2 - n2*d1;
    *d3 = d1*d2;
    fraction_simplify(n3, d3);
} /* end fraction_sub */

void fraction_mul(int n1, int d1, int n2, int d2, int * n3, int * d3) {
    *n3 = n1 * n2;
    *d3 = d1 * d2;
    fraction_simplify(n3, d3);
} /* end fraction_mul */

void fraction_div(int n1, int d1, int n2, int d2, int * n3, int * d3) {
    *n3 = n1 * d2;
    *d3 = d1 * n2;
    fraction_simplify(n3, d3);
} /* end fraction_div */


void fraction_simplify(int * n, int * d) {
    //I used temporary variables to calculate GCD because I want to prevent to
	//change original values of nominator and denominator in case of working on negative numbers. 
	int i,gcd,temp_n,temp_d;
	
	//I declared a few special situation to prevent confusion.
	if(*n == 0 && *d != 0 ){
	    printf("The answer is zero: ");
	}else if(*n != 0 && *d == 0 ){
	    printf("The answer is indefinite: ");
	}else if(*n == 0 && *d == 0 ){
	    printf("The answer is undefined: ");
	}else{
	
	//By using Elvis operator,I turned negative numbers to positive numbers to calculate GCD.
	temp_n = (*n > 0) ? *n : -*n;
	temp_d = (*d > 0) ? *d : -*d;
    
    if( temp_n >= temp_d ){
    	for(i=temp_d ; i >=1 ; i--){
    		if( temp_d%i == 0 && temp_n%i == 0){
    			gcd = i;
    			break;
			}
		}
	}else{
	    for(i=temp_n ; i >= 1 ; i--){
    		if( temp_d%i == 0 && temp_n%i == 0){
    			gcd = i;
    			break;
			}
		}
	}
	
	//By dividing input numbers to gcd,I simplified the inputs.
	*n = *n / gcd;
	*d = *d / gcd;
  } 
    
} /* end fraction_div */
