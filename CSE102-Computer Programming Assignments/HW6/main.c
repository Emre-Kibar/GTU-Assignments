#include<stdio.h>
#include <stdlib.h>


//To hold variables in files,I used structs at some parts.
struct Product {
    int pID;
    char Type;
    char Name[20];
    char Brand[20];
    float Price;
};

struct Stock {
    int sID;
    int pID;
    char branch[20];
    int current_stock;
};


//Part1 Functions
void menu();
//Part2 Functions
void submenu_Part2();
void add_product_entry();
void delete_product();
void add_stock_entry();
void delete_stock();
//Part3 Functions
void submenu_Part3();
void list_all_products();
//Part4 Functions
void submenu_Part4();
void query_stock();
void list_outof_stock();
void list_branch_stocks();
//Part5 Functions
void brand_stock_control();
//Part6 Functions
void print_report();

//Other Functions
int stringCompare(char str1[], char str2[]); 
void bubble_sort(int arr[], int n);

int main(){
	
	menu(); 
	
	return 0;
}

//Part1

void menu(){
	
	int option; //Option is the input variable for menu.
	int exit_flag = 0; //Exit flag controls the loop for menu.
	
	do{   
	
	printf("Welcome to the product/stock management system.\n");
	printf("1. File Operations\n");
	printf("2. Querry Products\n");
	printf("3. Check Stock Status\n");
	printf("4. Stock Control by Brand\n");
	printf("5. Export Report\n");
	
	printf("Please enter a number for selected operation:");
	scanf("%d",&option);
	
		switch(option){
			case 1:
				submenu_Part2();
				break;
			case 2:				
				submenu_Part3();
				break;
			case 3:
				submenu_Part4();
				break;	
			case 4:
			    brand_stock_control();
				break;
			case 5:
				print_report();
				exit_flag = 1;			
				break;
			default:		
				printf("Please enter a valid input!\n");
				break;
		} 
				
	//According to option value,calling the related function.
				
	}while(!exit_flag);
	
}

//Part2

void submenu_Part2(){
	
	int option;
	int exit_flag = 0;
	
	
	do{
	
	printf("1.Add new product\n");
	printf("2.Delete a product\n");
	printf("3 Update a product\n");
	printf("4.Add feature to products\n");
	printf("5.Add new stock entry\n");
	printf("6.Delete a stock entry\n");
	printf("7.Update stock entry\n");
	printf("8.Return to main menu\n");
	
	printf("Please enter a number for selected operation:");
	scanf("%d",&option);
	
	//According to option value related function called but some part are missing.Sorry about it.
	
		switch(option){
			case 1:
				add_product_entry();
				break;
			case 2:				
				delete_product();
				break;
			case 3:
				printf("This part isn't available.\n");
				break;	
			case 4:
				printf("This part isn't available.\n");
				break;	
			case 5:
				add_stock_entry();
				break;
			case 6:
				delete_stock();
				break;
			case 7:
				printf("This part isn't available.\n");
				break;
			case 8:
				printf("Returning to main menu.\n");
				exit_flag = 1;			
				break;
			default:		
				printf("Please enter a valid input!\n");
				break;
		} 
				
	}while(!exit_flag);
	
}


void add_product_entry(){
	
	FILE *products_file = fopen("products.txt","a+"); //I opened the products.txt in a+ mode to append and read.
	
	char line[100]; //While reading line by line hold the string in line array.
	
	int pID,pID_read,pID_match; 
	float price;
	char type,name[20],brand[20];	

	//pID,type,name[],brand[],price are the input variables.pID_read is pID value which read from taken line.pID_match controls input pID value.
	
	if(products_file == NULL){
		
		printf("The file cannot be opened!\n"); //Checked products.txt opened or not.
	
	}else{
	
		do {
			pID_match = 0; //I used pID_match to check if the pID entered by the user has already been used.
		
			printf("Enter the pID value for product:");
			scanf("%d",&pID); //Asking pID value of product wanted to add.
		
			rewind(products_file); // Reset file pointer to beginning of file.
		
			while (fgets(line, 100, products_file) != NULL) { //Until end of file taking the lines.
				
				sscanf(line, "%d,%*c,%*s,%*s,%*f", &pID_read); //Reading only pID value of line with pID_read.
				
				if (pID == pID_read) { //If pID value in line and input pID is same asking another pID value.
				printf("The pID value you entered is already used, please enter another pID!\n");
				pID_match = 1;
				break; // Exit loop if there's a match.
			}
		}	
		
		} while (pID_match);
	
	
		printf("Enter the type of product:");
		scanf(" %c",&type);
	
		printf("Enter the name of product:");
		scanf("%s",name);
	
		printf("Enter the brand of product:");
		scanf("%s",brand);
	
		printf("Enter the price of product:");
		scanf("%f",&price);
		
		//After pID value determined asking type,name,brand and price of product.
	
		fprintf(products_file,"%d,%c,%s,%s,%.1f\n",pID,type,name,brand,price); //Printing the taken product entry to products.txt.
	}
	
	fclose(products_file); //products.txt is closed.
}


