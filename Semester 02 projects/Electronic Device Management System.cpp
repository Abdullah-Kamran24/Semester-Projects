#include <iostream> //Standard input and output stream library
using namespace std; //Using Standard namespace to avoid to write std:: on each step 

class Device {  // Base class Device
protected:
    int battery_life;
    double price;

public:
    Device(){  // Default constructor
        battery_life = 0;
        price = 0.0;
    }

    Device(int battery, double pr) { // Parameterized constructor
         battery_life = battery;
         price = pr; 
    }

    virtual void displayInfo()  {  // Display device information
        cout << "Battery Life: " << battery_life << " hours\n";
        cout << "Price: $" << price << endl;
    }

    virtual ~Device() {}  // Destructor
    
     
    int getBatteryLife() const { // Getter for battery life
    return battery_life;
}
};

class Laptop : public Device { // sub-class of device => Laptop
protected:
    int ram_size;
    double storage_capacity;
    int screen_size;

public:
    
    Laptop(){ // Default constructor
        ram_size = 0;
        storage_capacity= 0.0;
        screen_size = 0; 
        }
        
    Laptop(int battery, double pr, int ram, double storage, int screen): Device(battery, pr){ // Parameterized constructor
        ram_size = ram; 
        storage_capacity = storage; 
        screen_size = screen;
    }

    void displayInfo() {  // Display laptop information
        Device::displayInfo();
        cout << "RAM Size: " << ram_size << " GB\n";
        cout << "Storage Capacity: " << storage_capacity << " GB\n";
        cout << "Screen Size: " << screen_size << " inches\n";
        cout<<endl;
    }
    
    Laptop(const Laptop& other) : Device(other) {   //Deep copy Constructor
    ram_size = other.ram_size; 
    storage_capacity = other.storage_capacity; 
    screen_size = other.screen_size;
}
};

class HP : public Laptop { // Subclass of laptop => HP
private:
    string model_name;

public:
    HP(){} //Default Constructor

    HP(int battery, double pr, int ram, double storage, int screen, const string& model): Laptop(battery, pr, ram, storage, screen){  //Parameterized Constructor
            model_name = model; 
        }
        
    void displayInfo()  { // Display information
        cout << "Model Name: " << model_name << endl;
        Laptop::displayInfo();
    }
};

class Dell : public Laptop { // Subclass of Laptop => Dell
private:
    string model_name;

public:
    Dell() {} //Default Constructor

    Dell(int battery, double pr, int ram, double storage, int screen, const string& model) : Laptop(battery, pr, ram, storage, screen){  //Parameterized Constructor
        model_name = model; 
    }

    void displayInfo()  { // Display information
        cout << "Model Name: " << model_name << endl;
        Laptop::displayInfo();
    }
};

class Mobile : public Device { // Subclass of Device => Mobile
protected:
    int camera_resolution;
    int internal_storage;
    string operating_system;

public:
    Mobile(){  //Default constructor
        camera_resolution=  0; 
        internal_storage = 0; 
        operating_system = ""; 
    }

    Mobile(int battery, double pr, int camera, int storage, const string& os) : Device(battery, pr){  // Parameterized Constructor
        camera_resolution = camera; 
        internal_storage = storage; 
        operating_system = os;
    }

    void displayInfo()  { //Display Informations
        Device::displayInfo();
        cout << "Camera Resolution: " << camera_resolution << " MP\n";
        cout << "Internal Storage: " << internal_storage << " GB\n";
        cout << "Operating System: " << operating_system << endl;
        cout<<endl;
    }
};


class Samsung : public Mobile { // Subclass of MOdile => Samsung
private:
    string model_name;

public:
    Samsung() {} //Default Constructor

    Samsung(int battery, double pr, int camera, int storage, const string& os, const string& model): Mobile(battery, pr, camera, storage, os){ //Parameterized Constructor
        model_name = model;
    } 

    void displayInfo()  { //Display Information
        cout << "Model Name: " << model_name << endl;
        Mobile::displayInfo();
    }
};


class Apple : public Mobile { // Subclass of Mobile => Apple
private:
    string model_name;

public:
    Apple() {} //Default Constructor

    Apple(int battery, double pr, int camera, int storage, const string& os, const string& model) : Mobile(battery, pr, camera, storage, os){  //Parameterized Constructor
        model_name = model;
    }

    void displayInfo()  { //Display inoformation
        cout << "Model Name: " << model_name << endl;
        Mobile::displayInfo();
    }
};

