#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define RANDMAX 100

typedef struct Node {
    void* data;
    struct Node* next;
} Node;

typedef struct {
    char type[20];
    int ivals[1];
    double svals[1];
} Asset1;

typedef struct {
    char type[20];
    double svals[2];
    int ivals[2];
} Asset2;

typedef struct {
    char type[20];
    char string1[50];
    char string2[50];
} Asset3;

typedef struct {
    char type[20];
    double value1;
    float value2;
    double value3;
} Asset4;


void fillLinkedList(struct Node** head);
void serializeLinkedList(struct Node* head);
void deserializeLinkedList(struct Node** head);
void printLinkedList(struct Node* head);
void freeLinkedList(struct Node** head);

int main(){
    
	Node* head = NULL;
	
	//A linked list randomly generated using fillLinkedList function and printed to terminal.
    fillLinkedList(&head);
    printLinkedList(head);
    
    //The linked list serialized to binary file and linked list freed.
	serializeLinkedList(head);
	freeLinkedList(&head);
	
	//A new linked generated while deserializing the binary file and printed to terminal.
	head = NULL;
	deserializeLinkedList(&head);
    printLinkedList(head);
    
    freeLinkedList(&head); //The linked list freed.
    return 0;
}


void fillLinkedList(struct Node** head){
    
    Node* newNode;
    Node* current = *head;
	int i;
	int assetNum, assetType; 
	
    srand(time(NULL));

	//assetNum holds the number of asset in the linked list.It is between 10-20.
    assetNum = rand() % 11 + 10;

    for(i = 0; i < assetNum; i++){
        
        //newNode is generated for linked list.
        newNode = (Node*)malloc(sizeof(Node));
        newNode->next = NULL;

		assetType = rand() % 4 + 1; //assetType holds the generated asset's type.
        
        //According to random assetType,some memory generated and the random data is holds there.The newNode->data assigned to asset.
        switch(assetType){
            case 1:{
                Asset1* asset = (Asset1*)malloc(sizeof(Asset1));
                strcpy(asset->type, "Asset1");
                asset->ivals[0] = rand() % RANDMAX;
                asset->svals[0] = (double)(rand() % 1000) / 10.0;
                newNode->data = asset;
                break;
            }
            case 2:{
                Asset2* asset = (Asset2*)malloc(sizeof(Asset2));
                strcpy(asset->type, "Asset2");
                asset->svals[0] = (double)(rand() % 1000) / 10.0;
                asset->svals[1] = (double)(rand() % 1000) / 10.0;
                asset->ivals[0] = rand() % RANDMAX;
                asset->ivals[1] = rand() % RANDMAX;
                newNode->data = asset;
                break;
            }
            case 3:{
                Asset3* asset = (Asset3*)malloc(sizeof(Asset3));
                strcpy(asset->type, "Asset3");
                sprintf(asset->string1, "String1/%d", i);
                sprintf(asset->string2, "String2/%d", i);
                newNode->data = asset;
                break;
            }
            case 4:{
                Asset4* asset = (Asset4*)malloc(sizeof(Asset4));
                strcpy(asset->type, "Asset4");
                asset->value1 = (double)(rand() % 1000) / 10.0;
                asset->value2 = (float)(rand() % 1000) / 10.0f;
                asset->value3 = (double)(rand() % 1000) / 10.0;
                newNode->data = asset;
                break;
            }
        }
	
		//Using this if-else statement,the code iterates over linked list and newNode assigned to correct place. 
        if(*head == NULL){
            *head = newNode;
        }else{
            current->next = newNode;
        }
        current = newNode;
    }
    
    printf("---Linked list generated successfully---\n"); //A message printed to control the fillLinkedList function.
}

void serializeLinkedList(struct Node* head){
	
    FILE* file = fopen("linkedlist.bin", "wb"); //Selected file opened to write in binary form.
    Node* current = head; //current pointer goes over linked list while linked list printing.
    
    //The file is controlled to prevent an error.
	if(file == NULL){
        printf("---ERROR! The file cannot be opened.---\n");
        return;
    }
    
    //Until all linked list printed this while loop continues. 
	//In the if-else statements,type of each asset in the node is determined and according to asset type,asset is printed to file.
	while(current != NULL){ 
		
        if(strcmp(((Asset1*)current->data)->type, "Asset1") == 0){
            fwrite(current->data, sizeof(Asset1), 1, file);
            
        }else if(strcmp(((Asset2*)current->data)->type, "Asset2") == 0){
            fwrite(current->data, sizeof(Asset2), 1, file);
            
        }else if(strcmp(((Asset3*)current->data)->type, "Asset3") == 0){
            fwrite(current->data, sizeof(Asset3), 1, file);
            
        }else if(strcmp(((Asset4*)current->data)->type, "Asset4") == 0){
            fwrite(current->data, sizeof(Asset4), 1, file);
        }

        current = current->next;
    }

    fclose(file); //File closed.
	//A message printed to control the serializeLinkedList function.
    printf("---The linked list is serialized to linkedlist.bin successfully.---\n");
}


