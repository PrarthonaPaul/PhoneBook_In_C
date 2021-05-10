#include <stdio.h>
#include <stdlib.h>
#include "contactList.h"
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAXCONTACTS 30 /* max # of contacts */
#define MAXPHONES 10 /* max # of phone numbers for each contact */
#define PHONE_NUMBER_MAX_LENGTH 12

//This is a structure for the name and Phone number elements on the phone book
typedef struct contact{

    char name[128];
    char phoneNumber[128];

}contact;

//This is the array of contact structures that holds the info of each person
contact phoneBook[MAXCONTACTS];

//this function compares the sent data and returns if preA is larger than ptrB
int matchString(const void *ptrA, const void *ptrB){
    return strcmp(ptrA, ptrB);
}

void assignNull(int size, contact sentList[size]){
    for(int i = 0; i < size; i++)
    {
        strcpy(sentList[i].name, "\0"); 
        strcpy(sentList[i].phoneNumber, "\0"); 
    }
}

int initialize(){             //initializes the array 
    int size = 0;
    char temp[] = "0";
    int contactsSize = (sizeof(phoneBook))/(sizeof(phoneBook[0]));
    
    
    for (int i = 0; i < contactsSize ; i++){                                       
        if (strcmp(phoneBook[i].name, temp)){      //If the contact array contains a "0", then omit it ftom size
            size++;
        }
    }
    return size;
}
//
void ListAllContacts()
{
    int initSize = initialize();
    char temp[] = "0";
    contact simple[initSize]; 
    int increment = 0, index = 0;
        
    assignNull(sizeof(simple)/sizeof(simple[0]), simple); 

    while (index < initSize){
        if (strcmp(phoneBook[index].name, temp)){
            strcpy(simple[increment].name, phoneBook[index].name);
            strcpy(simple[increment].phoneNumber, phoneBook[index].phoneNumber);
            increment++;
        }
        index++;
    }

    int sizeOfSimple = 0;
    
    for (int i = 0; i < initSize; i++){                                       
        if (strcmp(simple[i].name, temp)){
            sizeOfSimple++;
        }

    }
    
    char names[sizeOfSimple][50];
    
    for (int i = 0; i < sizeOfSimple; i++){
        strcpy(names[i], simple[i].name);
    }

    qsort(names, sizeOfSimple, 50, matchString);
    
    /*char *tempName;
    char *tempNumber;*/

    contact arrayInOrder[sizeOfSimple];
    assignNull(sizeof(arrayInOrder)/sizeof(arrayInOrder[0]), arrayInOrder); 

    for (int outer = 0; outer < sizeOfSimple; outer++){
        strcpy(arrayInOrder[outer].name, names[outer]);
        for (int inner = 0; inner < sizeOfSimple; inner++){
            if (strcmp(names[outer], simple[inner].name) == 0){
                strcpy(arrayInOrder[outer].phoneNumber, simple[inner].phoneNumber);
            }
        }
    }
    
    for (int i = 0; i < sizeOfSimple; i++){
        if(strcmp(arrayInOrder[i].name, "\0")){
            printf("Name: %s\n", arrayInOrder[i].name);
            printf("Phone(s): %s\n", arrayInOrder[i].phoneNumber);
        }
    }
}


/*
 * convertInputToDataStructure
 * Takes the information in contactList.h and puts it into a data
 * structure of your choosing, however: 1 mark of the lab will be
 * for using structs with pointers in your solution.
 * You might also want to consider the outputs from the program
 * (see the menu printed in printMenu) since some structures will
 * make this easier than others.
 */
