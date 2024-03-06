/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:10:16 by lbirloue          #+#    #+#             */
/*   Updated: 2024/03/06 10:20:38 by lbirloue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	child_cmd(t_pipex *pipex, char **av, char **envp)
{
	v_error(pipex, pipe(pipex->pipe_fds), "pipe", NULL);
	pipex->pid = fork();
	if (pipex->pid == -1)
		v_error(pipex, -1, "fork", NULL);
	if (pipex->i == 0 && pipex->f_cmd_status == -1)
		return ;
	if (pipex->pid == 0)
	{
		if (pipex->i == 0)
			first_cmd(pipex, av);
		pipex->cmd_split = ft_split(av[pipex->i + 2], ' ');
		pipex->path_cmd = get_good_path(pipex, 0, pipex->cmd_split, av);
		v_error(pipex, dup2(pipex->prev_pipe, STDIN_FILENO), "dup2", NULL);
		v_error(pipex, dup2(pipex->pipe_fds[1], STDOUT_FILENO), "dup2", NULL);
		close(pipex->pipe_fds[0]);
		v_error(pipex, execve(pipex->path_cmd, &pipex->cmd_split[0], envp),
			"execve :", NULL);
		pipex->fd_input = -1;
	}
	else
	{
		pipex->prev_pipe = pipex->pipe_fds[0];
		v_error(pipex, close(pipex->pipe_fds[1]), "close :", NULL);
	}
	return ;
}

void	child_last_cmd(t_pipex *pipex, char **argv, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pipex->pid == -1)
		v_error(pipex, -1, "fork error", NULL);
	pipex->fd_output = open(argv[pipex->argc - 1],
			O_CREAT | O_RDWR | O_TRUNC | O_CLOEXEC, 0644);
	if (pipex->fd_output == -1)
		v_error(pipex, -1, argv[1], "open");
	if (pid == 0)
	{
		pipex->cmd_split = ft_split(argv[pipex->i + 2], ' ');
		pipex->path_cmd = get_good_path(pipex, 0, pipex->cmd_split, argv);
		v_error(pipex, dup2(pipex->prev_pipe, STDIN_FILENO), "dup2", NULL);
		close(pipex->prev_pipe);
		v_error(pipex, dup2(pipex->fd_output, STDOUT_FILENO), "dup2", NULL);
		close(pipex->fd_output);
		v_error(pipex, execve(pipex->path_cmd, &pipex->cmd_split[0], envp),
			"execve :", NULL);
		pipex->fd_output = -1;
	}
	v_error(pipex, close(pipex->pipe_fds[1]), "close :", NULL);
	v_error(pipex, close(pipex->prev_pipe), "close :", NULL);
	return ;
}

void	wpid(t_pipex *pipex, int i)
{
	int	status;
	int	ret_pid;
	int	exit_status;

	while (i > 0)
	{
		ret_pid = waitpid(-1, &status, 0);
		if (ret_pid == -1)
		{
			if (errno == EINTR)
				continue ;
			else
			{
				v_error(pipex, -1, "waitpid", NULL);
			}
		}
		else if (ret_pid > 0)
		{
			if (WIFEXITED(status))
				exit_status = WEXITSTATUS(status);
			i--;
		}
	}
	exit (exit_status);
}

void	first_cmd(t_pipex *pipex, char **av)
{
	pipex->fd_input = open(av[1], O_RDONLY | O_CLOEXEC);
	if (pipex->fd_input == -1)
	{
		v_error(pipex, 127, av[1], "No such file or directory");
		pipex->f_cmd_status = -1;
		exit(1);
	}
	if (pipex->f_cmd_status != -1)
		v_error(pipex, dup2(pipex->fd_input, STDIN_FILENO), "dup2", NULL);
}
