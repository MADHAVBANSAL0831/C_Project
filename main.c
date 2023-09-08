#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct items
{
    char item[20];
    float price;
    int qty;
};

struct orders
{
    char customer[50];
    char date[50];
    int numOfItems;
    struct items itm[50];
};

void generateBillHeader(char name[50], char date[30])
{
    printf("\n\n");
    printf("\t    ADV. Restaurant");
    printf("\n\t   -----------------");
    printf("\nDate:%s", date);
    printf("\nInvoice To: %s", name);
    printf("\n");
    printf("-----------------------------------------------------------\n");
    printf("Items\t\t");
    printf("Qty\t\t");
    printf("Price\t\t");
    printf("Total\t\t");
    printf("\n-----------------------------------------------------------");
    printf("\n\n");
}

void generateBillBody(char item[30], int qty, float price)
{
    printf("%s\t\t", item);
    printf("%d\t\t", qty);
    printf("%.2f\t\t", price);
    printf("%.2f\t\t\t", qty * price);
    printf("\n");
}

void generateBillFooter(float total)
{
    printf("\n");
    float dis = 0.1 * total;
    float netTotal = total - dis;
    float cgst = 0.09 * netTotal, grandTotal = netTotal + 2 * cgst;
    printf("-----------------------------------------------------------\n");
    printf("Sub Total\t\t\t\t\t%.2f", total);
    printf("\nDiscount @10%s\t\t\t\t\t%.2f", "%", dis);
    printf("\n\t\t\t\t");
    printf("\nNet Total\t\t\t\t\t%.2f", netTotal);
    printf("\nCGST @9%s\t\t\t\t\t%.2f", "%", cgst);
    printf("\nSGST @9%s\t\t\t\t\t%.2f", "%", cgst);
    printf("\n-----------------------------------------------------------");
    printf("\nGrand Total\t\t\t\t\t%.2f", grandTotal);
    printf("\n-----------------------------------------------------------\n");
}

int checkNum(char str[])
{
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            i++;
            continue;
        }
        else
        {
            return 0;
        }
    }

    return 1;
}

int checkfloat(char str[])
{
    int i=0;
    int flag=1;
    while (str[i] != '\0')
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            i++;
            continue;
        }
        else
        if(str[i]=='.' && flag==1)
        {
            flag=0;
            i++;
        }
        else
        {
            return 0;
        }
    }

    return 1;
}

float stringToFloat(char str[])
{
    float floatValue;
    floatValue = atof(str);

    return floatValue;
}

int stringToNum(char str[])
{
    int num = 0;
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            int x = str[i] - '0';
            num = num * 10 + x;
        }
        i++;
    }

    return num;
}

