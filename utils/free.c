#include "../minishell.h"

void	free_tokens(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->value);
		free(tmp);
	}
}

void	free_cmd_(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return ;
	if (cmd->args)
	{
		while (cmd->args[i])
		{
			free(cmd->args[i]);
			i++;
		}
		free(cmd->args);
	}
	if (cmd->outfile)
		free(cmd->outfile);
	if (cmd->infile)
		free(cmd->infile);
	free(cmd);
}

void	free_ast(t_node *node)
{
	int	i;

	i = 0;
	if (!node)
		return ;
	free_ast(node->left);
	free_ast(node->right);
	if (node->cmd)
	{
		if (node->cmd->args)
		{
			while (node->cmd->args[i])
				free(node->cmd->args[i++]);
			free(node->cmd->args);
		}
		if (node->cmd->infile)
			free(node->cmd->infile);
		if (node->cmd->outfile)
			free(node->cmd->outfile);
		free(node->cmd);
	}
	free(node);
}
