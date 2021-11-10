#include<stdio.h>
#include<string.h>
#include<ctype.h>

#define MAX 5

typedef struct
{
 int nameCardID;
 char personName[20];
 char companyName[20];
} NameCard; 

void listNameCards(NameCard card[MAX], int *number_of_elements);
void addNameCard(NameCard card[MAX], int *number_of_elements);
void removeNameCard(NameCard card[MAX], int *number_of_elements);
void getNameCard(NameCard card[MAX], int *number_of_elements);
int searchID(NameCard card[MAX], int *number_of_elements, int targetID);
void sortStructure(NameCard card[MAX], int *number_of_element);
int stringCompareIgnoreCase(char string1[20],char string2[20]);
int searchName(NameCard card[MAX], int *number_of_elements, char targetName[20]);

void listNameCards(NameCard card[MAX], int *number_of_elements){
    int i=0;
    printf("listNameCards():\n");

    if((*number_of_elements)==0){
        printf("The name card holder is empty\n");
    } else {
        for(i=0; i<(*number_of_elements); i++){
            printf("nameCardID: %d\n", card[i].nameCardID);
            printf("personName: %s\n", card[i].personName);
            printf("companyName: %s\n", card[i].companyName);
        }
    }
}

void addNameCard(NameCard card[MAX], int *number_of_elements){
    int c, i=0;
    NameCard inputCard;
    char *p;
    char dummy;
    printf("addNameCard():\n");

    
    printf("Enter nameCardID:\n");
    scanf("%d", &inputCard.nameCardID);

    printf("Enter personName:\n");
    scanf("%c", &dummy);
    fgets(inputCard.personName, 20, stdin);
    if(p = strchr(inputCard.personName, '\n')){
        *p = '\0';
    }

    printf("Enter companyName:\n");
    fgets(inputCard.companyName, 20, stdin);
    if(p = strchr(inputCard.companyName, '\n')){
        *p = '\0';
    }
    

    if(*number_of_elements == MAX){
        printf("The name card holder is full\n");
        return;
    } else if(searchID(card, number_of_elements, inputCard.nameCardID)){
        printf("The nameCardID has already existed\n");
    } else {
        card[*number_of_elements].nameCardID = inputCard.nameCardID;
        strcpy(card[*number_of_elements].personName, inputCard.personName);
        strcpy(card[*number_of_elements].companyName, inputCard.companyName);
        *number_of_elements += 1;
        printf("The name card has been added successfully\n");
    }
}

void removeNameCard(NameCard card[MAX], int *number_of_elements){
    int i=0, index=-1;
    char *p;
    char dummy;
    char targetName[20];

    printf("removeNameCard():\n");

    printf("Enter personName: \n");
    scanf("%c", &dummy);
    fgets(targetName, 20, stdin);
    if(p = strchr(targetName, '\n')){
        *p = '\0';
    }

    if(*number_of_elements==0){
        printf("The name card holder is empty\n");
        return;
    }

    index = searchName(card, number_of_elements, targetName);

    if(index!= -1){
        printf("The name card is removed\n");
        printf("nameCardID: %d\n", card[index].nameCardID);
        printf("personName: %s\n", card[index].personName);
        printf("companyName: %s\n", card[index].companyName);
        if(index != *number_of_elements){ 
            for(i=index; i<*number_of_elements-1; i++){
                card[i].nameCardID = card[i+1].nameCardID;
                strcpy(card[i].personName, card[i+1].personName);
                strcpy(card[i].companyName, card[i+1].companyName);
            }   
        }
        *number_of_elements -= 1;
    } else {
        printf("The target person name is not in the name card holder\n");
    }
}

void getNameCard(NameCard card[MAX], int *number_of_elements){
    char dummy, *p, targetName[20];
    int index=-1;
    printf("getNameCard():\n");

    printf("Enter personName: \n");
    scanf("%c", &dummy);
    fgets(targetName, 20, stdin);
    if(p = strchr(targetName, '\n')){
        *p = '\0';
    }
    index = searchName(card, number_of_elements, targetName);

    if(index != -1){
        printf("The target person name is found\n");
        printf("nameCardID: %d\n", card[index].nameCardID);
        printf("personName: %s\n", card[index].personName);
        printf("companyName: %s\n", card[index].companyName);
    } else {
        printf("The target person name is not found\n");
    }
}

int searchID(NameCard card[MAX], int *number_of_elements, int targetID){
    int i=0;
    for(i=0; i<*number_of_elements; i++){
        if(card[i].nameCardID == targetID){
            return 1;
        }
    }
    return 0;
}

int searchName(NameCard card[MAX], int *number_of_elements, char targetName[20]){
    int i=0;
    for(i=0; i<*number_of_elements-1; i++){
        if(stringCompareIgnoreCase(card[i].personName, targetName)){
            return i;
        }
    }
    return -1;
}

void sortStructure(NameCard card[MAX], int *number_of_elements){
    int j=0, i=0; 
    NameCard tempCard;
    for(i=0; i<*number_of_elements-1; i++){
        for(j=0; j<*number_of_elements-i-1; j++){
            if(card[j].nameCardID>card[j+1].nameCardID){
                tempCard = card[j];
                card[j] = card[j+1];
                card[j+1] = tempCard;
            }
        }
    }
}

int stringCompareIgnoreCase(char string1[20],char string2[20]){
    int i=0;
    for(i=0; string1[i]!='\0'; i++){
        if(toupper(string1[i])!=toupper(string2[i]) ){
            return 0;
        }               
    }
    return 1;
}

int main(){
    int choice;
    int number_of_elements = 0;
    NameCard card[MAX];
    printf("NTU NAME CARD HOLDER MANAGEMENT PROGRAM: \n");
    printf("1: listNameCards()\n");
    printf("2: addNameCard()\n");
    printf("3: removeNameCard()\n");
    printf("4: getNameCard()\n");
    printf("5: quit\n");
    do{
        printf("Enter your choice: \n");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            listNameCards(card, &number_of_elements);
            break;
        case 2:
            addNameCard(card, &number_of_elements);
            sortStructure(card, &number_of_elements);
            break;
        case 3:
            removeNameCard(card, &number_of_elements);
            break;
        case 4:
            getNameCard(card, &number_of_elements);
            break;
        }
    } while(choice<5);

    return 0;
}
