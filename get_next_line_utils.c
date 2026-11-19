/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urastell <urastell@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 15:41:38 by urastell          #+#    #+#             */
/*   Updated: 2026/11/19 13:09:01 by urastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_new_line(const char *c)
{
	size_t	i;

	i = 0;
	while (c[i])
	{
		if (c[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}
