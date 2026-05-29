/* PF Project "INVENTORY CONTROL SYSTEM"

  Abdullah Kamran (23P-0612)
  M. Haseeb Afridi (23P-0541)
 FAST-NUCES
*/
#include <stdio.h>
#include <string.h> //including the string library to use functions like strcmp & strcpy to compare and copy strings
  //declaring global variables to keep count throughout the whole program
  FILE *fp;
  char item[20];
  int quantity;
  float price;
  int sold=0;

void login()
{ //function to handle login process
  printf("**Please Login to access the inventory.**\n");
  do
  { //start a loop that continues until the user successfully logs in
    char user[20];
    char pass[20];
    printf("Enter Username: ");
    scanf("%s", &user);
    printf("Enter Password: ");
    scanf("%s", &pass);
      if(strcmp(user, "23P-0541") == 0 && strcmp(pass, "2004")==0)
      { //using strcmp to compare inputs
        printf("***Login Successfully!***\n"); //if user and pass matches, breaking loop & logging in the user.
        break;
      }
      else 
      {
        printf("Invalid Username or Password. Please Try again.\n");
      }
   } while(1);
}

void displayMenu()
{ //function to display menu
  printf("\n");
  printf("\t\t\t ===============================\n");
  printf("\t\t\t    INVENTORY CONTROL SYSTEM\n");
  printf("\t\t\t ===============================");
  printf("\n\nPress:");
  printf("\n 1.) List all the items.");
  printf("\n 2.) Add a item.");
  printf("\n 3.) Delete a item.");
  printf("\n 4.) Update item's price & quantity");
  printf("\n 5.) Search for a item");
  printf("\n 6.) Sell an item");
  printf("\n 7.) Display the item record with highest sale.");
  printf("\n 8.) Display all item with zero quantity");
  printf("\n 0.) Exit the program.");
}
void getUserInput(int *choice) 
{ //taking user input using pointers
  printf("\nChoice => ");
  scanf("%d", choice);
}
void listItems()
{
  int id=1;
  fp = fopen("inventory.txt", "r"); //open inventory file for reading
  if(fp == NULL)
  { //if file could not be opened, print error
    printf("Items not found, Please add items.\n");
  }
  else
  { //if file opening was successful, print the inventory
    printf("\t\t\t ***** INVENTORY *****\n");
    printf("-------------------------------------------------\n");
    printf("I.D.| Item Name   | Quantity | Price ($)\n");
    printf("-------------------------------------------------\n");
  while(fscanf(fp, "%s %d %f", item, &quantity, &price) != EOF)
  { //reads the data from file until End Of File.
    printf("%-4d| %-12s | %-8d | %.2f\n", id, item, quantity, price); //prints the data to the user
    id++;
  }
  fclose(fp);
  }
}

void addItem()
{
  // Request user input for the item to be added
  printf("Item name to add: ");
  scanf("%s", item);
  printf("Quantity of the item: ");
  scanf("%d", &quantity);
  printf("Price of the item: ");
  scanf("%f", &price);
  // Open the inventory file in append mode
  fp = fopen("inventory.txt", "a");
  // If the file opens successfully, write the item details to the file otherwise Error.
    if(fp != NULL)
    {
    fprintf(fp, "%s %d %.2f\n", item, quantity, price);
    fclose(fp);
    printf("Item added Successfully!\n");
    }
    else
    {
    printf("Error opening file!");
    }
}

void removeItem()
{
  // Declare a temporary file pointer
  FILE *fp_temp;
  char item_to_remove[20];
  int found = 0;
  // Request user input for the item to be removed
  printf("Item name to remove: ");
  scanf("%s", item_to_remove);
  // Open the inventory file in read mode and a temporary file in write mode
  fp = fopen("inventory.txt", "r");
  fp_temp = fopen("temp.txt", "w");
  // Read the inventory file line by line
  while(fscanf(fp, "%s %d %f", item, &quantity, &price) != EOF)
  {
  // If the line does not contain the item to be removed, write it to the temporary file
    if(strcmp(item, item_to_remove) == 0)
    {
    found=1;
    }
    else
    {
    fprintf(fp_temp, "%s %d %.2f", item, quantity, price);
    }
 }

  //close both files
  fclose(fp);
  fclose(fp_temp);
  //replace original file with temp file we created
  remove("inventory.txt");
  rename("temp.txt", "inventory.txt");
    if(found)
    {
    printf("Item removed successfully.\n");
    }
    else
    {
    printf("Item not found.\n");
    }
}