void convertInputToDataStructure() {   
    
    int length = sizeof(contactList)/sizeof(contactList[0]);
    int count = -1;

    for (int i = 0; i < length; i++){
        char strName[128] ;
        char strNumber[MAXPHONES * (PHONE_NUMBER_MAX_LENGTH+1)] ;
        char strTemp [MAXPHONES * (PHONE_NUMBER_MAX_LENGTH+1)] = "\0";

        if (isalpha(*contactList[i])){
            strcpy(strName, contactList[i]);
            int n = 1; 
            
            if (isdigit(*contactList[i+n])){
                strcpy(strNumber, contactList[i+n]);
                n++;
                
                if ((i + n) < length){
                    while (isdigit(*contactList[i+n])){
                        strcpy(strTemp, contactList[i+n]);
                        strcat(strTemp, " ");
                        strcat(strTemp, strNumber);
                        strcpy(strNumber, strTemp);
                        i++;
                    }
                }
            }
            
            count++;
            strcpy(phoneBook[count].name, strName);  
            strcpy(phoneBook[count].phoneNumber, strNumber);
        }
    }
    
    for (int i = (count+1); i < MAXCONTACTS; i++){    //All elements of the phonebook are given a placeholder "0"
        strcpy(phoneBook[i].name, "0");
    }
}

/*
 * printMenu - Prints out the user menu
 */
void printMenu() {
   printf("\n\nEnter a command by number\n");
   printf("1. List all contacts in alphabetical order\n");
   printf("2. Print phone(s) for a contact\n");
   printf("3. Delete contact\n");
   printf("4. Exit the program\n");
   printf("Your input: ");
}

//eliminate trailing \n
char* rtrim(char* str)
{
   int i;
   for (i = strlen(str) - 1; i >= 0 && str[i] == '\n'; i--)
      str[i] = '\0';
   return str;
}

//This function searches the list by the name entered and checks if it is in the list 
bool findMatch(int length, char *nameInput, contact simple[length])
{
    for (int i = 0; i < length; i++){
        if (strcmp(nameInput, simple[i].name) == 0){
            printf("Phone(s): %s\n", simple[i].phoneNumber);
            return true;
            break;
        }
        else
            return false;
    }
    return false; 
}

//This function prints the contact list
void PrintContact() {
    int length = 0, sizeOfSimple = 0;
    char temp[] = "0"; 
    int contactsSize = initialize();
    bool contactMatch = true;
    contact simple[contactsSize];
    int i = 0; 
    assignNull(sizeof(simple)/sizeof(simple[0]), simple); 

    while ( i < contactsSize){ 
        if (strcmp(phoneBook[i].name, temp)){
            strcpy(simple[length].name, phoneBook[i].name);
            strcpy(simple[length].phoneNumber, phoneBook[i].phoneNumber);
            length++;
        }
        i++; 
    }
    
    for (int i = 0; i < contactsSize; i++){
        if (strcmp(simple[i].name, temp)){
            sizeOfSimple+=1;
        }
    }
    
    printf("Enter name: ");
    char nameInput[128];
    char *input = fgets(nameInput,sizeof(nameInput), stdin);
    input = rtrim(input);       //deletes trailing \n

    for (int i = 0; i < sizeOfSimple; i++){       
        if (strcmp(input, simple[i].name) == 0){         //If user input exists in our list, then then print the phone numbers                
            printf("Name: %s\n", input);
            printf("Phone(s): %s\n", simple[i].phoneNumber);              
            contactMatch = true;
            break;
        }
        else
            contactMatch = false;
    }

    if (contactMatch == false){
        printf("Contact not found\n");
    }
}

/*
 * DeleteContact deletes a contact from the list
 * The user must enter the name of the contact to delete
 * 
 */

