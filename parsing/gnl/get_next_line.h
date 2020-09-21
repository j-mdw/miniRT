/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaydew <jmaydew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 00:24:41 by jmaydew           #+#    #+#             */
/*   Updated: 2020/06/08 00:25:03 by jmaydew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# define BUFFER_SIZE 128

int	get_next_line(int fd, char **line);
void	ft_my_strcpy(char *dst, const char *src);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
int	my_ft_strlen(const char *s);
int	ft_gnl(char **line, char *buffer);

#endif
