/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_preprocessing.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikitin <anikitin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 10:47:15 by anikitin          #+#    #+#             */
/*   Updated: 2024/10/30 11:14:55 by anikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

t_info	fill_the_struct(int argc, char **argv, char **env)
{
	t_info	str;
	int		counter;

	if (ft_strcmp(argv[1], "here_doc") == 0)
		str.i = 3;
	else
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

void	preprocessing(t_info *info)
{
	if (ft_strcmp(info->argv[1], "here_doc") == 0)
		handle_here_doc(info);
	else
		handle_files(info, 1);
}

void	handle_here_doc(t_info *info)
{
	char	*buffer;
	int		file;

	file = open_file(".heredoc_tmp", 'W', info);
	while (1)
	{
		write(1, "heredoc> ", 9);
		buffer = get_next_line(0);
		if (ft_strncmp(info->argv[2], buffer, ft_strlen(info->argv[2])) == 0)
			break ;
		ft_putstr_fd(buffer, file);
		free(buffer);
	}
	free(buffer);
	close(file);
	info->file1 = open_file(".heredoc_tmp", 'R', info);
	handle_dup2(info, info->file1, -1);
	unlink(".heredoc_tmp");
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
		if (ft_strcmp(info->argv[1], "here_doc") == 0)
			info->file2 = open_file(info->argv[info->argc - 1], 'A', info);
		else
			info->file2 = open_file(info->argv[info->argc - 1], 'W', info);
		handle_dup2(info, -1, info->file2);
	}
}