int main()
{

    int opt, n;
    struct orders ord;
    struct orders order;
    char saveBill = 'y', contFlag = 'y';
    char name[50];
    FILE *fp;
    // dashboard
    while (contFlag == 'y')
    {
        float total = 0;
        int invoiceFound = 0;
        printf("\t============ADV. RESTAURANT============");
        printf("\n\nPlease select your prefered operation");
        printf("\n\n1.Generate Invoice");
        printf("\n2.Show all Invoices");
        printf("\n3.Search Invoice");
        printf("\n4.Exit");

        printf("\n\nYour choice:\t");
        scanf("%d", &opt);
        fgetc(stdin);
        switch (opt)
        {
        case 1:
            printf("\nPlease enter the name of the customer:\t");
            fgets(ord.customer, 50, stdin);
            //printf("%d", strlen(ord.customer));
            while(strlen(ord.customer)==1)
            {
                printf("\nPlease Give Some Input!!!\n");
                printf("\nPlease enter the name of the customer:\t");
                fgets(ord.customer, 50, stdin);
            }
            ord.customer[strlen(ord.customer) - 1] = 0;
            strcpy(ord.date, __DATE__);

            char str[100];
            printf("\nPlease enter the number of items:\t");
            scanf("%s", &str);
            while (checkNum(str) == 0)
            {
                printf("\nNumber of items is invalid, Please Try again\n");
                printf("\nPlease enter the number of items:\t");
                scanf("%s", &str);
            }
            n = stringToNum(str);
            ord.numOfItems = n;

            for (int i = 0; i < n; i++)
            {
                fgetc(stdin);
                printf("\n\n");
                printf("Please enter the item %d:\t", i + 1);
                fgets(ord.itm[i].item, 20, stdin);
                while(strlen(ord.itm[i].item)==1)
                {
                    printf("\nPlease Give Some Input!!!\n\n");
                    printf("Please enter the item %d:\t", i + 1);
                    fgets(ord.itm[i].item, 20, stdin);
                }
                ord.itm[i].item[strlen(ord.itm[i].item) - 1] = 0;

                int unit;
                printf("Please enter the quantity:\t");
                scanf("%s", &str);
                while (checkNum(str) == 0)
                {
                    printf("Quantity is invalid, Please Try again\n\n");
                    printf("Please enter the quantity:\t");
                    scanf("%s", &str);
                }
                unit = stringToNum(str);
                ord.itm[i].qty = unit;

                float unit_price;
                printf("Please enter the unit price:\t");
                scanf("%s", &str);
                while (checkfloat(str) == 0)
                {
                    printf("\nPrice is invalid, Please Try again\n\n");
                    printf("Please enter the unit price:\t");
                    scanf("%s", &str);
                }
                unit_price = stringToFloat(str);
                ord.itm[i].price = unit_price;

                total += ord.itm[i].qty * ord.itm[i].price;
            }

            generateBillHeader(ord.customer, ord.date);
            for (int i = 0; i < ord.numOfItems; i++)
            {
                generateBillBody(ord.itm[i].item, ord.itm[i].qty, ord.itm[i].price);
            }
            generateBillFooter(total);

            printf("\nDo you want to save the invoice [y/n]:\t");
            scanf("%s", &saveBill);

            if (saveBill == 'y')
            {
                fp = fopen("RestaurantBill.txt", "a+");
                fwrite(&ord, sizeof(struct orders), 1, fp);
                if (fwrite != 0)
                    printf("\nSuccessfully saved");
                else
                    printf("\nError saving");
                fclose(fp);
            }
            break;

        case 2:
            fp = fopen("RestaurantBill.txt", "r");
            printf("\n  *****Your Previous Invoices*****\n");
            while (fread(&order, sizeof(struct orders), 1, fp))
            {
                float tot = 0;
                generateBillHeader(order.customer, order.date);
                for (int i = 0; i < order.numOfItems; i++)
                {
                    generateBillBody(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
                    tot += order.itm[i].qty * order.itm[i].price;
                }
                generateBillFooter(tot);
            }
            fclose(fp);
            break;

        case 3:
            printf("Enter the name of the customer:\t");
            // fgetc(stdin);
            fgets(name, 50, stdin);
            name[strlen(name) - 1] = 0;
            fp = fopen("RestaurantBill.txt", "r");
            printf("\t*****Invoice of %s*****", name);
            while (fread(&order, sizeof(struct orders), 1, fp))
            {
                float tot = 0;
                if (!strcmp(order.customer, name))
                {
                    generateBillHeader(order.customer, order.date);
                    for (int i = 0; i < order.numOfItems; i++)
                    {
                        generateBillBody(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
                        tot += order.itm[i].qty * order.itm[i].price;
                    }
                    generateBillFooter(tot);
                    invoiceFound = 1;
                }
            }
            if (!invoiceFound)
            {
                printf("Sorry the invoice for %s doesnot exists", name);
            }
            fclose(fp);
            break;

        case 4:
            printf("\n\t\t Bye Bye :)\n\n");
            exit(0);
            break;

        default:
            printf("Sorry invalid option");
            break;
        }
        printf("\nDo you want to perform another operation?[y/n]:\t");
        scanf("%s", &contFlag);
    }
    printf("\n\t\t Bye Bye :)\n\n");
    printf("\n\n");

    return 0;
}
