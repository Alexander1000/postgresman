class Lexer
{
public:
    Lexer(IOReader* reader)
    {
        this->eof = false;
        this->reader = reader;

        this->currentBuffer = new char[LEXER_BUFFER_SIZE];
        this->forwardBuffer = new char[LEXER_BUFFER_SIZE];

        memset(this->currentBuffer, 0, LEXER_BUFFER_SIZE * sizeof(char));
        memset(this->forwardBuffer, 0, LEXER_BUFFER_SIZE * sizeof(char));

        this->currentPosition = 0;

        this->mode = LEXER_MODE_DEFAULT;
        this->currentLexeme = NULL;

        this->lexemeWriter = NULL;

        this->tokenStream = new TokenStream;

        this->currentLine = 0;
        this->currentColumn = 0;
    }

    ~Lexer()
    {
        delete this->currentBuffer;
        delete this->forwardBuffer;
    }

    void parse()
    {
        int readSize = this->reader->read(this->currentBuffer, LEXER_BUFFER_SIZE);
        bool eof = false;
        this->posCurrent = 0;
        this->posForward = 0;

        if (readSize < LEXER_BUFFER_SIZE) {
            eof = true;
            this->posCurrent = readSize;
        } else {
            this->posCurrent = readSize;
            this->posForward = this->reader->read(this->forwardBuffer, LEXER_BUFFER_SIZE);
            if (this->posForward < LEXER_BUFFER_SIZE) {
                eof = true;
            }
        }

        while (!this->eof) {
            this->eof = eof;

            // если текущий указатель перешел в forward-буфер
            if (this->currentPosition >= LEXER_BUFFER_SIZE && this->currentPosition < 2 * LEXER_BUFFER_SIZE) {
                // очищаем буфер со старыми данными
                memset(this->currentBuffer, 0, LEXER_BUFFER_SIZE * sizeof(char));
                // копируем данные из forward buffer в current
                memcpy(this->currentBuffer, this->forwardBuffer, LEXER_BUFFER_SIZE);
                // копируме конечную позицию в буфере из forward в current
                this->posCurrent = this->posForward;
                // смещаем текущую позицию
                this->currentPosition -= LEXER_BUFFER_SIZE;
                // подготавливаем память для заливки новых данных
                memset(this->forwardBuffer, 0, LEXER_BUFFER_SIZE * sizeof(char));

                if (!eof) {
                    // если не был достигнут конец файла, читаем новый forward-буфер
                    this->posForward = this->reader->read(this->forwardBuffer, LEXER_BUFFER_SIZE);

                    if (this->posForward < LEXER_BUFFER_SIZE) {
                        eof = true;
                    }
                } else {
                    // если конец файла, то освобождаем память от forward-буфера
                    this->posForward = 0;
                }
            }

            if (this->currentPosition >= 0 && this->currentPosition < LEXER_BUFFER_SIZE) {
                // текущий указатель находится внутри первого буфера
                while (this->currentPosition < this->posCurrent) {
                    // продвигаемся по буферу вперед
                    char symbol = this->currentBuffer[this->currentPosition];
                    this->proceedSymbol(symbol);

                    // координаты токена
                    if (symbol == 0x0A) {
                        this->currentColumn = 0;
                        ++this->currentLine;
                    } else {
                        ++this->currentColumn;
                    }

                    ++this->currentPosition;
                }
            }

            if (this->currentPosition < 0 || this->currentPosition >= 2 * LEXER_BUFFER_SIZE) {
                // невалидная позиция - выход из цыкла
                this->eof = true;
            }
        }
    }

    TokenStream* getTokenStream()
    {
        return this->tokenStream;
    }
protected:
    IOReader* reader;
    KeywordList keywords;

    char* currentBuffer;
    char* forwardBuffer;

    bool eof;

    int currentPosition;

    int posCurrent;
    int posForward;

    int mode;

    char* currentLexeme;

    IOMemoryBuffer* lexemeWriter;

    char *quote;

    TokenStream* tokenStream;

    int currentLine;
    int currentColumn;

    void proceedSymbol(char symbol)
    {
        switch (this->mode) {
            case LEXER_MODE_DEFAULT: {
                // однострочный комментарий
                if (symbol == '-') {
                    char forwardSymbol = this->getForwardCharacter(1);

                    if (forwardSymbol == '-') {
                        ++this->currentPosition;
                        this->mode = LEXER_MODE_ONELINE_COMMENT;
                        return;
                    }
                }

                // многостроковый комментарий
                if (symbol == '/') {
                    char forwardSymbol = this->getForwardCharacter(1);

                    if (forwardSymbol == '*') {
                        ++this->currentPosition;
                        this->mode = LEXER_MODE_MULTILINE_COMMENT;
                        return;
                    }
                }

                if (symbol == '\'') {
                    this->appendCurrentLexeme(symbol);
                    this->mode = LEXER_MODE_LEXEME_QUOTES;
                    return;
                }

                // пробельные символы
                if (symbol == 0x20 || symbol == 0x0A || symbol == 0x0D) {
                    // пробел + перенос строк
                    return;
                }

                if (this->isLetter(symbol) || symbol == '_') {
                    this->appendCurrentLexeme(symbol);
                    this->mode = LEXER_MODE_LEXEME_WORD;
                    return;
                }

                if (this->isDigit(symbol)) {
                    this->appendCurrentLexeme(symbol);
                    this->mode = LEXER_MODE_NUMERIC;
                    return;
                }

                if (symbol == '(') {
                    Token *token = new ParenthesisOpen(this->currentLine, this->currentColumn);
                    this->tokenStream->add(token);
                    return;
                }

                if (symbol == ')') {
                    Token *token = new ParenthesisClose(this->currentLine, this->currentColumn);
                    this->tokenStream->add(token);
                    return;
                }

                if (symbol == '[') {
                    Token *token = new SquareBracketOpen(this->currentLine, this->currentColumn);
                    this->tokenStream->add(token);
                    return;
                }

                if (symbol == ']') {
                    Token *token = new SquareBracketClose(this->currentLine, this->currentColumn);
                    this->tokenStream->add(token);
                    return;
                }

                if (symbol == ',') {
                    Token *token = new Comma(this->currentLine, this->currentColumn);
                    this->tokenStream->add(token);
                    return;
                }

                if (symbol == ';') {
                    Token *token = new Semicolon(this->currentLine, this->currentColumn);
                    this->tokenStream->add(token);
                    return;
                }

                if (symbol == '.') {
                    Token *token = new Dot(this->currentLine, this->currentColumn);
                    this->tokenStream->add(token);
                    return;
                }

                if (symbol == '$') {
                    this->mode = LEXER_MODE_CUSTOM_QUOTE;
                    this->appendCurrentLexeme(symbol);
                    return;
                }

                break;
            }

            case LEXER_MODE_ONELINE_COMMENT: {
                if (symbol == 0x0A) {
                    this->mode = LEXER_MODE_DEFAULT;
                }

                return;
            }

            case LEXER_MODE_MULTILINE_COMMENT: {
                if (symbol == '*') {
                    char forwardSymbol = this->getForwardCharacter(1);

                    if (forwardSymbol == '/') {
                        ++this->currentPosition;
                        this->mode = LEXER_MODE_DEFAULT;
                    }
                }

                return;
            }

            case LEXER_MODE_LEXEME_QUOTES: {
                // если встретилась закрывающаяся кавычка
                if (symbol == '\'') {
                    char forwardSymbol = this->getForwardCharacter(1);

                    // экранированная кавычка
                    if (forwardSymbol == '\'') {
                        this->appendCurrentLexeme(forwardSymbol);
                        ++this->currentPosition;
                        return;
                    }

                    this->appendCurrentLexeme(symbol);
                    this->mode = LEXER_MODE_DEFAULT;
                    Token* token = new TokenLexemeQuote(this->currentLine, this->currentColumn, this->lexemeWriter);
                    this->tokenStream->add(token);
                    this->lexemeWriter = NULL;
                    return;
                }

                this->appendCurrentLexeme(symbol);
                return;
            }

            case LEXER_MODE_LEXEME_WORD: {
                if (this->isLetter(symbol) || this->isDigit(symbol) || symbol == '_') {
                    this->appendCurrentLexeme(symbol);
                    return;
                }

                this->mode = LEXER_MODE_DEFAULT;
                Token* token = NULL;

                int lexemeLength = this->lexemeWriter->length();
                char *pLexeme = new char[lexemeLength];
                this->lexemeWriter->read(pLexeme, lexemeLength);
                this->lexemeWriter->setPosition(0);

                if (this->keywords.exists(pLexeme)) {
                    token = new TokenLexemeKeyword(this->currentLine, this->currentColumn, this->lexemeWriter);
                } else {
                    token = new TokenLexemeWord(this->currentLine, this->currentColumn, this->lexemeWriter);
                }

                free(pLexeme);

                this->tokenStream->add(token);
                this->lexemeWriter = NULL;
                // нужно обработать в другом месте
                --this->currentPosition;
                return;
            }

            case LEXER_MODE_NUMERIC: {
                if (this->isDigit(symbol)) {
                    this->appendCurrentLexeme(symbol);
                    return;
                }

                // todo уметь различать токен Float & Integer

                this->mode = LEXER_MODE_DEFAULT;
                Token* token = new TokenLexemeNumeric(this->currentLine, this->currentColumn, this->lexemeWriter);
                this->tokenStream->add(token);
                this->lexemeWriter = NULL;
                return;
            }

            case LEXER_MODE_CUSTOM_QUOTE: {
                if (symbol != '$') {
                    this->appendCurrentLexeme(symbol);
                    return;
                }

                this->mode = LEXER_MODE_CONTENT_QUOTED;

                int lexemeLength = this->lexemeWriter->length();
                char *pLexeme = new char[lexemeLength];
                this->lexemeWriter->read(pLexeme, lexemeLength);
                this->lexemeWriter->setPosition(0);
                this->quote = pLexeme;

                this->appendCurrentLexeme(symbol);
                Token* token = new TokenCustomQuote(this->currentLine, this->currentColumn, this->lexemeWriter);
                this->tokenStream->add(token);
                this->lexemeWriter = NULL;
                return;
            }

            case LEXER_MODE_CONTENT_QUOTED: {
                if (symbol == '$') {
                    // проверяем впереди идущие символы
                    int lengthQuote = strlen(this->quote);
                    bool isQuote = true;

                    for (int i = 1; i < lengthQuote; ++i) {
                        char forwardedSymbol = this->getForwardCharacter(i);
                        if (forwardedSymbol != this->quote[i]) {
                            isQuote = false;
                            break;
                        }
                    }

                    if (isQuote) {
                        // если достигли закрывающейся скобки, записываем токен
                        this->mode = LEXER_MODE_DEFAULT;
                        Token *token = new TokenLexemeQuote(this->currentLine, this->currentColumn, this->lexemeWriter);
                        this->tokenStream->add(token);
                        this->lexemeWriter = NULL;
                        // @todo добавить в поток закрывающий токен-кавычку
                        this->currentPosition += lengthQuote;
                        this->currentColumn += lengthQuote;
                        return;
                    }
                }

                this->appendCurrentLexeme(symbol);
                return;
            }
        }

        cout << symbol;
    }

    bool isLetter(char symbol)
    {
        return (symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z');
    }

    bool isDigit(char symbol)
    {
        return symbol >= '0' && symbol <= '9';
    }

    void appendCurrentLexeme(char symbol)
    {
        if (this->lexemeWriter == NULL) {
            this->lexemeWriter = new IOMemoryBuffer;
        }

        this->lexemeWriter->write(&symbol, 1);
    }

    char getForwardCharacter(int relativePosition)
    {
        int position = this->currentPosition + relativePosition;

        if (position >= 0 && position < this->posCurrent) {
            return this->currentBuffer[position];
        }

        if (position >= LEXER_BUFFER_SIZE && position < LEXER_BUFFER_SIZE << 1) {
            if (position - LEXER_BUFFER_SIZE < this->posForward) {
                return this->forwardBuffer[position - LEXER_BUFFER_SIZE];
            }
        }

        // конец файла
        return '\0';
    }
};
