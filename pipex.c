/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muyumak <muyumak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 14:21:39 by muyumak           #+#    #+#             */
/*   Updated: 2023/01/09 20:38:03 by muyumak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

void	close_pipes(t_pipex *pipex)
{
	close(pipex->tube[0]);
	close(pipex->tube[1]);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	if (ac != 5)
		return (msg(ERR_INPUT));
	pipex.fd_infile = open(av[1], O_RDONLY);
	if (pipex.fd_infile < 0)
		msg_error(ERR_INFILE);
	pipex.fd_outfile = open(av[4], O_TRUNC | O_CREAT | O_RDWR, 0777);
	if (pipex.fd_outfile < 0)
		msg_error(ERR_OUTFILE);
	if (pipe(pipex.tube) < 0)
		msg_error(ERR_PIPE);
	pipex.paths = find_path(envp);
	pipex.cmd_paths = ft_split(pipex.paths, ':');
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		first_child(pipex, av, envp);
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
		second_child(pipex, av, envp);
	close_pipes(&pipex);
	waitpid(pipex.fd_infile, NULL, 0);
	waitpid(pipex.fd_outfile, NULL, 0);
	parent_free(&pipex);
	return (0);
}
