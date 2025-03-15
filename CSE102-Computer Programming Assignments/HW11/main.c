#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
	
	char name[30];
	int age;
	struct node* mother;
	struct node* father;
	struct node* children[5];

}node;


void menu();
void addNode(node* roots[4]);
void removeNode(node* roots[4]);
void printNuclearFamily(node* roots[4]);
void printRelatives(node* roots[4]);
void printFamilyFile(FILE* fp, node* root);
node* searchNode(node* root, char name[30]);
void freeFamilyTree(node* root);


int main(){
	
	menu();
    
	return 0;
}


void menu(){
	
	int choice, i;
	node* roots[4] = {NULL}; //roots holds the adress of veryfirst grandparents.
	
	char fileName[30]; 
	FILE* familyFile;
	
	do{
		printf("1. Add Node\n");
		printf("2. Print a Person's Nuclear Family\n");
		printf("3. Print a Person's Relatives\n");
		printf("4. Remove Node\n");
		printf("5. Save Family Tree\n");
		printf("6. Remove Family\n");
		printf("7. Exit\n> ");	
		scanf("%d",&choice); //The choice of user is taken.

		//According to the choice selected operation is made.
		switch(choice){
			case 1:
					addNode(roots);
					break;
			case 2:
					printNuclearFamily(roots);
					break;
			case 3:
					printRelatives(roots);		
					break;
			case 4:
					removeNode(roots);
					break;
			case 5:
					printf("Enter the name of the file:");
					scanf("%s", fileName); //To print the tree,a file name is taken.
					
					//The familyTree is printed to selectedFile by using printFamilyFile function.
					familyFile = fopen(fileName,"w");
					for(i = 0; i < 4; i++){
							printFamilyFile(familyFile, roots[i]);
					}
					
					fclose(familyFile); //File is closed and a message printed to control the program.
					printf("The family is printed to the %s file successfully.\n", fileName);
					break;
			case 6:
					printf("Enter the name of the familyFile to remove:");
					scanf("%s", fileName); //To remove the file,a filename is taken
					
					remove(fileName); //selected file is removed by using remove function. 
					printf("The selected %s file is deleted successfully.\n", fileName);
					break;
			case 7:
					printf("Program terminated\n");
					break;	
			default:
					printf("Please enter a valid input!\n");
					break;	
		}
		
	}while(choice != 7);
	
	//FamilyTree is freed.
	for(i = 0; i < 4; i++){
		freeFamilyTree(roots[i]);
	}
}

void addNode(node* roots[4]){
	
	int i, j;
	static int rootNumber = 0; //rootNumber variable holds the number of grandparents that assigned to roots[4] array.
	node* newnode;
	node* selectedNode = NULL;
	
	char mother[30];
	char father[30];
	
	//The user firstly must enter the very first grandparents which must be 4.
	if(rootNumber < 4){
		
		//To add the grandmother,a memory allocated and her name-age is taken as input and father,mother,children pointers assigned to NULL.
		newnode = (node*)malloc(sizeof(node));
		printf("Enter the name of grandmother:");
		scanf("%s", newnode->name);
		printf("Enter the age of grandmother:");
		scanf("%d", &(newnode->age));
		newnode->father = NULL;
		newnode->mother = NULL;
		
		for(i = 0; i < 5; i++){
    		newnode->children[i] = NULL;
		}
		
		roots[rootNumber] = newnode; //newNode assigned in roots array and rootsNumber increased.
		rootNumber++;
	
		//To add the grandfather,a memory allocated and her name-age is taken as input and father,mother,children pointers assigned to NULL.
		newnode = (node*)malloc(sizeof(node));
		printf("Enter the name of grandfather:");
		scanf("%s", newnode->name);
		printf("Enter the age of grandfather:");
		scanf("%d", &(newnode->age));
		newnode->father = NULL;
		newnode->mother = NULL;
		
		for(i = 0; i < 5; i++){
    		newnode->children[i] = NULL;
		}
		
		roots[rootNumber] = newnode; //newNode assigned in roots array and rootsNumber increased.
		rootNumber++;
	
	}else{
		
		//To add a node except of roots,a newNode generated dynamically and inputs are taken.
		newnode = (node*)malloc(sizeof(node));
		printf("Enter the name of person:");
		scanf("%s", newnode->name);
		printf("Enter the age of person:");
		scanf("%d", &(newnode->age));
		printf("Enter the mother's name of person:");
		scanf("%s", mother);
		printf("Enter the father's name of person:");
		scanf("%s", father);
		
		//Children of newNode assigned as NULL.
		for(i = 0; i < 5; i++){
    		newnode->children[i] = NULL;
		}
		
		//Using this loop,the place of mother of newNode will be found.
		for(i = 0; i <= 2; i = i + 2){
		
			selectedNode = searchNode(roots[i], mother); //mother of newNode is found.
		
			//If selectedNode ism't NULL,this means mother is found.  
			if(selectedNode != NULL){
				newnode->mother = selectedNode; //newNode's mother pointer updated. 
				
					//Until a Null node,mother's children array elements will be passed.
					j = 0;
					while(newnode->mother->children[j] != NULL){
						j++;
					}
					newnode->mother->children[j] = newnode; //First Null node assigned as newnode.
					
				printf("Mother is found!\n"); //A message is printed to control the program.
				break;
			}
		}
		
		selectedNode = NULL; //SelectedNode assigned to NUll before finding father.
		//Using this loop,the place of father of newNode will be found.
		for(i = 1; i <= 3; i = i + 2){
		
			selectedNode = searchNode(roots[i], father); //father of newNode is found.
		
			//If selectedNode ism't NULL,this means father is found.  
			if(selectedNode != NULL){
				newnode->father = selectedNode; //newNode's father pointer updated. 
				
				//Until a Null node,father's children array elements will be passed.
				j = 0;
				while(newnode->father->children[j] != NULL){
					j++;
				}
				newnode->father->children[j] = newnode; //First Null node assigned as newnode.
				
				printf("Father is found!\n"); //A message is printed to control the program.
				break;			
			}
		}
		
		//The node that is added will printed to control the correctness of add process.
		printf("%s,%d,%s,%s\n",newnode->name,newnode->age,newnode->mother->name,newnode->father->name);	
	}
	
}

