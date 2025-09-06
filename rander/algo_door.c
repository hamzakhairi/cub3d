/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_door.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:37:07 by hkhairi           #+#    #+#             */
/*   Updated: 2025/09/06 15:41:48 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	v_get_doors(t_game *game, int x, int y)
{
	t_door	*tmp;

	tmp = game->doors;
	while (tmp)
	{
		if (tmp->x == x && tmp->y == y)
		{
			if (!tmp->state)
				return (0);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	state_door(t_door *head, int x, int y)
{
	t_door	*tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->x == x && tmp->y == y)
		{
			tmp->state = !tmp->state;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	ft_add_door(int i, int j, t_door **head)
{
	t_door	*tmp;
	t_door	*new_door;

	new_door = malloc(sizeof(t_door));
	if (!new_door)
		return (0);
	new_door->x = j;
	new_door->y = i;
	new_door->state = 0;
	new_door->next = NULL;
	if (*head == NULL)
	{
		*head = new_door;
		return (1);
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_door;
	return (1);
}

int	fetch_door(t_game *game)
{
	char	**map;
	int		i;
	int		j;

	map = game->map->grid;
	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'D' && !ft_add_door(i, j, &game->doors))
				return (ft_putendl_fd(ERROR_ALOCATION, 2), 0);
			j++;
		}
		i++;
	}
	return (1);
}
