/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:00:28 by lbirloue          #+#    #+#             */
/*   Updated: 2024/03/05 08:38:39 by lbirloue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	init_value(t_pipex *pipex)
{
	pipex->i = 0;
	pipex->exit_s = 0;
	pipex->f_cmd_status = 0;
	pipex->fd_input = 0;
	pipex->cmd_counter = pipex->argc - 3;
	pipex->pipe_counter = pipex->cmd_counter - 1;
	pipex->path_list = NULL;
	pipex->cmd_split = NULL;
	pipex->path_cmd = NULL;
	return (0);
}

void	ppx(t_pipex *pipex, char **envp, char **argv)
{
	int	i;

	i = pipex->pipe_counter + 1;
	while (pipex->i < pipex->pipe_counter)
	{
		child_cmd(pipex, argv, envp);
		pipex->i++;
	}
	if (pipex->i == pipex->pipe_counter)
		child_last_cmd(pipex, argv, envp);
	free_all(pipex, 1);
	wpid(pipex, i);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	pipex.argc = argc;
	if (argc < 5)
		v_error(&pipex, -1, "not enough arguments", NULL);
	init_value(&pipex);
	get_env(&pipex, envp);
	sep_path(&pipex, envp);
	ppx(&pipex, envp, argv);
}
