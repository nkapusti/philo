/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akapusti <akapusti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 19:28:36 by akapusti          #+#    #+#             */
/*   Updated: 2023/10/17 18:22:49 by akapusti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>

# define MAX_PHILOS	250
# define STR_MAX_PHILOS "250"

# define STR_PROG_NAME	"philo:"
# define STR_USAGE	"%s usage: ./philo <number_of_philosophers> \
<time_to_die> <time_to_eat> <time_to_sleep> \
[number_of_times_each_philosopher_must_eat]\n"
# define STR_ERR_INPUT_DIGIT	"%s invalid input: %s: \
not a valid unsigned integer between 0 and 2147483647.\n"
# define STR_ERR_INPUT_POFLOW	"%s invalid input: \
must be between 1 and %s philosophers.\n"
# define STR_ERR_THREAD	"%s error: Could not create thread.\n"
# define STR_ERR_MALLOC	"%s error: Could not allocate memory.\n"
# define STR_ERR_MUTEX	"%s error: Could not create mutex.\n"

typedef struct s_table	t_table;

typedef struct s_philo
{
	time_t				last_meal;
	pthread_t			thread;
	unsigned int		id;
	unsigned int		times_ate;
	unsigned int		fork[2];
	pthread_mutex_t		meal_time_lock;
	t_table				*table;
}						t_philo;

typedef struct s_table
{
	int					must_eat_count;
	bool				sim_stop;
	time_t				start_time;
	time_t				time_to_die;
	time_t				time_to_eat;
	time_t				time_to_sleep;
	pthread_t			monitor;
	unsigned int		nb_philos;
	pthread_mutex_t		sim_stop_lock;
	pthread_mutex_t		write_lock;
	pthread_mutex_t		*fork_locks;
	t_philo				**philos;
}						t_table;

typedef enum e_status
{
	DIED = 0,
	EATING = 1,
	SLEEPING = 2,
	THINKING = 3,
	GOT_FORK_1 = 4,
	GOT_FORK_2 = 5
}	t_status;

//init.c 
t_table	*init_table(int argc, char **argv, int i);

//philosopher.c
void	*philosopher(void *data);

//time.c
time_t	time_in_ms(void);
void	philo_sleep(t_table *table, time_t sleep_time);
void	start_delay(time_t start_time);

//output.c
void	write_status(t_philo *philo, bool monitor_report, t_status status);

//monitor.c
void	*monitor(void *data);
bool	simulation_stopped(t_table *table);

//utils.c
bool	valid_input(int argc, char **argv);
int		int_atoi(char *str);

//	exit.c
int		error_failure(char *str, char *details, t_table *table);
void	*free_table(t_table *table);
void	destroy_mutexes(t_table *table);
int		msg(char *str, char *detail, int exit_no);
void	*error_null(char *str, char *details, t_table *table);

#endif
