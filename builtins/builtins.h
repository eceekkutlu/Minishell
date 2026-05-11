#ifndef BUILTINS_H
# define BUILTINS_H

/*
** builtins/builtins.c          (YAZILACAK)
**   Komut adini kontrol edip ilgili builtin'i cagirir.
**   is_builtin()  : string karsilastirma, 1/0 doner
**   run_builtin() : uygun ft_* fonksiyonunu dispatch eder
**
** Her builtin ayri dosyada:
**   builtins/ft_echo.c         echo [-n]
**   builtins/ft_cd.c           cd [path]   — PWD/OLDPWD gunceller
**   builtins/ft_pwd.c          pwd
**   builtins/ft_export.c       export [KEY=VAL ...]
**   builtins/ft_unset.c        unset [KEY ...]
**   builtins/ft_env.c          env
**   builtins/ft_exit.c         exit [n]
*/
int		is_builtin(char *cmd);
int		run_builtin(t_cmd *cmd, char ***envp);

int		ft_echo(t_cmd *cmd);
int		ft_cd(t_cmd *cmd, char ***envp);
int		ft_pwd(void);
int		ft_export(t_cmd *cmd, char ***envp);
int		ft_unset(t_cmd *cmd, char ***envp);
int		ft_env(char **envp);
int		ft_exit(t_cmd *cmd);

#endif
