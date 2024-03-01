/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:01:16 by lbirloue          #+#    #+#             */
/*   Updated: 2024/03/01 13:01:27 by lbirloue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <limits.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include "../ft_printf/ft_printf.h"
# include <stdio.h>

typedef struct s_pipex {
	int			envline;
	int			exit_s;
	char		*path_cmd;
	char		**cmd_split;
	char		**path_list;
	int			path_counter;
	int			cmd_counter;
	int			pipe_counter;
	int			argc;
	int			fd_output;
	int			fd_input;
	int			prev_pipe;
	int			pipe_fds[2];
	int			f_cmd_status;
	int			*pipe_verif;
	int			i;
	pid_t		cpid;
	pid_t		pid;
	// pid_t		*cpid;
}				t_pipex;

int		main(int argc, char **argv, char **envp);
int		init_value(t_pipex *pipex);
void	get_path(t_pipex *pipex, char **envp);
void	get_env(t_pipex *pipex, char **envp);
void	sep_path(t_pipex *pipex, char **envp);
void	join_path(t_pipex *pipex, char **argv);

char	*prep_path(t_pipex *pipex, int i, char **cmd_split);
void	cmd_not_found(t_pipex *pipex, char **argv, char **cmd_split);

char	*get_good_path(t_pipex *pipex, int i, char **cmd_split, char **argv);
void	one(t_pipex *pipex, char **envp, char **argv);
void	v_error(t_pipex *pipex, int ret, char *err, char *err2);
void	free_all(t_pipex *pipex, int status);
void	first_cmd(t_pipex *pipex, char **av);

char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *str);

void	child_cmd(t_pipex *pipex, char **argv, char **envp);
void	child_last_cmd(t_pipex *pipex, char **argv, char **envp);
void	wpid(t_pipex *pipex, int i);

#endif