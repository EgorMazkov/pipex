/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghumbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 13:42:20 by ghumbert          #+#    #+#             */
/*   Updated: 2021/08/08 13:42:22 by ghumbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../libs/libft/libft.h"

typedef struct s_pipex
{
	int		fd1;
	int		fd2;
	pid_t	pid;
	char	**path_priem;
	char	**comm;
	char	*path_com;
}	t_pipex;

void	ft_perror(char *line);
char	*slash_for_path(char *path_priem, char *com);
char	*right_way(t_pipex *pipex);
void	get_path(t_pipex *pipex, char **env);
void	child_process(t_pipex *pipex, int *fd, char **env, char **argv);
void	parent_process(t_pipex *pipex, int *fd, char **env, char **argv);

#endif