void printNuclearFamily(node* roots[4]){

	int i;
	char name[30];
	node* selectedNode = NULL;
	
	//The family is controlled for being NULL.
	if(roots[0] == NULL){
		printf("ERROR!There is no member of a family.\n");
		return;
	}
	
	printf("Enter the name of person you wanted to see nuclear family:");
	scanf("%s", name);	//The family member selected by user.

	for(i = 0; i < 4; i++){
		selectedNode = searchNode(roots[i], name); //selectedNode is found in tree.
		
		if(selectedNode != NULL){
			break;
		}
	}
	
	//If selectedNode is Null,that means there is no person with selected name.
	if(selectedNode == NULL){
		printf("A person with name %s cannot be found in the family tree.Going back to menu.\n", name);
		return;
	}else{
		printf("---The Nuclear Family of %s---\n", name);
		
		//Mother is printed.
		if(selectedNode->mother != NULL){
			printf("Mother:%s\n", selectedNode->mother->name);
		}else{
			printf("Mother:Unknown Person.\n");
		}
		
		//Father is printed.
		if(selectedNode->father != NULL){
			printf("Father:%s\n", selectedNode->father->name);
		}else{
			printf("Father:Unknown Person.\n");
		}

		//If mother and father pointers not Null, the children array of mother is controlled 
		//and all childrens of mother is printed except of the selected child.		
		if (selectedNode->mother != NULL && selectedNode->father != NULL) {
            
			printf("Siblings:");
            for (i = 0; i < 5; i++) {
                if(selectedNode->mother->children[i] != NULL && strcmp(selectedNode->mother->children[i]->name, name) != 0 ){
                    printf("%s ", selectedNode->mother->children[i]->name);
                }
            }
            printf("\n");
		}else{
            printf("Siblings: None\n");
        }
		
		//Cildren array is control for being Null or not.
		if(selectedNode->children[0] != NULL){
			
			//The children of selectedNode printed.
			printf("Children:");
			i=0;
			while(selectedNode->children[i] != NULL){
				
				printf("%s ", selectedNode->children[i]->name);
				i++;
			}
			
			//The spouse of selectedNode is found in this if-else staement and it is printed.
			if(selectedNode->children[0]->mother != NULL && selectedNode->children[0]->father != NULL) {
   				if(strcmp(selectedNode->children[0]->mother->name, name) == 0) {
        			printf("\nSpouse:%s\n", selectedNode->children[0]->father->name);
    			}else{
        			printf("\nSpouse:%s\n", selectedNode->children[0]->mother->name);
    			}
			}
		
		}else{
			
			printf("Children:None.\n");
			printf("Spouse:None.\n");
		}		
	}
}