void delete_product(){
	
	FILE *products_file = fopen("products.txt", "r"); //Read product.txt

    // Declare arrays to store products.
    struct Product products[100];
	
    int num_products = 0;
    char line[100];
    
    fgets(line, 100, products_file); // skip the header line
    
	while (fgets(line, 100, products_file) != NULL) {  //Keep reading until NULL line.
		
		//While reading products.txt,holds the values in struct.	
		sscanf(line,"%d,%c,%[^,],%[^,],%f",&products[num_products].pID
		                                    ,&products[num_products].Type
		                                    ,products[num_products].Name
		                                    ,products[num_products].Brand
		                                    ,&products[num_products].Price);
		num_products++;
	} 

	fclose(products_file); //Close products_file.
	
	FILE *temp_file = fopen("temp.txt","w"); //Open temp.txt in write mode.
	int pID_input,i; 
	
	printf("Enter the pID value to be deleted:");
	scanf("%d",&pID_input); //pID_input holds the pID which want to be deleted.

	for (i = 0; i < num_products; i++) {
		
		//If taken pID_input is greater than the pID value in struct element,then we still didn't find the pID_input value.
		//So,keep writing struct elements to temp_file.
		
		if (pID_input > products[i].pID) {
			fprintf(temp_file,"%d,%c,%s,%s,%.2f\n",products[i].pID
												,products[i].Type
												,products[i].Name
												,products[i].Brand
												,products[i].Price);
			

		} else if (pID_input < products[i].pID) {
			
		//If taken pID_input is lower than the pID value in struct element,then we passed the pID_input value.
		//So,while writing struct elements to temp_file,we need to substract 1 from products[].pID value.
			
			fprintf(temp_file,"%d,%c,%s,%s,%.2f\n",(products[i].pID - 1)
												,products[i].Type
												,products[i].Name
												,products[i].Brand
												,products[i].Price);
												
		}
	}
	
	fclose(temp_file); //Close temp_file.
	
	temp_file = fopen("temp.txt","r"); //Open temp_file in read mode.
	products_file = fopen("products.txt", "w"); //Open products_file in write mode.
	
	fprintf(products_file,"pID,Type,Name,Brand,Price\n"); //Print header line to products.txt.
    
	while (fgets(line, 100, temp_file) != NULL ) { //Until NULL line,keep reading line by line from temp.txt.
		fprintf(products_file,"%s",line); //Print the lines one by one to products_file
   	}
	
	fclose(temp_file); //Close temp_file
	fclose(products_file); //Close products_file

}


void add_stock_entry(){
	
	FILE *stocks_file = fopen("stocks.txt","a+"); //I opened the stocks.txt in a+ mode to append and read.
	
	char line[100]; //While reading line by line hold the string in line array.
	
	int sID,sID_read,sID_match;
	int pID,current_stock;
	char branch[20];	
	
	//sID,pID,branch[],current stock are the input variables.sID_read is sID value which read from taken line.sID_match controls input sID value.

	if(stocks_file == NULL){
		
		printf("The file cannot be opened!\n"); //Checked products.txt opened or not
		
	}else{
	
	
		do {
			sID_match = 0;  //I used sID_match to check if the sID entered by the user has already been used.
		
			printf("Enter the sID value for stock entry:");
			scanf("%d",&sID); //Asking sID value of stock wanted to add.
		
			rewind(stocks_file); // Reset file pointer to beginning of file
		
			while (fgets(line, 100, stocks_file) != NULL) { //Until end of file,taking the lines.
				sscanf(line, "%d,%*d,%*s,%*d", &sID_read);
				
				if (sID == sID_read) { //If sID value in line and input sID is same asking another sID value.
					printf("The sID value you entered is already used, please enter another sID!\n");
					sID_match = 1;
					break; // Exit loop if there's a match
				}
			}	
		
		}while (sID_match);
	
		printf("Enter the pID of stock entry:");
		scanf("%d",&pID);
	
		printf("Enter the branch of stock entry:");
		scanf("%s",branch);
	
		printf("Enter the current stock of stock_entry:");
		scanf("%d",&current_stock);
	
		//After sID value determined asking pID,branch and current stock of stock.
	
		fprintf(stocks_file,"%d,%d,%s,%d\n",sID,pID,branch,current_stock); ////Printing the taken stock entry to stocks.txt.
	
	}
		
	fclose(stocks_file); //stocks.txt is closed.
}

