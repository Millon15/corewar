/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/02 16:39:40 by ndidenko          #+#    #+#             */
/*   Updated: 2018/10/17 20:01:35 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "libft/libft.h"
# include "op.h"
# include <stdio.h>

typedef struct			s_label
{
	char				*name;
	struct s_label		*next;
}						t_label;

typedef struct			s_arg
{
	int					binary;
	int					size;
	unsigned int		value;
	char				*name_label;
	struct s_arg		*next;
}						t_arg;

typedef struct			s_command
{
	char				*name;
	int					codage;
	int					count_args;
	int					label_size;
	int					args[3];
	int					opcode;
	t_label				*labels;
	int					number_byte;
	t_arg				*inst;
	struct s_command	*next;
}						t_command;

typedef struct			s_champ
{
	char				*name;
	char				*comment;
	char				*line;
	int					fd;
	int					count[3];
	t_command			*cmds;
	struct s_champ		*next;
}						t_champ;

t_command				g_operations[17];

char					*ft_strstr_d(char *str, char *to_find);
void					ft_putstr_d(char const *s);
char					*ft_strjoin_n(char *line, char *line2, int flag);
char					*ft_strdup_d(const char *string, char d);
void					ft_name(t_champ	**main_struct);
void					ft_comment(t_champ	**main_struct);
int						ft_detect_label(char *line);
char					*ft_detect_command(char *line);
int						ft_detect_command_i(char *line);
int						ft_emptyline(char *line);
void					ft_cmd(t_champ	**main_struct);
void					ft_parse_arg(char *line, t_command **cmd_s);
void					arg_in_end(t_arg **a, t_arg *b);
void					ft_parse_ind(char *line, int command,
												int i, t_command **cmd_s);
void					ft_parse_dir(char *line, int command, int i,
														t_command **cmd_s);
unsigned int			atoi_arg(const char *str);
void					ft_set_value(t_champ	**main_struct);
void					ft_write_in_file(char *argv, t_champ	*main_struct);
char					**ft_trim_args(char *lined, int cmdlen);
char					*ft_trim_comment(char *line);
void					del_array(char **array);
void					arg_in_end(t_arg **a, t_arg *b);
void					ft_parse_label(char *line, t_label **label_s);
void					ft_count_init(int *count);
int						ft_botsize(t_champ *main_struct);

#endif
