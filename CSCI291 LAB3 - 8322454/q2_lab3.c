#include <stdio.h>

int main() {
    /*We set the initial balance to 1000*/
    int accountBalance = 1000; 
    /*Given Example Array*/
    int transactions[] = {-2000}; 
    int transactionCount = sizeof(transactions) / sizeof(transactions[0]); 
    int tobeprocessed[sizeof(transactions) / sizeof(transactions[0])]; 
    int pendingCount = 0; 

    for (int i = 0; i < transactionCount; i++) { 
        int currentTransaction = transactions[i]; 
        
        if (currentTransaction < 0) {
            if (-currentTransaction > accountBalance) {
                printf("Invalid transaction: %d. Skipping this transaction. Not enough funds\n", currentTransaction);
                tobeprocessed[pendingCount++] = currentTransaction;
                continue;
            }
        }
        /*Processes both withdrawals and transactions*/
        accountBalance += currentTransaction;
        printf("Processed transaction of : %d AED. Current balance: %d AED\n", currentTransaction, accountBalance);
        
        if (accountBalance <= 0) {
            printf("Balance has reached zero. No further transactions will be processed.\n");
            break;
        }
    }
/*Prints the final balance*/
    printf("Final balance: %d AED\n", accountBalance);
/*Prints the pending transactions*/
    printf("Transactions to be processed: ");
    for (int i = 0; i < pendingCount; i++) { 
        printf("%d AED ", tobeprocessed[i]);
    }
    printf("\n");

    return 0;
}
