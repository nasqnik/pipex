/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikitin <anikitin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:25:52 by anikitin          #+#    #+#             */
/*   Updated: 2024/10/30 12:13:56 by anikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex_error(void)
{
	ft_printf("Incorrect amount of arguments\n");
	ft_printf("The correct usage: ");
	ft_printf("./pipex file1 cmd1 cmd2 file2\n");
	exit(EXIT_FAILURE);
}

void	function_error(char *message, t_info *info)
{
	perror(message);
	error_cleanup(info);
	if (info->i == info->argc - 2)
		exit(127);
	exit(EXIT_SUCCESS);
}

void	empty_cmd_error(char *cmd, t_info *info)
{
	if (ft_strcmp(cmd, "") == 0)
	{
		error_cleanup(info);
		ft_printf("pipex: : command not found\n");
		if (info->i == info->argc - 2)
			exit(127);
		exit(EXIT_SUCCESS);
	}
}

void	exec_error(char *path, char **array, char *msg, t_info *info)
{
	if (path)
		free(path);
	if (array)
		free_array(array);
	function_error(msg, info);
}

void	file_error(char *filepath, t_info *info)
{
	ft_printf("pipex: %s: ", filepath);
	perror("");
	error_cleanup(info);
	exit(EXIT_SUCCESS);
}
