class LexerSQL : public Lexer
{
public:
    LexerSQL(IOBuffer *buffer) : Lexer(buffer)
    {
        const char* keywords[] = {
                "create",
                "or",
                "replace"
        };

        for (int i = 0; i < 3; ++i) {
            this->keywords.addValue((char*) keywords[i]);
        }
    }
};
