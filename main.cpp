#include <iostream>
#include "cl.cpp"
#include <stdio.h>
#include <sys/stat.h>

using namespace std;

#define ERROR_MISSING_INPUT -1
#define ERROR_STAT_INFO -2
#define ERROR_STAT_INVALID_MODE -3

void help()
{
    cout << "Help message for postgresman:" << endl;
    cout << "-i [--input] - file or directory for analyze" << endl;
    cout << "-h [--help] - this help message" << endl;
}

int main(int argc, char* argv[])
{
    CommandLine commandLine(argc, argv);

    if (commandLine.is("-h") || commandLine.is("--help")) {
        help();
        return 0;
    }

    if (!commandLine.is("-i") && !commandLine.is("--input")) {
        help();
        return ERROR_MISSING_INPUT;
    }

    char* inputPath = 0x00;

    if (commandLine.is("-i")) {
        inputPath = commandLine.get("-i");
    } else if (commandLine.is("--input")) {
        inputPath = commandLine.get("--input");
    }

    if (inputPath == NULL) {
        cout << "Missing parameter value for -i [--input]" << endl;
        return ERROR_MISSING_INPUT;
    }

    struct stat s;
    int checkStat = stat(inputPath, &s);

    if (checkStat != 0) {
        cout << "Undefined errors: " << checkStat << endl;
        return ERROR_STAT_INFO;
    }

    if (s.st_mode & S_IFDIR) {
        cout << "is a directory" << endl;
    } else if(s.st_mode & S_IFREG) {
        cout << "it is a file" << endl;
    } else {
        return ERROR_STAT_INVALID_MODE;
    }

    FILE * pFile;
    pFile = fopen(inputPath, "r");

    if (pFile != NULL) {
        cout << "i open it" << endl;
        fclose(pFile);
    }

    return 0;
}
