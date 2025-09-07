/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 11:07:07 by hkhairi           #+#    #+#             */
/*   Updated: 2025/09/07 11:10:30 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	*ft_memcpy(void *dst, const void *src, int n)
{
	unsigned char		*ptr_dst;
	const unsigned char	*ptr_src;

	if (dst == NULL && src == NULL)
		return (NULL);
	if (dst == src)
		return (dst);
	ptr_dst = (unsigned char *)dst;
	ptr_src = (unsigned char *)src;
	while (n--)
		*ptr_dst++ = *ptr_src++;
	return (dst);
}
