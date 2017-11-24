class ParenthesisClose : public Token
{
public:
    ParenthesisClose(int line, int column, IOReader* reader) : Token(line, column)
    {
        this->reader = reader;
    }

protected:
    IOReader* reader;
};
