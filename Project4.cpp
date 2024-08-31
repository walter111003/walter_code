/*
 * EE312 Simple CRM Project
 *
 * Walter Contreras 
 * EID: wac944
 */

#include "Invent.h"
#include "MyString.h"
#include <assert.h>
#include <stdio.h>

#define MAX_CUSTOMERS 1000
Customer customers[MAX_CUSTOMERS];
int num_customers = 0;
Customer t; // Global inventory


void reset(void) {

    t.towers = 0;
    t.books = 0;

    t.figures = 0;

    t.dice = 0;

  
    for (int i = 0; i < num_customers; i++) {

        customers[i].towers = 0;
        customers[i].books = 0;
         customers[i].figures = 0;

        customers[i].dice = 0;





        StringDestroy(&customers[i].name);
    }
    num_customers = 0;
}


Customer* Finder(String name, bool notfound) {
    for (int i = 0; i < num_customers; ++i) {
        if (StringIsEqualTo(&name, &customers[i].name)) {
            return &customers[i];
        }
    }
    if (notfound && num_customers < MAX_CUSTOMERS) {
        Customer* newcustomer = &customers[num_customers];

        newcustomer->name = StringDup(&name);


        newcustomer->books = 0;


        newcustomer->dice = 0;

        newcustomer->figures = 0;

        newcustomer->towers = 0;

        num_customers++;

        return newcustomer;




    } else {
        return NULL;
    }
}


int Finder2(String object) {
    int result = -1;
    String towers = StringCreate("Towers");

    String figures = StringCreate("Figures");

    String books = StringCreate("Books");
    
    String dice = StringCreate("Dice");



    if (StringIsEqualTo(&object, &books)) {
        result = 0;
    } else if (StringIsEqualTo(&object, &dice)) {
        result = 1;
    } else if (StringIsEqualTo(&object, &figures)) {
        result = 2;



    } else if (StringIsEqualTo(&object, &towers)) {
        result = 3;
    }


    StringDestroy(&books);

    StringDestroy(&dice);

    StringDestroy(&figures);

    StringDestroy(&towers);

    return result;
}

int* recieve_inventory(int index) {
    switch (index) {
        case 0: return &t.books;

        case 1: return &t.dice;

        case 2: return &t.figures;

        case 3: return &t.towers;


        default: return NULL;
    }
}


int* recieve_customer(Customer* customer, int index) {
    switch (index) {
        case 0: return &customer->books;

        case 1: return &customer->dice;

        case 2: return &customer->figures;

        case 3: return &customer->towers;



        default: return NULL;
    }
}


void processSummarize() {
    printf("There are %d Books %d Dice %d Figures and %d Towers in inventory\n", t.books, t.dice, t.figures, t.towers);


    printf("We have had a total of %d different customers\n", num_customers);


    Customer* towers$ = num_customers > 0 ? &customers[0] : NULL;
    
    Customer* figures$ = num_customers > 0 ? &customers[0] : NULL;

    Customer* books$ = num_customers > 0 ? &customers[0] : NULL;



    Customer* dice$ = num_customers > 0 ? &customers[0] : NULL;
   
  

    for (int i = 0; i < num_customers; i++) { 
        if (customers[i].books > (books$ ? books$->books : 0)) { 
            books$ = &customers[i];


        }


        if (customers[i].dice > (dice$ ? dice$->dice : 0)) {
            dice$ = &customers[i];


        }
        if (customers[i].figures > (figures$ ? figures$->figures : 0)) {


            figures$ = &customers[i];
        }
        if (customers[i].towers > (towers$ ? towers$->towers : 0)) {
            towers$ = &customers[i];
        }
    }

    if (books$ && books$->books > 0) {
        StringPrint(&(books$->name));
        printf(" has purchased the most Books (%d)\n", books$->books);
    } else {

        printf("no one has purchased any Books\n");
    }
    if (dice$ && dice$->dice > 0) {

        StringPrint(&(dice$->name));

        printf(" has purchased the most Dice (%d)\n", dice$->dice);

    } else {
        printf("no one has purchased any Dice\n");
    }
    if (figures$ && figures$->figures > 0) {


        StringPrint(&(figures$->name));
        printf(" has purchased the most Figures (%d)\n", figures$->figures);


    } else {


        printf("no one has purchased any Figures\n");
    }
    if (towers$ && towers$->towers > 0) {
        StringPrint(&(towers$->name));

        printf(" has purchased the most Towers (%d)\n", towers$->towers);

    } else {
        printf("no one has purchased any Towers\n");
    }
}


void processPurchase() {
    String name;



    String type;

    int amount;

    readString(&name);

    readString(&type);

    readNum(&amount);
    
    int add = 0; 
     add = Finder2(type);
    if (add != -1) {
        if (amount > 0) {
            int* inventory = recieve_inventory(add);

            if (*inventory >= amount) {

                Customer* customerptr = Finder(name, true);

                if (customerptr != NULL) {

                    int* customerfield = recieve_customer(customerptr, add);

                    *inventory -= amount;



                    *customerfield += amount;


                }
            } else {
                printf("Sorry ");


                StringPrint(&name);


                printf(", we only have %d ", *inventory);


                StringPrint(&type);



                printf("\n");
            }
        }
    }

    StringDestroy(&name);


    StringDestroy(&type);
}

void processReturn() {
    String name;

    String type1;

    int amount1;

    readString(&name);

    readString(&type1);

    readNum(&amount1);

    Customer* customer = Finder(name, false);

    if (customer != NULL) {
        int index = Finder2(type1);
        if (index != -1) {
            int* inv1 = recieve_inventory(index);

            int* con_f = recieve_customer(customer, index);

            if (*con_f >= amount1) {

                *con_f -= amount1;
                *inv1 += amount1;
            } else {
                StringPrint(&name);
                printf(", you do not have %d ", amount1);

                StringPrint(&type1);


                printf("\n");
            }
        }
    } else {
        printf("Sorry ");
        StringPrint(&name);

        printf(", we do not have you in our database\n"); 
    }

    StringDestroy(&name);



    StringDestroy(&type1);
}


void processInventory() {
    String type2;
    int amount2;

    readString(&type2);




    readNum(&amount2);
    int add = 0; 
     add = Finder2(type2); 
    if (add != -1) {
        int* inv = recieve_inventory(add);



        *inv += amount2;
    }
    StringDestroy(&type2);
}
