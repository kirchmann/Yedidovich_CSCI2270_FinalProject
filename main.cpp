#include <iostream>
#include <string>
#include "library.h"

using namespace std;

int main()
{
    Library L;
    int choice = 0;
    string searchTitle = "";

    string in_title; int in_year; string in_type; string in_genre; int in_quantity; string in_author;

    while(choice!=7)
    {
        cout<<"Welcome to your library organizer! Please pick an option below:"<<endl<<"1. Check the status of an item"<<endl<<"2. Checkout or return an item"<<endl<<"3. Add an item to the library"<<endl<<"4. Delete an item from the library"<<endl<<"5. Display all items of a type"<<endl<<"6. Display all items"<<endl<<"7. Quit"<<endl;
        cin>>choice;
        if(choice == 1) //Check item status
        {
            cout<<"What is the title?"<<endl;
            cin.ignore(2000,'\n');
            getline(cin,searchTitle);
            cout<<endl;
            L.checkStatus(searchTitle);
        }
        else if(choice == 2) //Checkout/return
        {
            choice = 0;
            while(choice!=1&&choice!=2)
            {
                cout<<"1. Check out"<<endl<<"2. Return"<<endl;
                cin>>choice;
            }
            cout<<"What's the title?"<<endl;
            cin.ignore(1000,'\n');
            getline(cin,in_title);
            if(choice == 1)
                L.checkOutItem(in_title);
            else
                L.returnItem(in_title);
        }
        else if(choice == 3) //Add a movie
        {
            cout<<"What is its title?"<<endl;
            cin.ignore(1000,'\n');
            getline(cin,in_title);
            cout<<"What is the quantity?"<<endl;
            cin>>in_quantity;
            cout<<"What is the author?"<<endl;
            cin.ignore(2000,'\n');
            getline(cin,in_author);
            cout<<"What year was it made?"<<endl;
            cin>>in_year;
            cout<<"What genre is this?"<<endl;
            cin.ignore(1000,'\n');
            getline(cin,in_genre);
            cout<<"What media is this item?"<<endl;
            cin.ignore(2000,'\n');
            getline(cin,in_type);
            L.insertItem( in_title,  in_year,  in_type,  in_genre,  in_quantity, in_author);
        }
        else if(choice == 4)
        {
            cout<<"What's the title?"<<endl;
            cin.ignore(1000,'\n');
            getline(cin,in_title);
            L.deleteItem(in_title);
        }
        else if(choice == 5)
        {
            choice = 0;
            cout<<endl;
            while(choice!=1&&choice!=2&&choice!=3)
            {
                cout<<"Filter what?"<<endl<<"1. Genre"<<endl<<"2. Media type"<<endl<<"3. Author"<<endl;
                cin>>choice;
            }
            cout<<"Find what?"<<endl;
            cin.ignore(1000,'\n');
            getline(cin,in_title);
            L.printInventory(choice, in_title);
        }
        else if(choice == 6)
        {
            cout<<endl;
            L.printAllInventory();
        }
        else
        {
            cout<<choice<<" is not a valid option"<<endl;
        }
    }

    cout<<"Goodbye!"<<endl;

    return 0;
}
