#include <string>
#include <fstream>
#include <iostream>
#include <cctype>
using namespace std;

const int max_author = 100;
const int max_heading = 100;
const int max_directory = 240;
const int max_description = 10000;
const int max_isbn = 25;

void write_tofile(ofstream&f,string&);

void readString(string&,ifstream&);

enum SearchMode{title_m,author_m,isbn_m,description_m};

enum SortMode{title_s,author_s,rating_s};

enum PrintMode{sent_mode,row_mode};

bool str_eq(string&,string&,bool ignore = false);

class Book
{
    string author,heading,directory,description,isbn;
    int rating;
    bool loaded;

public:

    bool load(ifstream& str);

    void setAuthor(string&);
    void setHeading(string&);
    void setDirectory(string&);
    void setDescription(string&);
    void setIsbn(string&);
    void setRating(int);
    void setLoaded(bool loaded);


    bool compBook(string&,SearchMode,bool ignore);
    bool lessThan(const Book&,SortMode);
    void print();
    void shortPrint();
    bool getFile(ifstream&);
    bool delFile();

    void save(ofstream&);
};
