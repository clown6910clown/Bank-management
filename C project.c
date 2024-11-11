#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACCOUNTS 100
#define MAX_TRANSACTIONS 100

typedef struct Account {
    int accountNumber;
    char name[50];
    float balance;
    struct Account* next; // For linked list of adjacent accounts
} Account;

typedef struct Transaction {
    int accountNumber;
    char type; // 'D' for deposit, 'W' for withdrawal
    float amount;
} Transaction;

// Global variables
Account* accounts[MAX_ACCOUNTS]; // Array of account pointers
Transaction transactions[MAX_TRANSACTIONS];
int transactionCount = 0;

// Function prototypes
Account* createAccount(int accountNumber, const char* name);
void insertAccount(Account* newAccount);
Account* findAccount(int accountNumber);
void deposit(int accountNumber, float amount);
void withdraw(int accountNumber, float amount);
void transfer(int fromAccount, int toAccount, float amount);
void displayAccounts();
void displayTransactions();
void generateReport();

int main() {
    int choice;

    while (1) {
        printf("\n--- Banking Management System ---\n");
        printf("1. Create Account\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Transfer\n");
        printf("5. Display Accounts\n");
        printf("6. Display Transactions\n");
        printf("7. Generate Report\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int accountNumber;
                char name[50];
                printf("Enter account number: ");
                scanf("%d", &accountNumber);        // account number
                printf("Enter account holder name: ");
                scanf("%s", name);                  // holder name
                Account* newAccount = createAccount(accountNumber, name);
                insertAccount(newAccount);
                printf("Account created successfully. Account number: %d\n", accountNumber);
                break;
            }
            case 2: {
                int accountNumber;
                float amount;
                printf("Enter account number: ");
                scanf("%d", &accountNumber);        // account number
                printf("Enter amount to deposit: ");
                scanf("%f", &amount);               // amount 
                deposit(accountNumber, amount);
                break;
            }
            case 3: {
                int accountNumber;
                float amount;
                printf("Enter account number: ");
                scanf("%d", &accountNumber);        // account number
                printf("Enter amount to withdraw: ");
                scanf("%f", &amount);               // amount
                withdraw(accountNumber, amount);
                break;
            }
            case 4: {
                int fromAccount, toAccount;
                float amount;
                printf("Enter source account number: ");
                scanf("%d", &fromAccount);                  // from 
                printf("Enter destination account number: ");
                scanf("%d", &toAccount);                    // to
                printf("Enter amount to transfer: ");
                scanf("%f", &amount);                       // amount
                transfer(fromAccount, toAccount, amount);
                break;
            }
            case 5:
                displayAccounts();
                break;
            case 6:
                displayTransactions();
                break;
            case 7:
                generateReport();
                break;
            case 8:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

Account* createAccount(int accountNumber, const char* name) {
    Account* newAccount = (Account*)malloc(sizeof(Account));
    newAccount->accountNumber = accountNumber;
    strcpy(newAccount->name, name);
    newAccount->balance = 0.0; 
    newAccount->next = NULL; 
    return newAccount;
}

void insertAccount(Account* newAccount) {
    // Simple insertion into the accounts array
    accounts[newAccount->accountNumber] = newAccount;
}

Account* findAccount(int accountNumber) {
    if (accountNumber < 0 || accountNumber >= MAX_ACCOUNTS) {
        return NULL; // Out of bounds
    }
    return accounts[accountNumber];
}

void deposit(int accountNumber, float amount) {
    Account* account = findAccount(accountNumber);
    if (account == NULL) {
        printf("Account not found.\n");
        return;
    }
    if (amount <= 0) {
        printf("Invalid deposit amount.\n");
        return;
    }

    account->balance += amount;

    // Record transaction
    transactions[transactionCount++] = (Transaction){accountNumber, 'D', amount};
    printf("Deposited %.2f into account %d. New balance: %.2f\n",amount, accountNumber, account->balance);
}

void withdraw(int accountNumber, float amount) {
    Account* account = findAccount(accountNumber);
    if (account == NULL) {
        printf("Account not found.\n");
        return;
    }
    if (amount <= 0 || amount > account->balance) {
        printf("Invalid withdrawal amount.\n");
        return;
    }

    account->balance -= amount;

    // Record transaction
    transactions[transactionCount++] = (Transaction){accountNumber, 'W', amount};
    printf("Withdrew %.2f from account %d. New balance: %.2f\n",amount, accountNumber, account->balance);
}

void transfer(int fromAccount, int toAccount, float amount) {
    Account* fromAcc = findAccount(fromAccount);
    Account* toAcc = findAccount(toAccount);
    if (fromAcc == NULL || toAcc == NULL) {
        printf("One or both accounts not found.\n");
        return;
    }
    if (amount <= 0 || amount > fromAcc->balance) {
        printf("Invalid transfer amount.\n");
        return;
    }

    fromAcc->balance -= amount;
    toAcc->balance += amount;

    // Record transactions
    transactions[transactionCount++] = (Transaction){fromAccount, 'W', amount}; // Withdrawal from sender
    transactions[transactionCount++] = (Transaction){toAccount, 'D', amount}; // Deposit to receiver

    printf("Transferred %.2f from account %d to account %d.\n",amount, fromAccount, toAccount);
}

void displayAccounts() {
	int i;
    printf("\n--- Account List ---\n");
    for (i = 0; i < MAX_ACCOUNTS; i++) {
        if (accounts[i] != NULL) {
            printf("Account Number: %d, Name: %s, Balance: %.2f\n",
                   accounts[i]->accountNumber,
                   accounts[i]->name,
                   accounts[i]->balance);
        }
    }
}

void displayTransactions() {
	int i;
    printf("\n--- Transaction History ---\n");
    for (i = 0; i < transactionCount; i++) {
        printf("Account Number: %d, Type: %c, Amount: %.2f\n",
               transactions[i].accountNumber,
               transactions[i].type,
               transactions[i].amount);
    }
}

void generateReport() {
    // Simple report generation based on account balances
    printf("\n***********************************\n");
    printf("\n--- Account Balance Report ---\n");
    displayAccounts();
    printf("\n***********************************\n");
}
