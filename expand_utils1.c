/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 18:06:33 by melee             #+#    #+#             */
/*   Updated: 2023/06/30 18:06:44 by melee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*free_substr_join(char *res, char *substr)
{
	char	*temp;

	temp = res;
	res = ft_strjoin(res, substr);
	free(temp);
	free(substr);
	return (res);
}

char	*free_join1(char *res, char *str)
{
	char	*temp;

	temp = res;
	res = ft_strjoin(res, str);
	free(temp);
	return (res);
}

int	check_dol_delimit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] < 48 || (str[i] > 57 && str[i] < 65)
			|| (str[i] > 90 && str[i] < 95) || (str[i] > 95 && str[i] < 97)
			|| str[i] > 122)
			return (i);
		i++;
	}
	return (-1);
}

char	*parse_nondollar(char *res, char **str)
{
	char	*substr;

	if (res == NULL)
	{
		res = malloc(1 * sizeof(char));
		res[0] = '\0';
	}
	substr = ft_substr(*str, 0, 1);
	res = free_substr_join(res, substr);
	*str += 1;
	return (res);
}

char	*parse_dollar(t_shell *shell, char *res, char **str)
{
	char	*dol_substr;
	char	*temp;

	if (res == NULL)
	{
		res = malloc(1 * sizeof(char));
		res[0] = '\0';
	}
	*str += 1;
	if (check_dol_delimit(*str) == -1)
		dol_substr = ft_substr(*str, 0, ft_strlen(*str));
	else if (check_dol_delimit(*str) == 0)
	{
		temp = res;
		res = ft_strjoin(res, "$");
		free(temp);
		dol_substr = ft_substr(*str, 0, check_dol_delimit(*str));
	}
	else
		dol_substr = ft_substr(*str, 0, check_dol_delimit(*str));
	*str += ft_strlen(dol_substr);
	if (ft_getenv(shell, dol_substr) != NULL)
		res = free_substr_join(res, ft_strdup(ft_getenv(shell, dol_substr)));
	free(dol_substr);
	return (res);
}
