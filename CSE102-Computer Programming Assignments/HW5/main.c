#include <stdio.h>
#include<math.h>

//Defined a new variable as 'Color' for Part2
typedef enum {RED,GREEN,BLUE,YELLOW,ORANGE} Color;

//I used an array to assign color vectors.It is defined global because I cannot pass an array to functions in Part2 according to HW5 pdf.
float color_vector[5][3] = {
        
		{1.0, 0.0, 0.0}, //RED
        {0.0, 1.0, 0.0}, //GREEN
        {0.0, 0.0, 1.0}, //BLUE
        {0.5, 0.5, 0.0}, //YELLOW
        {0.5, 0.4, 0.2}  //ORANGE
    
	};
	
	
void menu(); //I created a menu for HW5-Parts to control the program easily.

//Part1 Functions
void Part1();
char letter_case(char c);

//Part2 Functions
void Part2();
Color convert_input(char selection);	
void colorMixer ( Color choice1, Color choice2, Color (*mix_color)(Color,Color) );
Color find_new_color(Color choice1,Color choice2);
Color find_closest_color(float color[3]);
float Euclidean_distance(float color[],int counter);

// Part3 Functions
void Part3();
void play_game();
void print_board(char board[3][3]);
int game_check(char board[3][3],int move_counter);



int main(){
	
	menu(); //Calling the menu function to control the program.  


    return 0;
}


void menu(){
	
	int option; //option is the input variable for the menu.
	int exit_flag = 0; //exit_flag checks the menu for exit.
	
	
	while(exit_flag != 1){   
	
	printf("Please enter a number for selected part(1->Part1, 2->Part2 ,3->Part3 ,4->Exit):");
	scanf("%d",&option);  //Taking input from user for selected part.
	
		
		if(option == 1){
			
			Part1();   //If user selected 1,Part1 function is called and executed.
			
		}else if(option == 2){
			
			Part2();   //If user selected 2,Part2 function is called and executed.
			
		}else if(option == 3){
			
			Part3();   //If user selected 3,Part3 function is called and executed.
			
		}else if(option == 4){
			
			printf("Program closed.\n");
			exit_flag = 1;  //If user selected 4,exit_flag assigned 1,that means the loop for menu ends.
			
		}else{
			
			printf("ERROR!Invalid Input.\n"); //User has to enter a valid input.
			
		}
				
	}
	
}


//Part1

void Part1(){
	
	FILE *fp;  //I used a file pointer to control the file processes. 
	char file_name[64];  //A array is created for taking the file name as input.
	int alphabet[26] = {0};  //This array holds the letter frequency of selected file.
	char c;  //While reading char by char,the taken char assingned to 'c' variable.
	int counter;  //Counter varible used for controlling the loop.
	
	
	do{
		
		printf("Enter a file name:");
		scanf("%s",file_name); //Taking the file name and assigned to 'file_name' array.
		
		fp = fopen(file_name, "r"); //The file that taken as input is opened in read mode.
		
		if(fp == NULL){
			
			printf("ERROR!File does not exist.\n");
			//If file is NULL,that means file cannot exist.So that,an error message printed.
		}
		
	}while(fp == NULL); //Until the user enters a valid file,program keep asking the file name.
	
	
	
	while((c = fgetc(fp)) != EOF){  //This loop continues to take characters until End Of File. 
		
		if(c >= 'A' && c <= 'Z'){  
			
			c = letter_case(c);
		//If the taken character is greater than 'A' or smaller than 'Z' as ASCII values.I convert it to lowercase version using Letter_case function.
		}
		
		//To prevent segmentation fault,checked the char is a letter or not.So,I don't assign other characters to the array. 
		if(c >= 'a' && c <= 'z'){ 
		
		//By substracting the taken character's ASCII value to 'a'(lower limit),I counted the letter frequency within the alphabet array.
		alphabet[c - 'a']++;
	    }
		
	}
	
	printf("Letter Frequency:\n");
	
	for(counter = 0; counter < 26 ;counter++){
		
		printf("%c : %d\n",('A'+counter),alphabet[counter]);
		//Using this loop the letter frequency printed.	
	}
	
	fclose(fp); //File is closed.
}


char letter_case(char c){
	
	char result;
		
	result = c + 32;
	//Between the lower and uppercase of every letter has 32 value.So,incoming uppercase char converted to lowercase by adding 32. 
		
	return result; //The lowercase of the letter returned.
}


//Part2

