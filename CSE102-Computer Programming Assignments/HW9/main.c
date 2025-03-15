#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct point{
	
	int row, col;
	
}point;

typedef struct block{
	
	char type;
	int value; 
	
}block; 


block*** init_board();
void draw_board(block*** board, point* snake, int snakeSize);
void play(block*** board);
void move(point* snake, point* lastPosition);
int check_status(block*** board, point* snake, int snakeSize);
void update(block*** board, point** snake, int* snakeSize, point* lastPosition);

int main(){
	
	int i, j;
	
	block*** board = init_board(); //board initilialized randomly.
	play(board); //To play the snake game play function is called.
	
	// When the game is finished the memory allocated for board is freed.
	for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            free(board[i][j]);
        }
        free(board[i]);
    }
    free(board);
    
	return 0;
}


block*** init_board(){
	
	block*** board;
    int i, j;
    int randRow, randCol; //To hold the random row-column of bait and obstacle randRow and randCol variables is used.

    // Allocate memory for the first dimension
    board = (block ***)malloc(10 * sizeof(block **));

    // Allocate memory for the remaining dimensions
    for (i = 0; i < 10; i++){
    	
        board[i] = (block **)malloc(10 * sizeof(block *));
        for (j = 0; j < 10; j++) {
        	
            board[i][j] = (block *)malloc(sizeof(block));
        }
    }

	//Every block in the 10x10 board is fixed as empty.
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
        
		    board[i][j][0].type = 'e';
			board[i][j][0].value = 0 ; 
        }
    }
    
    
    srand(time(NULL));
    randRow = rand() % 9 + 1;
    randCol = rand() % 9 + 1;
    
    //The first random row and column assigned as bait.
    board[randRow][randCol][0].type = 'b'; 
    board[randRow][randCol][0].value = 0;
    
    //In this loop,rand values taken until they are different from bait's location.
    while(board[randRow][randCol][0].type == 'b'){
	    randRow = rand() % 9 + 1;
    	randCol = rand() % 9 + 1;
	}
	
	//The second random row and column assigned as obstacle.
	board[randRow][randCol][0].type = 'o'; 
    board[randRow][randCol][0].value = 1;
    
    return board; //board is returned to main function.
}


void draw_board(block*** board, point* snake, int snakeSize){
	
	int i, j, k, check; //check variable checks block situation for emptiness.
		
	printf("---------------------\n");
	
	for(i = 0; i < 10;i++){
		printf("|");
		
		for(j = 0; j < 10; j++){
		
			check = 0; //This check value checks for every block if the block is available to print a space for empty block.
		
			if(board[i][j][0].type == 'b'){ //If the block is bait then '.' printed.
				printf(".");  
				check = 1;
				
			}else if(board[i][j][0].type == 'o'){ //If the block is obstacle then number of nested blocks is printed.
				printf("%d",board[i][j][0].value);
				check = 1; 
				
			}else if (snake[0].row == i && snake[0].col == j){ //If the block is the first value of snake array 'O' is printed.
            	printf("O");
            	check = 1;
            	
        	}else{ 
        		
        		//If the block is one of the elements of snake array 'X' is printed.
            	for(k = 1; k < snakeSize; k++){
                	if(snake[k].row == i && snake[k].col == j){
                    	printf("X");
						check = 1;
                    	break;
                	}
            	}
        	}

			//If the block isn't bait,obstacle or snake element(check=0),then,the block is really empty and ' ' printed. 
			if(!(check)){
			
				if(board[i][j][0].type == 'e'){
					printf(" ");
				} 
			}
			
		
			if(j == 9){
				printf("|");
			}else{
				printf(" ");	
			}
		}
		printf("\n");
	}
		
	printf("---------------------\n");	

}


void play(block*** board){
	
	int snakeSize = 1, exit_flag = 0; //snakeSize initialized as 1 for begining.
	point* snake; //snake array holds snake's location
	point lastPosition; //lastPosition holds position of snake's head.
	
	//The head of snake created and assigned to initial position.
	snake = (point*)malloc(snakeSize * sizeof(point));  
	snake[0].row = 0;
	snake[0].col = 0;

	do{
		
		draw_board(board, snake, snakeSize); //The board is drawn.
		move(snake, &lastPosition); //The move is wanted from user.
		exit_flag = check_status(board, snake, snakeSize); //exit conditions checked.
		
		//If game isnt finished,board and snake is updated.
		if(!(exit_flag)){
			update(board, &snake, &snakeSize, &lastPosition);
		}
			
	}while(!(exit_flag)); //This loop continues until ending conditions of game occurred.
	
	printf("Game Over!\n");
	free(snake); //The snake array freed.
}


