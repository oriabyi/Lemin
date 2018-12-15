/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabyi <oleksandr32riabyi@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 15:42:09 by oriabyi           #+#    #+#             */
/*   Updated: 2017/11/27 15:50:47 by oriabyi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcapitalize(char *s)
{
	int i;

	i = -1;
	if (!s)
		return (NULL);
	while (s[++i])
		if (ft_isalpha(s[i]) && !(ft_isalpha(s[i - 1])))
			if (ft_wcase(s[i]))
				s[i] = ft_toupper(s[i]);
	return (s);
}
