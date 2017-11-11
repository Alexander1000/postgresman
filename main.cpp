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

    cout << "Hello world" << endl;
    return 0;
}
