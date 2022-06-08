#include "Book.h"
#include <vector>

const int max_books=1000000;

class Library
{
    vector<Book> list;

public:
    Library();
    Library(const Library&) = delete;
    Library& operator=(const Library&) = delete;

    bool load(ifstream&);
    void add(const Book &);
    bool findBook(Book&,string&,SearchMode,bool ignore);
    void simplePrint();
    void printSorted(SortMode mode,bool des);
    void delBook(string& heading);

    void save(ofstream&);
};
