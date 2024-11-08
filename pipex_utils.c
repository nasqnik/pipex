/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikitin <anikitin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:25:38 by anikitin          #+#    #+#             */
/*   Updated: 2024/10/30 12:18:05 by anikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_file(char *filepath, char mode, t_info *info)
{
	int	fd;

	fd = 0;
	if (mode == 'R' && access(filepath, R_OK) == -1)
		file_error(filepath, info);
	if (mode == 'R')
		fd = open(filepath, O_RDONLY);
	else if (mode == 'W')
		fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (mode == 'A')
		fd = open(filepath, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
		file_error(filepath, info);
	return (fd);
}

char	*find_path(char **command_array, char **env)
{
	char	**all_paths;
	char	*command_path;
	char	*tmp;
	int		i;

	all_paths = ft_split(ft_getenv("PATH", env), ':');
	if (!all_paths)
		return (NULL);
	i = 0;
	while (all_paths[i])
	{
		tmp = ft_strjoin(all_paths[i], "/");
		command_path = ft_strjoin(tmp, command_array[0]);
		free(tmp);
		if (access(command_path, F_OK | X_OK) == 0)
		{
			free_array(all_paths);
			return (command_path);
		}
		free(command_path);
		i++;
	}
	free_array(all_paths);
	return (NULL);
}

char	*ft_getenv(char *key, char **env)
{
	int	i;
	int	key_length;

	i = 0;
	key_length = ft_strlen(key);
	while (env[i])
	{
		if (ft_strncmp(env[i], key, key_length) == 0
			&& env[i][key_length] == '=')
			return (env[i] + key_length + 1);
		i++;
	}
	return (NULL);
}

void	handle_dup2(t_info *info, int input_fd, int output_fd)
{
	if (input_fd != -1)
	{
		if (dup2(input_fd, STDIN_FILENO) == -1)
			function_error("dup2 failed in handle_dup2", info);
		close(input_fd);
	}
	if (output_fd != -1)
	{
		if (dup2(output_fd, STDOUT_FILENO) == -1)
			function_error("dup2 failed in handle_dup2", info);
		close(output_fd);
	}
}

void	error_cleanup(t_info *info)
{
	free(info->pid_array);
	close_unused_pipes(info);
	close(info->pipefd[info->process_counter][0]);
	close(info->pipefd[info->process_counter][1]);
	if (info->process_counter > 0)
		close(info->pipefd[info->process_counter - 1][0]);
	free_pipefd_array(info);
}
