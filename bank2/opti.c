#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define FILE_NAME "bank_data.txt"
#define MIN_BALANCE 500.0f

typedef struct {
    int accNo;
    char name[50];
    int pin;
    float balance;
} Bank;

Bank accounts[MAX];
int count = 0;

int findAccount(int accNo);
void loadFromFile(void);
void saveToFile(void);
int getInt(const char *prompt);
float getFloat(const char *prompt);
void getString(const char *prompt, char *str, int size);
int authenticate(int index);
void createAccount(void);
void deposit(void);
void withdrawMoney(void);
void checkBalance(void);
void viewAll(void);

int findAccount(int accNo) {
    for (int i = 0; i < count; i++) {
        if (accounts[i].accNo == accNo)
            return i;
    }
    return -1;
}

void loadFromFile(void) {
    FILE *fp = fopen(FILE_NAME, "r");
    count = 0;

    if (fp == NULL)
        return;

    while (count < MAX &&
           fscanf(fp, "%d %49s %d %f",
                  &accounts[count].accNo,
                  accounts[count].name,
                  &accounts[count].pin,
                  &accounts[count].balance) == 4) {
        count++;
    }

    fclose(fp);
}

void saveToFile(void) {
    FILE *fp = fopen(FILE_NAME, "w");
    if (fp == NULL) {
        printf("Error saving file!\n");
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

int getInt(const char *prompt) {
    int value;
    printf("%s", prompt);
    while (scanf("%d", &value) != 1) {
        while (getchar() != '\n');
        printf("Invalid input. %s", prompt);
    }
    return value;
}

float getFloat(const char *prompt) {
    float value;
    printf("%s", prompt);
    while (scanf("%f", &value) != 1) {
        while (getchar() != '\n');
        printf("Invalid input. %s", prompt);
    }
    return value;
}

void getString(const char *prompt, char *str, int size) {
    printf("%s", prompt);
    scanf(" ");
    fgets(str, size, stdin);
    str[strcspn(str, "\n")] = '\0';
}

int authenticate(int index) {
    int pin = getInt("Enter PIN: ");
    if (accounts[index].pin != pin) {
        printf("Invalid PIN!\n");
        return 0;
    }
    return 1;
}

void createAccount(void) {
    if (count >= MAX) {
        printf("Account limit reached!\n");
        return;
    }

    Bank acc;
    acc.accNo = getInt("\nEnter Account Number: ");

    if (findAccount(acc.accNo) != -1) {
        printf("Account Number already exists!\n");
        return;
    }

    getString("Enter Name: ", acc.name, sizeof(acc.name));
    acc.pin = getInt("Set 4-digit PIN: ");

    if (acc.pin < 1000 || acc.pin > 9999) {
        printf("PIN must be exactly 4 digits!\n");
        return;
    }

    acc.balance = getFloat("Enter Initial Deposit: ");

    if (acc.balance < MIN_BALANCE) {
        printf("Minimum balance %.2f required!\n", MIN_BALANCE);
        return;
    }

    accounts[count++] = acc;
    saveToFile();
    printf("Account Created Successfully!\n");
}

void deposit(void) {
    int accNo = getInt("\nEnter Account Number: ");
    int i = findAccount(accNo);

    if (i == -1) {
        printf("Account Not Found!\n");
        return;
    }

    if (!authenticate(i))
        return;

    float amt = getFloat("Enter Amount to Deposit: ");
    if (amt <= 0) {
        printf("Invalid Amount!\n");
        return;
    }

    accounts[i].balance += amt;
    saveToFile();
    printf("%.2f Deposited. New Balance: %.2f\n", amt, accounts[i].balance);
}

void withdrawMoney(void) {
    int accNo = getInt("\nEnter Account Number: ");
    int i = findAccount(accNo);

    if (i == -1) {
        printf("Account Not Found!\n");
        return;
    }

    if (!authenticate(i))
        return;

    float amt = getFloat("Enter Amount to Withdraw: ");
    if (amt <= 0) {
        printf("Invalid Amount!\n");
        return;
    }

    if (accounts[i].balance - amt < MIN_BALANCE) {
        printf("Cannot withdraw. Minimum balance %.2f must be maintained!\n", MIN_BALANCE);
        return;
    }

    accounts[i].balance -= amt;
    saveToFile();
    printf("%.2f Withdrawn. New Balance: %.2f\n", amt, accounts[i].balance);
}

void checkBalance(void) {
    int accNo = getInt("\nEnter Account Number: ");
    int i = findAccount(accNo);

    if (i == -1) {
        printf("Account Not Found!\n");
        return;
    }

    if (!authenticate(i))
        return;

    printf("\nAccount Holder: %s\n", accounts[i].name);
    printf("Account No: %d\n", accounts[i].accNo);
    printf("Current Balance: %.2f\n", accounts[i].balance);
}

void viewAll(void) {
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

int main(void) {
    int choice;
    loadFromFile();

    while (1) {
        printf("\n=====================================\n");
        printf(" BANK MANAGEMENT SYSTEM\n");
        printf("=====================================\n");
        printf("1. Create Account\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Check Balance\n");
        printf("5. View All Accounts\n");
        printf("6. Exit\n");

        choice = getInt("Enter Your Choice: ");

        switch (choice) {
            case 1: createAccount(); break;
            case 2: deposit(); break;
            case 3: withdrawMoney(); break;
            case 4: checkBalance(); break;
            case 5: viewAll(); break;
            case 6:
                printf("Thank You for using our Bank!\n");
                return 0;
            default:
                printf("Invalid Choice! Please try again.\n");
        }
    }
}