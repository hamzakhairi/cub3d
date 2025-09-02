/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 22:28:24 by hkhairi           #+#    #+#             */
/*   Updated: 2025/09/02 22:33:08 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

char	*ft_substr(char *str, int start, int end)
{
	int		lent;
	int		i;
	char	*new;

	i = 0;
	lent = end - start;
	new = malloc(sizeof(char) * (lent + 2));
	if (!new)
		return (ft_putendl_fd(ERROR_ALOCATION, 2), NULL);
	while (start < end)
	{
		new[i] = str[start];
		start++;
		i++;
	}
	new[i] = '\0';
	return (new);
}
