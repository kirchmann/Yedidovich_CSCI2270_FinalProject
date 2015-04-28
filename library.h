#ifndef LIBRARY_H_INCLUDED
#define LIBRARY_H_INCLUDED
#include <string>
#include <iostream>

using namespace std;

struct item{
    string title;
    string author;
    int year;
    string type; //book, DVD, CD, etc.
    string genre;
    bool checked_out;
    int quantity;
    item *next;

    item(){};

    item(string in_title, int in_year, string in_type, string in_genre, bool in_checked_out, int in_quantity, string in_author)
    {
        title = in_title;
        year = in_year;
        type = in_type;
        genre = in_genre;
        checked_out = in_checked_out;
        quantity = in_quantity;
        author = in_author;
    }
};

class Library
{
    public:
        Library();
        void insertItem(string in_title, int in_year, string in_type, string in_genre, int in_quantity, string in_author);
        void checkStatus(string in_title); //find item and display information
        void checkOutItem(string in_title); //check out an item
        void returnItem(string in_title); //return an item
        void deleteItem(string in_title); //delete the item from the library
        void printInventory(int filter, string input); // print all of one type of item (checked out, a specific genre, etc)
        void printAllInventory(); //print the entire inventory
    protected:
    private:
        item *hashTable[20];
        int hashSum(string title);
};

#endif // LIBRARY_H_INCLUDED
