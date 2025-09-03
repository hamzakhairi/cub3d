/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_atoi.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 21:57:22 by hkhairi           #+#    #+#             */
/*   Updated: 2025/09/03 11:13:04 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	ft_mini_atoi(char *str, int start, int end)
{
	int	result;

	result = 0;
	while (str[start] >= '0' && str[start] <= '9' && start < end)
	{
		if (result > 255)
			return (-1);
		result = result * 10 + (str[start] - '0');
		str++;
	}
	return (result);
}
