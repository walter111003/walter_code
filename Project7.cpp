/*
 * Name: Walter Contreras
 * EID: Wac944
 * PA7
 * Santacruz, Fall 2023
 */

#include "Customer.h"
#include "CustomerDB.h"
#include "UTString.h"
#include <iostream>
#include <stdio.h>

void readString(UTString &);
void readNum(int &);

CustomerDB database;

int num_books = 0;
int num_dice = 0;
int num_figures = 0;
int num_towers = 0;

/* clear the inventory and reset the customer database to empty */
void reset(void) {
  database.clear();
  num_books = 0;
  num_dice = 0;
  num_figures = 0;
  num_towers = 0;
}

/*
 * selectInventItem is a convenience function that allows you
 * to obtain a pointer to the inventory record using the item type name
 * word must be "Books", "Dice", "Figures" or "Towers"
 * for example the expression *selectInventItem("Books") returns the
 * current global variable for the number of books in the inventory
 */
int *selectInventItem(UTString word) {
  if (word == "Books") {
    return &num_books;
  } else if (word == "Dice") {
    return &num_dice;
  } else if (word == "Figures") {
    return &num_figures;
  } else if (word == "Towers") {
    return &num_towers;
  }

  /* NOT REACHED */
  return 0;
}

/*
 * this overload of selectInventItem is similar to selectInventItem above,
 * however this overload takes a Customer as a second argument and selects the
 * data member of that Customer that matches "word". The function returns a
 * pointer to one of the three data members from the specified customer.
 */
int *selectInventItem(UTString word, Customer &cust) {
  if (word == "Books") {
    return &cust.books;
  } else if (word == "Dice") {
    return &cust.dice;
  } else if (word == "Figures") {
    return &cust.figures;
  } else if (word == "Towers") {
    return &cust.towers;
  }

  /* NOT REACHED */
  return 0;
}

/*
 * findMax searches through the CustomerDB "database" and returns the Customer
 * who has purchased the most items of the specified type.
 * type must be one of "Books", "Dice", "Figures" or "Towers".
 *
 * Note: if two or more Customers are tied for having purchased the most of that
 * item type then findMax returns the first Customer in the CustomerDB who has
 * purchased that maximal quantity.
 *
 * Note: in the special case (invalid case) where there are zero Customers in
 * the CustomerDB, fundMax returns a null pointer (0)
 */
Customer *findMax(UTString type) {
  Customer *result = 0;
  int max = 0;
  for (int k = 0; k < database.size(); k += 1) {
    Customer &cust = database[k];
    int *p = selectInventItem(type, cust);
    if (*p > max) {

      max = *p;

      result = &cust;

    }
  }

  return result;

}
void processInventory() {
 UTString itemType;
    int q;  //quatity 'q'
    readString(itemType);

    readNum(q);

    int* inventoryItem = selectInventItem(itemType);
    if (inventoryItem != nullptr) {


        *inventoryItem += q;
    }
}



void processPurchase() {
  // TODO


UTString customerName, itemType;
    int q;
    readString(customerName);
    readString(itemType);
    readNum(q);

    int* inventoryItem = selectInventItem(itemType);
    if (inventoryItem == nullptr) {

        std::cout << "Invalid item type: " << itemType.c_str() << std::endl;
        return;

    }

    if (q > *inventoryItem) {



        std::cout << "sorry " << customerName.c_str() << ", we only have " << *inventoryItem << " " << itemType.c_str() << std::endl;
        return;



    }

    Customer& customer = database[customerName];  


    *inventoryItem -= q;

    int* customerItem = selectInventItem(itemType, customer);

    *customerItem += q;  

}

void processReturn() {
  // TODO

UTString customerName, itemType;

    int q;

    readString(customerName);



    readString(itemType);


    readNum(q);

    if (!database.isMember(customerName)) {

        std::cout << "sorry " << customerName.c_str() << ", we do not have you in our database" << std::endl;
        return;

    }

    Customer& customer = database[customerName];

    int* customerItem = selectInventItem(itemType, customer);

    if (*customerItem < q) {



        std::cout << customerName.c_str() << ", you do not have " << q << " " << itemType.c_str() << std::endl;
        return;



    }

    *customerItem -= q;


    int* inventoryItem = selectInventItem(itemType);

    *inventoryItem += q;


}

void processSummarize() {
    
  std::cout << "there are " << num_books << " books " << num_dice << " dice " << num_figures << " figures and " << num_towers << " towers in inventory" << std::endl;
    std::cout << "we have had a total of " << database.size() << " different customers" << std::endl;

    Customer* maxFigures = findMax("Figures");

    Customer* maxBooks = findMax("Books");

    Customer* maxDice = findMax("Dice");

    Customer* maxTowers = findMax("Towers");
   
    


    if (maxBooks != nullptr) {

        std::cout << maxBooks->name.c_str() << " has purchased the most books (" << maxBooks->books << ")" << std::endl;

    } else {
        std::cout << "no one has purchased any books" << std::endl;

    }
    if (maxDice != nullptr) {

        std::cout << maxDice->name.c_str() << " has purchased the most dice (" << maxDice->dice << ")" << std::endl;
    } else {

        std::cout << "no one has purchased any dice" << std::endl;


    }
    if (maxFigures != nullptr) {
        std::cout << maxFigures->name.c_str() << " has purchased the most figures (" << maxFigures->figures << ")" << std::endl;


    } else {


        std::cout << "no one has purchased any figures" << std::endl;
    }
    if (maxTowers != nullptr) {


        std::cout << maxTowers->name.c_str() << " has purchased the most towers (" << maxTowers->towers << ")" << std::endl;


    } else {
        std::cout << "no one has purchased any towers" << std::endl;
    }
}
