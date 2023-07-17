/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:39:06 by melee             #+#    #+#             */
/*   Updated: 2023/07/12 15:39:13 by melee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_exit_status(t_shell *shell, char *res, char **str)
{
	char	*exit_status;

	exit_status = ft_itoa(WEXITSTATUS(shell->exit_status));
	if (res == NULL)
	{
		res = malloc(1 * sizeof(char));
		res[0] = '\0';
	}
	*str += 2;
	res = free_substr_join(res, exit_status);
	return (res);
}
