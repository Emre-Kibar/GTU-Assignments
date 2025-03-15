#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Definitions for main() function
#define PART1 1
#define PART2 2
#define EXIT 0

//Definitions for Part1
#define YES 'Y'
#define NO 'N'

#define STUDENT_DISCOUNT_RATE 0.125
#define BONUS_DISCOUNT_RATE 0.1
#define VAT_RATE 0.18


//Definitions for Part2
#define STONE 1
#define PAPER 2
#define SCISSORS 3

#define CONTINUE 'Y'
#define STOP 'N'

//Functions that I used for Part1
void print_menu_file();
void read_menu_file();
void selection_receipt_print();
void print_current_time(FILE *fp);
void print_line(FILE *fp);
float food_price_calculation(int option,int portion_number,FILE *fp);
int find_digit_number(int portion_number);
float discount_calculation(float total_price,char student_check,FILE *fp);
float VAT(float discounted_price);
void read_receipt_file();


//Function that I used for Part2
void game();



int main(){
	
	//I created a menu for main function to compile Part1 and Part2 one by one.
	
	int option,exit_flag = 0; //option is the input variable for menu and exit_flag controls the menu loop.
	
	do{
	
	printf("Enter your option( 1 for Part1, 2 for Part2, 0 for exit ):");
	scanf("%d",&option); //Asking user to which part wanted to compile.
	
	    if(option == PART1){  //If user enters 1,Part1 functions will be compiled.
		
		    print_menu_file();
	        read_menu_file();
	        selection_receipt_print();
	        read_receipt_file();
		
	    }else if(option == PART2){  //If user enters 2,Part2 function will be compiled.
	
	        game();
	
        }else if(option == EXIT){  //If user enters 0,exit_flag assigned to 1,so that loop ends,program will be executed.
    	
            exit_flag = 1;	
    	
	    }else{  //Other input values will give an error message.
		
	        printf("Invalid choice.Please try again.\n");	
	    }
    
    }while(exit_flag != 1);  //When exit_flag is 1,the loop ends and program will be terminated.
    
	return 0;
}


//Part1

void print_menu_file(){
	
    FILE *menu = fopen("menu.txt", "w"); //Using a file pointer to print menu and open the menu.txt in write mode.

    //Printed the whole foods and prices to the menu.txt file.
    fprintf(menu,"Product               Price (TL)\n");
    fprintf(menu,"%-20s %11.2f\n", "Kebap", 75.99);
    fprintf(menu,"%-20s %11.2f\n", "Lahmacun", 21.50);
    fprintf(menu,"%-20s %11.2f\n", "Pide", 40.00);
    fprintf(menu,"%-20s %11.2f\n", "Doner", 55.60);
    fprintf(menu,"%-20s %11.2f\n", "Nugget", 53.45);
    fprintf(menu,"%-20s %11.2f\n", "Kola", 15.00);
    fprintf(menu,"%-20s %11.2f\n", "Su", 5.00);
    fprintf(menu,"%-20s %11.2f\n", "Kunefe", 60.00);
    fprintf(menu,"%-20s %11.2f\n", "Sutlac", 32.50);
    fprintf(menu,"%-20s %11.2f\n", "Baklava", 120.25);
    
    
    fclose(menu); //After I wrote the menu,I close the menu.txt file.

}



void read_menu_file(){
	
    char c; //While reading the file character by character assigning them to the c variable.
    int flag = 0; //To determine which part will be read,using flag variable.
    int counter = 1,number_of_foods = 10;  
	
	FILE *menu = fopen("menu.txt", "r"); //To read menu.txt file,created a file pointer and opened menu.txt in read mode.
	
	if(menu == NULL){ //If file is NULL,an error message printed.
		
		printf("File does not exist!\n");
	
	}else{
	    
		//To print the ordinal numbers orderly,I used a loop and to control the loop I used counter and number_of_foods variables.
    	
    	while((c = fgetc(menu)) != EOF){  //Until the character being read is EOF,this loop continues to read the menu.txt file.
    	
            if(c == ' '){ //If the character is white blank,then the food part is read,so that flag assigned to 1.  
		 
                flag = 1; 
        
		    }else if(c == '\n'){ //If the character is new line character,then the whole line is read. 
            
			    flag = 0;      
                printf("\n");   //flag is assigned to 0 and the file goes to next line.
            
			    if(counter <= number_of_foods){
			
			    printf("%d. ",counter); //For the begining of each new line,a ordinal number printed.
                counter++;
			    }
			
            }else if(flag == 0){ 
        
		        printf("%c",c);  
		        //If the flag is zero,that means the character being read is the name of the product and it is printed character by character.
        
		    }
        
        }
    
    }

    fclose(menu); //When the file reaches to the EOF,file will be closed.
}



