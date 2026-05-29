/*
Name: Abdullah Kamran (23P-0612)
Name: Shaheer Farooqui (23P-0587)
Name: Mehaal Khan (23P-0544)
*/

#include <iostream>
#include <iomanip>  
using namespace std;

// Static counter for items and customers
class StaticCounter {
public:
    static int itemCount;
    static int customerCount;
};

int StaticCounter::itemCount = 0;
int StaticCounter::customerCount = 0;

// Function to check if the input is a valid number
bool isValidNumber(const string& input) 
{
    for (char c : input)
	{  //range base for loop
        if (!isdigit(c)) 
		{    //!isdigit is a build in which is used to check if the character is not a digit
            return false;   //if the character is not a digit then it will return false
        }
    }
    return true;
}

// MenuItem Class
class MenuItem {
private:
    string name;
    double price;

public:
    // Default Constructor
    MenuItem(){
        //initializing the name and price to empty string and 0.0 respectively
        name = "";  
        price = 0.0;
    } 

    // Parameterized Constructor
    MenuItem(const string& itemName, double itemPrice){
        name = itemName; //initializing the name to the itemName
        price = itemPrice;  //initializing the price to the itemPrice
        StaticCounter::itemCount++;     //incrementing the itemCount by 1
    }
    
    // Copy Constructor
    MenuItem(const MenuItem& other){   
        name = other.name;  //initializing the name to the other.name
        price = other.price;    //initializing the price to the other.price
    }


    // Destructor
    ~MenuItem() {
        StaticCounter::itemCount--; //decrementing the itemCount by 1
    }

    // Set the price
    void setPrice(double newPrice) { 
        price = newPrice; //setting the price to the newPrice
    }

    // Get the price
    double getPrice() const { 
        return price;  //returning the price
    }

    // Get the name
    const string getName() const { 
        return name;  //returning the name
    }

   void displayItem(int index) const {
    cout << setw(10) << index  // Set the width of the 'index' to 10 characters.
         << setw(20) << name   // Set the width of the 'name' to 20 characters.
         << setw(10) << "$"    // Set the width for the '$' symbol to 10 characters.
         << fixed              // Use fixed-point notation for floating-point numbers.
         << setprecision(2)    // Set the precision of the control the number of digit after decimal point. floating-point number to 2 decimal places.
         << price              // Display the price.
         << endl;              // Move to the next line after printing.
}

};

// User Class
class User {
protected:
    string username;
    string password;

public:

    virtual void login(const string& uname, const string& pass) {  
        if (uname == username && pass == password) 
		{ //checking if the username and password are correct
            cout << "Login successful!\n";
        } 
        else 
		{
            cout << "Invalid credentials!\n";
        }
    }
};

// Menu Class
class Menu {
private:
    static const int MAX_ITEMS = 100;  // Define a limit for menu items
    MenuItem items[MAX_ITEMS];  // Array to store menu items    
    int itemCount;  // Current number of items in the menu

public:
    // Constructor
    Menu(){
        itemCount = 0;  // Initialize the itemCount to 0
    } 

    // Add an Item
    void addItem(const MenuItem& item) {
        if (itemCount < MAX_ITEMS)
		 { ///checking if the itemCount is less than the MAX_ITEMS
            items[itemCount++] = item;  // Add the item to the menu
        } 
        else
		 {
            cout << "Menu is full, cannot add more items.\n";
        }
    }

    // Update an Item
    void updateItem(int index, double newPrice) {
        if (index >= 0 && index < itemCount) 
		{  //checking if the index is greater than or equal to 0 and less than the itemCount
            items[index].setPrice(newPrice);
        } 
        else 
		{
            cout << "Invalid item index.\n";
        }
    }

