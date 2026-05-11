#ifndef EXECUTOR_H
# define EXECUTOR_H

void	execute(t_node *node, char **envp);
int		exec_cmd(t_cmd *cmd, char **envp);

#endif
