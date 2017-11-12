class Lexer
{
public:
    Lexer(IOBuffer* buffer)
    {
        this->buffer = buffer;
    }

private:
    IOBuffer* buffer;
};