    // Delete an Item
    void deleteItem(int index) {    //deleting the item from the menu
        if (index >= 0 && index < itemCount) 
		{      //checking if the index is greater than or equal to 0 and less than the itemCount
            for (int i = index; i < itemCount - 1; i++) 
			{       
                items[i] = items[i + 1];    //shifting the items to the left
            }
            itemCount--;
        } 
		else 
		{
            cout << "Invalid item index.\n";
        }
    }

    // Display Menu
    void displayMenu() const {
	
        cout << "\n                MENU of Our Restaurant\n";
        cout << "-------------------------------------------------\n";
        for (int i = 0; i < itemCount; i++) 
		{
            items[i].displayItem(i + 1);    //calling the displayItem function to display the item
        }
        cout << "-------------------------------------------------\n";
    }

    // Get Menu Items
    MenuItem* getItems() {
        return items;   //returning the items
    }

    // Get Item Count
    int getItemCount() const {
        return itemCount;       //returning the itemCount
    }
};

// Customer Class
class Customer {

private:
    string name;
    int age;
    string phone;
    static const int MAX_ORDER = 10;    // Define a limit for the order list
    MenuItem orderList[MAX_ORDER];      // Array to store order items   
    int orderCount;         // Current number of items in the order list

public:

    // Constructor
    Customer(const string& cname, int cage, const string& cphone){
        name = cname;   //initializing the name to the cname
        age = cage;       //initializing the age to the cage
        phone = cphone;   //initializing the phone to the cphone
        orderCount = 0;   //initializing the orderCount to 0
    } 

    // Destructor
    ~Customer() {
        StaticCounter::customerCount--;     //decrementing the customerCount by 1
    }

    // Display Customer Info
    void displayCustomer() const {  //displaying the customer information
        cout << "\nCustomer Information:\n";
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Phone: " << phone << endl;
    }

    // Add to Order List
    void addToOrder(const MenuItem& item) {     //adding the item to the order list

        if (orderCount < MAX_ORDER) 
		{   //checking if the orderCount is less than the MAX_ORDER
            orderList[orderCount++] = item; //adding the item to the order list
        } 
        else 
		{
            cout << "Order limit reached.\n";
        }
    }

    // Calculate Total Bill
    double calculateTotal() const {
        double total = 0;
        for (int i = 0; i < orderCount; i++) 
		{  //calculating the total bill
            total += orderList[i].getPrice();   //adding the price of the item to the total
        }
        return total;   //returning the total
    }

    // Display Order
    void displayOrder() const 
	{
        cout << "\nCustomer's Order:\n";
        for (int i = 0; i < orderCount; i++) {  // Loop to display the order list
        cout << setw(10) << i + 1;   // Displaying the index (order number)
        cout << setw(20) << orderList[i].getName();     // Displaying the item name from the orderList array
        cout << setw(10) << "$";        // Displaying the '$' symbol for price
        cout << fixed << setprecision(2);   // Setting the display format for the price (fixed-point with two decimal places)
        cout << orderList[i].getPrice();     // Displaying the price of the order item
        cout << endl;       // Move to the next line after displaying the current item
}
        cout << "-------------------------------------------------\n";      
    }

    // Overloaded Comparison Operator
    bool operator==(const Customer& other) const {
        if(name == other.name && phone == other.phone && age == other.age) 
		{        //checking if the name, phone and age of the current customer is equal to the name, phone and age of the other customer
            return true;
        } 
        else 
		{
            return false;
        }
    }
};


// Admin Class
class Admin : public User {
private:
    Menu* menu; // Pointer to the Menu object

public:
    Admin(Menu* m) : menu(m) {
        username = "Admin"; // Set the username for Admin
        password = "admin123";  // Set the password for Admin
    }

    // Add login method for Admin
    void login(const string& uname, const string& pass) override {
        if (uname == username && pass == password) 
		{    //checking if the username and password of the admin is equal to the username and password of the current admin
            cout << "Login successful!\n";
        } 
        else 
		{
            cout << "Invalid credentials!\n";
        }
    }

