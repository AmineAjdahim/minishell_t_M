/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-raki <yer-raki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 16:09:15 by yer-raki          #+#    #+#             */
/*   Updated: 2021/06/04 14:07:00 by yer-raki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
// #include <termcap.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../Libft/libft.h"


// typedef struct	s_env
// {
//     char *val; // all line
//     char *value; // after command
//     char *key; // command
//     struct s_env * next;
// }				t_env;

// typedef struct  s_sep
// {
// 	char    *path; // whereis echo for example
// 	char    t_sp; // type of separator ; or |
// 	char    *builtin; // name of command ex: echo, pwd ... 
// 	char    **args; // commands without builtin
// 	int		p_pip;

// 	t_env	*env;
// }               t_sep;

// t_sep *g_env;
int		ft_strcmp(char *s1, char *s2);
int		ft_strlen2(char **w);
void	ft_putstr(char *s);

#endif
