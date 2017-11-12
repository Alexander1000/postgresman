#include "io_file.cpp"
#include "lexer.cpp"

class Validator
{
public:
    Validator(char *fileName)
    {
        this->fileName = fileName;
        IOFile fileBuffer(fileName);
        Lexer lexer(&fileBuffer);
        this->lexer = &lexer;
    }

    bool validate()
    {
        this->lexer->parse();
        return true;
    }

private:
    Lexer* lexer;
    char* fileName;
};