void deserializeLinkedList(struct Node** head){
	
    FILE* file = fopen("linkedlist.bin", "rb"); ////Selected file opened to read in binary form.
    
    //The file is controlled to prevent an error.
    if(file == NULL){
        printf("---ERROR! The file cannot be opened.---\n");
        return;
    }
    
    char assetType[20]; //assetType holds the asset type in the node.
    size_t assetSize = 0; //assetSize holds the asset structs' size.
    void* asset; //asset pointers points to the dynamically allocated asset's memory. 
    Node* newNode;
    Node* current = *head;
    
    //Until the end of the file,this continues to read the selected file.
    while(!feof(file)){
        
        fread(assetType, sizeof(char), sizeof(assetType), file); //The 20 bytes of file is read and assigned to assetType.

		//According to the asseType,the asset which read and its size is determined.
        if(strcmp(assetType, "Asset1") == 0){
            assetSize = sizeof(Asset1);
            
        }else if(strcmp(assetType, "Asset2") == 0){
            assetSize = sizeof(Asset2);
            
        }else if(strcmp(assetType, "Asset3") == 0){
            assetSize = sizeof(Asset3);
            
        }else if(strcmp(assetType, "Asset4") == 0){
            assetSize = sizeof(Asset4);
        }

        fseek(file, -20, SEEK_CUR); //By using fseek,I returned the begining of the asset. 
		
		//According to the assetSize,some memory allocated and this memory assigned to the asset in the file by using fread.
        asset = malloc(assetSize); 
        fread(asset, assetSize, 1, file);
        
        //For the asset,a newNode created dynamically, and newNode's data points to the asset.
        newNode = (Node*)malloc(sizeof(Node));
        newNode->data = asset;
        newNode->next = NULL;

		//Using this if-else statement,the code iterates over linked list and newNode assigned to correct place. 
        if(*head == NULL){
            *head = newNode;
        }else{
            current->next = newNode;
        }
        current = newNode;
    }

	//At the end,file is closed and a message is printed to control the function.
    fclose(file);

    printf("---The linked list is deserialized from linkedlist.bin successfully.---\n");
}



void printLinkedList(struct Node* head){
    
	Node* current = head; //current pointers goes over the linked list.

	//The linked list is controlled.If it is empty a message printed.
    if (head == NULL) {
        printf("---The linked list is empty.---\n");
        return;
    }
	
	//This while loop continues until all nodes is printed.
	//In the if-else statements,assetType is controlled to find correct asset and then,asset is printed.
    while(current != NULL){
        if(strcmp(((Asset1*)current->data)->type, "Asset1") == 0){
            Asset1* asset = (Asset1*)(current->data);
            printf("Asset1: ivals[0] = %d, svals[0] = %.1lf\n", asset->ivals[0], asset->svals[0]);
            
        }else if(strcmp(((Asset2*)current->data)->type, "Asset2") == 0){
            Asset2* asset = (Asset2*)(current->data);
            printf("Asset2: svals[0] = %.1lf, svals[1] = %.1lf, ivals[0] = %d, ivals[1] = %d\n",
                   asset->svals[0], asset->svals[1], asset->ivals[0], asset->ivals[1]);
                   
        }else if(strcmp(((Asset3*)current->data)->type, "Asset3") == 0){
            Asset3* asset = (Asset3*)(current->data);
            printf("Asset3: string1 = %s, string2 = %s\n", asset->string1, asset->string2);
            
        }else if(strcmp(((Asset4*)current->data)->type, "Asset4") == 0){
            Asset4* asset = (Asset4*)(current->data);
            printf("Asset4: value1 = %.1lf, value2 = %.1f, value3 = %.1lf\n",
                   asset->value1, asset->value2, asset->value3);
        }

        current = current->next;
    }
}

void freeLinkedList(struct Node** head) {
    Node* current = *head;
    Node* next;
	
	//Using current and next pointers,I freed all nodes in the linked list.
    while(current != NULL){
        next = current->next;
        free(current->data);
        free(current);
        current = next;
    }

    *head = NULL; // Reset the head pointer to NULL after freeing all nodes
}
