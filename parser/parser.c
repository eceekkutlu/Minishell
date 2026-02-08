#include "../minishell.h"

int	argc_counter(t_token *token)
{
	t_token	*head;
	int		arg_count;

	arg_count = 0;
	head = token;
	while (head && head->type != PIPE)
	{
		if (head->type == WORD)
			arg_count++;
		head = head->next;
	}
	return (arg_count);
}

// bu gereksiz olabilir emin değilim şu an 
int	next_pipe_counter(t_token *token)
{
	t_token	*head;
	int		next_counter;

	head = token;
	next_counter = 0;
	while (head && head->type != PIPE)
		head = head->next;
	if (head && head->type == PIPE)
		head = head->next;
	while (head && head->type != PIPE)
	{
		if (head->type == WORD)
			next_counter++;
		head = head->next;
	}
	return (next_counter);
}
t_cmd *create_cmd(t_token **token)
{
    t_cmd *cmd;
    cmd = malloc(sizeof(t_cmd));
    if(!cmd)
        return (NULL);
    cmd -> args = NULL;
    cmd -> infile = NULL;
    cmd -> outfile = NULL;
    cmd -> append = 0;
    cmd -> next = NULL;

    return (cmd);
// tüm komut içinde olanları fonksiyonlar oluşturucam ve onlarla dolduracağım.