void selection_receipt_print(){
	
	int option,portion_number; //option is the variable for the selected food and number of portion is assigned to portion_number.
	int exit_flag = 0;  //To stop asking the food selection,I am using exit_flag variable. 
	float total_price = 0,discounted_price; 
	//To calculate total price of order,using total_price variable and discounted_price is used for assigning the price after discounts applied.
	char student_check; //To control user is student or not,I am using student_check variable.
	
	
	FILE *receipt = fopen("receipt.txt", "w"); //Using a file pointer to write the receipt and opening a file named receipt.txt in write mode.
	
	
	fprintf(receipt,"210104004093"); //Printing the student number to receipt.txt.
	print_current_time(receipt);  //Then printing the current date. 
	
	print_line(receipt); //Printing a line using print_line(FILE *fp) function to seperate the sections.
	fprintf(receipt, "Product                  Price (TL)\n"); //Printing the Product and Price part.
	print_line(receipt); //Then,printing a line again using print_line(FILE *fp) function.
	
	
	
	while(exit_flag != 1){ //Until the exit_flag isn't 1,asking to the user for food selection.
	
	   do{
	        printf("Please choose a product (1-10)(If you want to exit,press 0):");
	        scanf("%d",&option); //User enters a value between 1-10 for food selections and assigned to option.
	
	        if(option < 0 || option > 10){
		
		        printf("Invalid food selection.Please enter 1 to 10.\n");
		
	        }
	
        }while(option < 0 || option > 10); //If option isn't valid,an error message printed and asked another value from user.
        
        
		if(option != 0){ //If user don't enter 0(exit condition),the program asks portion_number.
		
            do{
	        printf("How many servings do you want?(If you want to exit,press 0):");
            scanf("%d",&portion_number);  //The number portion is taken and assigned to portion_number. 
	
	        if(portion_number < 0){
		
		        printf("Invalid portion number.Portion number has to be a positive number\n");
		
	        }
	
            }while(portion_number < 0);  //If portion_number isn't valid,an error message printed and asked another value from user.
		
        }
        
        
		if(option == 0 || portion_number == 0){
        	
        	exit_flag = 1; //If option or portion_number is 0,these are exit conditions,so that exit_flag assigned to 1.
		
		}else{
	        
	        //Otherwise total_price is calculated for each selection one by one.
	        //During the food_price_calculation function compiling,the prices for each selected food will be printed.
	        total_price = total_price + food_price_calculation(option,portion_number,receipt);
	    
	    }
	
	}
	
	
	do{
	
	    printf("Are you a student?(Y/N):");
	    scanf(" %c",&student_check);  //student condition of user is assigned to student_check.	
	
	    if(student_check != YES && student_check != NO){
	    	
	    	printf("ERROR!Invalid input.\n");
		}
	
    }while(student_check != YES && student_check != NO); 
	//If user enters another value except of 'Y' or 'N',an error message printed and asked for the input again.
    
    
    
	fprintf(receipt,"Total: %24.2f    \n",total_price); 
	//After all prices for the selected foods are printed at line 218,the total price printed.
    discounted_price = total_price - discount_calculation(total_price,student_check,receipt);
    //Then,discounted price is found by using discount_calculation function and discounts are printed at discount_calculation function. 
	print_line(receipt); //A line printed using print_line function.	
	
	fprintf(receipt,"Price: %24.2f    \n",discounted_price);
	fprintf(receipt,"Price + VAT: %18.2f    \n\n",VAT(discounted_price));
    //Finally,the price of foods printed and after that,taxed price printed by using VAT function.



    fclose(receipt); //The receipt file is closed.
}


void print_current_time(FILE *fp){ //I used this function to print current time to receipt.txt.
	
	time_t current_time = time(NULL);
    struct tm * time = localtime(&current_time);
    char date[100];

    strftime(date, sizeof(date), "%d.%m.%Y/%H:%M", time); //Using the strftime function,I am writing the whole date to date array.

    fprintf(fp,"\t   %s\n", date); //Printing the date to receipt.txt.
	
}


void print_line(FILE *fp){  //I used this function to print a line between the sections of receipt.txt. 
	
	int counter = 0,number_of_characters = 35; //I am using counter and number_of_characters variables to control the loop.
	
	while(counter < number_of_characters){
		
		fprintf(fp,"-");
		counter ++;
	}
	
	fprintf(fp,"\n"); 
	//Using a loop using '-' to print a line for wanted length.
	
}



