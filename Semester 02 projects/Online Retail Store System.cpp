#include <iostream> // Include the necessary header file for input/output operations
#include <cstring>   // Include the necessary header file for string manipulation
using namespace std;    // Use the standard namespace

const int MAX_PRODUCTS = 10;    // Define a constant for the maximum number of products
const int MAX_CUSTOMERS = 10;   // Define a constant for the maximum number of customers
const int MAX_EMPLOYEES = 10;   // Define a constant for the maximum number of employees

class Product { // Define a class named Product
private:
    char name[50];  // Declare a character array to store the product name
    char description[100];      // Declare a character array to store the product description
    char category[50];  // Declare a character array to store the product category
    double price;   // Declare a double variable to store the product price
    int stock_quantity;     // Declare an integer variable to store the product stock quantity

public:
    Product(const char* pname, const char* pdescription, const char* pcategory, double pprice, int pstock) {
        int i = 0;
        // Here, Copy the strings manually
        while (pname[i] != '\0' && i < 50) {
            name[i] = pname[i]; // Copy the product name
            i++;
        }
        name[i] = '\0';     // Add a null terminator to the product name

        i = 0;
        while (pdescription[i] != '\0' && i < 100) {
            description[i] = pdescription[i];   // Copy the product description
            i++;
        }
        description[i] = '\0';  // Add a null terminator to the product description

        i = 0;
        while (pcategory[i] != '\0' && i < 50) {
            category[i] = pcategory[i]; // Copy the product category
            i++;
        }
        category[i] = '\0';

        price = pprice; // Assign the product price
        stock_quantity = pstock;    // Assign the product stock quantity
        }

    void updateProduct(const char* new_description, double new_price) {
        int i = 0;  // Initialize a counter variable

        while (new_description[i] != '\0' && i < 100) { 
            description[i] = new_description[i];    // Copy the new description to the existing description
            i++;
        }
        description[i] = '\0';  
        price = new_price;  // Update the product price
    }

    void displayProduct() { // Define a function to display the product details
        cout<<"___________________________________________"<<endl;
        cout << "Product: " << name ;
        cout << "\nCategory: " << category;
        cout << "\nPrice: $" << price;
        cout << "\nStock: " << stock_quantity << endl;
        cout<<"___________________________________________"<<endl;
    }

    void reduceStock(int quantity) {        // Define a function to reduce the product stock quantity
        stock_quantity -= quantity;     // Update the stock quantity by subtracting the quantity
    }

    const char* getName() {     // Define a function to get the product name
        return name;    // Return the product name
    }

    const char* getCategory() {     // Define a function to get the product category
        return category;    //return the product category
    }

    double getPrice() {     // Define a function to get the product price
        return price;   // Return the product price
    }

    int getStock() {    // Define a function to get the product stock quantity
        return stock_quantity;  // Return the product stock quantity
    }
};

class Order {
private:
    static int id_counter;      // Declare a static variable to keep track of the order IDs
    int order_id;               // Declare a variable to store the order ID
    Product* product;           // Declare a pointer to a Product object
    int quantity;               // Declare a variable to store the quantity of the product in the order
    double total_cost;          // Declare a variable to store the total cost of the order

public:
    Order(Product* pproduct, int pquantity) {
        product = pproduct;        // Assign the product to the order
        quantity = pquantity;       // Assign the quantity to the order
        total_cost = product->getPrice() * quantity;        // Calculate the total cost of the order
        order_id = ++id_counter;        // Increment the order ID counter and assign it to the order ID
    }

    void displayOrder() {   // Define a function to display the order details
        cout<<"___________________________________________"<<endl;
        cout << "Order ID: " << order_id;
        cout << "\nProduct: " << product->getName();
        cout << "\nQuantity: " << quantity;
        cout << "\nTotal Cost: $" << total_cost << endl;
        cout<<"___________________________________________"<<endl;
    }

    int getOrderId() {           // Define a function to get the order ID
        return order_id;         // Return the order ID
    }

    Product* getProduct() {         // Define a function to get the product in the order
        return product;             // Return the product
    }

    int getQuantity() {         // Define a function to get the quantity of the product in the order
        return quantity;        // Return the quantity
    }

    double getTotalCost() {     // Define a function to get the total cost of the order
        return total_cost;      // Return the total cost
    }

