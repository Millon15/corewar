/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/02 16:41:18 by ndidenko          #+#    #+#             */
/*   Updated: 2018/09/02 16:41:19 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	available_args(int command, int index, int *aval_args)
{
	if (g_operations[command].args[index] == 3)
	{
		aval_args[0] = 2;
		aval_args[1] = 1;
	}
	else if (g_operations[command].args[index] == 5)
	{
		aval_args[0] = 1;
		aval_args[1] = 4;
	}
	else if (g_operations[command].args[index] == 6)
	{
		aval_args[0] = 2;
		aval_args[1] = 4;
	}
	if (g_operations[command].args[index] == 7)
		aval_args[0] = -1;
	if (g_operations[command].args[index] == 2)
		aval_args[0] = 2;
	if (g_operations[command].args[index] == 1)
		aval_args[0] = 1;
	if (g_operations[command].args[index] == 4)
		aval_args[0] = 4;
	aval_args[2] = 0;
}

static int	ft_valid_arg(char *line, int command, int index)
{
	int		aval_args[4];
	int		arg;
	int		i;

	arg = -1;
	if (ft_strchr(line, ' ') != 0)
		exit(ft_printf("ERROR! no valid arg in line: |%s|\n", line));
	available_args(command, index, aval_args);
	if (line[0] == 'r' && ft_isdigit(line[1]))
		arg = T_REG;
	if (line[0] == DIRECT_CHAR)
		arg = T_DIR;
	if (ft_isdigit(line[0]) || (line[0] == '-' && ft_isdigit(line[1]))
		|| line[0] == LABEL_CHAR)
		arg = T_IND;
	if (arg == -1)
		exit(ft_printf("ERROR! no valid arg in line: |%s|\n", line));
	i = -1;
	while (++i < 3 && aval_args[i])
		if (arg == aval_args[i] || aval_args[0] == -1)
			break ;
	if (!aval_args[i])
		exit(ft_printf("ERROR! command can't contain this arg: |%s|\n", line));
	return (arg);
}

void		ft_parse_reg(char *line, int command, int index, t_command **cmd_s)
{
	int			i;
	t_arg		*arg;

	i = 1;
	while (line[i] && ft_isdigit(line[i]))
		i++;
	if (line[i] != 0 && index + 1 != g_operations[command].count_args)
		exit(ft_printf("ERROR! bad characters near 'r'\n"));
	arg = (t_arg*)malloc(sizeof(t_arg));
	arg->size = 1;
	arg->value = atoi_arg(line + 1);
	if (arg->value > 16)
		exit(ft_printf("ERROR! big value for 'r'\n"));
	arg->binary = 1;
	arg->name_label = 0;
	arg_in_end(&(*cmd_s)->inst, arg);
}

void		ft_count_args_commas(t_command **cmd_s, int command, char *line)
{
	t_arg	*args;
	int		args_count;
	int		commas;

	args = (*cmd_s)->inst;
	args_count = 0;
	commas = 0;
	while (args)
	{
		args_count++;
		args = args->next;
	}
	if (g_operations[command].count_args > args_count)
		exit(ft_printf("ERROR! few arguments in line: |%s|\n", line));
	if (g_operations[command].count_args < args_count)
		exit(ft_printf("ERROR! many arguments\n"));
	if (args_count == 0)
		exit(ft_printf("ERROR! 0 arguments\n"));
	while (*line++)
		if (*line == ',')
			commas++;
	if (commas != args_count - 1)
		exit(ft_printf("ERROR! check commas!\n"));
}

void		ft_parse_arg(char *line, t_command **cmd_s)
{
	char	*lined;
	char	**args;
	int		cmdlen;
	int		i;
	int		valid;

	i = -1;
	cmdlen = 1 + ft_strlen(g_operations[ft_detect_command_i(line)].name);
	lined = ft_trim_comment(line);
	args = ft_trim_args(lined, cmdlen);
	while (args[++i])
	{
		valid = ft_valid_arg(args[i], ft_detect_command_i(line), i);
		if (valid == T_REG)
			ft_parse_reg(args[i], ft_detect_command_i(line), i, cmd_s);
		else if (valid == T_IND)
			ft_parse_ind(args[i], ft_detect_command_i(line), i, cmd_s);
		else
			ft_parse_dir(args[i], ft_detect_command_i(line), i, cmd_s);
	}
	ft_count_args_commas(cmd_s, ft_detect_command_i(line), lined);
	del_array(args);
	free(lined);
}
