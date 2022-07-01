
#include "minishell.h"

int	is_all_digit(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] == '-' || str[i] == '+') && i == 0)
		{
			i++;
			continue ;
		}
		if (ft_isdigit(str[i]) == 0)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static	int	calc(const char *str, long overlm, long cutlim, int is_minus)
{
	long	res;

	res = 0;
	while ('0' <= *str && *str <= '9')
	{
		if (is_minus)
		{
			if (res < overlm || (res == overlm && (*str - '0') > cutlim))
				return (TRUE);
			else
				res = 10 * res - (*str - '0');
		}
		else
		{
			if (res > overlm || (res == overlm && (*str - '0') > cutlim))
				return (TRUE);
			else
				res = 10 * res + (*str - '0');
		}
		str++;
	}
	return (FALSE);
}

static	int	check_over_long(const char *str, int is_minus)
{
	long	overlm;
	long	cutlim;
	long	res;

	if (is_minus)
		overlm = LONG_MIN;
	else
		overlm = LONG_MAX;
	cutlim = overlm % 10;
	overlm /= 10;
	if (is_minus)
	{
		if (cutlim > 0)
		{
			cutlim -= 10;
			overlm += 1;
		}
		cutlim = -cutlim;
	}
	res = calc(str, overlm, cutlim, is_minus);
	return (res);
}

int	overflow(const char *str)
{
	long	res;
	long	is_minus;

	is_minus = 0;
	while (*str == ' ' )
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			is_minus = 1;
		str++;
	}
	res = check_over_long;
}

int	is_over_long(const char *str)
{
	long	res;
	long	is_minus;

	is_minus = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n' || \
			*str == '\f' || *str == '\r' || *str == '\v')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			is_minus = 1;
		str++;
	}
	res = check_over_long(str, is_minus);
	return (res);
}

int	ft_exit(char **argv, t_envs **envs)
{
	(void)envs;
	ft_putendl_fd("exit", 1);
	if (argv[1] == NULL)
		exit(EXIT_SUCCESS);
	else if (is_all_digit(argv[1]) == FALSE || is_over_long(argv[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		exit(255);
		/* if you get an error with a code of 255,
		it means there's a problem with your SSH 
		connection */
	}
	else if (argv[2] != NULL)
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (EXIT_FAILURE);
	}
	exit(ft_atoi(argv[1]));
}

int main (int argc, char **argv)
{
	t_envs *env;
	
	ft_exit(argv, &env);
	return(0);
}
