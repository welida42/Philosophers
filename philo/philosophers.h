#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

//typedef struct s_info	t_info;

typedef struct s_phil
{
	int				phil_number;
	pthread_t		tred;
	pthread_mutex_t	forks;
	int				diner_number;
	unsigned long	time_last_diner;
	int				is_dead;
	struct s_info	*info;
}	t_phil;

typedef struct s_info
{
	unsigned long	time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	int				phil_count;
	unsigned long	start_time;
	t_phil			*phils;
	pthread_mutex_t	print;
	int				phil_died;
}	t_info;

int				start_threads(t_info *info);
int				print_status(t_phil *phil, char *str);
void			ft_sleep(unsigned long time);
unsigned long	get_time(void);
int				init_phils(t_info *info);
int				parser(int argc, char **argv, t_info *info);
int				ft_strcmp(char *s1, char *s2);
int				ft_atoi(const char *str);
int				ft_isdigit(int c);
void			ft_putstr_fd(char *s, int fd);

#endif
