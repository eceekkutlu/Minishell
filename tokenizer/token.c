<<<<<<< HEAD
#include "../minishell.h"

t_token	*new_token(t_type type, char *value)
{
	t_token	*t;

	t = (t_token *)malloc(sizeof(t_token));
	if (!t)
		return (NULL);
	t->type = type;
	t->value = value;
	t->quoted = 0;
	t->next = NULL;
	t->prev = NULL;
	return (t);
}

void	add_token(t_token **head, t_token *new)
{
	t_token	*tmp;

	if (!new)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head; 
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new -> prev = tmp;
	new ->next = NULL;
}
char	*read_word(char *s, int *i)
{
	int	start;

	while (s[*i] && is_empty(s[*i]))
		(*i)++;
	start = *i;
	while (s[*i]
		&& !is_empty(s[*i])
		&& !op(s[*i])
		&& s[*i] != '\''
		&& s[*i] != '"')
		(*i)++;
	return (ft_substr(s, start, *i - start));
}
t_token	*tokenize(char *s)
{
	t_token	*head;
	char	*new;
	int		i;
	int		len;
	t_type	type;
	char	quote_char;
	t_token	*tok;

	head = NULL;
	i = 0;
	while (s[i])
	{
		while (s[i] && is_empty(s[i]))
			i++;
		if (!s[i])
        	break ;
		if (s[i] == '\'' || s[i] == '"')
		{
			quote_char = s[i];
			new = many_word_control(s, &i, quote_char);
			if (!new)
				return (NULL);
			tok = new_token(WORD, new);
			if (!tok)
				return (NULL);
			tok->quoted = (quote_char == '\'') ? 1 : 2;
			add_token(&head, tok);
			/* Quoted word sonrası hemen yanında WORD karakteri varsa birleştir */
			if (s[i] && !is_empty(s[i]) && !op(s[i]) && s[i] != '\'' && s[i] != '"')
			{
				char	*next_word = read_word(s, &i);
				if (next_word && next_word[0] != '\0')
				{
					tok->value = append_str_simple(tok->value, next_word);
					if (!tok->value)
					{
						free(next_word);
						return (NULL);
					}
					free(next_word);
				}
				else if (next_word)
					free(next_word);
			}
		}
		else if (pipe_control(s, i) || double_token(s, i) || after_token(s, i))
			return (NULL);
		else if (op(s[i]))
		{
			len = op_number(s, i);
			type = op_type(s, i);
			add_token(&head, new_token(type, ft_substr(s, i, len)));
			i += len;
		}
		else
		{
			new = read_word(s, &i);
			if (!new)
				return (NULL);
			if (new[0] != '\0')
				add_token(&head, new_token(WORD, new));
			else
				free(new);
		}
	}
	return (head);
}
=======
#include "../minishell.h"

t_token	*new_token(t_type type, char *value)
{
	t_token	*t;

	t = (t_token *)malloc(sizeof(t_token));
	if (!t)
		return (NULL);
	t->type = type;
	t->value = value;
	t->next = NULL;
	return (t);
}

void	add_token(t_token **head, t_token *new)
{
	t_token	*tmp;

	if (!new)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

char	*read_word(char *s, int *i)
{
	int	start;

	while (s[*i] && is_empty(s[*i]))
		(*i)++;
	start = *i;
	while (s[*i]
		&& !is_empty(s[*i])
		&& !op(s[*i])
		&& s[*i] != '\''
		&& s[*i] != '"')
		(*i)++;
	return (ft_substr(s, start, *i - start));
}

t_token	*tokenize(char *s)
{
	t_token	*head;
	char	*new;
	int		i;
	int		len;
	t_type	type;

	head = NULL;
	i = 0;
	while (s[i])
	{
		while (s[i] && is_empty(s[i]))
			i++;
		if (!s[i])
			break ;

		if (pipe_control(s, i) || double_token(s, i) || after_token(s, i))
			return (NULL);

		if (op(s[i]))
		{
			len = op_number(s, i);
			type = op_type(s, i);
			add_token(&head, new_token(type, ft_substr(s, i, len)));
			i += len;
		}
		else if (s[i] == '\'' || s[i] == '"')
		{
			new = many_word_control(s, &i, s[i]);
			if (!new)
				return (NULL);
			add_token(&head, new_token(WORD, new));
		}
		else
		{
			new = read_word(s, &i);
			if (!new)
				return (NULL);
			if (new[0] != '\0')
				add_token(&head, new_token(WORD, new));
			else
				free(new);
		}
	}
	return (head);
}
>>>>>>> 2942cb5a340d915b5b484187ee7906bb7554e94d
