#ifndef PARSER_H
# define PARSER_H

/* parser/parser.c */
t_node	*parse(t_token *t);
t_node	*create_node_cmd(t_token *t);
int		is_op(t_type type);
void	print_ast(t_node *node, int depth);

/* parser/parser_utils.c */
int		check_parser(t_token *t);
int		is_redirection(int type);
int		argc_counter(t_token *token);
t_cmd	*create_cmd(void);
t_token	*go_end(t_token *t);
t_token	*find_right_pipe(t_token *t);

#endif
