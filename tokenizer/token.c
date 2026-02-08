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