void updateItem()
{
  FILE *fp_temp;
  char item_to_update[20];
  int found = 0;
  printf("Item Name to update: ");
  scanf("%s", item_to_update);
  fp = fopen("inventory.txt", "r");
  fp_temp = fopen("temp.txt", "w");
  while(fscanf(fp, "%s %d %f", item, &quantity, &price) != EOF)
  {
  // If the line contains the item to be updated, request and update its quantity and price
    if(strcmp(item, item_to_update) == 0)
    {
    printf("Enter the new quantity: ");
    scanf("%d", &quantity);
    printf("Enter the new price: ");
    scanf("%f", &price);
    found = 1;
    }
  fprintf(fp_temp, "%s %d %.2f", item, quantity, price);
  }
  fclose(fp);
  fclose(fp_temp);
  remove("inventory.txt");
  rename("temp.txt", "inventory.txt");
  if(found)
  {
  printf("Item updated successfully.\n");
  }
  else
  {
  printf("Item not found.\n");
  }
}

void searchItem()
{
 char item_to_search[20];
 int found = 0;
 printf("Item Name to search: ");
 scanf("%s", item_to_search);
 fp = fopen("inventory.txt", "r");
 while(fscanf(fp, "%s %d %f", item, &quantity, &price) != EOF)
 {
 // If the line contains the item to search, print its details and break the loop
  if(strcmp(item, item_to_search) == 0){
  printf("Item: %s| Quantity: %d| Price: %.2f$\n", item, quantity, price);
  found = 1;
  break;
  }
  }
 fclose(fp);
  if(!found)
  {
  printf("Item not found.\n");
  }
}

void sellItem()
{
  // Declare a temporary file pointer
  FILE *fp_temp;
  char item_to_sell[20];
  int quant, found = 0;
  float total_bill=0.0;
  // Request user input for the item to update
  printf("Item Name to sell: ");
  scanf("%s", item_to_sell);
  printf("Quantity to sell: ");
  scanf("%d", &quant);
  // Open the inventory file in read mode and a temporary file in write mode
  fp = fopen("inventory.txt", "r");
  fp_temp = fopen("temp.txt", "w");
  while(fscanf(fp, "%s %d %f", item, &quantity, &price) != EOF){
    if(strcmp(item, item_to_sell) == 0)
    {
    if(quantity < quant)
    {
    printf("Insufficient Quantity Please Restock.");
    } 
    else 
    {
    quantity -= quant;
    sold += quant;
    total_bill=price*quant;
    printf("Item: %s| Remaining Quantity: %d| Sold: %d| Price: %.2f$\n", item, quantity, sold,
    price);
    printf("Item(s) has been sold. The total bill is: %.2f$\n", total_bill);
    found = 1;
    }
    }
  // Write the item details to the temporary file
  fprintf(fp_temp, "%s %d %.2f", item, quantity, price);
  }
  fclose(fp); //close both files
  fclose(fp_temp);
  remove("inventory.txt"); //replace original file with temporary.
  rename("temp.txt", "inventory.txt");
  if(!found)
  {
  printf("Item not found.");
  }
}

void highestSold()
{
 char highest_item[20];
 int highest_sold = 0;
// Open the inventory file in read mode
 fp = fopen("inventory.txt", "r");
// Read the inventory file line by line
 while(fscanf(fp, "%s %d %f", item, &quantity, &price) != EOF){
 // If the current item's sales are higher than the highest sales found so far, update the highest sales and highest item
  if(sold > highest_sold)
  {
  highest_sold = sold;
  strcpy(highest_item, item);
  }
 }
 fclose(fp);
// If the highest sales are greater than 0, print the highest selling item and its sales
 // Otherwise, print a message indicating that no items have been sold yet
  if(highest_sold > 0)
  {
    printf("Item with highest sales: %s, Sold: %d", highest_item, highest_sold);
  } 
  else 
  {
  printf("No items sold yet.");
  }
}

void zeroStock()
{ // This function finds and prints all items with zero quantity in stock
  int found = 0;
  fp = fopen("inventory.txt", "r"); // Open the inventory file in read mode
  printf("Items with zero stock:\n");
  while(fscanf(fp, "%s %d %f", item, &quantity, &price) != EOF)
  {
    if(quantity == 0){ // If the current item's quantity is 0, print the item and its price, and set the found flag to 1
    printf("Item: %s| Price: %.2f$\n", item, price);
    found = 1;
    }
  }
  fclose(fp);
    if(!found)
    {
    printf("No items with zero stock.");
    }
}

int main()
{
 login(); //calling login function for login process
 while(1)
 { // Enter an infinite loop for the menu-driven system until user decides to exit.
 displayMenu();
 int userChoice;
 getUserInput(&userChoice);
 switch(userChoice)
 {
 case 0:
 return 0;
 case 1:
 listItems();
 break;
 case 2:
 addItem();
 break;
 case 3:
 removeItem();
 break;
 case 4:
 updateItem();
 break;
 case 5:
 searchItem();
 break;
 case 6:
 sellItem();
 break;
 case 7:
 highestSold();
 break;
 case 8:
 zeroStock();
 break;
 default:
 printf("Invalid Input.. Please enter choice again.");
 }
 }
}

