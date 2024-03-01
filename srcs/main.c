/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:00:28 by lbirloue          #+#    #+#             */
/*   Updated: 2024/03/01 10:02:12 by lbirloue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	init_value(t_pipex *pipex, char **argv)
{
	(void)argv;
	pipex->i = 0;
	pipex->exit_s = 0;
	pipex->f_cmd_status = 0;
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

int status;
	int ret_pid;
	int exit_status;
	pipex->fd_input = 0;
	int i = pipex->pipe_counter;

	tempo = NULL;
	// if (pipex->i == 0)
	// {
	// 	pipex->fd_input = open(argv[1], O_RDONLY | O_CLOEXEC);
	// 	if (pipex->fd_input == -1)
	// 	{
	// 		v_error(pipex, -2, argv[1], "No such file or directory");
	// 		pipex->f_cmd_status = -1;
			
	// 	}
	// if (pipex->f_cmd_status != -1)
	// 	v_error(pipex, dup2(pipex->fd_input, STDIN_FILENO), "dup2", NULL);
	// }
	while (pipex->i < pipex->pipe_counter)
	{
		child_first_cmd(pipex, argv, envp, tempo);
		pipex->i++;
	}
	if (pipex->i == pipex->pipe_counter)
		child_last_cmd(pipex, argv, envp, tempo);
	while (i > 0)
	{
		ret_pid = waitpid(-1, &status, 0);
		if (ret_pid == -1)
		{
			if (errno == EINTR)
				continue ;
			else
				break ;
		}
		else if (ret_pid > 0)
		{
			if (WIFEXITED(status))
				exit_status = WEXITSTATUS(status);
		}
			i--;
	}
	exit (exit_status);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	pipex.argc = argc;
	parsing(&pipex);
	init_value(&pipex, argv);
	get_env(&pipex, envp);
	sep_path(&pipex, envp);
	one(&pipex, envp, argv);
}
