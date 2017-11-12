#include "io_file.cpp"
#include "lexer/lexer.cpp"
#include "lexer/lexer_sql.cpp"

class Validator
{
public:
    Validator(char *fileName)
    {
        this->fileName = fileName;
        IOFile fileBuffer(fileName);
        LexerSQL lexer(&fileBuffer);
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