void delete_stock(){
	
	FILE *stocks_file = fopen("stocks.txt", "r"); //Read stocks.txt

	// Declare arrays to store stocks.
    struct Stock stocks[100];
	
    int num_stocks = 0;
    char line[100];
    
    fgets(line, 100, stocks_file); // skip the header line
    
	while (fgets(line, 100, stocks_file) != NULL) {  //Keep reading until NULL line.
	
		//While reading stocks.txt,holds the values in struct.	
		sscanf(line,"%d,%d,%[^,],%d",&stocks[num_stocks].sID
		                            ,&stocks[num_stocks].pID
		                            ,stocks[num_stocks].branch
		                            ,&stocks[num_stocks].current_stock);
		num_stocks++;
	}

	fclose(stocks_file);  //Close stocks_file
	
	FILE *temp_file = fopen("temp.txt","w"); //Open temp.txt in write mode.
	int sID_input,i;
	
	printf("Enter the sID value to be deleted:");
	scanf("%d",&sID_input);   //sID_input holds the sID which want to be deleted.

	for (i = 0; i < num_stocks; i++) {
		
		//If taken sID_input is greater than the sID value in struct element,then we still didn't find the sID_input value.
		//So,keep writing struct elements to temp_file.
	
		if (sID_input > stocks[i].sID) {
			fprintf(temp_file,"%d,%d,%s,%d\n",stocks[i].sID
		                            			,stocks[i].pID
		                            			,stocks[i].branch
		                            			,stocks[i].current_stock);
			

		} else if (sID_input < stocks[i].sID) {
			
		//If taken pID_input is lower than the sID value in struct element,then we passed the sID_input value.
		//So,while writing struct elements to temp_file,we need to substract 1 from stocks[].sID value.
			
			fprintf(temp_file,"%d,%d,%s,%d\n",(stocks[i].sID - 1)
		                            			,stocks[i].pID
		                            			,stocks[i].branch
		                            			,stocks[i].current_stock);
												
		}
	}
	
	fclose(temp_file); //Close temp_file.
	
	temp_file = fopen("temp.txt","r");  //Open temp.txt in read mode.
	stocks_file = fopen("stocks.txt", "w"); //Open stocks.txt in write modeç
	
	fprintf(stocks_file,"sID,pID,branch,currentStock\n"); //Print the header line.
    
	while (fgets(line, 100, temp_file) != NULL ) {  //Until NULL line,keep reading line by line from temp.txt.
		fprintf(stocks_file,"%s",line);  //Print the lines one by one to stocks_file
   	}
	
	fclose(temp_file); //Close temp_file
	fclose(stocks_file); //Close stocks_file

}

//Part3
void submenu_Part3(){
	
	int option, exit_flag = 0;

	do {
        
        printf("Enter an option to do selected operation(1-List all products,2-Filter Products,3-Go back to main menu): ");
        scanf("%d", &option);
        
        //According to option value related function called but some part are missing.Sorry about it.
        
        switch (option) {
            case 1:
                list_all_products();
                break;
            case 2:
                printf("This part isn't available.\n");
                break;
            case 3:
            	printf("Returning to main menu.\n");
                exit_flag = 1;
                break;
            default:
                printf("Invalid option. Please try again.\n");
                break;
        }
        
    } while (!exit_flag);
	
}


