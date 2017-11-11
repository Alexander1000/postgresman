#include <iostream>
#include "cl.cpp"

using namespace std;

void help()
{
    cout << "Help message for postgresman:" << endl;
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

    if (inputPath == 0x00) {
        cout << "Missing parameter value for -i [--input]" << endl;
        return 0;
    }

    cout << "Hello world: " << inputPath << endl;
    return 0;
}
