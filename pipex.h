/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikitin <anikitin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:26:14 by anikitin          #+#    #+#             */
/*   Updated: 2024/10/30 12:14:27 by anikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include "ft_printf/ft_printf.h"

# include <unistd.h> // access
# include <stdio.h> // perror
# include <fcntl.h> // open
# include <string.h> // strerror
# include <errno.h> 
# include <sys/types.h>
# include <sys/wait.h>

typedef struct info_p
{
	int		file1;
	int		file2;
	int		*pid_array;
	int		pipe_num;
	int		**pipefd;
	int		argc;
	char	**argv;
	char	**env;
	int		i;
	int		process_counter;
}	t_info;

// pipex_preprocessing.c
t_info	fill_the_struct(int argc, char **argv, char **env);
void	handle_files(t_info *info, int flag);

// pipex_bonus_pipes.c
int		**initialize_pipefd(int counter, t_info *info);
void	open_pipes(t_info *info);
void	close_unused_pipes(t_info *info);

// pipex_bonus_execute.c
void	execute(char *command, t_info *info);
void	free_array(char **array);
void	free_pipefd_array(t_info *info);
int		wait_children(t_info *info);

// pipex_utils.c
int		open_file(char *filepath, char mode, t_info *info);
char	*find_path(char **command_array, char **env);
char	*ft_getenv(char *key, char **env);
void	handle_dup2(t_info *info, int input_fd, int output_fd);
void	error_cleanup(t_info *info);

// pipex_errors.c
void	function_error(char *message, t_info *info);
void	empty_cmd_error(char *cmd, t_info *info);
void	exec_error(char *path, char **array, char *msg, t_info *info);
void	pipex_error(void);
void	file_error(char *filepath, t_info *info);

#endif