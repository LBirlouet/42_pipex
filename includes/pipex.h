/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:01:16 by lbirloue          #+#    #+#             */
/*   Updated: 2024/02/20 09:21:17 by lbirloue         ###   ########.fr       */
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
	char		*path_cmd;
	char		**cmd_split;
	char		**path_list;
	int			path_counter;
	int			cmd_counter;
	int			pipe_counter;
	int			argc;
	int			fd_output;
	int			fd_input;
	int			*pipe;
	int			first_pipe[2];
	int			sec_pipe[2];
	
	int			*pipe_verif;
	int			i;
	pid_t		cpid;
	// pid_t		*cpid;
}				t_pipex;

int		main(int argc, char **argv, char **envp);
void	parsing(t_pipex *pipex);
int		init_value(t_pipex *pipex, char **argv);
void	get_path(t_pipex *pipex, char **envp);
void	get_env(t_pipex *pipex, char **envp);
void	sep_path(t_pipex *pipex, char **envp);
void	join_path(t_pipex *pipex, char **argv);

char	*get_good_path(t_pipex *pipex, int i, char *tempo, char **cmd_split);

void	v_error(t_pipex *pipex, int ret, char *err);
void	free_all(t_pipex *pipex, int status);

/*utils*/
char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *str);

void	child_first_cmd(t_pipex *pipex, char **argv);
void	child_mid_cmd(t_pipex *pipex);
void	child_last_cmd(t_pipex *pipex, char **argv, int argc);
void	refresh_pipe(int fd[2]);


/*lst*/
// void	ft_lstdelone(t_cmd *cmd, void (*del)(void *));
// void	ft_lstclear(t_cmd **lst, void (*del)(void *));
// void	ft_lstadd_back(t_cmd **lst, t_cmd *new);
// t_cmd	*ft_lstnew(void *content);



#endif