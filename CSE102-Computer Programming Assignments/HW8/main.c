#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 3

typedef struct board{ //This struct holds the 8 puzzle board in multidimensional array.  

	int nums[SIZE][SIZE];

}board;


void menu();
void puzzle(int option);

//Part1
void randomizeBoard(board *currentBoard);
int check_solvability(board *currentBoard);
void printBoard(board *currentBoard);
void printBoard_file(board *currentBoard, int move_counter);
void board_movement(board *currentBoard,int number,char direction);
void swap(int* a, int* b);
int check_board(board *currentBoard);
void check_bestScore(int move_counter);

//Part2
void auto_finish(board *currentBoard,int preNumber,int move_counter);

//Part3
void show_bestScore();


int main(){
    
	menu(); //main function only calls the menu for 8 puzzle game.
    
	return 0;
}

void menu(){

	int option,exit_flag = 0;

	do{
		
	printf("Welcome to the 8-Puzzle Game!\n");
	printf("Please select an option:\n");	
	printf("1. Play game as user\n");
	printf("2. Finish the game with PC\n");
	printf("3. Show the best score\n");
	printf("4. Exit\n> ");
	scanf("%d",&option);
	
		switch(option){ //Using switch-case calling the related function according to user's option value.
			case 1 :
					puzzle(option);
					break;
			case 2 :
					puzzle(option);
					break;
			case 3 :
					show_bestScore();
					break;
			case 4 : 
					printf("Program terminated.\n");
					exit_flag = 1;
					break;
			default:
					printf("Please enter a valid input.\n");
					break;		
			
		}	
			
	}while(!exit_flag);
	
}


void puzzle(int option) {
    
	board currentBoard; //currentBoard holds the puzzle board value.  
    int number, input_match = 0, move_counter = 0, i;
    char direction;
	//number = selected number(1-8) to move , direction = selected movement direction.
	//input_match controls if the user entered a valid value for number and direction.
	//move_counter holds the number of movements. 


	do{ //This do-while loop randomize the numbers within the puzzle until a 8 puzzle which can be solvable is created.  
		
	    randomizeBoard(&currentBoard);
	
	}while(!(check_solvability(&currentBoard)));


	if(option == 1){ //If user choose to solve the puzzle by him/herself,this part of puzzle function is used.
	
    	do{
    	    printBoard(&currentBoard);  //currentBoard is printed to console.
        	printBoard_file(&currentBoard, move_counter);  //currentBoard is printed to the board.txt file.

	        while (!(input_match)){ 
	        	
    	        printf("Enter your move(number-direction, e.g., 2-R): ");
        	    scanf("%d-%c", &number, &direction);

        	    for (i = 1; i <= 8; i++){ //In this for loop,number value is controlled about is number between 1-8 or not.
    				if (number == i){
            	        input_match = 1;
            	        break;
            	    }
        		}
				
				//If number is valid but direction is not valid,then input_match assigned to 0.
            	if (input_match == 1 && (direction != 'U' && direction != 'D' && direction != 'R' && direction != 'L')) {
                	input_match = 0;
                }

    			if (input_match == 0){ //If input values are not valid,the inputs will be asked again.
            		printf("Please enter valid input values! (number: 1-8, direction: U, D, R, L)\n");
            	}
        	}

	        board_movement(&currentBoard, number, direction); //The selected number is moved in selected direction.

			input_match = 0; //input_match is resetted for next moves.
        	move_counter++; //move_counter increased with 1.
    	
		}while (!(check_board(&currentBoard))); //This loop continues until every number is in the correct place.
    	
    	
    	printBoard(&currentBoard);
        printBoard_file(&currentBoard, move_counter);
        printf("Congrats! You solved the 8-Puzzle Game.\n"); 
        //The last state of currentBoard and congratulations message is printed after 8 puzzle is solved.
        	
		check_bestScore(move_counter); //The score of every game is calculated and compared with best score.

	}else if(option == 2){
		
		//If user select to finish the game with PC auto_finish function is called.
		auto_finish(&currentBoard, 0, move_counter); 
				
	}
	
}



//Part1

void randomizeBoard(board *currentBoard){
    int i, j, k, temp;
    int nums[SIZE * SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 0}; //Initial numbers for 8 puzle game.

    //The numbers in board is shuffled.
    srand(time(NULL));
    for (k = SIZE * SIZE - 1; k > 0; k--){
        i = rand() % (k + 1);
        temp = nums[k];
        nums[k] = nums[i];
        nums[i] = temp;
    }

    //The shuffled numbers in one-dimensional array is assigned to multi-dimensional array.
    k = 0;
    for (i = 0; i < SIZE; i++){
        for (j = 0; j < SIZE; j++){
            currentBoard->nums[i][j] = nums[k++];
        }
    }
}


