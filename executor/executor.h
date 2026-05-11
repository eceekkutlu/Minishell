#ifndef EXECUTOR_H
# define EXECUTOR_H

/*
** executor/executor.c          (YAZILACAK)
**   AST'i yurutur.
**   execute()     : giris noktasi, LEAF_PIPE / LEAD_CMD ayirir
**
** executor/exec_cmd.c          (YAZILACAK)
**   Tek komut calistirir: fork + execve + PATH arama.
**   exec_cmd()    : t_cmd alinir, child surec olusturulur
**
** executor/exec_pipe.c         (YAZILACAK)
**   Pipe zinciri: her LEAF_PIPE dugumu icin pipe() + fork().
**   exec_pipe()   : sol/sag subashi recursive calistirir
**
** executor/exec_redir.c        (YAZILACAK)
**   Yonlendirme: open() + dup2().
**   apply_redirs(): t_cmd icerisindeki infile/outfile/append uygular
**   open_heredoc(): << DELIM icin gecici fd olusturur
*/
void	execute(t_node *node, char **envp);

#endif
