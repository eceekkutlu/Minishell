<<<<<<< HEAD
#include "../minishell.h"

int	pipe_control(char *str, int i)
{
	int	j;

	if (str[i] != '|')
		return (0);
	if (i == 0)
	{
		perror("minishell: syntax error");
		return (1);
	}
	j = i - 1;
	while (j >= 0 && is_empty(str[j]))
		j--;
	if (j < 0)
	{
		perror("minishell: syntax error");
		return (1);
	}
	j = i + 1;
	while (str[j] && is_empty(str[j]))
		j++;
	if (!str[j])
	{
		perror("minishell: syntax error");
		return (1);
	}
	return (0);
}
// tüm pipe kontolleri tamamlandı 
int	double_token(char *str, int i)
{
	if (op(str[i]) && op(str[i + 1]))
	{
		if (!((str[i] == '<' && str[i + 1] == '<') ||
			  (str[i] == '>' && str[i + 1] == '>')))
		{
			perror("minishell: syntax error");
			return (1);
		}
	}
	return (0);
}

int	after_token(char *s, int i)
{
	if (op(s[i]))
	{
		i += op_number(s, i);
		while (s[i] && is_empty(s[i]))
			i++;
		if (!s[i] || op(s[i]))
		{
			perror("minishell: syntax error ");
			return (1);
		}
		return (0);
	}
	return (0);
}
//
char	*many_word_control(char *s, int *i, char c)
{
	int		start;
	char	*new;

	(*i)++;
	start = *i;
	while (s[*i] && s[*i] != c)
		(*i)++;
	if (s[*i] != c)
		return (NULL);
	new = ft_substr(s, start, *i - start);
	(*i)++;
	return (new);
}
// expand 
//nokta da 
// aaa
=======
#include "../minishell.h"

int	pipe_control(char *str, int i)
{
	int	j;

	if (str[i] != '|')
		return (0);
	if (i == 0)
	{
		perror("minishell: syntax error");
		return (1);
	}
	j = i - 1;
	while (j >= 0 && is_empty(str[j]))
		j--;
	if (j < 0)
	{
		perror("minishell: syntax error");
		return (1);
	}
	j = i + 1;
	while (str[j] && is_empty(str[j]))
		j++;
	if (!str[j])
	{
		perror("minishell: syntax error");
		return (1);
	}
	return (0);
}
int	double_token(char *str, int i)
{
	if (op(str[i]) && op(str[i + 1]))
	{
		if (!((str[i] == '<' && str[i + 1] == '<') ||
			  (str[i] == '>' && str[i + 1] == '>')))
		{
			perror("minishell: syntax error");
			return (1);
		}
	}
	return (0);
}
int	after_token(char *s, int i)
{
	if (op(s[i]))
	{
		i += op_number(s, i);
		while (s[i] && is_empty(s[i]))
			i++;
		if (!s[i] || op(s[i]))
		{
			perror("minishell: syntax error ");
			return (1);
		}
		return (0);
	}
	return (0);
}
char	*many_word_control(char *s, int *i, char c)
{
	int		start;
	char	*new;

	(*i)++;
	start = *i;
	while (s[*i] && s[*i] != c)
		(*i)++;
	if (s[*i] != c)
		return (NULL);
	new = ft_substr(s, start, *i - start);
	(*i)++;
	return (new);
}
>>>>>>> 2942cb5a340d915b5b484187ee7906bb7554e94d
