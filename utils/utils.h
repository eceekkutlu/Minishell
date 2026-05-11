#ifndef UTILS_H
# define UTILS_H

/* utils/utils.c */
char	*ft_substr(const char *s, unsigned int start, size_t len);

/* utils/free.c */
void	free_tokens(t_token *head);
void	free_ast(t_node *node);
void	free_cmd_(t_cmd *cmd);

#endif
