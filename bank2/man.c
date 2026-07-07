#include <stdio.h>
#include <string.h>

#define MAX 100
#define FILE_NAME "bank_data.txt"

struct Bank {
    int accNo;
    char name[50];
    int pin;
    float balance;
};

struct Bank accounts[MAX];
int count = 0;

// FUNCTION DECLARATIONS
int findAccountInMemory(int accNo);
void loadFromFile();
void writeToFile();
void createAccount();
void deposit();
void withdraw();
void checkBalance();
void viewAll();

// Find account in array
int findAccountInMemory(int accNo) {
    for (int i = 0; i < count; i++) {
        if (accounts[i].accNo == accNo)
            return i;
    }
    return -1;
}

// Load all accounts from file to array
void loadFromFile() {
    FILE *fp = fopen(FILE_NAME, "r");
    count = 0;

    if (fp == NULL) {
        return;
    }

    while (fscanf(fp, "%d %49s %d %f",
                  &accounts[count].accNo,
                  accounts[count].name,
                  &accounts[count].pin,
                  &accounts[count].balance) == 4) {
        count++;
        if (count >= MAX)
            break;
    }

    fclose(fp);
}

// Rewrite all accounts to file
void writeToFile() {
    FILE *fp = fopen(FILE_NAME, "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%d %s %d %.2f\n",
                accounts[i].accNo,
                accounts[i].name,
                accounts[i].pin,
                accounts[i].balance);
    }

    fclose(fp);
}

int main() {
    int choice;

    printf("=====================================\n");
    printf(" BANK MANAGEMENT SYSTEM\n");
    printf("=====================================\n");

    while (1) {
        printf("\n1. Create Account\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Check Balance\n");
        printf("5. View All Accounts\n");
        printf("6. Exit\n");
        printf("Enter Your Choice: ");
        scanf("%d", &choice);

        switch (choice) {
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

// CREATE ACCOUNT with file operation
void createAccount() {
    struct Bank acc;
    FILE *fp;

    loadFromFile();

    printf("\n--- CREATE NEW ACCOUNT ---\n");
    printf("Enter Account Number: ");
    scanf("%d", &acc.accNo);

    if (findAccountInMemory(acc.accNo) != -1) {
        printf("Account Number already exists!\n");
        return;
    }

    printf("Enter Name: ");
    scanf(" %49s", acc.name);

    printf("Set 4-digit PIN: ");
    scanf("%d", &acc.pin);

    printf("Enter Initial Deposit: ");
    scanf("%f", &acc.balance);

    if (acc.balance < 500) {
        printf("Minimum balance 500 required!\n");
        return;
    }

    fp = fopen(FILE_NAME, "a");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fprintf(fp, "%d %s %d %.2f\n",
            acc.accNo, acc.name, acc.pin, acc.balance);

    fclose(fp);

    printf("Account Created Successfully!\n");
}

// DEPOSIT with file operation
void deposit() {
    int accNo, pin, i;
    float amt;

    loadFromFile();

    printf("\nEnter Account Number: ");
    scanf("%d", &accNo);

    i = findAccountInMemory(accNo);

    if (i == -1) {
        printf("Account Not Found!\n");
        return;
    }

    printf("Enter PIN: ");
    scanf("%d", &pin);

    if (accounts[i].pin != pin) {
        printf("Invalid PIN!\n");
        return;
    }

    printf("Enter Amount to Deposit: ");
    scanf("%f", &amt);

    if (amt <= 0) {
        printf("Invalid Amount!\n");
        return;
    }

    accounts[i].balance += amt;
    writeToFile();

    printf("%.2f Deposited. New Balance: %.2f\n", amt, accounts[i].balance);
}

// WITHDRAW with file operation
void withdraw() {
    int accNo, pin, i;
    float amt;

    loadFromFile();

    printf("\nEnter Account Number: ");
    scanf("%d", &accNo);

    i = findAccountInMemory(accNo);

    if (i == -1) {
        printf("Account Not Found!\n");
        return;
    }

    printf("Enter PIN: ");
    scanf("%d", &pin);

    if (accounts[i].pin != pin) {
        printf("Invalid PIN!\n");
        return;
    }

    printf("Enter Amount to Withdraw: ");
    scanf("%f", &amt);

    if (amt <= 0) {
        printf("Invalid Amount!\n");
        return;
    }

    if (amt > accounts[i].balance) {
        printf("Insufficient Balance!\n");
        return;
    }

    accounts[i].balance -= amt;
    writeToFile();

    printf("%.2f Withdrawn. New Balance: %.2f\n", amt, accounts[i].balance);
}

// CHECK BALANCE with file operation
void checkBalance() {
    int accNo, pin, i;

    loadFromFile();

    printf("\nEnter Account Number: ");
    scanf("%d", &accNo);

    i = findAccountInMemory(accNo);

    if (i == -1) {
        printf("Account Not Found!\n");
        return;
    }

    printf("Enter PIN: ");
    scanf("%d", &pin);

    if (accounts[i].pin != pin) {
        printf("Invalid PIN!\n");
        return;
    }

    printf("\nAccount Holder: %s\n", accounts[i].name);
    printf("Account No: %d\n", accounts[i].accNo);
    printf("Current Balance: %.2f\n", accounts[i].balance);
}

// VIEW ALL with file operation
void viewAll() {
    loadFromFile();

    if (count == 0) {
        printf("No Accounts Created Yet!\n");
        return;
    }

    printf("\n--- ALL ACCOUNTS ---\n");
    for (int i = 0; i < count; i++) {
        printf("AccNo: %d | Name: %s | Balance: %.2f\n",
               accounts[i].accNo,
               accounts[i].name,
               accounts[i].balance);
    }
}