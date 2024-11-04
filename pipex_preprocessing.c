/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_preprocessing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikitin <anikitin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 10:47:15 by anikitin          #+#    #+#             */
/*   Updated: 2024/10/30 11:15:05 by anikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_info	fill_the_struct(int argc, char **argv, char **env)
{
	t_info	str;
	int		counter;

	str.i = 2;
	counter = argc - str.i;
	str.pid_array = ft_calloc(counter, sizeof(int));
	if (!str.pid_array)
		function_error("calloc failed in fill_the_struct", &str);
	str.pipe_num = counter - 1;
	str.pipefd = initialize_pipefd(str.pipe_num, &str);
	str.argc = argc;
	str.argv = argv;
	str.env = env;
	str.file1 = 0;
	str.file2 = 0;
	str.process_counter = 0;
	return (str);
}

void	handle_files(t_info *info, int flag)
{
	if (flag == 1)
	{
		info->file1 = open_file(info->argv[1], 'R', info);
		handle_dup2(info, info->file1, -1);
	}
	else if (flag == 2)
	{
		info->file2 = open_file(info->argv[info->argc - 1], 'W', info);
		handle_dup2(info, -1, info->file2);
	}
}