    static int getNextOrderId() {   // Define a function to get the next order ID
        return id_counter + 1;      // Return the next order ID
    }
};

int Order::id_counter = 0;      // Initialize the static variable to 0

class Customer {    
private:
    char name[50];      // Declare a character array to store the customer name
    char email[50];     // Declare a character array to store the customer email
    char address[100];     // Declare a character array to store the customer address
    Order* orderObj;        // Declare a pointer to an Order object

public:
    Customer(const char* cname, const char* cemail, const char* caddress) {
        int i = 0;
        // Copy the strings manually
        while (cname[i] != '\0' && i < 50) {    // Copy the customer name
            name[i] = cname[i];     
            i++;    
        }
        name[i] = '\0';     // Add null terminator

        i = 0;
        while (cemail[i] != '\0' && i < 50) {       // Copy the customer email
            email[i] = cemail[i];       
            i++;
        }
        email[i] = '\0';        // Add null terminator

        i = 0;
        while (caddress[i] != '\0' && i < 100) {        // Copy the customer address
            address[i] = caddress[i];   
            i++;
        }
        address[i] = '\0';

        orderObj = nullptr;     // Initialize the order object to nullptr
    }

    ~Customer() { // Destructor to handle cleanup
        if (orderObj != nullptr) {
            delete orderObj; // Free the dynamically allocated memory
        }
    }

    void placeOrder(Product* product, int quantity) {       // Define a function to place an order

        if (product->getStock() >= quantity) {  // Check if there is enough stock for the order
            orderObj = new Order(product, quantity);    // Create a new order object
            product->reduceStock(quantity);         // Reduce
            cout <<endl<< name << " placed an order for " << quantity << " of " << product->getName() << endl;    // Display a message to the user
        } 
        else {
            cout <<endl<< "\t\tInsufficient stock for your order!" << endl;
        }
    }

    void cancelOrder() {    // Define a function to cancel an order
        if (orderObj != nullptr) {      // Check if there is an order to cancel
            Product* product = orderObj->getProduct();          // Get the product in the order
            product->reduceStock(-orderObj->getQuantity());  // Restores stock
            delete orderObj;            // Delete the order object
            orderObj = nullptr;           // Set the order object to nullptr
            cout << "\t\tOrder cancelled." << endl;        
        } 
        else {
            cout << "\t\tNo order to cancel." << endl;
        }
    }

    void displayCustomer() {
        cout << "___________________________________________" << endl;
        cout << "\nCustomer: " << name;
        cout << "\nEmail: " << email;
        cout << "\n Address: " << address << endl;
        cout << "___________________________________________" << endl;
        if (orderObj != nullptr) {  // Check if there is an order
            cout << "\n\t\tOrder Details:" << endl;
            orderObj->displayOrder();   // Display the order details
        }
    }

    const char* getName() {     // Define a function to get the customer name
        return name; 
    }

    const char* getEmail() {    // Define a function to get the customer email
        return email; 
    }
};

class Employee {
private:
    char name[50];          // Declare a character array to store the employee name
    char position[50];      // Declare a character array to store the employee position
    char role[50];          // Declare a character array to store the employee role

public:
    Employee(const char* ename, const char* eposition, const char* erole) {
        // Copy the strings manually
        int i = 0;
        while (ename[i] != '\0' && i < 50) {    /// Copy the employee name
            name[i] = ename[i];
            i++;
        }
        name[i] = '\0';

        i = 0;
        while (eposition[i] != '\0' && i < 50) {        // Copy the employee position
            position[i] = eposition[i];
            i++;
        }
        position[i] = '\0';

        i = 0;
        while (erole[i] != '\0' && i < 50) {        // Copy the employee role
            role[i] = erole[i]; 
            i++;
        }
        role[i] = '\0';
    }

    void displayEmployee() {        // Define a function to display the employee information
        cout << "___________________________________________" << endl;
        cout << "\nEmployee: " << name;
        cout << "\nPosition: " << position;
        cout << "\nRole: " << role << endl;
        cout << "___________________________________________" << endl;
    }

    void assignRole(Employee* emp, const char* new_role) {  // Define a function to assign a new role to an employee
        int i = 0;
        while (new_role[i] != '\0' && i < 50) {     // Copy the new role
            emp->role[i] = new_role[i];     // Update the employee's role       
            i++;
        }
        emp->role[i] = '\0';
        cout <<endl<< "\tRole for " << emp->getName() << " has been changed to " << new_role << endl;       // Display a message to the user
    }

