class Lexer
{
public:
    Lexer(IOBuffer* buffer)
    {
        this->buffer = buffer;
    }

    void parse()
    {
    }
protected:
    IOBuffer* buffer;
    KeywordList keywords;
};
