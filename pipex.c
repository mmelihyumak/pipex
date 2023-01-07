/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muyumak <muyumak@student.42>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 18:32:20 by muyumak           #+#    #+#             */
/*   Updated: 2023/01/07 18:32:20 by muyumak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char *envp[])
{
	while (ft_strncmp("PATH", *envp, 4))
		*envp++;
	return (*envp + 5);
}

int main(int ac, char *av[], char *envp[])
{

	t_pipex pipex;

	if (ac != 5)
		return(printf("Invalid number of arguments.\n"));
	pipex.infile = open(av[1], O_RDONLY);
	if (pipex.infile < 0)
	{
		perror("Infile");
		exit(1);
	}
	pipex.outfile = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex.outfile < 0)
	{
		perror("Outfile");
		exit(1);
	}
	if (pipe(pipex.tube) < 0)
	{
		perror("Pipe");
		exit(1);
	}
	pipex.paths = find_path(envp);
	pipex.cmd_paths = ft_split(pipex.paths, ':');
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		first_child(pipex, av, envp);
	pipex.pid2 = fork();
	if (pipex.pid1 == 0)
		second_child(pipex, av, envp);
	close(pipex.tube[0]);
	close(pipex.tube[1]);
	waitpid(pipex.pid2, NULL, 0);
	waitpid(pipex.pid1, NULL, 0);
	parent_free(&pipex);
	return (0);
}
