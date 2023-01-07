/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muyumak <muyumak@student.42>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 19:41:24 by muyumak           #+#    #+#             */
/*   Updated: 2023/01/07 19:41:24 by muyumak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>

typedef struct s_pipex
{
	pid_t	pid1;
	pid_t	pid2;
	int		tube[2];
	int		infile;
	int		outfile;
	char	*paths;
	char	**cmd_paths;
	char	**cmd_args;
	char	*cmd;
}t_pipex;

void	first_child(t_pipex pipex, char *av[], char *envp[]);
void	second_child(t_pipex pipex, char *av[], char *envp[]);
char	*ft_strjoin(const char *s1, const char *s2);
char	**ft_split(const char *s, char c);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(char const *s);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
void	parent_free(t_pipex *pipex);
void	child_free(t_pipex *pipex);

#endif
