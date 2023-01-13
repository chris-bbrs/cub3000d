#include "MLX42/MLX42_Int.h"
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
# define STDOUT_FILENO 1

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;

	if (s == NULL)
		return (NULL);
	if (start >= strlen((char *)s))
		return (calloc(1, sizeof(char)));
	if (len > strlen((char *)s))
		len = strlen((char *)s);
	substr = malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	strlcpy(substr, s + start, len + 1);
	return (substr);
}

int	mlx_get_pid(char *s)
{
	FILE	*fn;
	int		pid;
	size_t	n;
	int		ps_fd;
	char	*buff;
	int		tmp_fd;

	tmp_fd = dup(STDOUT_FILENO);
	pid = 0;
	buff = NULL;
	ps_fd = open("ps", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	dup2(ps_fd, STDOUT_FILENO);
	system("ps");
	dup2(tmp_fd, STDOUT_FILENO);
	close(tmp_fd);
	close(ps_fd);
	n = 0;
	fn = fopen("ps", "r");
	while (getline(&buff, &n, fn) >= 0)
	{
		if (buff && strnstr(buff, s, strlen(buff)) != NULL)
		{
			char *sub_str = ft_substr(buff, 0, 10);
			pid = atoi(sub_str);
			free(sub_str);
			free(buff);
			break ;
		}
	}
	if (pid == 0)
		free(buff);
	fclose(fn);
	return (pid);
}

void	mlx_start_sound(int pid, char *name)
{
	if (!pid)
		system(name);
}

void	mlx_stop_sound(int pid)
{
	if (pid)
		kill(pid, SIGKILL);
}