void list_all_products(){
	
	FILE *products_file = fopen("products.txt","r"); //Open products.txt in r mode to read.
	
	char line[100]; // While reading the products.txt,holding the lines in line[] array.
	
	while(fgets(line,100,products_file) != NULL){ //Until NULL line,continue to get lines.
		
		printf("%s",line); //Printing the line to terminal.
				
	}

	fclose(products_file);	//Close products.txt.
}

//Part4

void submenu_Part4() {
    
    int option,exit_flag = 0;

	do {
        
        printf("Enter an option for selected operation(1-Query Stock,2-List Branch Stocks,3-List Out of Stock for Branch,4-Go Back Main Menu): ");
        scanf("%d", &option);
        
        //According to option value,calling the related function.
        
        switch (option) {
            case 1:
                query_stock();
                break;
            case 2:
                list_branch_stocks();
                break;
            case 3:
                list_outof_stock();
                break;
            case 4:
                printf("Returning to main menu.\n");
                exit_flag = 1;
                break;
            default:
                printf("Invalid option. Please try again.\n");
                break;
        }
        
    } while (!exit_flag);

}

void query_stock(){
	
	FILE *stocks_file = fopen("stocks.txt","r"); //Open stocks.txt in read mode.
	
	
	int product_ID;
    char branch_name_input[20]; //product_ID and branch_name_input are input variables.
	
	int pID,current_stock;
	char branch[20]; //While reading the stocks.txt line by line holding pID,current_stock and branch values in variables.
	int total_stock = 0; //The total current_stocks of stock entries which filtered according to taken pID and branch values.
	
	char line[100]; //line array holds header line.
	
	if( stocks_file == NULL){ //Check file is available.
		
		printf("File cannot be opened!\n"); 
	
	}else{
	
		printf("Enter product ID:");
		scanf("%d",&product_ID); //Take pID value from user.
	
		printf("Enter the branch name:");
		scanf("%s",branch_name_input); //Take branch name from user and assign branc_name_input array.
	
	
		fgets(line, 100, stocks_file); //Skip the header line.
	
		while(!feof(stocks_file)){ //Check EOF of products.txt.
		
			fscanf(stocks_file,"%*d,%d,%[^,],%d",&pID,branch,&current_stock); 
			//Ignore sID values in lines and take pID,branch,current_stock values.
			
			//Compare pID and branch values of input and file values in lines.
			if(pID == product_ID && stringCompare(branch, branch_name_input)){
			
				total_stock += current_stock; //If pID and Branch is same for an entry by adding the current_stock values,find total_stock.
			
			}
		
		}
	
		printf("The product with ID number %d from %s branch has %d stock\n",product_ID,branch_name_input,total_stock);
		//Print	taken pID,branch values and total_stock value which is found.
	}	
	fclose(stocks_file); //Close stocks.txt.
}


void list_branch_stocks(){
	
	FILE *stocks_file = fopen("stocks.txt","r"); //Open stocks.txt in 'r' mode.
	
	char branch_name_input[20]; // branch_name_input array holds input branch name.
	
	int pID,current_stock;
	char branch[20]; //pID,current_stock and branch variables holds the values in file lines.

	char line[100]; //line array holds the header line.
		
	if( stocks_file == NULL){ //check file can be available.
		
		printf("File cannot be opened!\n");
	
	}else{
	
		printf("Enter the branch name:");
		scanf("%s",branch_name_input); //Input branch name is taken.
	
		printf("%s Branch Stocks\n",branch_name_input);
		printf("pID\tStocks\n");  //The header lines are printed to terminal
	
		fgets(line, 100, stocks_file); //Skip header line.
	
		while(fgets(line, 100, stocks_file) != NULL){ //Until NULL line,lines of file is taken.
		
			sscanf(line,"%*d,%d,%[^,],%d",&pID,branch,&current_stock); //sID value ignored,rest of line is assigned to variables.
		
			//If input branch and branch which read from line is same according tp stringCompare function,pID and current_stock values printed.		
			if(stringCompare(branch, branch_name_input)){
			
			printf("%d\t%d\n",pID,current_stock);	
			
			}
		
		}
	}
	
	fclose(stocks_file); //stocks.txt closed.
}


