#include "library.h"
#include <iostream>
#include <string>
/*
Constructor for the library class which creates the hashTables and points all values to a null pointer
*/
Library::Library()
{
    for(int i=0;i<20;i++) //create a hash table of size 20
    {
        hashTable[i] = nullptr;
    }
    for(int i=0;i<20;i++) //create a hash table of size 20
    {
        renterHash[i] = nullptr;
    }
}


/*
a method that creates the hash value for a passed in string
*/
int Library::hashSum(string title)
{
    int sum = 0;
    for (int i = 0; i < title.length(); i++)
        sum = sum + title[i];  //ascii value of ith character in the string
    sum = sum % 10;
    return sum;
}

/*
a method that inserts an item into its hash table
*/
void Library::insertItem(string in_title, int in_year, string in_type, string in_genre, int in_quantity,string in_author)
{
    bool in_checked_out;
    if(in_quantity<=0)
        in_checked_out = false;
    else
        in_checked_out = true;
    item *New = new item(in_title,in_year,in_type,in_genre,in_checked_out,in_quantity, in_author);
    int location = hashSum(in_title);
    item *temp;
    if(hashTable[location] == nullptr){
        hashTable[location] = New;
        New->next = nullptr;
    }
    else{
        temp = hashTable[location];
        item *temp2 = temp;
        while(temp != nullptr){
            if(in_title.compare(temp->title) == 0){
                cout<<"item in Table"<<endl;
                return;
            }
            if(in_title.compare(temp->title) < 0){
                if(temp == temp2){
                    New->next = temp;
                    hashTable[location] = New;
                    return;
                }
                else{
                    temp2->next = New;
                    New->next = temp;
                    return;
                }
            }
            if(temp->next == nullptr || temp->next == NULL){
                if(temp2 == temp){
                    hashTable[location]->next = New;
                    New->next = NULL;
                    break;
                }
                else{
                    temp->next = New;
                    New->next = nullptr;
                    break;
                }
            }
            else{
                temp2 = temp;
                temp = temp->next;
            }
        }
    }
}


/*
A function that finds an item within the hash table and prints out all of the information on that item
*/
void Library::checkStatus(string in_title)
{
    int hashLocation;
    hashLocation = hashSum(in_title);
    if(hashTable[hashLocation] == NULL)
    {
        return;
    }
    item* temp = hashTable[hashLocation];
    while(temp != NULL)
    {
        if(temp->title == in_title)
        {
            cout<<temp->title<<endl<<temp->author<<endl<<"Genre: "<<temp->genre<<endl<<"Year: " << temp->year<<endl<<"Medium: "<<temp->type<<endl<<"Quantity: "<<temp->quantity<<endl<<endl;

            return;
        }
        else
            temp = temp -> next;

    }
    cout<< "not found" <<endl;
}

/*
A method that reduces the quantity of an item by one and adds another person to the checked out list
*/
void Library::checkOutItem(string in_title, string in_name)
{
        int hashLocation;
    hashLocation = hashSum(in_title);
    if(hashTable[hashLocation] == NULL)
    {
        return;
    }
    item* temp = hashTable[hashLocation];
    while(temp != NULL)
    {
        if(temp->title == in_title&&temp->quantity>0)
        {
            temp->quantity--;
            if(temp->quantity<=0)
            {
                temp->checked_out = true;
            }

            newRenter(in_title, in_name);

            return;
        }
        else if(temp->title == in_title&&temp->quantity<=0)
        {
            cout<<"Item is out-of-stock"<<endl;
        }
        else
            temp = temp -> next;

    }
    cout<< "not found" <<endl;
}

/*
method that increases the quantity of an item by one
*/
void Library::returnItem(string in_title)
{
        int hashLocation;
    hashLocation = hashSum(in_title);
    if(hashTable[hashLocation] == NULL)
    {
        return;
    }
    item* temp = hashTable[hashLocation];
    while(temp != NULL)
    {
        if(temp->title == in_title&&temp->quantity>0)
        {
            temp->quantity++;
            if(temp->quantity>0)
            {
                temp->checked_out = false;
            }

            return;
        }
        else if(temp->title == in_title&&temp->quantity<=0)
        {
            cout<<"Item is out-of-stock"<<endl;
            return;
        }
        else
            temp = temp -> next;

    }
    cout<< "Item not found in library" <<endl;
}

