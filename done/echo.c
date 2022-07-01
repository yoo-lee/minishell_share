/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoo-lee <yoo-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 13:44:26 by yoo-lee           #+#    #+#             */
/*   Updated: 2022/06/27 13:44:29 by yoo-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
# include "/Users/yoo-lee/42/minishell0307/libft/libft.h"


// echo - テキストの行を表示する  
int	ft_echo(char **argv, t_envs *envs)
{
	int		has_n_option;
	size_t	i;

	(void)envs;
	if (argv[1] != NULL && !ft_strncmp(argv[1], "-n", 3))
	{
		has_n_option = TRUE;
		i = 2;
	}
	else
	{
		has_n_option = FALSE;
		i = 1;
	}
	while (argv[i])
	{
		write(1, argv[i], ft_strlen(argv[i]));
		i++;
		if (argv[i] != NULL)
			write(1, " ", 1);
	}
	if (!has_n_option)
		write(1, "\n", 1);
	return (SUCCESS);
}

int main (int argc, char **argv)
{
	t_envs *env;
	
	ft_echo(argv, env);
	return(0);
}