int main() {

    int laptopCount = 0;
    int mobileCount = 0;
    int maxLaptops;
    int maxMobiles;

    int choice; //declare varaibale for switches

    cout<<"\t\t\tWelcome to Electronic Device Management System"<<endl;
    cout<<endl;
    
    cout << "How many laptops you want to store;\n\t\tEnter Numbers of Laptop: ";
    cin >> maxLaptops;
     cout<<endl;
    cout << "how many Mobiles you want to store:\n\t\tEnter Numbers of Mobile: ";
    cin >> maxMobiles;

    // The Dynamically allocate arrays
    Dell* dellLaptops = new Dell[maxLaptops];
    HP* hpLaptops = new HP[maxLaptops];
    Samsung* samsungMobiles = new Samsung[maxMobiles];
    Apple* appleMobiles = new Apple[maxMobiles];

    do {
        cout << "\n\t\t~MENU~\n";
        cout << "\t1. Add Laptop\n";
        cout << "\t2. Add Mobile\n";
        cout << "\t3. Remove Laptop\n";
        cout << "\t4. Remove Mobile\n";
        cout << "\t5. Display all the Laptops\n";
        cout << "\t6. Display all the Mobiles\n";
        cout << "\t7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: // Add Laptop
                if (laptopCount < maxLaptops){
                    
                    string model;
                    int battery;
                    int ram;
                    int screen;
                    double price;
                    double storage;
                    
                    cout <<endl<< "Enter the model (Dell/HP): ";
                    cin >> model;
                    cout << "Enter battery life of "<<model<<": ";
                    cin >> battery;
                    cout<<"Enter Price of "<<model<<": ";
                    cin >> price;
                    cout<<"Enter RAM of "<<model<<": ";
                    cin >> ram;
                    cout<<"Enter Storage of "<<model<<": ";
                    cin>> storage;
                    cout<<"Enter Screen Size of " <<model<<": ";
                    cin>> screen;
                    

                    if (model == "Dell" || model == "dell") {
                        dellLaptops[laptopCount] = Dell(battery, price, ram, storage, screen, model);
                    } 
                    
                    else if (model == "HP" || model == "hp") {
                        hpLaptops[laptopCount] = HP(battery, price, ram, storage, screen, model);
                    }
                    laptopCount++;
                } 
                else {
                    cout << "Laptop storage full!\n";
                }
                break;

            case 2: // Add Mobile
                if (mobileCount < maxMobiles) {

                    string model;
                    string os;
                    int battery;
                    int camera;
                    int storage;
                    double price;
                    
                    cout << "Enter the model (Samsung/Apple): ";
                    cin >> model;
                     cout << "Enter Battery Life of "<<model<<": ";
                    cin >> battery;
                    cout<<"Enter Price of "<<model<<": ";
                    cin >> price;
                    cout<<"Enter Camera Resolution of "<<model<<": ";
                    cin >> camera;
                    cout<<"Enter Internal Storage of "<<model<<": ";
                    cin>> storage;
                    cout<<"Enter Operating System of " <<model<<": ";
                    cin>> os;

                    if (model == "Samsung" || model == "samsung") {
                        samsungMobiles[mobileCount] = Samsung(battery, price, camera, storage, os, model);
                    } 
                    else if (model == "Apple" || model == "apple") {
                        appleMobiles[mobileCount] = Apple(battery, price, camera, storage, os, model);
                    }
                    mobileCount++;
                } 
                else {
                    cout << "Mobile storage full!\n";
                }
                break;

            case 3: // Remove Laptop
                if (laptopCount > 0) {
                    laptopCount--;
                    cout << "Last laptop removed.\n";
                } 
                else {
                    cout << "No laptops to remove.\n";
                }
                break;

            case 4: // Remove Mobile
                if (mobileCount > 0) {
                    mobileCount--;
                    cout << "Last mobile removed.\n";
                } 
                else {
                    cout << "No mobiles to remove.\n";
                }
                break;

          case 5: // Display all Laptops
                cout <<endl<< "Displaying all Laptops: \n";
             for (int i = 0; i < laptopCount; ++i) {
                
            if (dellLaptops[i].getBatteryLife() > 0) {  // Checking if the Dell laptop not zero
                 dellLaptops[i].displayInfo();
                }
            if (hpLaptops[i].getBatteryLife() > 0) {  // Check if the HP laptop not zero
                hpLaptops[i].displayInfo();
                }
            }
             break;

        case 6: // Display all Mobiles
            cout <<endl<<"Displaying all Mobiles: \n";
            for (int i = 0; i < mobileCount; ++i) {
                if (samsungMobiles[i].getBatteryLife() > 0) {  // Check if the Samsung mobile not zero
                    samsungMobiles[i].displayInfo();
                }
                if (appleMobiles[i].getBatteryLife() > 0) {   // Check if the Apple mobile not zero
                    appleMobiles[i].displayInfo();
                }
            }
            break;


            case 7:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice, please try again.\n";
                break;
        }
    } while (choice != 7);

    // Free allocated memory
    delete[] dellLaptops;
    delete[] hpLaptops;
    delete[] samsungMobiles;
    delete[] appleMobiles;

    return 0;
}