/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_errors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikitin <anikitin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 18:47:29 by anikitin          #+#    #+#             */
/*   Updated: 2024/10/30 12:16:58 by anikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	pipex_error(int flag)
{
	ft_printf("Incorrect amount of arguments\n");
	ft_printf("The correct usage: ");
	if (flag == 0)
		ft_printf("./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2\n");
	else
		ft_printf("./pipex here_doc LIMITER cmd cmd1 file\n");
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
	if ((ft_strcmp(info->argv[1], "here_doc") == 0))
		unlink(".heredoc_tmp");
	error_cleanup(info);
	exit(EXIT_SUCCESS);
}
