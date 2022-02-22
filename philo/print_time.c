#include "philosophers.h"

unsigned long	get_time(void)
{
	struct timeval	time;
	unsigned long	milliseconds;

	gettimeofday(&time, NULL);
	milliseconds = time.tv_sec * 1000;
	milliseconds += time.tv_usec / 1000;
	return (milliseconds);
}

int	print_status(t_phil *phil, char *str)
{
	unsigned long	time;

	time = get_time() - phil->info->start_time;
	if (phil->info->phil_died == 0)
	{
		pthread_mutex_lock(&phil->info->print);
		printf("%lu %d %s\n", time, phil->phil_number, str);
		pthread_mutex_unlock(&phil->info->print);
		return (0);
	}
	if (!ft_strcmp("died", str))
	{
		pthread_mutex_lock(&phil->info->print);
		printf("%lu %d died\n", time, phil->phil_number);
		pthread_mutex_unlock(&phil->info->print);
	}
	return (0);
}

void	ft_sleep(unsigned long time)
{
	unsigned long	begin;

	begin = get_time();
	while (get_time() - begin < time)
		usleep(100);
}
