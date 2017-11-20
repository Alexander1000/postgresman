class LexerSQL : public Lexer
{
public:
    LexerSQL(IOReader* reader) : Lexer(reader)
    {
        const char* keywords[] = {
                "create",
                "or",
                "replace",
                "insert",
                "into",
                "values",
                "table",
                "alter",
                "function",
                "declare",
                "begin",
                "end",
                "as",
                "language",
                "in",
                "out"
        };

        int count = sizeof(keywords) / sizeof(char*);

        for (int i = 0; i < count; ++i) {
            this->keywords.addValue((char*) keywords[i]);
        }
    }
};
