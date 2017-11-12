class LexerSQL : public Lexer
{
public:
    LexerSQL(IOBuffer *buffer) : Lexer(buffer)
    {
        this->keywords.addValue((char*) "create");
    }
};
