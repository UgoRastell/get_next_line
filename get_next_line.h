/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urastell <urastell@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 18:19:53 by urastell          #+#    #+#             */
/*   Updated: 2026/11/23 12:21:01 by urastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE BUFSIZ
# endif

# if BUFFER_SIZE > 9223372036854775806
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif

char	*get_before_newline(const char *s);
char	*get_after_newline(const char *s);
void	ft_read_line(int fd, char **keep, char **tmp);
char	*ft_parse_line(char **keep, char **tmp);
char	*get_next_line(int fd);

// UTILS
size_t	ft_new_line(const char *c);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_free_strs(char **str, char **str2, char **str3);
void	*ft_malloc_zero(size_t count, size_t size);
char	*ft_strdup(const char *s1);

#endif
