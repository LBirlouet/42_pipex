/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:00:28 by lbirloue          #+#    #+#             */
/*   Updated: 2024/03/01 11:24:25 by lbirloue         ###   ########.fr       */
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


void	one(t_pipex *pipex, char **envp, char **argv)
{
	char	*tempo;
	pipex->fd_input = 0;
	int i;
	
	i = pipex->pipe_counter + 1;
	tempo = NULL;
	while (pipex->i < pipex->pipe_counter)
	{
		child_cmd(pipex, argv, envp, tempo);
		pipex->i++;
	}
	if (pipex->i == pipex->pipe_counter)
		child_last_cmd(pipex, argv, envp, tempo);
	wpid(pipex, i);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	pipex.argc = argc;
	if (argc < 5)
		v_error(&pipex, -1, "not enough arguments", NULL);
	init_value(&pipex, argv);
	get_env(&pipex, envp);
	sep_path(&pipex, envp);
	one(&pipex, envp, argv);
}
