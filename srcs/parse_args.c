/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moelamma <moelamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 16:44:34 by moelamma          #+#    #+#             */
/*   Updated: 2026/06/19 14:33:40 by moelamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	ft_atoi_strict(const char *s, long *out)
{
	long	result;
	int		i;

	result = 0;
	i = 0;
	if (!s || !s[i])
		return (0);
	while (s[i])
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			if (result > (LONG_MAX - (s[i] - '0')) / 10)
				return (0);
			result = result * 10 + (s[i] - '0');
		}
		else
			return (0);
		i++;
	}
	*out = result;
	return (1);
}

static int	parse_counts(char **argv, t_args *args)
{
	long	tmp;

	if (!ft_atoi_strict(argv[1], &tmp) || tmp < 1 || tmp > INT_MAX)
		return (fprintf(stderr, "Error: invalid number_of_coders\n"), 0);
	args->number_of_coders = (int)tmp;
	if (!ft_atoi_strict(argv[6], &tmp) || tmp < 1 || tmp > INT_MAX)
		return (fprintf(stderr,
				"Error: invalid number_of_compiles_required\n"), 0);
	args->number_of_compiles_required = (int)tmp;
	return (1);
}

static int	parse_time(char **argv, t_args *args)
{
	long	tmp;

	if (!ft_atoi_strict(argv[2], &tmp) || tmp < 1)
		return (fprintf(stderr, "Error: invalid time_to_burnout\n"), 0);
	args->time_to_burnout = tmp;
	if (!ft_atoi_strict(argv[3], &tmp))
		return (fprintf(stderr, "Error: invalid time_to_compile\n"), 0);
	args->time_to_compile = tmp;
	if (!ft_atoi_strict(argv[4], &tmp))
		return (fprintf(stderr, "Error: invalid time_to_debug\n"), 0);
	args->time_to_debug = tmp;
	if (!ft_atoi_strict(argv[5], &tmp))
		return (fprintf(stderr, "Error: invalid time_to_refactor\n"), 0);
	args->time_to_refactor = tmp;
	if (!ft_atoi_strict(argv[7], &tmp))
		return (fprintf(stderr, "Error: invalid dongle_cooldown\n"), 0);
	args->dongle_cooldown = tmp;
	return (1);
}

int	parse_args(int argc, char **argv, t_args *args)
{
	if (argc != 9)
		return (fprintf(stderr, "Error: expected 8 arguments\n"), 0);
	if (!parse_counts(argv, args))
		return (0);
	if (!parse_time(argv, args))
		return (0);
	if (strcmp(argv[8], "fifo") == 0)
		args->scheduler = 0;
	else if (strcmp(argv[8], "edf") == 0)
		args->scheduler = 1;
	else
		return (fprintf(stderr,
				"Error: scheduler must be 'fifo' or 'edf'\n"), 0);
	return (1);
}