void list_outof_stock(){
	
	FILE *stocks_file = fopen("stocks.txt","r"); //Open stocks.txt in 'r' mode to read.

	char branch_name_input[20]; //product_ID and branch_name_input holds the input values taken from user.  
	
	int pID,current_stock;
	char branch[20]; //While reading the stocks.txt line by line holding pID,current_stock and branch values in variables.
	
	char line[100]; //line array holds header line.
	
	if( stocks_file == NULL){ //Check stock.txt is available.
		
		printf("File cannot be opened!\n");
	
	}else{
	
		printf("Enter the branch name:");
		scanf("%s",branch_name_input);  //branch name is taken from user.
	
		printf("%s Branch without Stocks\n",branch_name_input);
		printf("pID\tCurrent Stock\n"); //header lines for out of stock list is printed to terminal.
	
		fgets(line, 100, stocks_file); //Skip the header line.
	
		while(fgets(line, 100, stocks_file) != NULL){ //Until the NULL line,loop continues to read lines.
		
			sscanf(line,"%*d,%d,%[^,],%d",&pID,branch,&current_stock); // Ignore sID value and assign rest of the array to variables.
			
			//If branch names are same and current stock value is 0,print pID and current_stock to terminal.
			if(stringCompare(branch, branch_name_input) && current_stock == 0){
			
				printf("%d\t%d\n",pID,current_stock);
			
			}
		
		}
	}
	
	fclose(stocks_file); //Close stock.txt.	
}

//Part5
void brand_stock_control(){
	
	// Read products.txt and stock.txt files.
    FILE *products_file = fopen("products.txt", "r");
    FILE *stock_file = fopen("stocks.txt", "r");

    // Declare arrays to store products and stocks.
    struct Product products[100];
    struct Stock stocks[100];
	
    // Read products from the file and store them in the products array
    int num_products = 0;
    char line[100];
    int i,j;
    
    fgets(line, 100, products_file); // skip the header line
    
	while ( fgets(line, 100, products_file) != NULL ){ //Keep reading the lines until the NULL line.
        
		sscanf(line,"%d,%c,%[^,],%[^,],%f",&products[num_products].pID
													,&products[num_products].Type
													,products[num_products].Name
													,products[num_products].Brand
													,&products[num_products].Price );
        
        num_products++;
    }
    
   
	// Read stocks from the file and store them in the stocks array
    int num_stocks = 0;
    
	fgets(line, 100, stock_file); // skip the header line
    
	while (fgets(line, 100, stock_file) != NULL ) { //Keep reading the lines until the NULL line.
        
		sscanf(line,"%d,%d,%[^,],%d",&stocks[num_stocks].sID
											 ,&stocks[num_stocks].pID
									   		 ,stocks[num_stocks].branch
											 ,&stocks[num_stocks].current_stock );
        
        num_stocks++;
    }
    

    // Close the files
    fclose(products_file);
    fclose(stock_file);

    
    // Take brand name from the user
    char brand[20];
    printf("Enter a brand name: ");
    scanf("%s", brand);

    // Declare and initialize the 2D array to store the products and their current stock
    float product_stock[100][3];
    int num_products_with_stock = 0;
    

    // Iterate over the products and stocks arrays and find the products with the given brand
    for (i = 0; i < num_products; i++) { 
    	
        if ( (stringCompare(products[i].Brand, brand)) ) {
            // Find the stock of this product in each branch
            int total_stock = 0;
            for (j = 0; j < num_stocks; j++) {
                
				if (stocks[j].pID == products[i].pID) {
                    
					total_stock += stocks[j].current_stock;

				}
            }

            // Store the pID, price, and current stock of this product in the product_stock array
            product_stock[num_products_with_stock][0] = products[i].pID;
            product_stock[num_products_with_stock][1] = products[i].Price;
            product_stock[num_products_with_stock][2] = total_stock;

            num_products_with_stock++;
            	
        }
        
    }
    

    // Print the product_stock array
    printf("Products of brand %s with their current stock:\n", brand);
	
	printf("pID\tPrice\tTotal_Stock\n");
	
	for (i = 0; i < num_products_with_stock; i++) {
    	printf("%d\t%.2f\t%d\n", (int)product_stock[i][0], product_stock[i][1], (int)product_stock[i][2]);
	}
	
}