/*
delete an item from the hashTable
*/
void Library::deleteItem(string in_title)
{
    int location = hashSum(in_title);
    if(hashTable[location] == NULL){
        cout<<"no"<<endl;
        return;
    }

    if(hashTable[location]->title == in_title)
    {
        hashTable[location] = hashTable[location]->next;
        return;
    }

    item* temp = hashTable[location];
    item* temp2 = temp;
    while(temp ->next != NULL)
    {
        if(temp->next->title == in_title && temp->next->next != NULL)
        {
            temp->next = temp->next->next;
            return;
        }
        else
            temp2 = temp;
        temp = temp->next;
    }
    if(temp->title == in_title)
    {
        temp2->next = NULL;
        return;
    }
    cout<<"Item not in library"<<endl;
}

/*
print everything in the hashTable
*/
void Library::printAllInventory()
{
    int counter = 0;
    item* temp;

    for(int i=0;i<20;i++)
    {
        if(hashTable[i] != nullptr)
        {
            temp = hashTable[i];
            while(temp->next != nullptr)
            {
                cout<<temp->title<<endl<<temp->author<<endl<<"Genre: "<<temp->genre<<endl<<"Year: " << temp->year<<endl<<"Medium: "<<temp->type<<endl<<"Quantity: "<<temp->quantity<<endl<<endl;
                temp = temp->next;
            }
            cout<<temp->title<<endl<<temp->author<<endl<<"Genre: "<<temp->genre<<endl<<"Year: " << temp->year<<endl<<"Medium: "<<temp->type<<endl<<"Quantity: "<<temp->quantity<<endl<<endl;
        }
        else
            counter++;
    }
    if(counter == 20)
    {
        cout<<"empty"<<endl;
    }
}

/*
print the inventory but only for specific filters
*/
void Library::printInventory(int filter, string input) //1 is genre, 2 is media type, 3 is author
{
    int counter = 0;
    item* temp;

    for(int i=0;i<20;i++)
    {
        if(hashTable[i] != nullptr)
        {
            temp = hashTable[i];
            while(temp->next != nullptr)
            {
                if(filter == 1)
                {
                    if(temp->genre == input)
                        cout<<temp->title<<endl<<temp->author<<endl<<"Genre: "<<temp->genre<<endl<<"Year: " << temp->year<<endl<<"Medium: "<<temp->type<<endl<<"Quantity: "<<temp->quantity<<endl<<endl;
                }
                else if(filter == 2)
                {
                    if(temp->type == input)
                        cout<<temp->title<<endl<<temp->author<<endl<<"Genre: "<<temp->genre<<endl<<"Year: " << temp->year<<endl<<"Medium: "<<temp->type<<endl<<"Quantity: "<<temp->quantity<<endl<<endl;
                }
                else if(filter == 3)
                {
                    if(temp->author == input)
                        cout<<temp->title<<endl<<temp->author<<endl<<"Genre: "<<temp->genre<<endl<<"Year: " << temp->year<<endl<<"Medium: "<<temp->type<<endl<<"Quantity: "<<temp->quantity<<endl<<endl;
                }


                temp = temp->next;
            }
            if(filter == 1)
                {
                    if(temp->genre == input)
                        cout<<temp->title<<endl<<temp->author<<endl<<"Genre: "<<temp->genre<<endl<<"Year: " << temp->year<<endl<<"Medium: "<<temp->type<<endl<<"Quantity: "<<temp->quantity<<endl<<endl;
                }
                else if(filter == 2)
                {
                    if(temp->type == input)
                        cout<<temp->title<<endl<<temp->author<<endl<<"Genre: "<<temp->genre<<endl<<"Year: " << temp->year<<endl<<"Medium: "<<temp->type<<endl<<"Quantity: "<<temp->quantity<<endl<<endl;
                }
                else if(filter == 3)
                {
                    if(temp->author == input)
                        cout<<temp->title<<endl<<temp->author<<endl<<"Genre: "<<temp->genre<<endl<<"Year: " << temp->year<<endl<<"Medium: "<<temp->type<<endl<<"Quantity: "<<temp->quantity<<endl<<endl;
                }

        }
        else
            counter++;
    }
    if(counter == 20)
    {
        cout<<"empty"<<endl;
    }
}