int check_solvability(board *currentBoard){
	
	int i, j, inversion_count = 0;
	int flatBoard[9];
	
	//inversion_count counts the number of inversions in board if count is even,it is solvable.
	
	//The board in struct is assgined to one-dimensional array.
	 for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            
			flatBoard[i * SIZE + j] = currentBoard->nums[i][j];   
        }
    }
	
	//The number of inversions is counted between the array elements one by one.
	for (i = 0; i < SIZE * SIZE - 1; i++){
        for (j = i + 1; j < SIZE * SIZE; j++){
           
            // If the previous element is greater than next element,it means the inversion.Blank value(0) has to be ignored.
			if (flatBoard[i] > flatBoard[j] && flatBoard[j] != 0){
                inversion_count++;
			}	
        }
    }
		
	//If inversion_count is even,it means it is solvable.If it is odd it is not solvable.	
	if(inversion_count % 2 == 0){		
		return 1;
	}else if(inversion_count % 2 == 1){
		return 0;
	}
	
}


void printBoard(board* currentBoard){
    
	int i, j;

	//The numbers in board is printed but 0 is printed as blank('_ ').
	for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            
			if (currentBoard->nums[i][j] == 0) {
                printf("_ ");
            } else {
                printf("%d ", currentBoard->nums[i][j]);
            }            
        }
        printf("\n");
    }
}


void printBoard_file(board* currentBoard, int move_counter){
	
	FILE* boardFile;
	
	//If it is the first move,the previous writings deleted using 'w'mode.Otherwise,it is appended.
	if(move_counter == 0){
		boardFile = fopen("board.txt","w");	
	}else{		
		boardFile = fopen("board.txt","a");
	}
	
	int i, j;
	
	//The board is printed for every move.
	fprintf(boardFile,"---Board %d---\n",move_counter);
	
	for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            
			if (currentBoard->nums[i][j] == 0) {
                fprintf(boardFile,"_ ");
            } else {
                fprintf(boardFile,"%d ", currentBoard->nums[i][j]);
            }
            
        }
        fprintf(boardFile,"\n");
    }
		
	fclose(boardFile);
}


void board_movement(board *currentBoard,int number,char direction){
	
	int i, j, board_x, board_y;
	
	//The position of selected number is found within the board.
	for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            
			if(currentBoard->nums[i][j] == number){
				
				board_x = j;
				board_y = i;
			}
		}
    }
	
	//According to the selected direction,conditions checked if the number in the border that cause passing through walls 
	//or if the number in direction isn't 0 those means a illegal move.
	//If the move is legal then the blank space and slected number swapped.
	switch(direction){
		case 'U':
				
				if(board_y == 0){
					printf("This is an illegal move!Make a legal move.\n");
				}else if(currentBoard->nums[board_y - 1][board_x] != 0){
					printf("This is an illegal move!Make a legal move.\n");
				}else{
					swap(&currentBoard->nums[board_y][board_x], &currentBoard->nums[board_y - 1][board_x]);
				}
				break;
				
		case 'D':
				
				if(board_y == 2){
					printf("This is an illegal move!Make a legal move.\n");
				}else if(currentBoard->nums[board_y + 1][board_x] != 0){
					printf("This is an illegal move!Make a legal move.\n");
				}else{
					swap(&currentBoard->nums[board_y][board_x], &currentBoard->nums[board_y + 1][board_x]);
				}
				break;
				
		case 'R':
				
				if(board_x == 2){
					printf("This is an illegal move!Make a legal move.\n");
				}else if(currentBoard->nums[board_y][board_x + 1] != 0){
					printf("This is an illegal move!Make a legal move.\n");
				}else{
					swap(&currentBoard->nums[board_y][board_x], &currentBoard->nums[board_y][board_x + 1]);
				}
				break;
				
		case 'L':
			
				if(board_x == 0){
					printf("This is an illegal move!Make a legal move.\n");
				}else if(currentBoard->nums[board_y][board_x - 1] != 0){
					printf("This is an illegal move!Make a legal move.\n");
				}else{
					swap(&currentBoard->nums[board_y][board_x], &currentBoard->nums[board_y][board_x - 1]);
				}
				break;		
	}
	
}


void swap(int* a, int* b){

	int temp = *a;
    *a = *b;
    *b = temp;
}


