#include "philosophers.h"

void	phil_eating(t_phil *phil)
{
	int	right;

	right = phil->phil_number;
	if (phil->phil_number == phil->info->phil_count)
		right = 0;
	pthread_mutex_lock(&phil->forks);
	print_status(phil, "has taken a fork");
	pthread_mutex_lock(&phil->info->phils[right].forks);
	print_status(phil, "has taken a fork");
	phil->time_last_diner = get_time() - phil->info->start_time;
	print_status(phil, "is eating");
	if (!phil->info->phil_died)
		ft_sleep(phil->info->time_to_eat);
	pthread_mutex_unlock(&phil->forks);
	pthread_mutex_unlock(&phil->info->phils[right].forks);
	phil->diner_number++;
}

void	*start_phil(void *arg)
{
	t_phil	*phil;

	phil = arg;
	while (phil->is_dead == 0 || phil->info->phil_died == 0)
	{
		phil_eating(phil);
		if ((phil->info->phil_died || phil->is_dead) || \
		(phil->diner_number == phil->info->must_eat_count))
			return (NULL);
		print_status(phil, "is sleeping");
		ft_sleep(phil->info->time_to_sleep);
		print_status(phil, "is thinking");
	}
	return (NULL);
}

int	start_threads(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->phil_count)
	{
		pthread_create(&info->phils[i].tred, NULL, &start_phil,
			   &info->phils[i]);
		pthread_detach(info->phils[i].tred);
		usleep(100);
		i++;
	}
	return (0);
}
