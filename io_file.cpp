#include "io_buffer.cpp"

class IOFile : public IOBuffer
{
public:
    IOFile(char* fileName) : IOBuffer()
    {
        this->fileName = fileName;
    }
private:
    char* fileName;
};