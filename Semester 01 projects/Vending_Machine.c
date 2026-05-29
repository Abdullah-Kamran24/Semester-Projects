#include <stdio.h>

// function declarations
double calculateBill(int quantity, double price);
int checkAvailability(int availableQuantity, int requestedQuantity);
void updateStock(int *availableQuantity, int purchasedQuantity);

int main()
{
    int cokeAvailable = 10;
    int pepsiAvailable = 15;
    int spriteAvailable = 15;
    int sevenUpAvailable = 25;
    double cokePrice = 5.0;
    double pepsiPrice = 7.0;
    double spritePrice = 7.0;
    double sevenUpPrice = 3.0;
    int choice;
    int quantity;
    double totalBill = 0.0;
    printf("Welcome to the Vending Machine!\n\n");
    do
    {
        // available drinks
        printf("Available Drinks:\n");
        printf("1. Coke (Price: $%.2lf, Available: %d)\n", cokePrice, cokeAvailable);
        printf("2. Pepsi (Price: $%.2lf, Available: %d)\n", pepsiPrice, pepsiAvailable);
        printf("3. Sprite (Price: $%.2lf, Available: %d)\n", spritePrice, spriteAvailable);
        printf("4. 7UP (Price: $%.2lf, Available: %d)\n", sevenUpPrice, sevenUpAvailable);
        printf("5. EXIT\n");

        printf("\nEnter the drink number you want to purchase (1-4): ");
        scanf("%d", &choice);

        if (choice >= 1 && choice <= 4)
        {
            printf("Enter the quantity you want to buy: ");
            scanf("%d", &quantity);
        }

        switch (choice)
        {
        case 1:
            quantity = checkAvailability(cokeAvailable, quantity);
            if (quantity == 0)
                break;
            totalBill += calculateBill(quantity, cokePrice);
            updateStock(&cokeAvailable, quantity);
            printf("You have ordered %d Coke(s).\n", quantity);
            break;

        case 2:
            quantity = checkAvailability(pepsiAvailable, quantity);
            if (quantity == 0)
                break;
            totalBill += calculateBill(quantity, pepsiPrice);
            updateStock(&pepsiAvailable, quantity);
            printf("You have ordered %d Pepsi(s).\n", quantity);
            break;

        case 3:
            quantity = checkAvailability(spriteAvailable, quantity);
            if (quantity == 0)
                break;
            totalBill += calculateBill(quantity, spritePrice);
            updateStock(&spriteAvailable, quantity);
            printf("You have ordered %d Sprite(s).\n", quantity);
            break;

        case 4:
            quantity = checkAvailability(sevenUpAvailable, quantity);
            if (quantity == 0)
                break;
            totalBill += calculateBill(quantity, sevenUpPrice);
            updateStock(&sevenUpAvailable, quantity);
            printf("You have ordered %d 7UP(s).\n", quantity);
            break;

        case 5:
            printf("Exiting program...\n");
            break;

        default:
            printf("Invalid drink choice.\n");
        }

    } while (choice != 5);

    printf("\nFinal Available Drinks:\n");
    printf("1. Coke (Price: $%.2lf, Available: %d)\n", cokePrice, cokeAvailable);
    printf("2. Pepsi (Price: $%.2lf, Available: %d)\n", pepsiPrice, pepsiAvailable);
    printf("3. Sprite (Price: $%.2lf, Available: %d)\n", spritePrice, spriteAvailable);
    printf("4. 7UP (Price: $%.2lf, Available: %d)\n", sevenUpPrice, sevenUpAvailable);
    printf("\nTotal Bill: $%.2lf\n", totalBill);

    return 0;
}

// function definitions
double calculateBill(int quantity, double price)
{
    return quantity * price;
}

int checkAvailability(int availableQuantity, int requestedQuantity)
{
    if (requestedQuantity > availableQuantity)
    {
        printf("Sorry, not enough stock available! Only %d left.\n", availableQuantity);
        return 0;
    }
    else
    {
        return requestedQuantity;
    }
}

void updateStock(int *availableQuantity, int purchasedQuantity)
{
    *availableQuantity -= purchasedQuantity;
}
