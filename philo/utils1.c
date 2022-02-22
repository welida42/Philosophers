#include "philosophers.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if ((!s1) && (!s2))
		return (0);
	if ((!s1) && (s2))
		return (-s2[0]);
	if ((s1) && (!s2))
		return (s1[0]);
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

int	ft_atoi(const char *str)
{
	int	number;
	int	sign;

	number = 0;
	sign = 1;
	while ((*str == ' ') || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str && (*str >= '0' && *str <= '9'))
	{
		if ((sign == -1) && \
				((number > 214748364) || (number == 214748364 && *str > '8')))
			return (0);
		else if ((sign == 1) && \
				((number > 214748364) || (number == 214748364 && *str > '7')))
			return (-1);
		number = number * 10 + *str - '0';
		str++;
	}
	return (sign * number);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	if (!s)
		return ;
	while (s[i] != '\0')
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}
