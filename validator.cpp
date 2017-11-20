#include "buffer/io_buffer.h"
#include "lexer/lexer.h"

class Validator
{
public:
    Validator(char *fileName)
    {
        this->fileName = fileName;
        IOFileReader* fileBuffer = new IOFileReader(fileName);
        this->lexer = new LexerSQL(fileBuffer);
    }

    ~Validator()
    {
        delete this->lexer;
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
