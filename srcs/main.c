/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:00:28 by lbirloue          #+#    #+#             */
/*   Updated: 2024/02/27 11:58:49 by lbirloue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	init_value(t_pipex *pipex, char **argv)
{
	(void)argv;
	pipex->exit_s = 0;
	pipex->cmd_counter = pipex->argc - 3;
	pipex->pipe_counter = pipex->cmd_counter - 1;
	pipex->path_list = NULL;
	pipex->cmd_split = NULL;
	pipex->path_cmd = NULL;
	return (0);
}

void	refresh_pipe(t_pipex *pipex, int fd[2])
{
	v_error(pipex, close(fd[0]), "close :", NULL);
	v_error(pipex, close(fd[1]), "close :", NULL);
	pipe(fd);
	return ;
}

void	one(t_pipex *pipex, char **envp, char **argv)
{
	char	*tempo;

	tempo = NULL;
	if (pipex->i == 0)
	{
		pipex->fd_input = open(argv[1], O_RDONLY | O_CLOEXEC);
		if (pipex->fd_input == -1)
		{
			v_error(pipex, -1, argv[1], "No such file or directory");
			free_all(pipex, -1);
		}
	}
	v_error(pipex, dup2(pipex->fd_input, STDIN_FILENO), "dup2", NULL);
	while (pipex->i < pipex->pipe_counter)
	{
		child_first_cmd(pipex, argv, envp, tempo);
		pipex->i++;
	}
	child_last_cmd(pipex, argv, envp, tempo);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		i;

	pipex.argc = argc;
	parsing(&pipex);
	init_value(&pipex, argv);
	get_env(&pipex, envp);
	sep_path(&pipex, envp);
	i = 0;
	pipex.i = 0;
	one(&pipex, envp, argv);
}
