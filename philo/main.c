#include "philosophers.h"

int	init_phils(t_info *info)
{
	int	i;

	i = 0;
	info->phils = malloc(sizeof (t_phil) * info->phil_count);
	info->phil_died = 0;
	while (i < info->phil_count)
	{
		info->phils[i].phil_number = i + 1;
		pthread_mutex_init(&info->phils[i].forks, NULL);
		info->phils[i].is_dead = 0;
		info->phils[i].diner_number = 0;
		info->phils[i].info = info;
		info->phils[i].time_last_diner = 0;
		i++;
	}
	pthread_mutex_init(&info->print, NULL);
	return (0);
}

int	check_eating_count(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->phil_count)
	{
		if (info->phils[i].diner_number != info->must_eat_count)
			return (0);
		i++;
	}
	if (i == info->phil_count)
		return (1);
	return (0);
}

int	check_dying(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->phil_count)
	{
		if (info->time_to_die < get_time() - info->start_time - \
		info->phils[i].time_last_diner)
		{
			info->phil_died = 1;
			info->phils[i].is_dead = 1;
			print_status(&info->phils[i], "died");
			return (1);
		}
		i++;
	}
	return (0);
}

int	monitor(t_info *info)
{
	while (1)
	{
		if (info->must_eat_count)
			if (check_eating_count(info))
				return (0);
		if (check_dying(info))
			return (0);
		usleep(100);
	}
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (parser(argc, argv, &info))
	{
		ft_putstr_fd("Invalid argument parameters!\n", 2);
		return (1);
	}
	init_phils(&info);
	info.start_time = get_time();
	start_threads(&info);
	monitor(&info);
	usleep(250000);
	return (0);
}