void printRelatives(node* roots[4]){
	
	int choice, i, j, k;
	char name[30];
	node* selectedNode = NULL;
	node* selectedGrandmother;
	node* selectedMother;
	
	//The family is controlled for being NULL.
	if(roots[0] == NULL){
		printf("ERROR!There is no member of a family.\n");
		return;
	}
	
	printf("Enter the name of the person to search relatives:");
	scanf("%s", name); //The person selected by user.
	
	printf("Select a type of relative:\n");
	printf("1. Parents\n");
	printf("2. Spouse\n");
	printf("3. Children\n");
	printf("4. Grandparents\n");
	printf("5. Cousins\n>");
	scanf("%d", &choice); //The choice is determined by user.
	
	//The selectedNode is found.
	for(i = 0; i < 4; i++){
		selectedNode = searchNode(roots[i], name);
		
		if(selectedNode != NULL){
			break;
		}
	}
	
	//If selectedNode is NULL,this means there is nobody with that name in the tree.
	if(selectedNode == NULL){
		printf("A person with name %s cannot be found in the family tree.Going back to menu.\n", name);
		return;	
	}else{
		switch(choice){
			case 1:
				//Mother is printed.
				if(selectedNode->mother != NULL){
					printf("%s Mother:%s\n", name, selectedNode->mother->name);
				}else{
					printf("%s Mother:Unknown Person.\n", name);
				}
				//Father is printed.
				if(selectedNode->father != NULL){
					printf("%s Father:%s\n", name, selectedNode->father->name);
				}else{
					printf("%s Father:Unknown Person.\n", name);
				}
				break;
			case 2:
				//Children array,the mother and father of children is cotrolled for not being NULL.
				//Then the name of mother-father name is compared with selectedNode's name.The name which is not matched is printed as spouse.
				if(selectedNode->children[0] != NULL){
					if(selectedNode->children[0]->mother != NULL && selectedNode->children[0]->father != NULL){
	   					if(strcmp(selectedNode->children[0]->mother->name, name) == 0) {
	       					printf("%s Spouse:%s\n", name, selectedNode->children[0]->father->name);
	    				}else{
	       					printf("%s Spouse:%s\n", name, selectedNode->children[0]->mother->name);
	    				}	
					}
				}else{
					printf("%s Spouse:None.\n", name);
				}	
				break;
			case 3:
				//Children array is checked for not being NULL.
				if(selectedNode->children[0] != NULL){
					//The children of selectedNode is printed.
					printf("%s Children:", name);
					i=0;
					while(selectedNode->children[i] != NULL){
			
						printf("%s ", selectedNode->children[i]->name);
						i++;
					}
					printf("\n");
				}else{
					printf("%s Children:None.\n", name);
				}
				break;
			case 4:
				//Mother and father pointers of selectedNode controlled for not being NULL.
				if(selectedNode->mother != NULL && selectedNode->father != NULL){
					//If mother's father pointer is not Null,grandfather is printed.	
					printf("%s Grandfather:", name);
					if(selectedNode->mother->father != NULL){
						printf("%s,", selectedNode->mother->father->name);
					}else{
						printf("Unknown Person,");
					}
					//If father's father pointer is not Null,grandfather is printed.	
					if(selectedNode->father->father != NULL){
						printf("%s\n", selectedNode->father->father->name);
					}else{
						printf("Unknown Person\n");
					}
					//If mother's mother pointer is not Null,grandmother is printed.	
					printf("%s Grandmother:", name);
					if(selectedNode->mother->mother != NULL){
						printf("%s,", selectedNode->mother->mother->name);
					}else{
						printf("Unknown Person,");
					}
					//If father's mother pointer is not Null,grandmother is printed.	
					if(selectedNode->father->mother != NULL){
						printf("%s\n", selectedNode->father->mother->name);
					}else{
						printf("Unknown Person\n");
					}	
				}
				break;
			case 5:
				//Mother and father pointers of selectedNode controlled for not being NULL.
				if(selectedNode->mother != NULL && selectedNode->father != NULL){
					
					selectedMother = selectedNode->mother; //selectedNode's mother assigned as selectedMother.	
            			
					printf("%s Cousin:", name);
            			
					if(selectedMother->mother != NULL){ //Mother pointer of selectedMother controlled for not being NULL.
						
						selectedGrandmother = selectedMother->mother; //selectedMother's mother assigned as selectedGrandmother.
            				
           				for(i = 0; i < 5; i++){
            				
           					if(selectedGrandmother->children[i] != NULL && strcmp(selectedGrandmother->children[i]->name, selectedMother->name) != 0){
                    				
								for(j = 0; j < 5; j++){
									//The all grandchildren of selectedGrandmother except of selectedNode's children is printed as cousin.
									if(selectedGrandmother->children[i]->children[j] != NULL){
										printf("%s ", selectedGrandmother->children[i]->children[j]->name);
									}
								}	
							}
						}
					}
					printf("\n");
				}else{
		            printf("%s Cousin:None.\n", name);
		        }	
				break;				
			default:
				printf("Please enter a valid input!\n");
				break;	
		}
	}	
}

