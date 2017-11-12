#include "io_buffer.cpp"

class IOFile : public IOBuffer
{
public:
    IOFile(char* fileName) : IOBuffer()
    {
        this->fileName = fileName;
        this->hFile = NULL;
    }

    ~IOFile()
    {
        if (this->hFile != NULL) {
            fclose(this->hFile);
        }
    }

    int read(int length, char* buffer)
    {
        hFile = this->getHandler();

        if (hFile == NULL) {
            return -1;
        }

        return 0;
    }

    int write(char* buffer, int length)
    {
        return 0;
    }
private:
    char* fileName;

    FILE* hFile;

    FILE* getHandler()
    {
        if (this->hFile != NULL) {
            return this->hFile;
        }

        this->hFile = fopen(this->fileName, "r");
        return this->hFile;
    }
};