void Part2(){
	
	Color choice1,choice2; //These are the input values for Colors.
	char selection; //This is the user's selection for colors.
	
	do{
	
		printf("Enter color 1(r,g,b,y,o):");
		scanf(" %c",&selection); //The input is taken in character format.
		
		if(selection != 'r' && selection != 'g' && selection != 'b' && selection != 'y' && selection != 'o'){
			
			printf("Please enter a valid input!\n");
		}
    //If user entered a invalid input character,an error message printed and asked new value until a valid input entered.
    
	}while(selection != 'r' && selection != 'g' && selection != 'b' && selection != 'y' && selection != 'o');
    
    choice1 = convert_input(selection); //To convert the input to Color format from char format,I used convert_input function. 
    
    
    do{
	
		printf("Enter color 2(r,g,b,y,o):");
		scanf(" %c",&selection); //The input is taken in character format.
		
		if(selection != 'r' && selection != 'g' && selection != 'b' && selection != 'y' && selection != 'o'){
			
			printf("Please enter a valid input!\n");
		}
    //If user entered a invalid input character,an error message printed and asked new value until a valid input entered.
    
	}while(selection != 'r' && selection != 'g' && selection != 'b' && selection != 'y' && selection != 'o');
	
	choice2 = convert_input(selection); //To convert the input to Color format from char format,I used convert_input function.
	
	
	colorMixer ( choice1, choice2, find_new_color ); //With input values and selected function, colorMixer function called.
	
}


Color convert_input(char selection){
	
	Color result;
	
	switch(selection){
		case 'r' :
				result = RED;
				break;
		
		case 'g' :
				result = GREEN;
				break;
		
		case 'b' :
				result = BLUE;
				break;
				
		case 'y' : 			
				result = YELLOW;
				break;
				
		case 'o' :
				result = ORANGE;
				break;
				
	}
	
	//According the selected character,a Color variable assigned and returned as result.
	return result;
}


void colorMixer ( Color choice1, Color choice2, Color (*mix_color)(Color,Color) ){
	
	Color mixed_color = mix_color(choice1,choice2);
	//The mixed_color is found by using a function pointer.
	
	//According to mixed_color variable,the closest_color to mixed color is printed with color_vector.
	switch(mixed_color){
		case RED:
				printf("Mixed Color:RED [%.2f,%.2f,%.2f]\n",color_vector[mixed_color][0], color_vector[mixed_color][1], color_vector[mixed_color][2]);
				break;
		
		case GREEN:
				printf("Mixed Color:GREEN [%.2f,%.2f,%.2f]\n",color_vector[mixed_color][0], color_vector[mixed_color][1], color_vector[mixed_color][2]);
				break;
				
		case BLUE:
				printf("Mixed Color:BLUE [%.2f,%.2f,%.2f]\n",color_vector[mixed_color][0], color_vector[mixed_color][1], color_vector[mixed_color][2]);
				break;
				
		case YELLOW:
				printf("Mixed Color:YELLOW [%.2f,%.2f,%.2f]\n",color_vector[mixed_color][0], color_vector[mixed_color][1], color_vector[mixed_color][2]);
				break;
				
		case ORANGE:
				printf("Mixed Color:ORANGE [%.2f,%.2f,%.2f]\n",color_vector[mixed_color][0], color_vector[mixed_color][1], color_vector[mixed_color][2]);
				break;		
	}
	
}


Color find_new_color(Color choice1,Color choice2){

	float new_color[3]; //To hold the color vector of average three dimension of selected colors,I used 'new_color' array. 
    int counter; //counter variable controls the loop.
    
    for(counter = 0; counter < 3;counter++){
    	
    	new_color[counter] = (color_vector[choice1][counter] + color_vector[choice2][counter]) / 2; 
    	//The average of two input color's each dimension is taken and assigned to new_color array.  
	}
	
	return find_closest_color(new_color); //The closest_color to calculated color is returned by using 'find_closest_color' function
}


Color find_closest_color(float color[3]){
	
	float lowest_distance = INFINITY,distance; 
	//distance variable holds the Euclidean distance for each step of the loop(line 290).lowest_distance holds the lowest distance value.
	int counter; //counter controls the loop.
	Color closest_color; //closest_color holds the output value.
	
	
	for(counter = 0;counter < 5;counter++){
		
		distance = Euclidean_distance(color, counter); 
		//By using the Euclidean_distance function,the distance between calculated color and prespecified is calculated.
		 		
		if(distance < lowest_distance){
			
			lowest_distance = distance;
			closest_color = counter;
			//Closest_color's value is found by using lowest_distance variable. 	
		}
			
	}
	
	return closest_color; //closest_color value is returned.
}


float Euclidean_distance(float color[],int counter){
	
	float distance = 0;
	int i;
	
	for(i=0 ; i < 3 ; i++){
	
		distance += pow(color[i] - color_vector[counter][i], 2); //The distance is calculated by Euclidean distance formula.
	}
	
	return sqrt(distance); //square root of distance is returned.
}

//Part3

void Part3(){
	
	//I used a sub menu to control user want to keep playing or not.
	
	int option; // option is the input value to select any option in the menu.  
	int exit_flag = 0; //exit_flag controls the exit condition of menu.
	
	
	while(exit_flag != 1){   
	
	printf("Welcome to the TIC-TAC-TOE Game!\n");
	printf("1.New Game\n");
	printf("2.Exit\n");
	
	printf("Please enter a number for selected option:");
	scanf("%d",&option); // The input value taken.
	
		
		if(option == 1){
			
			play_game(); //If user select new game,play_game() function called.    
			
		}else if(option == 2){
			
			printf("Thanks for playing the game.\n");
			exit_flag = 1; //If user enters 2,exit_flag assigned 1 and loop ends.
			
		}else{
			
			printf("ERROR!Invalid Input.\n"); //If user enters an invalid input,an error message printed.
			
		}
				
	}
	
}


