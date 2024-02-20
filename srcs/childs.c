/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:10:16 by lbirloue          #+#    #+#             */
/*   Updated: 2024/02/20 12:06:52 by lbirloue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	child_first_cmd(t_pipex *pipex, char **argv)
{
	close(pipex->first_pipe[0]);
	close(pipex->sec_pipe[0]);
	close(pipex->sec_pipe[1]);
	pipex->fd_input = open(argv[1], O_RDONLY | O_CLOEXEC);
	if (pipex->fd_input == -1)
	{
		v_error(pipex, -1, argv[1], "No such file or directory");
		free_all(pipex, -1);
	}
	v_error(pipex, dup2(pipex->fd_input, STDIN_FILENO), "dup2", NULL);
	v_error(pipex, close(pipex->fd_input), "close :", NULL);
	v_error(pipex, dup2(pipex->first_pipe[1], STDOUT_FILENO), "dup2", NULL);
	v_error(pipex, close(pipex->first_pipe[1]), "close :", NULL);
	pipex->fd_input = -1;
	return ;
}

void	child_mid_cmd(t_pipex *pipex)
{
	if ((pipex->i % 2) == 0)
	{
		refresh_pipe(pipex->first_pipe);
		v_error(pipex, dup2(pipex->first_pipe[0], STDIN_FILENO), "dup2", NULL);
		v_error(pipex, dup2(pipex->sec_pipe[1], STDOUT_FILENO),
			"dup2", NULL);
	}
	else if ((pipex->i % 2) == 1)
	{
		refresh_pipe(pipex->sec_pipe);
		v_error(pipex, dup2(pipex->sec_pipe[0], STDIN_FILENO), "dup2", NULL);
		v_error(pipex, dup2(pipex->first_pipe[1], STDOUT_FILENO),
			"dup2", NULL);
	}
	close(pipex->first_pipe[0]);
	close(pipex->first_pipe[1]);
	close(pipex->sec_pipe[0]);
	close(pipex->sec_pipe[1]);
	return ;
}

void	child_last_cmd(t_pipex *pipex, char **argv, int argc)
{
	close(pipex->first_pipe[1]);
	close(pipex->sec_pipe[1]);
	if ((pipex->i % 2) == 0)
		v_error(pipex, dup2(pipex->first_pipe[0], STDIN_FILENO), "dup2", NULL);
	else
		v_error(pipex, dup2(pipex->first_pipe[0], STDIN_FILENO), "dup2", NULL);
	close(pipex->first_pipe[0]);
	close(pipex->sec_pipe[0]);
	pipex->fd_output = open(argv[argc - 1],
			O_WRONLY | O_TRUNC | O_CLOEXEC | O_CREAT, 0644);
	v_error(pipex, dup2(pipex->fd_output, STDOUT_FILENO), "dup2", NULL);
	v_error(pipex, close(pipex->fd_output), "close", NULL);
	return ;
}
