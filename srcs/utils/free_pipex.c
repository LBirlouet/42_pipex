/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 14:47:59 by lbirloue          #+#    #+#             */
/*   Updated: 2024/02/20 12:38:27 by lbirloue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

void	v_error(t_pipex *pipex, int ret, char *err, char *err2)
{
	if (ret == -1)
	{
		write(2,"pipex: ", 7);
		if (err)
			write(2, err, ft_strlen(err));
		if (err2)
			write(2,": ", 2);
			write(2, err2, ft_strlen(err2));
		write (2, "\n", 1);
		free_all(pipex, -1);
	}
	return ;
}

void	free_all(t_pipex *pipex, int status)
{
	int	i;

	i = 0;
	while (pipex->cmd_split && pipex->cmd_split[i])
		free(pipex->cmd_split[i++]);
	i = 0;
	if (pipex->cmd_split)
		free(pipex->cmd_split);
	while (pipex->path_list && pipex->path_list[i])
		free(pipex->path_list[i++]);
	if (pipex->path_list)
		free(pipex->path_list);
	if (pipex->path_cmd)
		free(pipex->path_cmd);
	if (status == -1)
		exit(EXIT_FAILURE);
	else if (status == 0)
		exit (EXIT_SUCCESS);
}
