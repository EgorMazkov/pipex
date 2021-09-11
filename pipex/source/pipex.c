/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghumbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 13:51:33 by ghumbert          #+#    #+#             */
/*   Updated: 2021/08/08 13:51:34 by ghumbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_perror(char *line)
{
	perror(line);
	exit(1);
}

char	*slash_for_path(char *path_priem, char *com)
{
	char	*res;

	com = ft_strjoin("/", com);
	res = ft_strjoin(path_priem, com);
	free(com);
	return (res);
}

char	*right_way(t_pipex *pipex)
{
	int		i;
	int		fd;
	char	*res;

	i = -1;
	while (pipex->path_priem[++i])
	{
		res = slash_for_path(pipex->path_priem[i], pipex->comm[0]);
		fd = open(res, O_RDONLY);
		free(res);
		if (fd != -1)
			break ;
	}
	if (fd == -1)
		return (NULL);
	else
		return (res);
}

void	get_path(t_pipex *pipex, char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			pipex->path_priem = ft_split(env[i], ':');
	}
}

int	main(int argc, char **argv, char **env)
{
	int		fd[2];
	t_pipex	pipex;

	if (argc < 5)
		ft_perror("Few arguments");
	pipe(fd);
	pipex.pid = fork();
	if (pipex.pid == 0)
		child_process(&pipex, fd, env, argv);
	else
		parent_process(&pipex, fd, env, argv);
	return (0);
}