    const char* getName() const {
        return name;
    }
};

class Store {   
public:
    Product* products[MAX_PRODUCTS];        // Declare an array of Product pointers to store products
    Customer* customers[MAX_CUSTOMERS];     // Declare an array of Customer pointers to store customers
    Employee* employees[MAX_EMPLOYEES];     // Declare an array of Employee pointers to store employees
    int productCount;       // Declare an integer to keep track of the number of products
    int customerCount;      // Declare an integer to keep track of the number of customers
    int employeeCount;      // Declare an integer to keep track of the number of employees

    Store(){
        // Initialize the store with empty arrays and counters
        productCount = 0;
        customerCount = 0;
        employeeCount = 0;
    }

    ~Store() { // Destructor to handle cleanup
        for (int i = 0; i < productCount; ++i) {
            delete products[i];         // Delete each product
        }
        for (int i = 0; i < customerCount; ++i) {
            delete customers[i];        //Delete each customer
        }
        for (int i = 0; i < employeeCount; ++i) {
            delete employees[i];        // Delete each employee
        }
    }

    void addProduct(Product* product) {     // Define a function to add a product to the store
        if (productCount < MAX_PRODUCTS) {      // Check if the product count is less than the maximum allowed
            products[productCount++] = product;         // Add the product to the array
            cout <<endl << "\tProduct " << product->getName() << " added to the store." << endl; 
        }
    }

    void registerCustomer(Customer* customer) {         // Define a function to register a customer
        if (customerCount < MAX_CUSTOMERS) {            // Check if the customer count is less than the maximum allowed
            customers[customerCount++] = customer;      // Add the customer to the array
            cout <<endl << "\tCustomer " << customer->getName() << " registered." << endl;       // Display a message to the user
        }
    }

    void addEmployee(Employee* employee) {          // Define a function to add an employee to the store
        if (employeeCount < MAX_EMPLOYEES) {        // Check if the employee count is less than the maximum allowed
            employees[employeeCount++] = employee;  //Add the employee to the array
            cout <<endl << "\tEmployee " << employee->getName() << " added." << endl;
        }
    }

    void displayProducts() {        // Define a function to display the products in the store
        if (productCount == 0) {        // Check if there are no products in the store
            cout <<endl<< "\tNo products available in the store." << endl;  // Display a message to the user
            return;
        }
        cout <<endl<< "\tProducts available in the store: " << endl;    // Display a message to the user
        for (int i = 0; i < productCount; ++i) {        // Loop through the products array
            products[i]->displayProduct();      // Display the product information
        }
    }

    void displayCustomers() {           // Define a function to display the customers in the store
        if (customerCount == 0) {       // Check if there are no customers in the store
            cout << "No customers registered." << endl;     // Display a message to the user
            return;         
        }
        cout << "Registered Customers: " << endl;       // Display a message to the user
        for (int i = 0; i < customerCount; ++i) {       // Loop through the customers array
            customers[i]->displayCustomer();            // Display the customer information
        }
    }

    void displayEmployees() {               // Define a function to display the employees in the store
        if (employeeCount == 0) {           /// Check if there are no employees in the store
            cout <<endl<< "\tNo employees added." << endl;      // Display a message to the user
            return;
        }
        cout <<endl<< "\tEmployees: " << endl;  
        for (int i = 0; i < employeeCount; ++i) {
            employees[i]->displayEmployee();    // Display the employee information
        }
    }

    void searchProductsByNameOrCategory(const char* searchTerm) {   // Define a function to search for products by name or category
        bool found = false;     // Declare a boolean variable to track if a product was found
        for (int i = 0; i < productCount; ++i) {        // Loop through the products array
            bool nameMatch = true;                      // Declare a boolean variable to track if the name matches the search term
            int j = 0;                                        
            while (searchTerm[j] != '\0' && products[i]->getName()[j] != '\0') {        // Loop through the product name and search term
                if (searchTerm[j] != products[i]->getName()[j]) {       // Check if the characters match
                    nameMatch = false;          // If they don't match, set the nameMatch variable to false and break out of the loop
                    break;
                }
                j++;
            }

            bool categoryMatch = true;      // Declare a boolean variable to track if the category matches the search term
            j = 0;
            while (searchTerm[j] != '\0' && products[i]->getCategory()[j] != '\0') {        // Loop through the product category and search term
                if (searchTerm[j] != products[i]->getCategory()[j]) {   // Check if the characters match
                    categoryMatch = false;      // If they don't match, set the categoryMatch variable to false and break out of the loop
                    break;
                }
                j++;
            }

            if (nameMatch || categoryMatch) {       //Check if either the name or category matches the search term
                products[i]->displayProduct();      // Display the product information
                found = true;                       // Set the found variable to true
            }
        }

        if (!found) {                   // Check if a product was found
            cout << "\tNo matching products found!" << endl;
        }
    }
};


