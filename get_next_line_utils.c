/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urastell <urastell@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 15:41:38 by urastell          #+#    #+#             */
/*   Updated: 2026/11/19 12:58:06 by urastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *c)
{
	size_t	i;

	i = 0;
	while (c[i])
	{
		i++;
	}
	return (i);
}

bool	*ft_new_line(const char *s, int c)
{
	const char	*last;

	last = NULL;
	while (*s)
	{
		if (*s == c)
			last = s;
		s++;
	}
	if (c == '\n')
		return (1);
	return (0);
}
