#include<stdio.h>
#include<iostream>
#include<fstream>
#include<string.h>
#include<conio.h>
#include<stdlib.h>

using namespace std;

class Book
{
private:
    int bookID;
    char title[20];
    float price;
public:
    Book()
    {
        bookID=0;
        strcpy(title,"No title");
        price=0;
    }

    void getBookData()
    {
        cout<<"\n  Enter bookID of the book: ";
        cin>>bookID;
        cout<<"  Enter title of the book: ";
        cin.ignore();
        cin.getline(title,19);
        cout<<"  Enter price of the book: ";
        cin>>price;
    }

    void showBookData()
    {
        cout<<"\n\t"<<bookID<<"     "<<title<<"     "<<price;
    }

    int storeBook()
    {
    if(bookID==0&&price==0)
    {
      cout<<"\n---Book data not initialised---"<<endl;
    }
    else
    {
        ofstream fout;
        fout.open("file.dat",ios::app|ios::binary);
        fout.write((char*)this,sizeof(*this));
        cout<<"\n  Record inserted successfully!";
        fout.close();
        return(1);
    }
    }

    void viewAllBooks()
    {
    ifstream fin;
    fin.open("file.dat",ios::in|ios::binary);
    if(!fin)
      cout<<"\nFile not found";
    else
    {
        fin.read((char*)this,sizeof(*this));
        while(!fin.eof())
        {
            showBookData();
            fin.read((char*)this,sizeof(*this));
        }
        fin.close();
    }
    }

    void searchBook(char *t)
    {
    int count=0;
    ifstream fin;
    fin.open("file.dat",ios::in|ios::binary);
    if(!fin)
        cout<<"\n  File not found!";
    else
    {
        fin.read((char*)this,sizeof(*this));
        while(!fin.eof())
        {
            if(!strcmp(t,title))
            {
                showBookData();
                count++;
            }
            fin.read((char*)this,sizeof(*this));
        }
        if(count==0)
            cout<<"\n  Record not found!";
        fin.close();
    }
    }

    void deleteBook(char *t)
    {
        ifstream fin;
        ofstream fout;
        fin.open("file.dat",ios::in|ios::binary);
        if(!fin)
            cout<<"\n  File not found!";
        else
        {
            fout.open("temp.dat",ios::out|ios::binary);
            fin.read((char*)this,sizeof(*this));
            while(!fin.eof())
            {
                if(strcmp(title,t))
                {
                    fout.write((char*)this,sizeof(*this));
                    cout<<"\n  Record deleted successfully!";
                }
             fin.read((char*)this,sizeof(*this));
            }
            cout<<"\n  Record not found!";
            fin.close();
            fout.close();
            remove("file.dat");
            rename("temp.dat","file.dat");
        }
    }

    void updateBook(char *t)
    {
        fstream file;
        file.open("file.dat",ios::in|ios::out|ios::ate|ios::binary);
        file.seekg(0);
        file.read((char*)this,sizeof(*this));
        while(!file.eof())
        {
            if(strcmp(t,title))
            {
             getBookData();
             file.seekp(file.tellp()-sizeof(*this));
             file.write((char*)this,sizeof(*this));
             cout<<"\n  Record updated successfully!";
            }
         file.read((char*)this,sizeof(*this));
        }
        cout<<"\n  Record not found!";
        file.close();
    }
};

int menu()
    {
    int choice;
    cout<<"\n\ ---Book Management---\n";
    cout<<"\n 1. Insert book record";
    cout<<"\n 2. View all books ";
    cout<<"\n 3. Search book";
    cout<<"\n 4. Delete book";
    cout<<"\n 5. Update book";
    cout<<"\n 6. EXIT";
    cout<<"\n\  ______________________\n";
    cout<<"\n Enter your choice: ";
    cin>>choice;
    return(choice);
    }

int main()
{
    Book b1;
    char  title[20];
    while(1)
    {
        system("cls");
        switch(menu())
        {
            case 1:
                b1.getBookData();
                b1.storeBook();
                getch();
                break;
            case 2:
                b1.viewAllBooks();
                getch();
                break;
            case 3:
                cout<<"\n  Enter the title of the book to search: ";
                cin.getline(title,19);
                b1.searchBook(title);
                getch();
                break;
            case 4:
                cout<<"\n  Enter the title of the book to delete: ";
                cin.ignore();
                cin.getline(title,19);
                b1.deleteBook(title);
                getch();
                break;
            case 5:
                cout<<"\n  Enter the title of the book to update: ";
                cin.ignore();
                cin.getline(title,19);
                b1.updateBook(title);
                getch();
                break;
            case 6:
                cout<<"\n---Thank you for using this application---";
                cout<<"\n\n\t---Press any key to EXIT---";
                getch();
                exit(0);
            default:
                cout<<"\n---Invalid choice---";
        }
    }
}

