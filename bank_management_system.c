#include <stdio.h> // file handling
#include <string.h>

const char *ACCOUNT_NAME = "bank_accounts.dat";

typedef struct
{
     char name[100];
     int acc_no;
     float balance;
} Account;

// Function to create a new account
void create_account()
{
     Account acc;
     FILE *file = fopen(ACCOUNT_NAME, "ab+"); // open file in append mode
     if (file == NULL)
     {
          printf("Error opening file!\n");
          return;
     }

     char c;
     do
     {
          c = getchar();
     } while (c != '\n' && c != EOF);

     printf("enter your name: ");
     fgets(acc.name, sizeof(acc.name), stdin); // input user name
     int index = strcspn(acc.name, "\n");
     acc.name[index] = '\0';           // last ar enter(\n) ta k character hisab a dhorbe na..
     printf("enter account number: "); // input account number
     scanf("%d", &acc.acc_no);
     acc.balance = 0;

     fwrite(&acc, sizeof(acc), 1, file); // write account to file
     fclose(file);
     printf("Account created successfully!\n");
}

// Function to deposit money
void deposit_money()
{
     FILE *file = fopen(ACCOUNT_NAME, "rb+"); // open file in read/update mode
     if (file == NULL)
     {
          printf("Error opening file!\n");
          return;
     }

     int acc_no;
     float money;
     Account acc_to_read;
     printf("Enter account number: ");
     scanf("%d", &acc_no);
     printf("enter amount to deposit: ");
     scanf("%f", &money);
     while (fread(&acc_to_read, sizeof(acc_to_read), 1, file))
     {
          if (acc_to_read.acc_no == acc_no)
          {                                                        // check if account exists
               acc_to_read.balance += money;                       // update balance
               fseek(file, -sizeof(acc_to_read), SEEK_CUR);        // move file pointer back
               fwrite(&acc_to_read, sizeof(acc_to_read), 1, file); // write updated account back to file
               printf("Successfully Deposited: Rs.%.2f\nNew balance: Rs.%.2f\n", money, acc_to_read.balance);
               fclose(file);
               return;
          }
     }

     fclose(file);
     printf("Account no:%d was not found.\n", acc_no);
}

// Function to withdraw money
void withdraw_money()
{
     FILE *file = fopen(ACCOUNT_NAME, "rb+"); // open file in read/update mode
     if (file == NULL)
     {
          printf("Error opening file!\n");
          return;
     }

     int acc_no;
     float money;
     Account acc_to_read;
     printf("Enter account number: ");
     scanf("%d", &acc_no);
     printf("enter amount to withdraw: ");
     scanf("%f", &money);
     while (fread(&acc_to_read, sizeof(acc_to_read), 1, file))
     {
          if (acc_to_read.acc_no == acc_no)
          { // check if account exists
               if (acc_to_read.balance >= money)
               {
                    acc_to_read.balance -= money;                       // update balance
                    fseek(file, -sizeof(acc_to_read), SEEK_CUR);        // move file pointer back
                    fwrite(&acc_to_read, sizeof(acc_to_read), 1, file); // write updated account back to file
                    printf("Successfully Withdrawn: Rs.%.2f\nNew balance: Rs.%.2f\n", money, acc_to_read.balance);
               }
               else
               {
                    printf("Insufficient balance!\n");
               }
               fclose(file);
               return;
          }
     }

     fclose(file);
     printf("Account no:%d was not found.\n", acc_no);
}

// Function to check account balance
void check_balance()
{
     Account acc;
     FILE *file = fopen(ACCOUNT_NAME, "rb"); // open file in read mode
     if (file == NULL)
     {
          printf("Error opening file!\n");
          return;
     }

     int acc_no;
     Account acc_read;
     printf("Enter account number: ");
     scanf("%d", &acc_no);

     while (fread(&acc_read, sizeof(acc_read), 1, file))
     {
          if (acc_read.acc_no == acc_no)
          {
               printf("Your Account Balance is Rs.%.2f\n", acc_read.balance);
               fclose(file);
               return;
          }
     }
     fclose(file);
     printf("Account no:%d was not found.\n", acc_no);
}

// main function
int main()
{
     while (1)
     {
          int choice;
          printf("\n");
          printf("*** bank management system ***\n");
          printf("1.create account\n");
          printf("2.deposit money\n");
          printf("3.withdraw money\n");
          printf("4.check balance\n");
          printf("5.exit\n");
          printf("enter the choice: ");
          scanf("%d", &choice);
          switch (choice)
          {
          case 1:
               create_account();
               break;
          case 2:
               deposit_money();
               break;
          case 3:
               withdraw_money();
               break;
          case 4:
               check_balance();
               break;
          case 5:
               printf("Exiting...\n");
               return 0;
          default:
               printf("Invalid choice. Please try again.\n");
          }
     }
}