/*
print everything in the renters hashTable
*/
void Library::printRenters()
{
    int counter = 0;
    renter* temp;

    for(int i=0;i<20;i++)
    {
        if(renterHash[i] != nullptr)
        {
            temp = renterHash[i];
            while(temp->next != nullptr)
            {
                cout<<"Renter:"<<temp->rentedItem<<endl<<"Item checked out:"<<temp->name<<endl<<endl;
                temp = temp->next;
            }
            cout<<"Renter:"<<temp->rentedItem<<endl<<"Item checked out:"<<temp->name<<endl<<endl;
        }
        else
            counter++;
    }
    if(counter == 20)
    {
        cout<<"empty"<<endl;
    }
}

/*
add a renter to the renter Hashtable
*/
void Library::newRenter(string in_title, string in_name)
{
    renter *New = new renter(in_title,in_name);
    int location = hashSum(in_title);
    renter *temp;
    if(renterHash[location] == nullptr){
        renterHash[location] = New;
        New->next = nullptr;
    }
    else{
        temp = renterHash[location];
        renter *temp2 = temp;
        while(temp != nullptr){
            if(in_title.compare(temp->name) == 0){
                cout<<"item in Table"<<endl;
                return;
            }
            if(in_title.compare(temp->name) < 0){
                if(temp == temp2){
                    New->next = temp;
                    renterHash[location] = New;
                    return;
                }
                else{
                    temp2->next = New;
                    New->next = temp;
                    return;
                }
            }
            if(temp->next == nullptr || temp->next == NULL){
                if(temp2 == temp){
                    renterHash[location]->next = New;
                    New->next = NULL;
                    break;
                }
                else{
                    temp->next = New;
                    New->next = nullptr;
                    break;
                }
            }
            else{
                temp2 = temp;
                temp = temp->next;
            }
        }
    }
}

/*
print all items in the inventory that have a quantity of 0 or less
*/
void Library::outStock()
{
    int counter = 0;
    item* temp;

    for(int i=0;i<20;i++)
    {
        if(hashTable[i] != nullptr)
        {
            temp = hashTable[i];
            while(temp->next != nullptr)
            {
                if(temp->quantity<=0)
                    cout<<temp->title<<endl<<temp->author<<endl<<"Genre: "<<temp->genre<<endl<<"Year: " << temp->year<<endl<<"Medium: "<<temp->type<<endl<<"Quantity: "<<temp->quantity<<endl<<endl;
                temp = temp->next;
            }
            if(temp->quantity<=0)
                cout<<temp->title<<endl<<temp->author<<endl<<"Genre: "<<temp->genre<<endl<<"Year: " << temp->year<<endl<<"Medium: "<<temp->type<<endl<<"Quantity: "<<temp->quantity<<endl<<endl;
        }
        else
            counter++;
    }
    if(counter == 20)
    {
        cout<<"empty"<<endl;
    }
}

/*
print all items that have a quantity of greater than 0
*/
void Library::inStock()
{
       int counter = 0;
    item* temp;

    for(int i=0;i<20;i++)
    {
        if(hashTable[i] != nullptr)
        {
            temp = hashTable[i];
            while(temp->next != nullptr)
            {
                if(temp->quantity>0)
                    cout<<temp->title<<endl<<temp->author<<endl<<"Genre: "<<temp->genre<<endl<<"Year: " << temp->year<<endl<<"Medium: "<<temp->type<<endl<<"Quantity: "<<temp->quantity<<endl<<endl;
                temp = temp->next;
            }
            if(temp->quantity>0)
                cout<<temp->title<<endl<<temp->author<<endl<<"Genre: "<<temp->genre<<endl<<"Year: " << temp->year<<endl<<"Medium: "<<temp->type<<endl<<"Quantity: "<<temp->quantity<<endl<<endl;
        }
        else
            counter++;
    }
    if(counter == 20)
    {
        cout<<"empty"<<endl;
    }
}



/*
Finds and returns item, if not found return NULL
Can use this private function in many of functions to reduce amount of code and make it clearer.
*/
item* Library::findItem(string in_title){
    int hashLocation;
    hashLocation = hashSum(in_title);
    if(hashTable[hashLocation] == NULL)
    {
        return NULL;
    }
    item* temp = hashTable[hashLocation];
    while(temp != NULL)
    {
        if(temp->title == in_title)
        {
            return temp;
        }
        else
            temp = temp -> next;

    }
    return NULL;
}


