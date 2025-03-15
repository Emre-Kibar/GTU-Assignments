#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LEFT 'a'
#define RIGHT 'd'
#define UP 'w'
#define DOWN 's'

#define NEWGAME 1
#define HELP 2
#define EXIT 3

// I defined the directions and menu options before the code.

void menu();
void play_game();
void print_rules();
void print_room(int horizontal,int vertical,int C_x,int C_y,int D_x,int D_y);
void print_wall(int horizontal);
int DoorStatus(int C_x,int C_y,int D_x,int D_y);

//These are the definitions of my functions that I used during the code.

int main(){
	
	menu();
	//In the main function,I am only calling the void menu() function,
	
	return 0;
}


void menu(){
	
	int option;
	int exit_flag = 0;
	//option variable is my input variable for menu options and exit_flag is my control variable and initialized to 0.
	
	
	while(exit_flag != 1){  //If exit_flag isn't equal to 1 code enter the loop(at the beginning exit_flag is 0). 
	
	printf("Welcome to the 2D Puzzle Game!\n");
	printf("1.New Game\n");
	printf("2.Help\n");
	printf("3.Exit\n");
	
	printf("Please enter a number for selected option:");
	scanf("%d",&option);
	//I am printing the menu and asking input for predetermined menu options.
		
		if(option == NEWGAME){
			
			play_game();  // If user selects newgame(1),menu function calls the void play_game() function and the game starts.
		
		}else if(option == HELP){
			
			print_rules();  //If user selects help(2),menu function calls the void print_rules() function and prints the rules.  
			
		}else if(option == EXIT){
			
			printf("Thanks for playing the game.\n");
			exit_flag = 1;
			
			//If user selects exit(3),a thanks message printed 
			//and exit_flag turns 1 that means this is the last repetition of while loop.
			
		}else{
			
			printf("ERROR!Invalid Input.\n");
			//If user enters another value except of the menu options,an error message printed.
			
		}
				
	}
	
}


void play_game(){
	
	char move;                //move is the input variable for the direction of move(left,right,up,down).
	int horizontal,vertical;  //horizontal and vertical are my input variables for size of the room.
	int C_x,C_y,D_x,D_y;      //C_x,C_y,D_x,D_y are the x and y coordinates of current position and the door.
	int move_counter = 0;     //move_counter is my counter for the current position's moves.
	 
		
	do{
		
	printf("Enter horizontal and vertical size of the room in order: ");
	scanf("%d %d",&horizontal,&vertical);  //Asking for the size of the room.
	
	
	    if(horizontal > 10 || horizontal < 5 || vertical > 10 || vertical < 5 ){
		
		printf("Horizontal and Vertical sizes cannot be greater than 10 or lower than 5.\n");
		//If user didn't enter the sizes of the room between 5 to 10.An error message printed.
        }  
    
    //If user entered false size values,sizes will be asked again in this loop.
	}while(horizontal > 10 || horizontal < 5 || vertical > 10 || vertical < 5);
	    
	
		
	srand(time(NULL)); //To select different random locations,I am using srand function to get different seeds for every run.
    C_x= rand() % horizontal + 1;
    C_y= rand() % vertical + 1;
    D_x= rand() % horizontal + 1;
    D_y= rand() % vertical + 1;
    //By using the rand() function,I am initiliazing the x and y coordinates of C and D 
	//between 1 to taken horizontal and vertical sizes.
    
    while(C_x == D_x && C_y == D_y){
    	
       D_x= rand() % horizontal + 1;
       D_y= rand() % vertical + 1;	
    //If C and D are at the same location while initializing the coordinates,
	//I will specify new x and y coordinates for D. 	
	}
    
	
	
	print_room(horizontal,vertical,C_x,C_y,D_x,D_y); 
	//Calling the void print_room(int horizontal,int vertical,int C_x,int C_y,int D_x,int D_y) function 
	//to print the room and the initial C and D locations.
		
	


	while(DoorStatus(C_x,C_y,D_x,D_y) != 1){
	//By using int DoorStatus(int C_x,int C_y,int D_x,int D_y) function,controlling if D and C are in the same location.
		
	    printf("Enter your move(a-left,d-right,w-up,s-down):");
        scanf(" %c",&move); //Asking the wanted direction to move the C.

	
    
	    while(getchar() != '\n'){
    
	    printf("ERROR!Please enter only one move at a time.\n");
	    //If user enters multiple direction at the same time which means getchar != '\n',printing an error message.
	
	    while(getchar() != '\n'); // To clean the whole buffer,calling getchar function to give space for new input.
    
	    printf("Enter your move (a-left, d-right, w-up, s-down): ");
        scanf(" %c", &move);  //Asking again for direction of the room.
    
	    }
	
	
	
	    move_counter++; //After user selects a direction,move_counter increased by 1.
		  
	
	    switch(move) {
	        case LEFT:
		        C_x = C_x - 1; //To move left subtracting 1 from initial C_x value.
				
				    if(C_x < 1 ){
					
					    printf("ERROR!You cannot cross the borders of the room.\n");
					    printf("Please make your move again.\n");
					    C_x = C_x + 1;
					    //If C_x is smaller than 1 that means,user tried to cross the left wall of the room
					    //So that,an error message printed and the move reversed. 
				    }
				 
		        break;  
	        
			case RIGHT:
		        C_x = C_x + 1; //To move right adding 1 to initial C_x value.
		        
		            if(C_x > horizontal){
					
					    printf("ERROR!You cannot cross the borders of the room.\n");
					    printf("Please make your move again.\n");
					    C_x = C_x - 1;
					    //If C_x is greater than horizontal that means,user tried to cross the right wall of the room
					    //So that,an error message printed and the move reversed.
				    }
		        
		        break; 	
	        
			case UP:
		        C_y = C_y - 1; //To move down subtracting 1 from initial C_y value.
		        
		            if(C_y < 1){
					
					    printf("ERROR!You cannot cross the borders of the room.\n");
					    printf("Please make your move again.\n");
					    C_y = C_y + 1;
					    //If C_y is smaller than 1 that means,user tried to cross the lower wall of the room
					    //So that,an error message printed and the move reversed.
				    }
				
		        break; 
	        
			case DOWN:	
	            C_y = C_y + 1; //To move up adding 1 to initial C_y value.
	            
	                if(C_y > vertical){
					
					    printf("ERROR!You cannot cross the borders of the room.\n");
					    printf("Please make your move again.\n");
					    C_y = C_y - 1;
					    //If C_y is greater than vertical that means,user tried to cross the upper wall of the room
					    //So that,an error message printed and the move reversed.
				    }
	            
		        break;
		         
	        default:
		        printf("Invalid Input!Please try again.\n");
		        break;
				//If user enters invalid input,an error message printed. 			  			 	
	    }
	    
	    
		if(DoorStatus(C_x,C_y,D_x,D_y) != 1){ //If C and D aren't at the same position,printing C,D and the room.
		
	    print_room(horizontal,vertical,C_x,C_y,D_x,D_y);
	    //After new coordinates calculated,the room and locations of C and D printed.
	    
	    }
	}
	
	printf("CONGRATS.You reached the door and game is over.\n");
	printf("You reached the door at %d moves.\n\n",move_counter);
	//After the program leaves the while loop that means the locations of C and D are same.
	//So that,finally congrats message and move_counter printed.
    
}