int main() {
    Store store;        // Create a new store object
    int choice;
    do {
        cout << "\n\t\t\tONLINE RETAIL STORE SYSTEM\n";       
        cout << "1. Add a product to the store\n";
        cout << "2. Update product details\n";
        cout << "3. Register a new customer\n";
        cout << "4. Allow a customer to place an order\n";
        cout << "5. Allow a customer to cancel an order\n";
        cout << "6. Display list of products\n";
        cout << "7. Display list of customers\n";
        cout << "8. Display list of employees\n";
        cout << "9. Search for products by name or category\n";
        cout << "10. Store manager - Add or remove products\n";
        cout << "11. Assign roles and permissions to employees\n";
        cout << "0. Exit\n";

        cout <<endl<< "Choose an option from (0-11): ";       // Prompt the user to choose an option
        cin >> choice;

        switch (choice) {
            case 1: {
                // Add a product
                char pname[50], pdescription[100], pcategory[50];       // Declare variables to store product details
                double pprice;          // Declare a variable to store product price
                int pstock;             // Declare a variable to store product stock

                cout <<endl<< "\tEnter product name: ";
                cin >> pname;           // Prompt the user to enter product details
                cout << "\tEnter product description: ";
                cin >> pdescription;    // Prompt the user to enter product details
                cout << "\tEnter product category: ";
                cin >> pcategory;       // Prompt the user to enter product details
                cout << "\tEnter product price: ";
                cin >> pprice;          // Prompt the user to enter product details
                cout << "\tEnter stock quantity: ";
                cin >> pstock;          // Prompt the user to enter product details

                Product* newProduct = new Product(pname, pdescription, pcategory, pprice, pstock);      // Create a new product object
                store.addProduct(newProduct);           // Add the new product to the store
                break;
            }
            case 2: {
                // Update product details
                char pname[50], newDescription[100];    // Declare variables to store updated product details
                double newPrice;        // Declare a variable to store updated product price

                cout <<endl<< "\tEnter the product name to update: ";
                cin >> pname;       // Prompt the user to enter product details
                cout << "\tEnter new description: ";
                cin >> newDescription;      // Prompt the user to enter product details
                cout << "\tEnter new price: ";
                cin >> newPrice;        // Prompt the user to enter product details

                bool productFound = false;          // Declare a boolean variable to track if the product was found
                for (int i = 0; i < store.productCount; ++i) {      // Loop through the products in the store
                    if (strcmp(store.products[i]->getName(), pname) == 0) {     // Check if the product name matches the search term
                        store.products[i]->updateProduct(newDescription, newPrice);     // Update the product details
                        productFound = true;        // Set the productFound variable to true
                        break;
                    }
                }

                if (!productFound) {        // Check if the product was found
                    cout << "\n\tProduct not found!" << endl;
                }
                break;
            }
            case 3: {
                // Register a new customer
                char cname[50], cemail[50], caddress[100];

                cout <<endl<< "\tEnter customer name: ";
                cin >> cname;
                cout << "\tEnter customer email: ";
                cin >> cemail;
                cout << "\tEnter customer address: ";
                cin >> caddress;

                Customer* newCustomer = new Customer(cname, cemail, caddress);      // Create a new customer object
                store.registerCustomer(newCustomer);        // Register the new customer
                break;
            }
            case 4: {
                // Allow a customer to place an order
                char cname[50], pname[50];      // Declare variables to store customer and product details
                int quantity;

                cout << "Enter customer name: ";
                cin >> cname;
                cout << "Enter product name: ";
                cin >> pname;
                cout << "Enter quantity: ";
                cin >> quantity;

                Customer* customer = nullptr;       // Declare a pointer to a Customer object
                Product* product = nullptr;         // Declare a pointer to a Product object

                // Find the customer
                for (int i = 0; i < store.customerCount; ++i) {             // Loop through the customers in the store
                    if (strcmp(store.customers[i]->getName(), cname) == 0) {        // Check if the customer name matches the search term
                        customer = store.customers[i];      // Set the customer pointer to the current customer
                        break;
                    }
                }

                // Find the product
                for (int i = 0; i < store.productCount; ++i) {      //L oop through the products in the store
                    if (strcmp(store.products[i]->getName(), pname) == 0) {     // Check if the product name matches the search term
                        product = store.products[i];        // Set the product pointer to the current product
                        break;
                    }
                }

                if (customer != nullptr && product != nullptr) {        // Check if both the customer and product pointers are not null
                    customer->placeOrder(product, quantity);            // Place the order
                } else {
                    cout << "\tCustomer or Product not found!" << endl;
                }
                break;
            }
            case 5: {
                // Allow a customer to cancel an order
                char cname[50];     // Declare a variable to store customer name

                cout << "\tEnter customer name to cancel order: ";
                cin >> cname;

                Customer* customer = nullptr;       // Declare a pointer to a Customer object       
                for (int i = 0; i < store.customerCount; ++i) {         // Loop through the customers in the store
                    if (strcmp(store.customers[i]->getName(), cname) == 0) {            // Check if the customer name matches the search term
                        customer = store.customers[i];
                        break;
                    }
                }

                if (customer != nullptr) {      // Check if the customer pointer is not null
                    customer->cancelOrder();    // Cancel the order
                } 
                else {
                    cout << "Customer not found!" << endl;      // Print an error message if the customer is not found
                }
                break;
            }
            case 6: {
                // Display list of products
                store.displayProducts();        // Display the list of products
                break;
            }
            case 7: {
                // Display list of customers
                store.displayCustomers();       // Display the list of customers
                break;
            }
            case 8: {
                // Display list of employees
                store.displayEmployees();       // Display the list of employees
                break;
            }
            case 9: {
                // Search for products by name or category
                char searchTerm[50];
                cout << "\tEnter search term (name or category): ";
                cin >> searchTerm;      
                store.searchProductsByNameOrCategory(searchTerm);       // Search for products by name or category
                break;
            }
            case 10: {
                // Store manager - Add or remove products
                char pname[50];
                cout << "\tEnter product name to remove: ";
                cin >> pname;

                bool productFound = false;      // Declare a boolean variable to track if the product is found
                for (int i = 0; i < store.productCount; ++i) {      // Loop through the products in the store
                    if (strcmp(store.products[i]->getName(), pname) == 0) {     // Check if the product name matches the search term
                        delete store.products[i];       // Delete the product
                        for (int j = i; j < store.productCount - 1; ++j) {  // Shift the remaining products to fill the gap
                            store.products[j] = store.products[j + 1];      
                        }
                        store.productCount--;           // Decrement the product count
                        productFound = true;            // Set the flag to true
                        cout << "\tProduct removed from store." << endl;      // Print a success message
                        break;
                    }
                }

                if (!productFound) {
                    cout << "\tProduct not found!" << endl;
                }
                break;
            }
            case 11: {
                // Assign roles and permissions to employees
                char ename[50], newRole[50];    // Declare variables to store employee name and new role

                cout << "\tEnter employee name: ";
                cin >> ename;
                cout << "\tEnter new role for employee: ";
                cin >> newRole;

                Employee* employee = nullptr;       // Declare a pointer to an Employee object
                for (int i = 0; i < store.employeeCount; ++i) {     // Loop through the employees in the store
                    if (strcmp(store.employees[i]->getName(), ename) == 0) {        // Check if the employee name matches the search term
                        employee = store.employees[i];      // Assign the employee pointer
                        break;      
                    }
                }

                if (employee != nullptr) {      // Check if the employee pointer is not null
                    employee->assignRole(employee, newRole);        // Assign the new role to the employee
                } 
                else {
                    cout << "\tEmployee not found!" << endl;
                }
                break;
            }

            case 0: {
                cout << "\tExiting the system." << endl;
                break;
            }

            default:
                cout << "\tInvalid choice, please try again!" << endl;
        }
    } while (choice != 0);      // Continue the loop until the user chooses to exit

    return 0;
}
