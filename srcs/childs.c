/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:10:16 by lbirloue          #+#    #+#             */
/*   Updated: 2024/02/27 11:58:55 by lbirloue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	child_first_cmd(t_pipex *pipex, char **argv, char **envp, char *tempo)
{
	pid_t	pid;

	pipex->cmd_split = ft_split(argv[pipex->i + 2], ' ');
	pipex->path_cmd = get_good_path(pipex, 0, tempo, pipex->cmd_split, argv);
	pipe(pipex->pipe_fds);
	pid = fork();
	if (pid == 0)
	{
		v_error(pipex, dup2(pipex->prev_pipe, STDIN_FILENO), "uiski", NULL);
		v_error(pipex, dup2(pipex->pipe_fds[1], STDOUT_FILENO), "dup2", NULL);
		v_error(pipex, execve(pipex->path_cmd, &pipex->cmd_split[0], envp),
			"execve :", NULL);
		pipex->fd_input = -1;
	}
	else
	{
		pipex->prev_pipe = pipex->pipe_fds[0];
		waitpid(-1, &pid, WNOHANG);
		v_error(pipex, close(pipex->pipe_fds[1]), "close :", NULL);
	}
	return ;
}

void	child_last_cmd(t_pipex *pipex, char **argv, char **envp, char *tempo)
{
	pid_t	pid;

	pipex->cmd_split = ft_split(argv[pipex->i + 2], ' ');
	pipex->path_cmd = get_good_path(pipex, 0, tempo, pipex->cmd_split, argv);
	pipex->fd_output = open(argv[pipex->argc - 1],
			O_CREAT | O_RDWR | O_TRUNC | O_CLOEXEC, 0644);
	if (pipex->fd_output == -1)
	{
		v_error(pipex, -1, argv[1], "No such file or directory");
		free_all(pipex, -1);
	}
	pid = fork();
	if (pid == 0)
	{
		v_error(pipex, dup2(pipex->prev_pipe, STDIN_FILENO), "dup2", NULL);
		v_error(pipex, dup2(pipex->fd_output, STDOUT_FILENO), "dup2", NULL);
		v_error(pipex, execve(pipex->path_cmd, &pipex->cmd_split[0], envp),
			"execve :", NULL);
		pipex->fd_output = -1;
	}
		waitpid(-1, &pid, WNOHANG);

	return ;
}