void removeNode(node* roots[4]){
	
	int choice, i, j;
	char name[30];
	node* selectedNode = NULL;
	
	//The family is controlled for being NULL.
	if(roots[0] == NULL){
		printf("ERROR!There is no member of a family.\n");
		return;
	}
	
	printf("Enter the name of the person you wanted to remove:");
	scanf("%s", name); //The name input is taken as input from user.
	
	//selectedNode is searched using searchNode function.
	for(i = 0; i < 4; i++){
		
		selectedNode = searchNode(roots[i], name);
		
		if(selectedNode != NULL){
			break;
		}
	}
	
	//selectedNode is controlled for being NULL or not.
	if(selectedNode == NULL){
		printf("A person with the selected name cannot be found in the tree\n");
	}else{
		//Children of selectedNode is controlled.
		j = 0;
		while(selectedNode->children[j] != NULL){				
			j++;
			break;
		}
		
		if(j != 0){
			//If selectedNode has children,a warning message printed to user.
			printf("Warning!%s has children,removing %s will also remove his/her children.Do you still want to continue(1-Yes/0-No):"
					, name, name);
			scanf("%d", &choice);
			
			if(choice){
				
				//Before freeing selectedNode,selectedNode's children pointers assigned as NULL.
				if(selectedNode->children[0]->mother != NULL && selectedNode->children[0]->father != NULL){
				
					if(strcmp(selectedNode->children[0]->mother->name, selectedNode->name) == 0){
						for(i = 0;i < 5;i++){
						selectedNode->children[0]->father->children[i] = NULL;	
		    			}
					}else{
						for(i = 0; i < 5; i++){
						selectedNode->children[0]->mother->children[i] = NULL;	
		    			}
		    		}
				}
				
				freeFamilyTree(selectedNode); //selectedNode and the nodes below are freed.
				selectedNode = NULL;
				printf("%s and his/her children is removed.\n", name);
				
			}else{
				printf("Going back to menu.");
				return;
			}
			
		}else{
			freeFamilyTree(selectedNode); //If selectedNode has no children,selectedNode directly freed.
			selectedNode = NULL;
			printf("%s is removed.\n", name);
		}
	}	
		
}

void printFamilyFile(FILE* fp, node* root) {
	
	int i;
	
	//The family is controlled for being NULL.
	if (root == NULL){
		printf("ERROR!There is no member in the family.\n");
		return;
	}
	//The root is printed with elements of struct.
	fprintf(fp, "%s,%d,%s,%s\n", root->name, root->age, root->mother->name, root->father->name);

	// Recursively print the family tree for each child
	for (i = 0; i < 5; i++) {
		if (root->children[i] != NULL)
			printFamilyFile(fp, root->children[i]);
	}
}


node* searchNode(node* root, char name[30]){
    int i;
    node* selectedNode = NULL;
    
    //If the name sent and root's name is same this means selectedNode is found and it is returned.
    if(strcmp(root->name, name) == 0){
        selectedNode = root;
        return selectedNode;
    }
    
    //Recursively the selectedNode is searched in the children of root.
    for(i = 0; i < 5; i++){
        if(root->children[i] != NULL){
            selectedNode = searchNode(root->children[i], name);
            
            if(selectedNode != NULL)
                return selectedNode;
        }
    }
    
    return selectedNode; // SelectedNode is returned as NULL or the found selectedNode.
}


void freeFamilyTree(node* root){
    
	int i;
	
	if (root == NULL){
        return;
    }
    //Recursively all elements is freed.
    for (i = 0; i < 5; i++) {
        freeFamilyTree(root->children[i]);
    }
    
    free(root);
}

