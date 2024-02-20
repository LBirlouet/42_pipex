/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:00:28 by lbirloue          #+#    #+#             */
/*   Updated: 2024/02/20 13:04:25 by lbirloue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	init_value(t_pipex *pipex, char **argv)
{
	(void)argv;
	pipex->cmd_counter = pipex->argc - 3;
	pipex->pipe_counter = pipex->cmd_counter - 1;
	pipex->path_list = NULL;
	pipex->cmd_split = NULL;
	pipex->path_cmd = NULL;
	pipe(pipex->first_pipe);
	pipe(pipex->sec_pipe);
	return (0);
}

void	refresh_pipe(t_pipex *pipex, int fd[2])
{
	v_error(pipex, close(fd[0]), "close :", NULL);
	v_error(pipex, close(fd[1]), "close :", NULL);
	pipe(fd);
	return ;
}

void	one(t_pipex *pipex, char **envp, char **argv, int argc)
{
	char *tempo;

	tempo = NULL;
	pipex->cmd_split = ft_split(argv[pipex->i + 2], ' ');
	pipex->path_cmd = get_good_path(pipex, 0, tempo, pipex->cmd_split);
	if (pipex->i == 0)
		child_first_cmd(pipex, argv);
	else if (pipex->i != pipex->pipe_counter)
		child_mid_cmd(pipex);
	else
		child_last_cmd(pipex, argv, argc);
	v_error(pipex, execve(pipex->path_cmd, &pipex->cmd_split[0], envp), "execve :", NULL);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	pipex.argc = argc;
	parsing(&pipex);
	init_value(&pipex, argv);
	get_env(&pipex, envp);
	sep_path(&pipex, envp);
	int i = 0;
	pipex.i = -1;
int j = pipex.pipe_counter + 1;
	while (i < pipex.pipe_counter + 1)
	{
		++pipex.i;
		pipex.cpid= fork();
		if (pipex.cpid == 0)
			one(&pipex, envp, argv, argc);
			i++;
	}
	close(pipex.first_pipe[0]);
	close(pipex.first_pipe[1]);
	close(pipex.sec_pipe[0]);
	close(pipex.sec_pipe[1]);
	int test;
	pid_t status;
	while (j > 0)
	{
		test = waitpid(-1, &status, WNOHANG);
		if (test == -1)
		{
			if (errno == EINTR)
				continue ;
			else
				free_all(&pipex, -1);
		}
		else if (test > 0)
		{
			if (WIFEXITED(status))
				WEXITSTATUS(status);
			j--;
		}
	}
	return (0);
}
