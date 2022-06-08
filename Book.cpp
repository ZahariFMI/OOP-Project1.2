#include "Book.h"

void write_tofile(ofstream&file,string& str)
{
    file<<str.size()<<endl;
    file<<str<<endl;
}

void readString(string& str,ifstream & file)
{
    int size;
    file>>size;
    file.ignore();
    str.resize(size);
    getline(file,str);
}

bool str_eq(string& str1, string& str2, bool ignore)
{
    if(str1.size() != str2.size())
        return false;
    int n = str1.size();
    for(int i=0; i<n; i++)
    {
        if(ignore)
        {
            if(tolower(str1[i]) != tolower(str2[i]))
                return false;
        }
        else
            if(str1[i] != str2[i])
                return false;
    }
    return true;
}

bool Book::load(ifstream &file)
{
    if(loaded==true)
        return false;

    readString(author,file);
    readString(heading,file);
    readString(directory,file);
    readString(isbn,file);
    file>>rating;

    loaded = true;
    return true;
}

void Book::setAuthor(string& str)
{
    author = str;
}

void Book::setHeading(string& str)
{
    heading = str;
}

void Book::setDirectory(string& str)
{
    directory = str;
}

void Book::setDescription(string& str)
{
    description = str;
}

void Book::setIsbn(string& str)
{
    isbn = str;
}

void Book::setRating(int rating)
{
    this->rating = rating;
}

void Book::setLoaded(bool loaded)
{
    this->loaded = loaded;
}

bool Book::compBook(string& str,SearchMode mode,bool ignore)
{
    if(mode == title_m)
        return str_eq(str,heading,ignore);
    if(mode == author_m)
        return str_eq(str,author,ignore);
    if(mode == isbn_m)
        return str_eq(str,isbn,ignore);
    if(mode == description_m)
    {
        int n = description.size();
        int m = str.size();
        string buff;
        //char * buff = new char[m+1];
        for(int i=0; i<=n-m; i++)
        {
            buff = description.substr(i,m);
            //strncpy(buff,description+i,m);
            //buff[m]='\0';
            if( str_eq(str,buff,ignore) )
                return true;
        }
    }
    return false;
}

bool Book::lessThan(const Book& book,SortMode mode)
{
    if(mode == title_s)
        return heading < book.heading;
    if(mode == author_s)
        return author < book.author;
    if(mode == rating_s)
        return rating < book.rating;
    return 0;
}

void Book::print()
{
    cout<<"Title: "<<heading<<endl;
    cout<<"Author: "<<author<<endl;
    cout<<"Description: "<<description<<endl;
    cout<<"Directory: "<<directory<<endl;
    cout<<"ISBN: "<<isbn<<endl;
    cout<<"rating: "<<rating<<endl;
}

void Book::shortPrint()
{
    cout<<"Title: "<<heading<<endl;
    cout<<"Author: "<<author<<endl;
    cout<<"ISBN: "<<isbn<<endl;
}

bool Book::getFile(ifstream &file)
{
    file.open(directory);
    if(!file)
        return false;
    return true;
}

bool Book::delFile()
{
    if( remove(directory.c_str() ) == 0 )
        return true;
    return false;
}

void Book::save(ofstream& file)
{
    write_tofile(file,author);
    write_tofile(file,heading);
    write_tofile(file,directory);
    write_tofile(file,description);
    write_tofile(file,isbn);
    file<<rating;
}