    void manageMenu() { // managing the menu
    string choices;

    do {
        cout << "\n\t\t\t\tMenu Management"<<endl;
        cout << "\t\t1. Add Item\n";
        cout << "\t\t2. Update Item\n";
        cout << "\t\t3. Delete Item\n";
        cout << "\t\t4. View Menu\n";
        cout << "\t\t5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choices; // taking the choice from the user

        if (isValidNumber(choices)) 
		{
            int choice = 0;
            for (char c : choices) 
			{
                choice = choice * 10 + (c - '0');
            }

           if (choice == 1) 
		   {
			    string name;
			    string price;
			    cout << "Enter Item Name: ";
			    cin >> name;
			    cout << "Enter Item Price: ";
			    cin >> price;
			
			    if (isValidNumber(price)) 
				{
			        int ch = 0;
			        for (char c : price) {
			            ch = ch * 10 + (c - '0');
			        }
			        menu->addItem(MenuItem(name, ch)); // adding the item to the menu
			    } 
				else 
				{
			        cout <<endl<< "\t\tInvalid input! Please enter a valid number.\n";
			    }
			}

		 
            else if (choice == 2) 
			{
                int index;
                double price;
                cout << "Enter Item Index: ";
                cin >> index;
                cout << "Enter New Price: ";
                cin >> price;
                menu->updateItem(index - 1, price);
            } 
            else if (choice == 3) 
			{
                int index;
                cout << "Enter Item Index: ";
                cin >> index;
                menu->deleteItem(index - 1);
            } 
            else if (choice == 4) 
			{
                menu->displayMenu(); // displaying the menu
            } 
            else if (choice == 5) 
			{
                cout << "Exiting...\n";
                break;
            } 
            else 
			{
                cout <<endl<<"Invalid choice!\n";
            }
        } 
		else 
		{
            cout <<endl<< "Invalid input! Please enter a valid number.\n";
        }
    } while (true); // looping the menu management until the user chooses to exit
}

    
};
    

// Manager Class
class Manager : public User {
private:
    Menu *menu; // Pointer to the Menu object

public:
    Manager(Menu *m) : menu(m) {    //constructor for the manager class
        username = "Manager";   //setting the username of the manager
        password = "123";   //setting the password of the manager   
    }

	 bool isValidNumber(const string& input) {
	    for (char c : input) 
		{
	        if (!isdigit(c)) 
			{
	            return false;
	        }
	    }
	    return true;
	}
	
