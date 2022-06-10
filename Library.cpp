#include "Library.h"

Library::Library(){}

bool Library::load(ifstream& str)
{
    if(list.size()!=0)
        return false;

    int book_amount;
    str>>book_amount;


    if(book_amount<1 && book_amount>max_books)
        return false;

    list.resize(book_amount);
    for(int i=0; i<book_amount; i++)
    {
        bool res = list[i].load(str);
        if(res==false) return false;
    }
    return true;
}

void Library::add(const Book & book)
{
    list.push_back(book);
}

bool Library::findBook(Book& result,string& str,SearchMode mode, bool ignore)
{
    for(int i=0; i<list.size(); i++)
        if(list[i].compBook(str,mode,ignore))
        {
            result = list[i];
            return true;
        }
    return false;
}


void Library::simplePrint()
{
    cout<<"Book amount: "<<list.size()<< endl<<endl;
    for(int i=0; i< list.size(); i++)
    {
        list[i].print();
        cout<<endl;
    }
}

void Library::printSorted(SortMode mode,bool des)
{
    int book_amount = list.size();
    cout<<"Book amount: "<<book_amount<< endl<<endl;

    if(book_amount ==0)
        return;

    Book** arr = new Book*[book_amount];
    for(int i=0; i<book_amount; i++)
        arr[i] = & (list[i]);
    // bubble sort ascending

    for(int i=0; i<book_amount-1; i++)
        for(int j=book_amount-2; j>=i; j--)
            if( (*arr[j+1]).lessThan( *arr[j] , mode) )
                swap( arr[j+1], arr[j]);

    if(des)
        for(int i=book_amount-1; i>=0; i--)
        {
            (*arr[i]).shortPrint();
            cout<<endl;
        }
    else
        for(int i=0; i<book_amount; i++)
        {
            (*arr[i]).shortPrint();
            cout<<endl;
        }
    
    delete[] arr;
}

void Library::delBook(string& heading)
{
    int book_amount = list.size();

    int pos=-1;

    for(int i=0; i<book_amount; i++)
        if(list[i].compBook(heading,title_m,false))
        {
            pos = i;
            break;
        }
    if(pos==-1)
        return;

    list.erase( list.begin() + pos);
}

void Library::save(ofstream & str)
{
//    if(book_amount==0)
//        return;
    str<< list.size() <<endl;
    for(int i=0; i< list.size() ; i++)
        list[i].save(str);
}
