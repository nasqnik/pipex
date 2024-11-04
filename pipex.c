/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikitin <anikitin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:26:07 by anikitin          #+#    #+#             */
/*   Updated: 2024/10/30 11:15:09 by anikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	last_process(t_info *info)
{
	int	status;
	int	pid;

	pid = fork();
	if (pid == -1)
		function_error("fork failed in last_process", info);
	else if (pid == 0)
	{
		empty_cmd_error(info->argv[info->i], info);
		handle_files(info, 2);
		handle_dup2(info, info->pipefd[info->process_counter - 1][0], -1);
		close_unused_pipes(info);
		execute(info->argv[info->argc - 2], info);
	}
	close(info->pipefd[info->process_counter - 1][0]);
	close(info->pipefd[info->process_counter][0]);
	close(info->pipefd[info->process_counter][1]);
	info->pid_array[info->process_counter++] = pid;
	status = wait_children(info);
	return (status);
}

void	first_process(t_info *info)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		function_error("fork failed in first_process", info);
	else if (pid == 0)
	{
		handle_files(info, 1);
		empty_cmd_error(info->argv[info->i], info);
		handle_dup2(info, -1, info->pipefd[0][1]);
		close_unused_pipes(info);
		execute(info->argv[info->i], info);
	}
	close(info->pipefd[0][1]);
	info->i++;
	info->pid_array[info->process_counter++] = pid;
}

int	main(int argc, char **argv, char **env)
{
	t_info	info;
	int		status;

	if (argc > 5 || argc < 5)
		pipex_error();
	info = fill_the_struct(argc, argv, env);
	open_pipes(&info);
	first_process(&info);
	status = last_process(&info);
	free(info.pid_array);
	free_pipefd_array(&info);
	return (WEXITSTATUS(status));
}