//Part6
void print_report(){
	
	// Read products.txt and stock.txt files.
	FILE *products_file = fopen("products.txt", "r");
    FILE *stock_file = fopen("stocks.txt", "r");

    // Declare arrays to store products and stocks
    struct Product products[100];
    struct Stock stocks[100];
	
    // Read products from the file and store them in the products array
    int num_products = 0;
    char line[100];
    int i,j;
    
    fgets(line, 100, products_file); // skip the header line
    
		while ( fgets(line, 100, products_file) != NULL ){ //Keep reading the lines until the NULL line.
        
		sscanf(line,"%d,%c,%[^,],%[^,],%f",&products[num_products].pID
													,&products[num_products].Type
													,products[num_products].Name
													,products[num_products].Brand
													,&products[num_products].Price );
        
        num_products++;
    }
    
   
	// Read stocks from the file and store them in the stocks array
    int num_stocks = 0;
    
	fgets(line, 100, stock_file); // skip the header line
    
	while (fgets(line, 100, stock_file) != NULL ) { //Keep reading the lines until the NULL line.
        
		sscanf(line,"%d,%d,%[^,],%d",&stocks[num_stocks].sID
											 ,&stocks[num_stocks].pID
									   		 ,stocks[num_stocks].branch
											 ,&stocks[num_stocks].current_stock );
        
        num_stocks++;
    }
    

    // Close the files
    fclose(products_file);
    fclose(stock_file);

    
	FILE *report_file = fopen("report.txt","w"); //Open report.txt in write mode.
	int stock_values[20]; //stock_values[] array holds the current stock values of the given brand
    int stock_counter,median_index; 
	//stock_counter count the number of entry for stock values,median_index indicate the middle element of stock_values array.
    
    fprintf(report_file,"pID,minimum_stock,maximum_stock,median_stock\n"); //Print header line to report.txt

    char brand[20];
    printf("Enter a brand name: ");
    scanf("%s", brand); //brand name is taken as input value.


    for (i = 0; i < num_products; i++) {
    	
		stock_counter = 0; //stock_counter is initialized for every pID value of given brand. 
    	
    	//Used stringCompare function to compare input brand and brand read from products.txt.
        if ( (stringCompare(products[i].Brand, brand)) ) { 

            for (j = 0; j < num_stocks; j++) {
                
				if (stocks[j].pID == products[i].pID) {
					
                    //Every current stock value of a pID is holded in stock_values array and stock_counter incremented.
                    stock_values[stock_counter] = stocks[j].current_stock; 
					stock_counter++;
				}
            }
            	
        }
        
        
        bubble_sort(stock_values,stock_counter); //stock_values array is sorted in ascending order.
        
        //If stock_counter is greater than 0,it means for selected pID value with i variable in loop has stock_values for given brand.
        if(stock_counter > 0){ 
        	
        	//median_index is found according to stock_counter(number of elements in stock_values array).
        	if(stock_counter % 2 == 0){
        		
        		median_index = (stock_counter/2) - 1;
        		
			}else if(stock_counter % 2 == 1){
				
				median_index = (stock_counter-1) / 2;
			}
        	
        	//The pID,min_stock_value,max_stock_value,median_stock_value for given brand is printed to report.txt.
        	fprintf(report_file,"%d,%d,%d,%d\n",products[i].pID,stock_values[0],stock_values[stock_counter-1],stock_values[median_index]);
		}
    }
    
	fclose(report_file); //Close report.txt.
}


int stringCompare(char str1[], char str2[]) {
    int i = 0;

	//Checking every array character one by one if there is inequality returns 0.
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return 0; // strings are not equal
        }
        i++;
    }
	
	//If the arrays has same chracters until 'i'th index and 'i'th index is the NULL,returns 1 else returns 0.
    if (str1[i] == '\0' && str2[i] == '\0') {
        return 1; // strings are equal
    } else {
        return 0; // strings are not equal
    }
}


void bubble_sort(int arr[], int n){
    
    //Checking every array elements,and using temp,swapping the elements in ascending order using bubble sort algorithm.
    
	int i, j, temp;
    
	for (i = 0; i < n - 1; i++){

        for (j = 0; j < n - i - 1; j++){
		
			if (arr[j] > arr[j + 1]){
            temp = arr[j+1];
			arr[j+1] = arr[j];
			arr[j] = temp; 	
            	
            }       
		}	
	}
}

