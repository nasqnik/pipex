/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikitin <anikitin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:05:23 by anikitin          #+#    #+#             */
/*   Updated: 2024/10/30 11:15:02 by anikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute(char *command, t_info *info)
{
	char	**command_array;
	char	*command_path;

	if (command[0] != '/')
	{
		command_array = ft_split(command, ' ');
		if (!command_array)
			function_error("split failed in execute", info);
		command_path = find_path(command_array, info->env);
	}
	else
	{
		command_array = malloc(2 * sizeof(char *));
		command_path = ft_strdup(command);
		command_array[0] = ft_strdup(command);
		command_array[1] = NULL;
	}
	if (!command_path || access(command_path, X_OK) == -1)
		exec_error(command_path, command_array,
			"pipex: command not found", info);
	if (execve(command_path, command_array, info->env) == -1)
		exec_error(command_path, command_array,
			"execve failed in execute", info);
}

void	free_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}

void	free_pipefd_array(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->pipe_num)
	{
		free(info->pipefd[i]);
		i++;
	}
	free(info->pipefd);
}

int	wait_children(t_info *info)
{
	int	status;
	int	k;

	k = 0;
	while (k < info->process_counter)
	{
		if (waitpid(info->pid_array[k], &status, 0) == -1)
			function_error("waitpid failed in wait_children", info);
		k++;
	}
	return (status);
}
