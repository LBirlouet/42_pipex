/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:00:28 by lbirloue          #+#    #+#             */
/*   Updated: 2024/02/13 09:58:48 by lbirloue         ###   ########.fr       */
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
	// pipex->pipe = malloc(sizeof(int) * pipex->pipe_counter * 2);
	// int i = 0;
	// while (i < pipex->pipe_counter * 2)
	// 	pipex->pipe[i++] = 0;
	// i = 0;
	// pipex->pipe_verif = malloc(sizeof(int) * pipex->pipe_counter * 2);
	// while (i < pipex->pipe_counter * 2)
	// 	pipex->pipe_verif[i++] = 0;
	
	return (0);
}
// void	parent(t_pipex *pipex)
// {
// 	v_error(pipex, close(pipex->pipefd[0]));
// 	v_error(pipex, close(pipex->pipefd[1]));
// 	v_error(pipex, waitpid(pipex->cpid1, &pipex->pipefd[0], 0));
// 	v_error(pipex, waitpid(pipex->cpid2, &pipex->pipefd[0], 0));
// 	free_all(pipex, 0);
// }

// void	close_pipe(t_pipex *pipex)
// {
// 	int z = 0;
// 	while (z < pipex->pipe_counter)
// 	{
// 		if (pipex->pipe_verif[z] != -1)
// 		{
// 			close(pipex->pipe[z]);
// 			pipex->pipe_verif[z] = -1;
// 		}
// 		z++;
// 	}
// 	return ;
// }
void	refresh_pipe(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
	pipe(fd);
	return ;
}

void	one(t_pipex *pipex, char **envp, char **argv, int argc)
{
	char *tempo = NULL;

	printf("(1)\n");
	pipex->cmd_split = ft_split(argv[pipex->i + 2], ' ');
	pipex->path_cmd = get_good_path(pipex, 0, tempo, pipex->cmd_split);
	
	if (pipex->i == 0)	// FIRST
	{
		printf("|%d|FIRST\n", pipex->i);
		
		close (pipex->first_pipe[0]);
		close (pipex->sec_pipe[0]);
		close (pipex->sec_pipe[1]);
		pipex->fd_input = open(argv[1], O_RDONLY | O_CLOEXEC);
		if (pipex->fd_input == -1)
		{
			printf("open pb\n");
			free_all(pipex, -1);
		}
		v_error(pipex, dup2(pipex->fd_input, STDIN_FILENO),"dup2");
		v_error(pipex, close (pipex->fd_input), "close :");
		v_error(pipex, dup2(pipex->first_pipe[1], STDOUT_FILENO), "dup222");

		v_error(pipex, close (pipex->first_pipe[1]), "close :");
		pipex->fd_input = -1;
	}
	else if (pipex->i != pipex->pipe_counter)		// MID
	{
		
		printf("|%d|MID ?\n", pipex->i);
		if ((pipex->i % 2) == 0) 
		{
			refresh_pipe(pipex->first_pipe);
			v_error(pipex, dup2(pipex->first_pipe[0], STDIN_FILENO), "dup222");
			v_error(pipex, dup2(pipex->sec_pipe[1], STDOUT_FILENO), "dupicippppppppppppp2");

		}
		else if ((pipex->i % 2) == 1) 
		{
			refresh_pipe(pipex->sec_pipe);
			v_error(pipex, dup2(pipex->sec_pipe[0], STDIN_FILENO ), "dup222");
			v_error(pipex, dup2(pipex->first_pipe[1], STDOUT_FILENO), "dupicipppbloulouiii2");
		}

		close(pipex->first_pipe[0]);
		close(pipex->first_pipe[1]);
		close(pipex->sec_pipe[0]);
		close(pipex->sec_pipe[1]);
	}
	else		// FIN
	{
		printf("|%d|FIN ?\n", pipex->i);
		close (pipex->first_pipe[1]);
		close (pipex->sec_pipe[1]);
		if ((pipex->i % 2) == 0)
			v_error(pipex, dup2(pipex->first_pipe[0], STDIN_FILENO), "duppp2");
		else
			v_error(pipex, dup2(pipex->first_pipe[0], STDIN_FILENO), "duppp2");
		close (pipex->first_pipe[0]);
		close (pipex->sec_pipe[0]);
		pipex->fd_output = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CLOEXEC | O_CREAT, 0644);
		v_error(pipex, dup2(pipex->fd_output, STDOUT_FILENO), "dupp2");
		v_error(pipex, close (pipex->fd_output), "clloosssse");
	}
	v_error(pipex, execve(pipex->path_cmd, &pipex->cmd_split[0], envp), "execve :");
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	char *tempo = NULL;

	pipex.argc = argc;
	parsing(&pipex);
	init_value(&pipex, argv);
	get_env(&pipex, envp);
	sep_path(&pipex, envp);	
	int i = 0;
	pipex.i = -1;
	// printf("AHHHH %d\n", pipex.pipe_counter);
	while (i < pipex.pipe_counter + 1)
	{
		++pipex.i;
		pipex.cpid = fork();
		if (pipex.cpid == 0)
		{
			printf("|%d| != |%d|\n", i, pipex.pipe_counter + 1);
			one(&pipex, envp, argv, argc);
			exit (0);
		}
		// else if (pipex.cpid > 0)
		// 	waitpid(pipex.cpid, 0, 0);
		// {
		// 	waitpid(pipex.cpid, &pipex.pipe[i], 0);
		// 	waitpid(pipex.cpid, &pipex.pipe[i + 1], 0);
		// }
		i++;
	}
	return (0);
}