#include "library.h"
#include <iostream>
#include <string>

Library::Library()
{
    for(int i=0;i<20;i++) //create a hash table of size 20
    {
        hashTable[i] = nullptr;
    }
}

int Library::hashSum(string title)
{
    int sum = 0;
    for (int i = 0; i < title.length(); i++)
        sum = sum + title[i];  //ascii value of ith character in the string
    sum = sum % 10;
    return sum;
}

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

void Library::checkOutItem(string in_title)
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
