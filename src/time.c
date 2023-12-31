/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akapusti <akapusti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 19:27:20 by akapusti          #+#    #+#             */
/*   Updated: 2023/10/18 14:27:41 by akapusti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	time_in_ms(void)
{
	struct timeval		tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	philo_sleep(t_table *table, time_t sleep_time)
{
	time_t	wake_up;

	wake_up = time_in_ms() + sleep_time;
	while (time_in_ms() < wake_up)
	{
		if (simulation_end(table))
			break ;
		usleep(100);
	}
}

void	start_delay(time_t start_time)
{
	while (time_in_ms() < start_time)
		continue ;
}