void move(point* snake, point* lastPosition){
	
	char moveSelect; //moveSelect holds the move selection of user.
	int newRow, newCol; //The row-col values of snake's head after the move is hold newRow-newCol variables.
	int i, exit_flag;
	
	do{
		exit_flag = 1;
		
		//Only first entered character is taken as input.
		printf("Enter a direction for snake(w,a,s,d):");
		scanf(" %c",&moveSelect);
		while(getchar() != '\n');
	
		newRow = snake[0].row;
    	newCol = snake[0].col;
    
    	//The shifting is done according to moveSelect.
    	switch (moveSelect) {
    		case 'w':
        		newRow--;
        		break;
    		case 'a':
        		newCol--;
        		break;
    		case 's':
        		newRow++;
        		break;
    		case 'd':
        		newCol++;
        		break;
    		default:
        		printf("Please enter a valid move.\n");
        		exit_flag = 0;
        		break;
		}
	
		
		//If the selected direction goes through snake's body,the move ignored.Otherwise,the head shifted for selected direction. 
		if(newRow == snake[1].row && newCol == snake[1].col){
			
			printf("You cannot go through to direction of snake's body.Please enter again.\n");		
			exit_flag = 0;
		}
		
	}while(!(exit_flag));
		
		//The current Location is kept for the movement of snake's body in update function.
		lastPosition->row = snake[0].row;
        lastPosition->col = snake[0].col;	
		//Snake's head is moved to its new location.
		snake[0].row = newRow;
        snake[0].col = newCol;					
}


int check_status(block*** board, point* snake, int snakeSize){
	
	int i;
	
	//If the head hits the its own body game is over.
	for(i = 1; i < snakeSize; i++){
		
        if (snake[0].row == snake[i].row && snake[0].col == snake[i].col) {
        	printf("\nSnake hit its own body.");
		    return 1;
        }
    }
	
	//If snake's head tried to pass board's limits game is over.
	if (snake[0].row < 0 || snake[0].col < 0 || snake[0].row > 9 || snake[0].col > 9) {
    	
		printf("\nSnake hit the wall.");
    	return 1;
	}

	
	//If snake tries to pass over a obstacle bigger than its own size game is over.
	if(board[snake[0].row][snake[0].col][0].type == 'o' && snakeSize < board[snake[0].row][snake[0].col][0].value){
			
		printf("\nSnake hit the obstacle greater than itself.");
		return 1;
	}
	
	return 0; //For other options,game continues.
}


