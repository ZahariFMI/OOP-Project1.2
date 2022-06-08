#include "Library.h"

const char * const lib_dir = "LibraryDatabase.txt";
const char * const pass_dir = "PasswordDatabase.txt";
const char * const pass = "admin";

class ProgramExecuter
{
private:
    Library lib;
    bool admin;
    bool checkCommand(string& command,char minval,char maxval);
    void saveLib();
    void printSorted();
    void findBook();
    void wait();
    void printContent();
    void login();
    void addBook();
    void removeBook();
    int mainPage();
    void loadLib();

public:
    ProgramExecuter();
    ProgramExecuter(const ProgramExecuter&) = delete;
    ProgramExecuter& operator=(const ProgramExecuter&) = delete;
    void run();
};