float food_price_calculation(int option,int portion_number,FILE *fp){  //I used this function to find price of selected food.
	
	float food_price,portion_price; 
	//food_price variable is used to calculate the price of selected food,portion_price is the price of 1 portion of selected food.
	int counter,digit_number; 
	//Using counter to find the price of selected food within the file and using digit_number to find the number of digits of portion_number.
    char c; //While reading the menu.txt character by character,I used c variable.
    
    
    FILE *menu = fopen("menu.txt", "r"); //Opened the menu.txt in read mode.
    
    if(menu == NULL){ //If file is NULL,an error message printed.
	
        printf("File does not exist!\n"); 
	
	}else{
	
        while((c = fgetc(menu)) != '\n'); 
	    //To release first line(Product  Price(TL),I used a while loop and taking the characters of first line until encounter the new line character.
    
	    for(counter = 1;counter <= option ;counter++){
	
	    //Using %*s,I ignored to strings at the begining of lines and then,assigned the values of foods to portion_price variable.
	    fscanf(menu,"%*s %f\n",&portion_price);
    
        }  //This loop reads the prices of foods until it encounters the right price of selected food. 
    
    }
	
	fclose(menu); //Closed the menu.txt.
	
	

	digit_number = find_digit_number(portion_number);
	//To align the line in receipt,finding the digit number of portion number.
	
	//According to the user's food selection and portion number,food price is found and printed to the receipt.txt.
	//To align the line,give 12 character limit for food name and 15-(digitnumber) digit limit for food_price. 
	switch(option){
    case 1:        
            food_price = portion_number * (portion_price);
            fprintf(fp, "%d * %-12s %*.2f    \n",portion_number,"Kebap",15-(digit_number),food_price);
            
            break;
    case 2:
            food_price = portion_number * (portion_price);
            fprintf(fp, "%d * %-12s %*.2f    \n",portion_number,"Lahmacun",15-(digit_number),food_price);
            
            break;
    case 3:
            food_price = portion_number * (portion_price);
            fprintf(fp, "%d * %-12s %*.2f    \n",portion_number,"Pide",15-(digit_number),food_price);
            
            break;
    case 4:
            food_price = portion_number * (portion_price);
            fprintf(fp, "%d * %-12s %*.2f    \n",portion_number,"Doner",15-(digit_number),food_price);
            
			break;
    case 5:
            food_price = portion_number * (portion_price);
            fprintf(fp, "%d * %-12s %*.2f    \n",portion_number,"Nugget",15-(digit_number),food_price);
			
			break;
    case 6:
            food_price = portion_number * (portion_price);
            fprintf(fp, "%d * %-12s %*.2f    \n",portion_number,"Kola",15-(digit_number),food_price);
			
			break;
    case 7:
            food_price = portion_number * (portion_price);
            fprintf(fp, "%d * %-12s %*.2f    \n",portion_number,"Su",15-(digit_number),food_price);
            
            break;
    case 8:
            food_price = portion_number * (portion_price);
            fprintf(fp, "%d * %-12s %*.2f    \n",portion_number,"Kunefe",15-(digit_number),food_price);
            
            break;
    case 9:
            food_price = portion_number * (portion_price);
            fprintf(fp, "%d * %-12s %*.2f    \n",portion_number,"Sutlac",15-(digit_number),food_price);
            
            break;
    case 10:
            food_price = portion_number * (portion_price);
            fprintf(fp, "%d * %-12s %*.2f    \n",portion_number,"Baklava",15-(digit_number),food_price);
            
            break;

    }
	
	return food_price; //To calculate total price,I returned the food_price.
	
}


int find_digit_number(int portion_number){
	
	int digit_counter = 0;
	
	while(portion_number != 0){
		
		portion_number = portion_number / 10;
		digit_counter++;
		//In this loop,dividing the portion_number to 10 and increasing digit_counter one by one.
	}
	
	return digit_counter;
}




float discount_calculation(float total_price,char student_check,FILE *fp){

   float student_discount = 0,bonus_discount = 0,total_discount;
   //student_discount is used to assign the discount value for a student.
   //bonus_discount is used to assign the discount value for a user who ordered food more than 150TL.

    if(student_check == YES){
   	
        student_discount = total_price * STUDENT_DISCOUNT_RATE;  
        fprintf(fp,"Student Discount: %13.2f    \n",(0.0-student_discount));
        //If student_check is 'Y',by multipliying the total_price with (0.125),the student_discount is found and printed to receipt.txt.
    }
	
	if(total_price > 150){
   		
        bonus_discount = total_price * BONUS_DISCOUNT_RATE;
   	    fprintf(fp,"Bonus Discount: %15.2f    \n",(0.0-bonus_discount));
   		//If total_price is greater than 150,by multipliying the total_price with (0.1),the bonus_discount is found and printed to receipt.txt.
	}
	
	
	total_discount = student_discount + bonus_discount;
	
    return total_discount; //The total price is returned.
    
}