void DeleteContact() {
    char placeholder[] = "0";
    bool contactMatch = false;
    int n = 0, sizeOfSimple = 0; 
    int length = initialize();
    contact simple[length];
    assignNull(sizeof(simple)/sizeof(simple[0]), simple); 

    while (n < length){          //Same as (1)
        if (strcmp(simple[n].name, placeholder)){
            strcpy(simple[sizeOfSimple].name, phoneBook[n].name);
            strcpy(simple[sizeOfSimple].phoneNumber, phoneBook[n].phoneNumber);
            sizeOfSimple++;
        }
        n++;
    }

    printf("Enter name: ");
    char nameInput[128];
    char *input = fgets(nameInput,sizeof(nameInput), stdin);
    input = rtrim(input);       //deletes trailing \n
    
    for (int i = 0; i < sizeOfSimple; i++){
        if(contactMatch == true){
            strcpy(phoneBook[i-1].name, phoneBook[i].name); 
            strcpy(phoneBook[i-1].phoneNumber, phoneBook[i].phoneNumber); 
            strcpy(phoneBook[i].name, "\0"); 
            strcpy(phoneBook[i].phoneNumber, "\0"); 
            continue; 
        }
        
        if (strcmp(nameInput, simple[i].name) == 0){    //If user input exists in our list, then delete the number ie. change its value to "0"  
            strcpy(phoneBook[i].name, "\0");
             contactMatch = true;
             strcpy(phoneBook[i].name, "\0"); 
             strcpy(phoneBook[i].phoneNumber, "\0"); 
             continue; 
        }
        else
            contactMatch = false;
    }
    
    if (contactMatch == false){             // If user input does not exist in list, print false
        printf("Contact not found\n");
    }
}

/*
 * findDuplicates finds the names of contacts with 
 * a phone number in common
 */

void FindDuplicates() {
    char placeholder[] = "0";
    bool match = false;
    int n = 0, sizeOfSimple = 0, i = 0; 
    int length = (sizeof(phoneBook))/(sizeof(phoneBook[0]));
    contact simple[length];
    assignNull(sizeof(simple)/sizeof(simple[0]), simple); 
    
   while (n < length){          
        if (strcmp(simple[n].name, placeholder)){
            strcpy(simple[sizeOfSimple].name, phoneBook[n].name);
            strcpy(simple[sizeOfSimple].phoneNumber, phoneBook[n].phoneNumber);
            sizeOfSimple++;
        }
        n++;
    }
    
    for (int i = 0; i < length; i++){                                       
        if (strcmp(simple[i].name, placeholder)){
            sizeOfSimple++;
        }
    }
    
    for(int i = 0; i < sizeOfSimple; i++)
    {
        while(match == false){
            printf("%s\n", phoneBook[i].phoneNumber); 
            match = true; 
        }
    }
    
    for(int i = 0; i < sizeOfSimple; i++){
        char strNum[5][13]; 
        int count = 0, n = 0; 
        char * token = strtok(simple[i].phoneNumber, " ");
        strcpy(strNum[count], token); 
        
        while( token != NULL ) {        // loop through the string to extract all other tokens
            token = strtok(NULL, " ");
            strcpy(strNum[++count], token); 
        }
        
        for (int j = 0; j < sizeOfSimple; j++){
            if(simple[i].name != simple[j].name){
                match = strstr(simple[j].name, strNum[n]);
                    if(match)
                        printf("%s and %s have a phone number in common\n", simple[i].name, simple[j].name); 
            }
        }
    }
}

int main()
{
    assignNull(sizeof(phoneBook)/sizeof(phoneBook[0]), phoneBook); 
   // first move data from contactList.h to a data structure
   convertInputToDataStructure();
   
   char notDone = 1;
   while (notDone) {
      printMenu();
      char userChoice[100];
      char* s = fgets(userChoice, sizeof(userChoice), stdin);
      if (!s)
      {
         printf("Wrong input\n");
         continue;
      }
      s = rtrim(s); /* eliminate trailing \n */
      //printf("selection = %s\n", s);
      int userSelection = atoi(s);

      switch (userSelection) {
         case 1: ListAllContacts(); 
            break;
         case 2: PrintContact(); 
            break;
         case 3: DeleteContact(); 
            break;
         case 4: notDone = 0;
            break;
         default: printf("Bad command...\n"); 
            break;
         }
     
   }    

   return 0;
}