void play_game(){
	
	char board[3][3] = {
        {'_', '_', '_'},
        {'_', '_', '_'},
        {'_', '_', '_'}
    };  //To print the game board a multidimensional array named board is used.
	
	int row,column; //row and column value is the input values taken from user.
	int move_counter = 0,player_num; // move_counter holds the number of moves value and player_num holds the player number.
	char move_character; //move_character variable holds 'X' and 'O' values according to player_num value.
	
	
	while( !(game_check(board,move_counter)) ){ //Until game_check function returns 1,the loop continues.
	
 	 	if(move_counter % 2 == 1){ //If move_counter can be divided by 2,that means second player will play.
 				
			player_num = 2; 
			move_character = 'O';  //The player_num and move_character values are assigned.	
		
		}else if(move_counter % 2 == 0){ //If move_counter can't be divided by 2,that means first player will play.
			
			player_num = 1;
			move_character = 'X';  //The player_num and move_character values are assigned.
			
		}	
	
		
		do{
		
			printf("Player %d(%c),enter your move(row,col):",player_num,move_character);
			scanf("%d %d",&row,&column); //The row and column values are taken from user.
	
            
			if(row > 2 || row < 0 || column > 2 || column < 0){
 				
                printf("ERROR!You cannot enter a row or column value greater than 2 or lower than 0!\n");
 				// If row and column values are greater than 2 or lower than 0,an error message printed.
		    }else if( board[row][column] == 'X' || board[row][column] == 'O' ){
		    	
		    	printf("ERROR!You cannot overwrite a X or O value!\n");
		    	//If there is a 'X' or 'O' value in selected coordinate,an error message printed.
			}
		    
		//Until a valid coordinate entered the row and column values are asked from user.	 		
        }while( row > 2 || row < 0 || column > 2 || column < 0 || board[row][column] == 'X' || board[row][column] == 'O');
		
		
		board[row][column] = move_character; //The selected element of board array assigned to move_character.
		
		move_counter++; //move_counter increased by 1.
		
		print_board(board); //The game board printed by using print_board function.
		
	}
}
		
	
void print_board(char board[3][3]){
	
	int row_counter,column_counter; //To control rows and columns,those counters are used.
	
	for(row_counter = 0;row_counter < 3;row_counter++){
	
		for(column_counter = 0;column_counter < 3;column_counter++){
			
			printf("%c",board[row_counter][column_counter]); //The three elements of array are printed for each row.
			
			printf(" ");
			
		}
	
	printf("\n"); //After the every elements printed in a row,the outer loop continues for next rows. 
	
    }
}


int game_check(char board[3][3],int move_counter){
	
	int gameover_flag = 0; //gameover_flag checks the exit conditions and if any condition is exist,it assigned to 1. 
	int i; //i controls the loop.
	
	
		//Exit conditions for rows
		for(i = 0 ; i < 3 ; i++){
		
			if( (board[i][0] != '_') && (board[i][0] == board[i][1]) && (board[i][1] == board[i][2]) ){
			
				gameover_flag = 1;
				break;
			//If the first element of a row isn't '_' and all three elements in a row is equal.gameover_flag is assigned to 1.	
			}
	
		}
	
		//Exit conditions for columns
		for(i = 0 ; i < 3 ; i++){
		
			if( (board[0][i] != '_') && (board[0][i] == board[1][i]) && (board[1][i] == board[2][i]) ){
		
				gameover_flag = 1;
				break;
			//If the first element of a column isn't '_' and all three elements in a column is equal.gameover_flag is assigned to 1.	
			}
	
		}
	
		
		//Exit conditions for diagonals
		if( (board[0][0] != '_') && (board[0][0] == board[1][1]) && (board[1][1] == board[2][2]) ){
		
	    	gameover_flag = 1;
	
		}else if( (board[0][2] != '_') && (board[0][2] == board[1][1]) && (board[1][1] == board[2][0]) ){
		
			gameover_flag = 1;
		}
		//If the first element of a diogonal isn't '_' and all three elements in a diagonal is equal.gameover_flag is assigned to 1.
	
		
		if(gameover_flag == 1){ //If gameover_flag is 1,that means a exit condition exist.
		
			if(move_counter % 2 == 1){
	
				printf("Player 1(X) wins!\n");
	
			}else if(move_counter % 2 == 0){
			
				printf("Player 2(O) wins!\n");
			}
			//By dividing the move_counter by 2,the player who won the game is specified and a message is printed.
		}
		
		
		if(move_counter == 9 && gameover_flag != 1){
		//If the move_counter is 9 and gameover_flag isn't assigned to 1,that means all board is full and game isn't finished.
		//In this case, a draw message printed and gameover_flag assigned as 1.
		printf("The game is draw!\n");
		gameover_flag = 1;
		}
    
	return gameover_flag;
}