void update(block*** board, point** snake, int* snakeSize, point* lastPosition){
    
    //randRow-randCol values holds the random position to put obstacle.
	//snakeMatch checks a empty block is a part of the snake.
	//obtacle_counter holds to count of obstacles, randObs select an obstacle to put nested obstacles over it.
	//foundObstacles checks if the nested obstacle placed or not.
	//bait_condition checks for is there a bait in the board. 
	//move_counter holds the count of move.
	
	int i, j, exit_flag = 0;
    int obstacle_counter = 0, randObs, foundObstacle, bait_condition = 1;
    int randRow, randCol, snakeMatch = 0;
    static int move_counter = 1;
    
    
    // If the snake's head encounters bait, increase the snake's size
    if(board[(*snake)[0].row][(*snake)[0].col][0].type == 'b'){
    	
        (*snakeSize)++;
        *snake = (point*)realloc(*snake, (*snakeSize) * sizeof(point)); //Snake array is reallocated for its new size.
        
        //The position of bait is now empty.
        board[(*snake)[0].row][(*snake)[0].col][0].type = 'e'; 
        board[(*snake)[0].row][(*snake)[0].col][0].value = 0;
        
        bait_condition = 0; //This means there isnt a bait in the board.
        
    }else if(board[(*snake)[0].row][(*snake)[0].col][0].type == 'o'){
        //If the snake's head hits an obstacle, destroys the obstacle (if the game isnt finished that means snakeSize is greater than obstacle's size).
        //The third dimension is reallocated because obstacle destroyed.
        board[(*snake)[0].row][(*snake)[0].col] = (block *)realloc(board[(*snake)[0].row][(*snake)[0].col], sizeof(block));
        
        board[(*snake)[0].row][(*snake)[0].col][0].type = 'e';  //The position of obstacle is now empty.
        board[(*snake)[0].row][(*snake)[0].col][0].value = 0;
    }
    
    //If snakeSize is greater than 1,this means snake has a body.So,snake's body needs to be shifted.
    if((*snakeSize) > 1){
	
    	// Shift the snake's body
    	for (i = (*snakeSize) - 1; i > 1; i--) {
        	(*snake)[i].row = (*snake)[i - 1].row;
        	(*snake)[i].col = (*snake)[i - 1].col;
		}
    	
    	//The first element of snake's body is initialized to previous position of snake's head. 
    	(*snake)[1].row = lastPosition->row;
    	(*snake)[1].col = lastPosition->col;
	}
    
    
    // Count the number of obstacles
    for(i = 0; i < 10; i++){
        for(j = 0; j < 10; j++){
            
			if(board[i][j][0].type == 'o'){
                obstacle_counter++;
            }
        }
    }
    
    // Add a new obstacle every 5 moves if there are less than 3 obstacles
    if(move_counter % 5 == 0 && obstacle_counter < 3){
    	
        do{
            srand(time(NULL));
            // row and col values is selected randomly.
            randRow = rand() % 10; 
            randCol = rand() % 10;
            
            //If selected position is a obstacle with less than value 9,a nested block has to be put.
            //The value of obstacle increased and new memory allocated for nested block and type-value entered for created memory.
            if(board[randRow][randCol][0].type == 'o' && board[randRow][randCol][0].value < 9){
               
			    board[randRow][randCol][0].value++;
                board[randRow][randCol] = (block *)realloc(board[randRow][randCol], board[randRow][randCol][0].value * sizeof(block));
                
                board[randRow][randCol][board[randRow][randCol][0].value - 1].type = 'o';
				board[randRow][randCol][board[randRow][randCol][0].value - 1].value = 1;
                
                exit_flag = 1; //This means obstacle placed successfully.
                
            }else if(board[randRow][randCol][0].type == 'e'){
                
        	//If selected place is empty,it needs to be checked is it a element of snake.
			 
				snakeMatch = 0;
                
                for(i = 0; i < (*snakeSize); i++){
                	
                    if((*snake)[i].row == randRow && (*snake)[i].col == randCol){
                        snakeMatch = 1; //If block is a element of snake,snakeMatch is 1.
                        break;
                    }
                }
                
                //If snakeMatch is 0 this means empty block isnt an element of snake.So,obstacle is placed.
                if(!(snakeMatch)){
                    board[randRow][randCol][0].type = 'o';
                    board[randRow][randCol][0].value = 1;
                    
                    exit_flag = 1; //This means obstacle placed successfully.
                }
            }
            
        }while(!(exit_flag));
    
	}else if(move_counter % 5 == 0 && obstacle_counter == 3){
		
	//If there is already 3 obstacle in the board,this part puts nested obstacles over the obstacles randomly.	
			
		exit_flag = 0;
		srand(time(NULL));
		
		do {
        	randObs = rand() % 3 + 1; // A obstacle value taken between 1 and 3. 
        	obstacle_counter = 0;
        	foundObstacle = 0;

	        for(i = 0; i < 10; i++){
    	        for(j = 0; j < 10; j++){
    	        	
        	        if(board[i][j][0].type == 'o'){
            	        obstacle_counter++; //If loop finds a obstacle increase the counter.
	
						//If the found obstacle is the randomly selected obstacle and it has a value less than 9,
						//the value increased and new memeory allocated for nested obstacle.Also,type and value assigned to nested obstacle.
    	                if(obstacle_counter == randObs && board[i][j][0].value < 9){ 
    	                	
        	                board[i][j][0].value++;
            	            board[i][j] = (block *)realloc(board[i][j], board[i][j][0].value * sizeof(block));
            	            
                	        board[i][j][board[i][j][0].value - 1].type = 'o';
                    	    board[i][j][board[i][j][0].value - 1].value = 1;
                    	    
                        	foundObstacle = 1; //The nested obstacle is placed. 
                        	break;
                    	}
					}
				}

            	if(foundObstacle){
                	exit_flag = 1;
                	break;
            	}
        	}
	
			//If nested obstacle isnt placed,this means every obstacle has the max value 9.
        	if(!foundObstacle){
            	exit_flag = 1;
            	break;
        	}

    	}while (!(exit_flag));
			
	}
  
    //If there isnt a bait in the board,new bait has to be placed.
    if(!(bait_condition)){
		
		do{
			//The randRow and randCol values is taken.
			srand(time(NULL));
			randRow = rand() % 10;
			randCol = rand() % 10;
			snakeMatch = 0;
			
			//The bait must be placed to an empty space which the block isnt a snake element.
			if(board[randRow][randCol][0].type == 'e'){
					
				for(i = 0; i < ((*snakeSize) - 1); i++){
					
					if((*snake)[i].row == randRow && (*snake)[i].col == randCol){
						
						snakeMatch = 1; //If there is a match with snakeMatch is equalized to 1.
						break;		
					} 						
				}
				
				//If the empty space isnt an element of snake then bait is placed.
				if(!(snakeMatch)){
					
					board[randRow][randCol][0].type = 'b'; //The type and value of bait is assigned.
					board[randRow][randCol][0].value = 0;
					bait_condition = 1; //By using bait_condition,I determined the bait is placed.
					
				}
			}
		
		}while(!(bait_condition));
		
	}
		
	move_counter++; //move_counter increased for next moves.
}


