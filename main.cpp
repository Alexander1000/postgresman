#include <iostream>
#include "cl.cpp"
#include <stdio.h>

using namespace std;

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
        return 0;
    }

    char* inputPath = 0x00;

    if (commandLine.is("-i")) {
        inputPath = commandLine.get("-i");
    } else if (commandLine.is("--input")) {
        inputPath = commandLine.get("--input");
    }

    if (inputPath == NULL) {
        cout << "Missing parameter value for -i [--input]" << endl;
        return 0;
    }

    FILE * pFile;
    pFile = fopen(inputPath, "r");

    if (pFile != NULL) {
        cout << "i open it" << endl;
        fclose (pFile);
    }

    return 0;
}
