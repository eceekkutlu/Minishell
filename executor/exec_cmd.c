#include "../minishell.h"

char	**get_path_dirs(char **envp)
{
	int		i;
	char	*path_line;

	/* PATH değişkenini ortamdan bulup ':' karakterine göre parçalara ayırıyoruz.
	   Böylece /bin, /usr/bin gibi dizinleri tek tek gezebiliyoruz. */
	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
		{
			/* "PATH=" kısmını atlayıp sadece gerçek dizin listesini alıyoruz. */
			path_line = envp[i] + 5;
			/* Dizinleri ':' ile ayırıp dizi halinde geri dönüyoruz. */
			return (ft_split(path_line, ':'));
		}
		i++;
	}
	/* PATH yoksa komut adı üzerinden klasör taraması yapamayız. */
	return (NULL);
}

char	*join_cmd_path(char *dir, char *cmd)
{
	char	*tmp;
	char	*full_path;

	/* Önce "dizin/" kısmını oluşturuyoruz. */
	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	/* Sonra komut adını ekleyip tam aday yolu üretiyoruz: /bin/ls gibi. */
	full_path = ft_strjoin(tmp, cmd);
	free(tmp);
	return (full_path);
}

char	*find_cmd_in_path(char **paths, char *cmd)
{
	int		i;
	char	*full_path;

	/* PATH içindeki her dizinde komutun çalıştırılabilir olup olmadığına bakıyoruz. */
	if (!paths || !cmd)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		/* Her dizini komut adıyla birleştirip tek tek deneme yolu oluşturuyoruz. */
		full_path = join_cmd_path(paths[i], cmd);
		if (!full_path)
			return (NULL);
		/* access(..., X_OK) komutun çalıştırılabilir olup olmadığını kontrol eder. */
		if (access(full_path, X_OK) == 0)
			/* Uygun bir yol bulunduysa artık bu yolu kullanabiliriz. */
			return (full_path);
		/* Bu yol çalışmıyorsa belleği temizleyip bir sonraki PATH dizinine geçiyoruz. */
		free(full_path);
		i++;
	}
	/* Hiçbir PATH dizininde komut bulunamadı. */
	return (NULL);
}

char	*find_cmd_path(char *cmd, char **envp)
{
	char	**paths;
	char	*cmd_path;

	/* Bu fonksiyonun görevi: verilen komut adından çalıştırılabilir tam yol üretmek. */
	if (!cmd || !cmd[0])
		return (NULL);
	/* Komut içinde '/' varsa PATH araması yapmayız; kullanıcı zaten bir yol vermiştir. */
	if (ft_strchr(cmd, '/'))
	{
		/* Verilen yol gerçekten çalıştırılabiliyorsa aynen kopyasını döndürüyoruz. */
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		/* Yol var ama çalıştırılamıyorsa NULL dönüyoruz. */
		return (NULL);
	}
	/* Komut sade isimse PATH değişkeninden dizinleri çıkarıyoruz. */
	paths = get_path_dirs(envp);
	if (!paths)
		return (NULL);
	/* PATH dizinlerini gezip komutu bulmaya çalışıyoruz. */
	cmd_path = find_cmd_in_path(paths, cmd);
	/* Split ile ayrılan PATH dizilerini serbest bırakıyoruz. */
	free_split(paths);
	/* Bulunan tam yolu, ya da bulunamadıysa NULL'u geri veriyoruz. */
	return (cmd_path);
}
int	exec_cmd(t_cmd_node *node, t_shell *shell)
{
	pid_t	pid;
	char	*cmd_path;

	if (!node || !node->args || !node->args[0])
		return (0);
	cmd_path = find_cmd_path(node->args[0], shell->envp);
	if (!cmd_path)
	{
		printf("%s: command not found\n", node->args[0]);
		return (127);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		free(cmd_path);
		return (1);
	}
	if (pid == 0)
	{
		
	}
    else
    {

    }
	return (0);
}
int exec_process(t_cmd_node *node, t_shell *shell)
// child ile komutu çalıştırmamız lazım 
// childın nasıl yazıldığını hatırlamıyorum 
//execve()ile childı çalıştırıyorduk 
//execve("/bin/ls", args, envp);
//execve çalıştığında program bu fd ' lere yazar okur 
// Biz fd lerin nereye baktığını değiştireceğiz