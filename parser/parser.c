#include "../minishell.h"

int	is_op(t_type type)
{
	return (type == PIPE || type == REDIR_IN || 
		type == REDIR_OUT || type == APPEND || type == HEREDOC);
}

t_node	*parse(t_token *t)
{
	t_token	*right;
	t_node	*node;

	if (!t)
		return (NULL);
	if (check_parser(t))
	{
		free_tokens(t);
		return (NULL);
	}
	right = find_right_pipe(t);
	if (!right)
		return create_node_cmd(t);
	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = LEAF_PIPE;
	node->cmd = NULL;
	node->left = parse(t);
	node->right = parse(right);
	return (node);
}

static t_node	*cmd_fail(t_node *node, t_cmd *cmd)
{
	free_cmd_(cmd);
	free(node);
	return (NULL);
}

static int	add_arg(t_cmd *cmd, t_token *t, int *i)
{
	if (!(t->prev && is_redirection(t->prev->type)))
	{
		cmd->args[*i] = strdup(t->value);
		if (!cmd->args[*i])
			return (1);
		(*i)++;
	}
	return (0);
}

t_node	*create_node_cmd(t_token *t)
{
	t_node	*node;
	t_cmd	*cmd;
	int		count;
	int		i;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = LEAD_CMD;
	node->left = NULL;
	node->right = NULL;
	node->cmd = NULL;

	cmd = create_cmd();
	if (!cmd)
	{
		free(node);
		return (NULL);
	}
	count = argc_counter(t);
	cmd->args = calloc(count + 1, sizeof(char *));
	if (!cmd->args)
		return (cmd_fail(node, cmd));
	i = 0;
	while (t && t->type != PIPE)
	{
		if (t->type == WORD)
		{
			if (add_arg(cmd, t, &i))
				return (cmd_fail(node, cmd));
			t = t->next;
		}
		else if (t->type == REDIR_IN)
		{
			t = t->next;
			if (t && t->type == WORD)
			{
				if (cmd->infile)
					free(cmd->infile);
				cmd->infile = strdup(t->value);
				if (!cmd->infile)
					return (cmd_fail(node, cmd));
			}
			if (t)
				t = t->next;
		}
		else if (t->type == REDIR_OUT || t->type == APPEND)
		{
			cmd->append = (t->type == APPEND);
			t = t->next;
			if (t && t->type == WORD)
			{
				if (cmd->outfile)
					free(cmd->outfile);
				cmd->outfile = strdup(t->value);
				if (!cmd->outfile)
					return (cmd_fail(node, cmd));
			}
			if (t)
				t = t->next;
		}
		else if (t->type == HEREDOC)
		{
			t = t->next;
			if (t && t->type == WORD)
			{
				if (cmd->infile)
					free(cmd->infile);
				cmd->infile = strdup(t->value);
				if (!cmd->infile)
					return (cmd_fail(node, cmd));
			}
			if (t)
				t = t->next;
		}
		else
			t = t->next;
	}
	node->cmd = cmd;
	return (node);
}

void	print_ast(t_node *node, int depth)
{
	int	i;

	if (!node)
		return;
	for (i = 0; i < depth; i++)
		printf("  ");
	if (node->type == LEAF_PIPE)
	{
		printf("PIPE\n");
		print_ast(node->left, depth + 1);
		print_ast(node->right, depth + 1);
	}
	else if (node->type == LEAD_CMD && node->cmd)
	{
		printf("CMD: ");
		if (node->cmd->args)
		{
			i = 0;
			while (node->cmd->args[i])
			{
				printf("%s ", node->cmd->args[i]);
				i++;
			}
		}
		if (node->cmd->infile)
			printf("< %s ", node->cmd->infile);
		if (node->cmd->outfile)
			printf("%s %s", node->cmd->append ? ">>" : ">", node->cmd->outfile);
		printf("\n");
	}
}
