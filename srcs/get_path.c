/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 12:08:57 by lbirloue          #+#    #+#             */
/*   Updated: 2024/02/12 14:28:11 by lbirloue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	get_env(t_pipex *pipex, char **envp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (*envp[i])
	{
		j = 0;
		if (envp[i][j] == 0)
			free_all(pipex, -1);
		if (envp[i][j] == 'P' && envp[i][j + 1] == 'A'
			&& envp[i][j + 2] == 'T' && envp[i][j + 3] == 'H'
			&& envp[i][j + 4] == '=')
		{
			pipex->envline = i;
			return ;
		}
		i++;
	}
	free_all(pipex, -1);
}

void	sep_path(t_pipex *pipex, char **envp)
{
	int	i;

	pipex->path_counter = 1;
	i = 0;
	while (envp[pipex->envline][i])
	{
		if (envp[pipex->envline][i] == ':')
			pipex->path_counter++;
		i++;
	}
	pipex->path_list = ft_split(envp[pipex->envline] + 5, ':');
	if (!pipex->path_list)
		free_all(pipex, -1);
	return ;
}

char	*get_good_path(t_pipex *pipex, int i, char *tempo, char **cmd_split)
{
	char *ret;
	while (i < pipex->path_counter)
	{
		tempo = ft_strjoin(pipex->path_list[i], "/");
		if (!tempo)
			free_all(pipex, -1);
		ret = ft_strjoin(tempo, cmd_split[0]);
		if (!ret)
		{
			free(tempo);
			free_all(pipex, -1);
		}
		free(tempo);
		tempo = NULL;
		if (access(ret, X_OK) == 0)
			break ;
		else
		{
			free(ret);
			ret = NULL;
		}
		if ((i + 1) == pipex->path_counter)
		{
			printf("SEG ?\n");	
			free_all(pipex, -1);
		}
		i++;
	}
	return (ret);
}