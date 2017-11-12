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

    /**
     * Чтение из файла
     * @param buffer
     * @param length
     * @return
     */
    int read(char* buffer, int length)
    {
        hFile = this->getHandler();

        if (hFile == NULL) {
            return -1;
        }

        size_t size = fread(buffer, sizeof(char), length, hFile);
        return (int) size;
    }

    /**
     * Запись в файл
     * @param buffer
     * @param length
     * @return
     */
    int write(char* buffer, int length)
    {
        hFile = this->getHandler();

        if (hFile == NULL) {
            return -1;
        }

        size_t size = fwrite(buffer, sizeof(char), length, hFile);
        return (int) size;
    }
private:
    char* fileName;

    FILE* hFile;

    /**
     * @return
     */
    FILE* getHandler()
    {
        if (this->hFile != NULL) {
            return this->hFile;
        }

        this->hFile = fopen(this->fileName, "r");
        return this->hFile;
    }
};
