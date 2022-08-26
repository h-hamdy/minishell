/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouanan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 17:08:33 by fbouanan          #+#    #+#             */
/*   Updated: 2022/08/22 17:08:37 by fbouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

pid_t	ft_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		printf("Error while trying to fork.");
	return (pid);
}

void infile_procces(t_list *pipeline, int i)
{
	int	infile;

	infile = open(((t_cmd*)pipeline->content)->red[i], O_RDONLY);
	if (infile < 0)
	{
		printf("minishell : no such file or directory: %s \n", ((t_cmd*)pipeline->content)->red[i]);
		exit (0);
	}
	((t_cmd*)pipeline->content)->in = infile;
	
}

void	outfile_procces(t_list *pipeline, int i)
{
	int	outfile;

	outfile = open(((t_cmd*)pipeline->content)->red[i], O_RDWR | O_CREAT, 0777);
	if (outfile < 0)
	{
		printf("Error while trying to open the outfile.\n");
		exit (0);
	}

	((t_cmd*)pipeline->content)->out = outfile;
	
}

void	append_hand(t_list *pipeline, int i)
{
	int	outfile;

	outfile = open(((t_cmd*)pipeline->content)->red[i], O_WRONLY | O_CREAT | O_APPEND, 0777);
	fprintf(stderr, "----> %d\n", outfile);
	if (outfile < 0)
	{
		printf("Error while trying to open the outfile.\n");
		exit (0);
	}
	((t_cmd*)pipeline->content)->out = outfile;
	
}

void	exec_child(int *fd, t_list *pipeline)
{
	// (void)fd;
	if (((t_cmd*)pipeline->content)->in != 0)
	{
		dup2(((t_cmd*)pipeline->content)->in, 0);
		close(((t_cmd*)pipeline->content)->in);
	}
	if (((t_cmd*)pipeline->content)->out != 0)
	{
		dup2(((t_cmd*)pipeline->content)->out, 1);
		close(((t_cmd*)pipeline->content)->out);
	}
	close(fd[0]);
	close(fd[1]);
	if(execve(((t_cmd*)pipeline->content)->cmd_path, ((t_cmd*)pipeline->content)->arg, g_v.envp))
		printf("minishell : no such file or directory: %s\n", ((t_cmd*)pipeline->content)->arg[0]);
	exit (1);
}

void    other_cmd(t_list *pipeline, int *fd)
{
	int		i;
	// int		fd[2];
	pid_t	pid;
	
	// (void)fd;
	i = 0;
													// if thete is no pipes
	if (g_v.n_node == 1)
	{
		if (!((t_cmd*)pipeline->content)->arg)
		{
			close(fd[0]);
			close(fd[1]);
			return ;
		}
		if (c_builtins(((t_cmd*)pipeline->content)->arg[0]))
		{
			builtins(pipeline);
			return ;
		}
		else
		{
			pid = fork();
			if (pid == 0)
			{
				open_files(pipeline, fd);
				if (!((t_cmd*)pipeline->content)->arg)
				{
					close(fd[0]);
					close(fd[1]);
					exit (0) ;
				}
				if (!((t_cmd*)pipeline->content)->type)
				{
					if(execve(((t_cmd*)pipeline->content)->cmd_path, ((t_cmd*)pipeline->content)->arg, g_v.envp))
					{
						printf("minishell: %s: command not found\n", ((t_cmd*)pipeline->content)->arg[0]);
						exit (0) ;
					}
				}
				exec_child(fd, pipeline);
			}
		}
	}
													// if there is pipes
	else
	{
		// if (pipe(fd) == -1)
		// {
		// 	printf("pipe failed\n");
		// 	exit (1);
		// }

		pid = fork();
		if (pid == 0)
		{
			close(fd[0]);
			open_files(pipeline, fd);
			if (!((t_cmd*)pipeline->content)->arg)
			{
				close(fd[0]);
				close(fd[1]);
				exit (0) ;
			}
			if (pipeline->next != NULL)
				dup2(fd[1], 1);
			if (c_builtins(((t_cmd*)pipeline->content)->arg[0]))
			{
				builtins(pipeline);
				exit (0);
			}
			if (!((t_cmd*)pipeline->content)->type)
			{
				if(execve(((t_cmd*)pipeline->content)->cmd_path, ((t_cmd*)pipeline->content)->arg, g_v.envp))
				{
					printf("minishell: %s: command not found\n", ((t_cmd*)pipeline->content)->arg[0]);
					exit (0) ;
				}
			}
			exec_child(fd, pipeline);
		}
	}
	// close(fd[0]);
	if (((t_cmd*)pipeline->content)->out != 0)
			close(((t_cmd*)pipeline->content)->out);
	
}