float VAT(float discounted_price){  //I used this function to find (price + VAT).
	
	float taxed_price;
	
	taxed_price = discounted_price + (discounted_price * VAT_RATE);
	
	return taxed_price;
	//The taxed_price is calculated by using discounted_price and returned.
}


void read_receipt_file(){
	
	char c; //c used for to read the file charachter by character.
	
	FILE *receipt = fopen("receipt.txt","r"); //A file pointer is used to read the receipt.txt.
    
    if(receipt == NULL){ //If file is NULL,an error message printed.
	
        printf("File does not exist!\n"); 
    
    }else{
    
        printf("\n");
    
        while ((c = fgetc(receipt)) != EOF){
    	
            printf("%c", c);
        }
        //Until the file reaches EOF,reading from file and printing to the terminal character by character.
    
    }
    
    fclose(receipt); //The receipt.txt is closed.
}



//Part2

void game(){
	
	//choice_user is the selection variable for user(stone,scissors,paper) and choice_program is the selection of my program.
	int choice_user,choice_program;
	char repeat; //repeat is another input value for keeping play the game.(It has to be Y/N)
	
	//By using do-while function with the control of repeat variable,the game will continue until user enters 'N'
	do{
	
	printf("Please make a choice!\n");
	printf("1: Stone, 2: Paper, 3: Scissors\n");
	//The game started with the printing of initial text.
	
	    do{
	
	        printf("Enter your choice:");
            scanf("%d",&choice_user);  //Asking input from user between stone,paper,scissors.
	        
	        if(choice_user != STONE && choice_user != PAPER && choice_user != SCISSORS){
		
		    printf("Please,enter an valid input.\n");
		    //If user enter invalid input value for selection,an error message printed.
	        }
	        
	    //If user didn't enter an valid input,the program will ask user's selection with this do-while loop.  
        }while(choice_user != STONE && choice_user != PAPER && choice_user != SCISSORS);
	
	
	srand(time(NULL)); // With srand() function,program can take different values for rand() function.
	choice_program = rand() % 3 + 1;  //With rand() % 3 + 1 statement,choice_program take a value between 1 to 3.
	
	    
		if(choice_user == STONE){
		
		    printf("You chose stone."); //If user selected stone by printing 1,a text printed about it.
		
		    switch(choice_program){
     
	        case STONE:
                printf("I chose stone.It is a tie.\n");
                //If choice_program takes value 1,that means it is stone vs stone,so that is a tie.
                break;
    
	        case PAPER:
                printf("I chose paper.I win.\n");
                //If choice_program takes value 2,that means it is stone vs paper,so that program wins.
                break;
    
	        case SCISSORS:
                printf("I chose scissors.You win.\n");
                //If choice_program takes value 3,that means it is stone vs scissors,so that user wins.
                break;

            }
		
	    }else if(choice_user == PAPER){
		
		    printf("You chose paper.");
		
		    switch(choice_program){
    
	        case STONE:
                printf("I chose stone.You win.\n");
                //If choice_program takes value 1,that means it is paper vs stone,so that user wins.
                break;
    
	        case PAPER:
                printf("I chose paper.It is a tie.\n");
                //If choice_program takes value 2,that means it is paper vs paper,so that is a tie.
                break;
    
	        case SCISSORS:
                printf("I chose scissors.I win.\n");
                //If choice_program takes value 3,that means it is paper vs scissors,so that program wins.
                break;

            }
		
		
	    }else if(choice_user == SCISSORS){
		
		    printf("You chose scissors.");
		
		    switch(choice_program){
    
	        case STONE:
                printf("I chose stone.I win.\n");
                //If choice_program takes value 1,that means it is scissors vs stone,so that program wins.
                break;
    
	        case PAPER:
                printf("I chose paper.You win.\n");
                //If choice_program takes value 2,that means it is scissors vs paper,so that user wins.
                break;
    
	        case SCISSORS:
                printf("I chose scissors.It is a tie.\n");
                //If choice_program takes value 3,that means it is scissors vs scissors,so that is a tie.
                break;

            }
	
        }
	
	    
	    //After the conditions checked for game,with this do-while loop asking to user about continue or stop.
	    do{
	
	        printf("Do you want to play again? (Y/N):");
	        scanf(" %c",&repeat);  //The input taken for repetition from user.
	
	        if(repeat != CONTINUE && repeat != STOP){
		
		        printf("Please,enter an valid answer.\n");
		    //If user didn't enter a valid answer(Y/N),the program prints an error message.
	        }
	        
        //This loop continues until user enters a valid input(Y/N).	
        }while(repeat != CONTINUE && repeat != STOP);
	
	
	//Until user enters STOP(N) value,the do-while loop continues and asks input from user.
    }while(repeat != STOP);
	
}