int check_board(board* currentBoard){

	board idealBoard;
	int i,j, match = 1;
	
	int idealValues[SIZE][SIZE] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 0}
    };
    
    //Ideal state of board is assigned idealBoard.nums array.
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            idealBoard.nums[i][j] = idealValues[i][j];
        }
    }
	
	//If the every element of currentBoard is equal to the idealBoard one by one,that means the puzzle ended.
	for(i = 0; i < SIZE; i++){
		for(j = 0; j < SIZE; j++){
			
			if(currentBoard->nums[i][j] != idealBoard.nums[i][j]){
				
				match = 0;
				break;
			}
		}
	}
		
	return match;
}


void check_bestScore(int move_counter){
	
	FILE* bestScoref = fopen("best_score.txt","r");
	int bestScore, score; //bestScore value is the value in best_score.txt and score value holds the previous game's score.
	
	//bestScore and score values are found.
	score = 1000 - (10 * move_counter);
	fscanf(bestScoref,"%d",&bestScore);
	
	if (score > bestScore){ //If score>bestScore,score is the new bestScore.So,it is printed to best_Score.txt.

        fclose(bestScoref);
        bestScoref = fopen("best_score.txt", "w");
        fprintf(bestScoref, "%d", score);
    }
	
	printf("Move counter = %d .Your score is %d\n",move_counter,score);
	
	fclose(bestScoref);
}


//Part2

void auto_finish(board *currentBoard,int preNumber,int move_counter){
	
    int i, j;
    int bRow, bColumn, randomNum, sRow, sColumn, adjacent_check;
    char direction;
    //bRow and bColumn holds the blank space's position.
    //For random movement,a random number which is adjacent to the blank space is taken.sRow and sColumn holds the randomNum's position.
    //adjacent_check controls the randomNum if it is adjacent to blank sapce or not.

	if((check_board(currentBoard))){ //If currentBoard is in the ideal position auto_finish function terminated completely.
		
		//Final state of board is printed to the console and board.txt file and congratulations text printed.
		printBoard(currentBoard);
    	printBoard_file(currentBoard, move_counter);
		printf("Computer finished the game.Move counter = %d.\n",move_counter);
		
		check_bestScore(move_counter); //Score is checked if the computer break the record or not.
		
	}else{
		
		//For every move,board is printed to the console and file.
        printBoard(currentBoard);
        printBoard_file(currentBoard, move_counter);

		//The position of blank space is found.
    	for(i = 0; i < SIZE; i++){
    		for(j = 0; j < SIZE; j++){
    			
    			if(currentBoard->nums[i][j] == 0){
    				bRow = i;
    				bColumn = j;
				}
			}
		}
		
		
		//In this loop a randomNum is found to move but this randomNum has to be adjacent to the blank space 
		//and randomNum has not to be the previous number that moved in the last move.  
		do{ 

			randomNum = rand() % 8 + 1;  //A randomNum is taken between 1-8.
			
			//The position of randomNum is found.		
			for(i = 0; i < SIZE; i++){
    			for(j = 0; j < SIZE; j++){
    				
    				if(currentBoard->nums[i][j] == randomNum){
    					sRow = i;
    					sColumn = j;
					}
				}
			}
	        
	        //The adjacency conditions of two number are like that 
			//if the rows equal the distance in column has to be 1 or -1 and same logic is valid for columns-rows.
			if ((sRow == bRow && (sColumn == bColumn - 1 || sColumn == bColumn + 1)) ||
        		(sColumn == bColumn && (sRow == bRow - 1 || sRow == bRow + 1))) {
        			
        			adjacent_check = 1;
        	}else{
        			adjacent_check = 0;
			}
		
		}while(!(randomNum != preNumber && adjacent_check == 1));
		
		//According to the distance of rows and columns,the direction is found. 
		if(sRow - bRow == 1){
			direction = 'U';
		}else if(sRow - bRow == -1){
			direction = 'D';
		}else if(sColumn - bColumn == 1){
			direction = 'L';
		}else if(sColumn - bColumn == -1){
			direction = 'R';
		}
		
		printf("Computer Move:%d-%c. Move counter = %d.\n",randomNum,direction,move_counter);
		
		//The blank space and randomNum is swapped in the board.
		swap(&currentBoard->nums[bRow][bColumn], &currentBoard->nums[sRow][sColumn]);

		preNumber = randomNum; //preNumber is assigned for next move.
        move_counter++;
		auto_finish(currentBoard,preNumber,move_counter); //auto_finish function acts as a recursive function.
			
	}
	
}


//Part3
void show_bestScore(){
	
	//best_score.txt is opened and bestScore is printed to the console.
	FILE* bestScoref = fopen("best_score.txt","r");
	int bestScore;
	
	fscanf(bestScoref,"%d",&bestScore);
	printf("The best score is %d.\n",bestScore);

	fclose(bestScoref);
}

