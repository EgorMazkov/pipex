/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghumbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 13:51:37 by ghumbert          #+#    #+#             */
/*   Updated: 2021/08/08 13:51:39 by ghumbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	child_process(t_pipex *pipex, int *fd, char **env, char **argv)
{
	close(fd[0]);
	pipex->fd1 = open(argv[1], O_RDONLY);
	if (pipex->fd1 == -1)
		ft_perror("not file");
	pipex->comm = ft_split(argv[2], ' ');
	get_path(pipex, env);
	pipex->path_com = right_way(pipex);
	dup2(pipex->fd1, 0);
	dup2(fd[1], 1);
	close(fd[1]);
	if (pipex->path_com == NULL)
		ft_perror("You should try another command");
	else
	{
		if (execve(pipex->path_com, pipex->comm, NULL) == -1)
			ft_perror("command");
	}
}

void	parent_process(t_pipex *pipex, int *fd, char **env, char **argv)
{
	wait(NULL);
	close(fd[1]);
	pipex->fd2 = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0664);
	if (pipex->fd2 == -1)
		ft_perror("file");
	pipex->comm = ft_split(argv[3], ' ');
	get_path(pipex, env);
	pipex->path_com = right_way(pipex);
	dup2(fd[0], 0);
	close(fd[0]);
	dup2(pipex->fd2, 1);
	if (pipex->path_com == NULL)
		ft_perror("You should try another command");
	else
	{
		if (execve(pipex->path_com, pipex->comm, NULL) == -1)
			ft_perror("command");
	}
	wait(NULL);
}
