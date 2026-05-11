#include "../minishell.h"

char	*append_str_simple(char *dst, const char *src)
{
	size_t	old_len;
	size_t	src_len;
	char	*tmp;

	old_len = dst ? strlen(dst) : 0;
	src_len = src ? strlen(src) : 0;
	tmp = realloc(dst, old_len + src_len + 1);
	if (!tmp)
		return NULL;
	if (src_len > 0)
		memcpy(tmp + old_len, src, src_len);
	tmp[old_len + src_len] = '\0';
	return (tmp);
}

char	*append_substr_simple(char *dst, const char *src, int start, int len)
{
	size_t	old_len;
	char	*tmp;

	old_len = dst ? strlen(dst) : 0;
	tmp = realloc(dst, old_len + len + 1);
	if (!tmp)
		return NULL;
	if (len > 0)
		memcpy(tmp + old_len, src + start, len);
	tmp[old_len + len] = '\0';
	return (tmp);
}

char	*get_var_name(char *value, int *i)
{
	int	start;

	(*i)++;
	start = *i;
	while (value[*i] && (isalnum((unsigned char)value[*i]) || value[*i] == '_'))
		(*i)++;
	return ft_substr(value, start, *i - start);
}

char	*expand_value(char *value)
{
	char	*var_name;
	char	*env_val;
	char	*res;
	int		i;
	int		start;

	res = NULL;
	i = 0;
	while (value[i])
	{
		if (value[i] == '$' && value[i + 1] == '?')
		{
			char	exit_str[12];
			snprintf(exit_str, sizeof(exit_str), "%d", g_exit_status);
			res = append_str_simple(res, exit_str);
			if (!res)
				return (NULL);
			i += 2;
		}
		else if (value[i] == '$' && value[i + 1]
			&& (isalnum((unsigned char)value[i + 1]) || value[i + 1] == '_'))
		{
			var_name = get_var_name(value, &i);
			if (!var_name)
				return (free(res), NULL);
			env_val = getenv(var_name);
			if (env_val)
			{
				res = append_str_simple(res, env_val);
				if (!res)
					return (free(var_name), NULL);
			}
			else
			{
				res = append_str_simple(res, "$");
				if (!res)
					return (free(var_name), NULL);
				res = append_str_simple(res, var_name);
				if (!res)
					return (free(var_name), NULL);
			}
			free(var_name);
		}
		else if (value[i] == '$')
		{
			res = append_substr_simple(res, value, i, 1);
			if (!res)
				return (NULL);
			i++;
		}
		else
		{
			start = i;
			while (value[i] && value[i] != '$')
				i++;
			res = append_substr_simple(res, value, start, i - start);
			if (!res)
				return (NULL);
		}
	}
	return (res);
}
