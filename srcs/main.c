/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbirloue <lbirloue@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:00:28 by lbirloue          #+#    #+#             */
/*   Updated: 2024/02/20 07:41:29 by lbirloue         ###   ########.fr       */
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

void	refresh_pipe(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
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
	v_error(pipex, execve(pipex->path_cmd, &pipex->cmd_split[0], envp), "execve :");
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
int j = pipex.pipe_counter ;
	while (i < pipex.pipe_counter + 1)
	{
		++pipex.i;
		pipex.cpid = fork();
		if (pipex.cpid == 0)
		{
			one(&pipex, envp, argv, argc);
			//exit (0);
		}
		i++;
	}
	int test;
	int status;
	while (j > 0)
	{
		test = waitpid(-1, &status, 0);
		if (test == -1)
		{
			if (errno == EINTR)
				continue ;
			free_all(&pipex, -1);
		}
		if (test > 0)
		{
			if (WIFEXITED(status))
				WEXITSTATUS(status);
			j--;
		}
	}

    // int status;
    // pid_t pid;
    // while ((pid = waitpid(-1, &status, 0)) > 0)
    // {
    //     // if (WIFEXITED(status))
    //     // {
    //     //     printf("Process with PID %d exited with status %d\n", pid, WEXITSTATUS(status));
    //     // }
    //     // else if (WIFSIGNALED(status))
    //     // {
    //     //     printf("Process with PID %d terminated by signal %d\n", pid, WTERMSIG(status));
    //     // }
    // }

    // if (pid == -1 && errno != ECHILD)
    // {
    //     perror("waitpid failed");
    //     free_all(&pipex, -1);
    // }

	return (0);
}
