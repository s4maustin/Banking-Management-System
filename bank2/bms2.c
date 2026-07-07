#include <stdio.h>
#include <string.h>

#define MAX 100

// 1. STRUCTURE
struct Bank {
    int accNo;
    char name[50];
    int pin;
    float balance;
};

struct Bank accounts[MAX];
int count = 0;

// FUNCTION DECLARATIONS
int findAccount(int accNo);
void createAccount();
void deposit();
void withdraw();
void checkBalance();
void viewAll();

int main() {
    int choice;

    printf("=====================================\n");
    printf(" BANK MANAGEMENT SYSTEM\n");
    printf("=====================================\n");

    while(1) { // WHILE LOOP
        printf("\n1. Create Account\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Check Balance\n");
        printf("5. View All Accounts\n");
        printf("6. Exit\n");
        printf("Enter Your Choice: ");
        scanf("%d", &choice);

        switch(choice) { // SWITCH CASE
            case 1: createAccount(); break;
            case 2: deposit(); break;
            case 3: withdraw(); break;
            case 4: checkBalance(); break;
            case 5: viewAll(); break;
            case 6:
                printf("Thank You for using our Bank!\n");
                return 0;
            default:
                printf("Invalid Choice! Please try again.\n");
        }
    }
    return 0;
}

// FUNCTION DEFINITIONS

int findAccount(int accNo) { // to search account
    for(int i = 0; i < count; i++) {
        if(accounts[i].accNo == accNo)
            return i;
    }
    return -1;
}

void createAccount() {
    struct Bank acc;
    printf("\n--- CREATE NEW ACCOUNT ---\n");
    printf("Enter Account Number: ");
    scanf("%d", &acc.accNo);

    if(findAccount(acc.accNo)!= -1) {
        printf("Account Number already exists!\n");
        return;
    }

    printf("Enter Name: ");
    scanf(" %[^\n]", acc.name);

    printf("Set 4-digit PIN: ");
    scanf("%d", &acc.pin);

    printf("Enter Initial Deposit: ");
    scanf("%f", &acc.balance);

    if(acc.balance < 500) { // IF condition
        printf("Minimum balance 500 required!\n");
        return;
    }

    accounts[count++] = acc;
    printf("Account Created Successfully!\n");
}

void deposit() {
    int accNo, pin;
    float amt;
    printf("\nEnter Account Number: ");
    scanf("%d", &accNo);
    int i = findAccount(accNo);

    if(i == -1) {
        printf("Account Not Found!\n");
        return;
    }

    printf("Enter PIN: ");
    scanf("%d", &pin);

    if(accounts[i].pin!= pin) { // IF condition
        printf("Invalid PIN!\n");
        return;
    }

    printf("Enter Amount to Deposit: ");
    scanf("%f", &amt);
    accounts[i].balance += amt;
    printf("%.2f Deposited. New Balance: %.2f\n", amt, accounts[i].balance);
}

void withdraw() {
    int accNo, pin;
    float amt;
    printf("\nEnter Account Number: ");
    scanf("%d", &accNo);
    int i = findAccount(accNo);

    if(i == -1) {
        printf("Account Not Found!\n");
        return;
    }

    printf("Enter PIN: ");
    scanf("%d", &pin);

    if(accounts[i].pin!= pin) {
        printf("Invalid PIN!\n");
        return;
    }

    printf("Enter Amount to Withdraw: ");
    scanf("%f", &amt);

    if(amt > accounts[i].balance) { // IF condition
        printf("Insufficient Balance!\n");
    } else {
        accounts[i].balance -= amt;
        printf("%.2f Withdrawn. New Balance: %.2f\n", amt, accounts[i].balance);
    }
}

void checkBalance() {
    int accNo, pin;
    printf("\nEnter Account Number: ");
    scanf("%d", &accNo);
    int i = findAccount(accNo);

    if(i == -1) {
        printf("Account Not Found!\n");
        return;
    }

    printf("Enter PIN: ");
    scanf("%d", &pin);

    if(accounts[i].pin!= pin) {
        printf("Invalid PIN!\n");
        return;
    }

    printf("\nAccount Holder: %s\n", accounts[i].name);
    printf("Account No: %d\n", accounts[i].accNo);
    printf("Current Balance: %.2f\n", accounts[i].balance);
}

void viewAll() {
    if(count == 0) {
        printf("No Accounts Created Yet!\n");
        return;
    }
    printf("\n--- ALL ACCOUNTS ---\n");
    for(int i = 0; i < count; i++) {
        printf("AccNo: %d | Name: %s | Balance: %.2f\n",
               accounts[i].accNo, accounts[i].name, accounts[i].balance);
    }
}