void print_rules(){
	
	printf("\n----Game Rules----\n");
	printf("The character is able to move one space in any of the four cardinal directions: up, down, left, and right.\n");
	printf("To move right press 'd',to move left press 'a',to move up press 'w',to move down press 's'\n");
	printf("Diagonal movement isn't allowed or you can not pass over the walls\n");
	printf("You need to go to the exit which is 'D' from your initial location which is 'C'\n\n");
	
	//If print_rules called in menu function,the rules are printed.
}



void print_room(int horizontal,int vertical,int C_x,int C_y,int D_x,int D_y){
	
	int x, y;
	
	print_wall(horizontal); //Printing the upper wall.
	
	
        for( y = 1; y <= vertical; y++){  //This loop controls the line number.
            printf("|");  //For each line,firstly a '|' printed.
            
            for(x = 1; x <= horizontal; x++){ //This loop controls the column number.
                
				if(x==C_x && y==C_y) {
					
                    printf("C"); //If the coordinates are C's coordinates,C printed.
                
				}else if(x==D_x && y==D_y){
					
                    printf("D"); //If the coordinates are D's coordinates,D printed.
                
				}else{
					
                    printf(" "); //Otherwise,a white space printed.
                
				}
				
                printf("|"); //In a line,a '|' is printed for each column.
            
			}
            
			printf("\n");
        }
    
	
	print_wall(horizontal); // Printing the lower wall.
	
}


void print_wall(int horizontal){
	
	int i;
	
	//To print upper and lower walls,I used for loop which is the upper limit is horizontal*2 + 1.
	
	for(i=1 ; i <= ((horizontal*2) + 1) ; i++){
		
		printf("-");
		
	}
	
	printf("\n");
}



int DoorStatus(int C_x,int C_y,int D_x,int D_y){
	
	if(C_x == D_x && C_y == D_y){
		
		return 1;
		//If the x and y coordinates of C and D are same,function returns 1 
		//which stops the while loop in play_game function.(line:129)
	
	}else{
		//Otherwise funtion return 0 that means the loop in play_game function will continue.(line:129)
		return 0;
	}
		
}

