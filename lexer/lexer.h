#define LEXER_BUFFER_SIZE 512

#define LEXER_MODE_DEFAULT 0
#define LEXER_MODE_ONELINE_COMMENT 1
#define LEXER_MODE_MULTILINE_COMMENT 2
#define LEXER_MODE_LEXEME_QUOTES 3
#define LEXER_MODE_LEXEME_WORD 4
#define LEXER_MODE_NUMERIC 5
// $$ or $BODY$ quoted expressions
#define LEXER_MODE_CUSTOM_QUOTE 6
#define LEXER_MODE_CONTENT_QUOTED 7

#include <stdio.h>
#include <stdlib.h>
#include "tokens/token.h"
#include "keyword_list.cpp"
#include "lexer.cpp"
#include "lexer_sql.cpp"