	void addCustomer() {
	    string name;    // Declaring the variables
	    string ageInput; // Age input as string for validation
	    int age = 0;
	    string phone;
	
	    // Input customer name
	    cout <<endl<< "Enter customer name: ";
	    cin >> name;
	
	    // Input and validate customer age
	    cout << "Enter customer age: ";
	    cin >> ageInput;
	
	    if (isValidNumber(ageInput)) 
		{
	        // Convert valid age string to integer
	        for (char c : ageInput) 
			{
	            age = age * 10 + (c - '0'); // Manual conversion from string to int
	        }
	    } 
		else 
		{
	        cout << "Invalid input! Please enter a valid number for age.\n";
	        return; // Exit if age input is invalid
	    }
	
	    // Input and validate customer phone
	    cout << "Enter customer phone: ";
	    cin >> phone;
	
	    if (!isValidNumber(phone)) 
		{
	        cout << "Invalid input! Please enter a valid number for phone.\n";
	        return; // Exit if phone input is invalid
	    }
	    Customer newCustomer(name, age, phone); // Creating a new customer object
	    // Call menu display function
	    menu->displayMenu();

        char moreItems; // Variable to track if the customer wants to add more items

        do {
            int choice;
            cout << "Enter the item index to add to order (0 to finish):\n  ";
            cin >> choice;

            if (choice == 0)
			{
                break;  // Exit the loop if the customer chooses to finish
            } 
            MenuItem* items = menu->getItems(); // Get the array of MenuItem objects
            int itemCount = menu->getItemCount();   // Get the number of items in the menu

            if (choice > 0 && choice <= itemCount) 
			{    // Check if the choice is within the valid range
                newCustomer.addToOrder(items[choice - 1]);  // Add the selected item to the customer's order
                cout << "Item added to order.\n";
            } 
            else 
			{
                cout << "Invalid item index.\n";
            }

            cout << "Add another item? (y/n): ";
            cin >> moreItems;
        } while (moreItems == 'y' || moreItems == 'Y'); // Continue adding items until the customer chooses not to

        newCustomer.displayCustomer();  // Display the customer's order
        newCustomer.displayOrder();     // Display the customer's order
        
        double total = newCustomer.calculateTotal();        // Calculate the total bill
        cout << "Total Bill: $";    // Display the total bill
        cout << fixed;      // Set fixed precision for displaying the total bill
        cout << setprecision(2);    // Set the number of decimal places to 2
        cout << total;      // Display the total bill
        cout << endl;
        cout<<"-------------------------------------------------"<<endl;

        // Process Payment
        char paymentChoice;
        cout << "\n\t\tPayment by Cash or Credit Card\n";
        cout << endl<<"Enter 'C' for Cash or 'R' for Credit Card: ";
        cin >> paymentChoice;

        if (paymentChoice == 'R' || paymentChoice == 'r') {
            int pin;
            cout << endl<<"\t\tEnter your 4-digit credit card PIN: ";
            cin >> pin;

            if (pin == 1001) {
                cout << "\t\tPIN verified successfully!"<<endl;;
                cout <<endl<<"\t\t\t\tPayment completed!";
				cout<< "\n\t\t\t   ~Thank you for visiting!~";
				cout<<"\n\t\t\t\tCome again!\n"<<endl;
            } else {
                cout << "Invalid PIN. Payment failed.\n";
            }
        } else {
            cout <<endl<< "\t\t\tPayment completed!";
			cout<<"\n\t\t\t   ~Thank you for visiting!~";
			cout<<"\n\t\t\tCome again!\n"<<endl;;
        }
    }
};

// Main function
int main() {
    Menu menu;  // Creating a Menu object
    Admin admin(&menu);     // Creating an Admin object
    Manager manager(&menu);     // Creating a Manager object

    while (true) {
        cout << "\n\t\t\t\t\tWELCOME TO THE RESTURANT\n"<<endl;    
        cout << "\t\t1. Login as Manager\n";
        cout << "\t\t2. Login as Admin\n";
        cout << "\t\t3. Exit\n";
        cout <<endl<< "Enter your choice: ";

        string input;
        cin >> input;

		if (isValidNumber(input)) 
		{
            int choice = 0;
            for (char c : input)
			 {
                choice = choice * 10 + (c - '0');
            }
            
        if (choice == 1) 
		{      // Login as Manager
            string uname, pass;     //declaring the variables
            cout <<endl<< "Enter username: ";
            cin >> uname;
            cout << "Enter password: ";
            cin >> pass;

            manager.login(uname, pass);     //calling the login function of the manager class
            if (uname == "Manager" && pass == "123") 
			{
                manager.addCustomer();  //calling the addCustomer function of the manager class
                exit(0);
            }
        } 
        
        else if (choice == 2) 
		{ // Login as Admin
            string uname, pass;
            cout << "Enter username: ";
            cin >> uname;
            cout << "Enter password: ";
            cin >> pass;

            admin.login(uname, pass);   //calling the login function of the admin class
            if (uname == "Admin" && pass == "admin123") 
			{
                admin.manageMenu();     //calling the manageMenu function of the admin class
            }
        } 
        
        else if (choice == 3) 
		{ // Exit
            cout << "Goodbye!\n";
            break;
        } 
        
        else 
		{
            cout << "Invalid choice!\n";
        }
    }
        else 
		{
            cout << "Invalid input! Please enter a valid number.\n";
        }
    }
    return 0;   //returning 0
}
