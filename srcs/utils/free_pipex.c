/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 14:47:59 by lbirloue          #+#    #+#             */
/*   Updated: 2024/02/12 08:11:58 by lbirloue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

void	v_error(t_pipex *pipex, int ret, char *err)
{
	if (ret == -1)
	{
		write(2,"pipex : ", 8);
		write(2, err, ft_strlen(err));
		write(2, "error", 5);
		write(2,"\n", 1);
		free_all(pipex, -1);
	}
	return ;
}

void	free_all(t_pipex *pipex, int status)
{
	int	i;

	i = 0;
	(void)pipex;
	// while (pipex->cmd1_split && pipex->cmd1_split[i])
	// 	free(pipex->cmd1_split[i++]);
	// i = 0;
	// while (pipex->cmd2_split && pipex->cmd2_split[i])
	// 	free(pipex->cmd2_split[i++]);
	// if (pipex->cmd1_split)
	// 	free(pipex->cmd1_split);
	// if (pipex->cmd2_split)
	// 	free(pipex->cmd2_split);
	// while (pipex->path_list && pipex->path_list[i])
	// 	free(pipex->path_list[i++]);
	// if (pipex->path_list)
	// 	free(pipex->path_list);
	// if (pipex->path_cmd1)
	// 	free(pipex->path_cmd1);
	// if (pipex->path_cmd2)
	// 	free(pipex->path_cmd2);
	if (status == -1)
		exit(EXIT_FAILURE);
	else if (status == 0)
		exit (EXIT_SUCCESS);
}
