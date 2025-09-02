/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_other_strdup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 22:31:45 by hkhairi           #+#    #+#             */
/*   Updated: 2025/09/02 22:32:41 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

char	*ft_other_strdup(char *s)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = ft_strlen(s);
	if (j == 1)
		return (NULL);
	str = (char *)malloc(sizeof(*str) * (j + 1));
	if (!str)
		return (NULL);
	while (i < j)
	{
		if (s[i] != '\n')
		{
			str[i] = s[i];
			i++;
		}
		else
			break ;
	}
	str[i] = '\0';
	return (str);
}
