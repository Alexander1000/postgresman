class Lexer
{
public:
    Lexer(IOBuffer* buffer)
    {
        this->buffer = buffer;
    }

    void parse()
    {}

private:
    IOBuffer* buffer;
};
