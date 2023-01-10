/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muyumak <muyumak@student.42>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 00:53:46 by muyumak           #+#    #+#             */
/*   Updated: 2023/01/10 00:53:46 by muyumak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>

int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(const char *s, char c);
char	*ft_strjoin(const char *s1, const char *s2);

char	*find_path(char **envp)
{
	while(ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

static char	*get_cmd(char **paths, char *cmd)
{
	char	*command;
	char	*tmp;

	while(*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		printf("command: %s\n", command);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	int		outfile;
	int		infile;
	pid_t	pid;
	int		pipe_fd[2];


	infile = open(argv[1], O_RDONLY);
	outfile = open(argv[4], O_CREAT | O_TRUNC | O_RDWR, 0777);
	if (outfile < 0)
		perror("fd");
	if (pipe(pipe_fd) < 0)
		perror("pipe");
	char *paths = find_path(envp);
	char	**cmd_paths = ft_split(paths, ':');
	pid = fork();
	if (pid < 0)
		perror("Process Error");
	else if (pid == 0)
	{
		dup2(infile, 0);
		dup2(pipe_fd[1], 1);
		close(pipe_fd[0]);
		char	**cmd_args = ft_split(argv[2], ' ');
		char	*cmd = get_cmd(cmd_paths, cmd_args[0]);
		if (!cmd)
			perror("Command not found");
		execve(cmd, cmd_args, envp);
	}
	else
	{
		dup2(pipe_fd[0], 0);
		dup2(outfile, 1);
		close(pipe_fd[1]);
		char **cmd_args = ft_split(argv[3], ' ');
		char	*cmd = get_cmd(cmd_paths, cmd_args[0]);
		if (!cmd)
			perror("Command not found");
		execve(cmd, cmd_args, envp);
	}

	waitpid(pid, NULL, 0);
	return (0);
}
