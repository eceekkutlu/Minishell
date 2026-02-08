#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef enum e_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC
}	t_type;

typedef struct s_cmd
{
	char			**args;
	char			*infile;
	char			*outfile;
	int				append;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_token
{
	t_type			type;
	char			*value;
	struct s_token	*next;
}	t_token;

t_token	*new_token(t_type type, char *value);
void	add_token(t_token **head, t_token *new);
char	*read_word(char *s, int *i);
t_token	*tokenize(char *s);

/* helper functions - token_helper.c */
int		is_empty(char c);
int		op(char a);
int		op_number(char *str, int i);
t_type	op_type(char *s, int i);

int		pipe_control(char *str, int i);
int		double_token(char *str, int i);
int		after_token(char *s, int i);
char	*many_word_control(char *s, int *i, char c);

void	free_tokens(t_token *head);
char	*ft_substr(const char *s, unsigned int start, size_t len);

#endif