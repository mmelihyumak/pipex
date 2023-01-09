/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muyumak <muyumak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 14:22:12 by muyumak           #+#    #+#             */
/*   Updated: 2023/01/09 20:37:14 by muyumak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdlib.h>

# define ERR_INFILE "Infile"
# define ERR_OUTFILE "Outfile"
# define ERR_INPUT "Invalid number of arguments.\n"
# define ERR_PIPE "Pipe"
# define ERR_CMD "Command not found\n"

typedef struct s_pipex
{
	pid_t	pid1;
	pid_t	pid2;
	int		fd_infile;
	int		fd_outfile;
	int		tube[2];
	char	*paths;
	char	**cmd_paths;
	char	**cmd_args;
	char	*cmd;
}t_pipex;

int		ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	first_child(t_pipex pipex, char **av, char **envp);
void	second_child(t_pipex pipex, char **av, char **envp);
char	**ft_split(const char *s, char c);
char	*ft_strjoin(const char *s1, const char *s2);
int		msg(char *err);
void	msg_error(char *err);
void	parent_free(t_pipex *pipex);
void	child_free(t_pipex *pipex);

#endif