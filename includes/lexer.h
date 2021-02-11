#ifndef LEXER_H
# define LEXER_H

typedef enum e_token_type{
	PIPE,
	QOUTE,
	DQUOTE,
	SEMICOLON,
    AMPERSAND,
	WHITESPACE,
	TAB,
	NEWLINE,   
	GREATER,
    DGREATER,
	LESSER,
    DASH,
    WORD,
} t_token_type;

typedef struct s_token {
    char *data;
    t_token_type type;
} t_token;

typedef struct s_lexer {
    t_list *tokens;
    int     nb_tokens;
} t_lexer;

int     build_lexer(char *line, t_lexer *lexer);
#endif