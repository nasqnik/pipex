/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikitin <anikitin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:03:18 by anikitin          #+#    #+#             */
/*   Updated: 2024/10/30 11:15:04 by anikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	**initialize_pipefd(int counter, t_info *info)
{
	int	**pipefd;
	int	j;
	int	k;

	j = 0;
	pipefd = ft_calloc(counter, sizeof(int *));
	if (!pipefd)
		function_error("calloc failed in initialize_pipefd", info);
	while (j < counter)
	{
		pipefd[j] = ft_calloc(2, sizeof(int));
		if (!pipefd[j])
		{
			k = 0;
			while (k < j)
			{
				free(pipefd[k]);
				k++;
			}
			free(pipefd);
			function_error("calloc failed in initialize_pipefd", info);
		}
		j++;
	}
	return (pipefd);
}

void	open_pipes(t_info *info)
{
	int	counter;
	int	j;

	j = 0;
	counter = info->argc - info->i - 1;
	while (j < counter)
	{
		if (pipe(info->pipefd[j]) == -1)
			function_error("pipe failed in open_pipes", info);
		j++;
	}
}

void	close_unused_pipes(t_info *info)
{
	int	i;

	i = info->process_counter + 1;
	while (i < info->pipe_num)
	{
		if (info->pipefd[i][0] != '\0')
			close(info->pipefd[i][0]);
		if (info->pipefd[i][1] != '\0')
			close(info->pipefd[i][1]);
		i++;
	}
	if (info->pipefd[info->process_counter][0] != '\0')
		close(info->pipefd[info->process_counter][0]);
	if (info->i == info->argc - 2
		&& info->pipefd[info->process_counter][1] != '\0')
		close(info->pipefd[info->process_counter][1]);
}
