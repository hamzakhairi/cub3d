/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 22:32:01 by hkhairi           #+#    #+#             */
/*   Updated: 2025/09/02 22:32:07 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

char	*ft_strchr(const char *s, int c)
{
	char	altc;
	char	*alts;
	int		i;

	i = 0;
	alts = (char *)s;
	altc = c;
	while (alts[i] != altc)
	{
		if (alts[i] == '\0')
		{
			return (NULL);
		}
		i++;
	}
	return ((char *)alts + i);
}
