#include "ProgramExecuter.h"

bool ProgramExecuter::checkCommand(string& command,char minval,char maxval)
{
    if( command.size() != 1 || command[0] < minval || command[0] > maxval)
    {
        cout<<"Wrong command\n\n";
        return false;
    }
    return true;
}

void ProgramExecuter::saveLib()
{
    ofstream file(lib_dir);
    if(!file)
    {
        cout<<"Error Saving Library"<< endl;
        return;
    }
    lib.save(file);
    file.close();
}

void ProgramExecuter::printSorted()
{
    string buff;
    SortMode mode;
    bool des;

    cout<<"Choose sort criterion:\n";
    cout<<"(1) Sort by title\n";
    cout<<"(2) Sort by author\n";
    cout<<"(3) Sort by rating\n";

    getline(cin,buff);
    if(!checkCommand(buff,'1','3'))
        return;
//   for debug
//    if(buff[0] == '4')
//    {
//        lib.simplePrint();
//        return;
//    }

    mode = (SortMode)(buff[0] - '1');

    cout<<"Choose sort criterion:\n";
    cout<<"(1) Sort ascending\n";
    cout<<"(2) Sort descending\n";

    getline(cin,buff);
    if(!checkCommand(buff,'1','2'))
        return;

    des = buff[0] - '1';

    lib.printSorted(mode,des);
}

void ProgramExecuter::findBook()
{
    string buff;
    cout<<"Write one of the following: title, author, ISBN, part of description."<< endl;
    getline(cin,buff);

    Book res;
    if(!lib.findBook(res,buff,title_m,true))
        if(!lib.findBook(res,buff,author_m,true))
            if(!lib.findBook(res,buff,isbn_m,true))
                if(!lib.findBook(res,buff,description_m,true))
                {
                    cout<<"Book not found.\n\n";
                    return;
                }
    cout<<"Book found!\n\n";
    res.print();
    cout<<endl;
}

void ProgramExecuter::wait()
{
    string buff;
    getline(cin,buff);
}

void ProgramExecuter::printContent()
{
    string buff;
    bool sent=false;
    Book res;
    ifstream file;

    cout<<"Write book title\n";
    getline(cin,buff);

    if(!lib.findBook(res,buff,title_m,false))
    {
        cout<<"Book not found.\n\n";
        return;
    }

    if(!res.getFile(file))
    {
        cout<<"Error opening file.\n\n";
        return;
    }

    cout<<"Choose print mode:\n";
    cout<<"(1) Print rows\n";
    cout<<"(2) Print sentences\n";

    getline(cin,buff);
    if(!checkCommand(buff,'1','2'))
        return;

    sent = buff[0] - '1';

    cout<<"Press enter for next\n";
    char buff2 = file.get();
    while(!file.eof())
    {
        if(!sent)
        {
            if(buff2=='\n')
                wait();
            else
                cout<<buff2;
        }
        else
        {
            if(buff2 !='\n')
                cout<<buff2;
            else
                cout<<' ';
            if(buff2 == '.' || buff2 == '?' || buff2 == '!')
                wait();
        }
        buff2 = file.get();
    }
    cout<<endl<<endl;
    file.close();
}


void ProgramExecuter::login()
{
    string buff;

    cout<<"\nWrite Password:\n";

    getline(cin,buff);

    if(buff == pass)
    {
        admin = true;
        cout<<"Successful login!\n\n";
    }
    else
    {
        cout<<"Wrong Password\n\n";
    }
}

void ProgramExecuter::addBook()
{
    Book book;
    string buff;

    cout<<"Enter book title: "<< endl;
    getline(cin,buff);

    book.setHeading(buff);

    cout<<"Enter book author: "<< endl;
    getline(cin,buff);

    book.setAuthor(buff);

    cout<<"Enter book description: "<< endl;
    getline(cin,buff);

    book.setDescription(buff);

    cout<<"Enter book text directory: "<< endl;
    getline(cin,buff);

    book.setDirectory(buff);

    cout<<"Enter book isbn: "<< endl;
    getline(cin,buff);

    book.setIsbn(buff);

    cout<<"Enter book rating: "<< endl;
    int temp;
    cin>>temp;
//    if(!cin)
//    {
//        clearCin();
//        cout<<"Wrong Input"<< endl;
//        return;
//    }
    cin.ignore();
    book.setRating(temp);

    book.setLoaded(true);
    lib.add(book);
    cout<<"Book successfully added\n\n";
}

void ProgramExecuter::removeBook()
{
    string buff,buff2;

    cout<<"Write book title\n";
    getline(cin,buff);
    Book book;
    if(!lib.findBook(book,buff,title_m,false))
    {
        cout<<"Book not found"<< endl;
        return;
    }

    cout<<"Do you want to delete book content?\n";
    cout<<"(1) No.\n";
    cout<<"(2) Yes.\n";
    getline(cin,buff2);
    if(!checkCommand(buff2,'1','2'))
        return;

    if(buff2[0] == '2')
        if( !book.delFile() )
            cout<<"Error deleting book content.\n";
        else
            cout<<"File deleted successfully.\n";

    lib.delBook(buff);
    cout<<"Book deleted successfully\n\n";
}


int ProgramExecuter::mainPage()
{
    if(admin)
        cout<<"----- Authorized access -----"<< endl;
    else
        cout<<"----- Unauthorized access -----"<< endl;
    cout<<"Enter number to choose command: "<< endl;
    cout<<"(0) Exit and Save"<< endl;
    cout<<"(1) Print sorted list"<< endl;
    cout<<"(2) Find book"<< endl;
    cout<<"(3) Print book content"<< endl;
    if(admin)
    {
        cout<<"(4) Add book"<< endl;
        cout<<"(5) Remove book"<< endl;
    }
    else
    {
        cout<<"(4) Login"<< endl;
    }

    string buff;
    getline(cin,buff);
    // command correctness
    if(admin)
    {
        if(!checkCommand(buff,'0','5'))
            return -1;
    }
    else
        if(!checkCommand(buff,'0','4'))
            return -1;
    //       command logic
    char number = buff[0];

    if(number == '0')
    {
        saveLib();
        return 0;
    }
    if(number == '1')
    {
        printSorted();
        return 1;
    }
    if(number == '2')
    {
        findBook();
        return 2;
    }
    if(number == '3')
    {
        printContent();
        return 3;
    }
    if(admin)
    {
        if(number=='4')
        {
            addBook();
            return 4;
        }
        if(number=='5')
        {
            removeBook();
            return 5;
        }
    }
    else
    {
        if(number=='4')
        {
            login();
            return 4;
        }
    }
    return -1;
}



void ProgramExecuter::loadLib()
{
    ifstream file(lib_dir);
    if(!file)
    {
        ofstream ofile(lib_dir);
        int temp=0;
        ofile<<temp<<endl;
        ofile.close();

        file.open(lib_dir, ios::binary);
//        cout<<"No libdatabase"<< endl;
//        return;
    }

    bool res = lib.load(file);
    if(res==false)
        cout<<"Error loading Library Database"<< endl;
    file.close();
}

ProgramExecuter::ProgramExecuter() : admin(false)
{
}

void ProgramExecuter::run()
{
    bool admin = false;

    loadLib();

    int result;
    while(1)
    {
        result = mainPage();
        if(result == 0)
            break;
    }
}
