#include "buffer/io_buffer.h"
#include "lexer/lexer.h"
#include "syntaxer/syntaxer.h"

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
        Syntaxer *syntaxer = new Syntaxer(this->lexer->getTokenStream());
        syntaxer->analyze();
        return true;
    }

private:
    Lexer* lexer;
    char* fileName;
};
