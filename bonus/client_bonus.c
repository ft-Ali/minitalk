/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:38:17 by alsiavos          #+#    #+#             */
/*   Updated: 2024/05/22 14:40:05 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

int		g_received;

void	signal_handler(int signum, siginfo_t *siginfo, void *context)
{
	static int	bits;

	(void)context;
	(void)siginfo;
	if (signum == SIGUSR1)
	{
		bits++;
		g_received = 1;
	}
	if (signum == SIGUSR2)
	{
		g_received = 0;
		ft_printf("\e[0;91mServer received %d bits\033[1;30m\n", bits);
		ft_printf("\e[1;32mServer received your msg\e[0m\n");
		bits = 0;
		exit(0);
	}
}

void	error_sigaction(struct sigaction *sa, int signum)
{
	int	error;

	error = sigaction(signum, sa, NULL);
	if (error == -1)
	{
		ft_printf("Error from sigaction, exiting process\n");
		exit(0);
	}
}

void	ft_signal(int pid, unsigned char character)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if ((character & (1 << (i))) != 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i++;
		while (!g_received)
			;
		g_received = 0;
	}
}

void	ft_send(pid_t server, char *msg)
{
	int	i;

	i = 0;
	while (msg[i])
	{
		ft_signal(server, msg[i]);
		i++;
	}
	ft_signal(server, '\0');
	exit(0);
}

int	main(int c, char **v)
{
	struct sigaction	sa;
	pid_t				pid;
	char				*msg;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &signal_handler;
	error_sigaction(&sa, SIGUSR1);
	error_sigaction(&sa, SIGUSR2);
	if (c != 3)
	{
		ft_printf("\033[1;31mUtilisation correcte \033[0m");
		ft_printf("\033[1;31m./client [PID] [MSG]\n\033[0m");
		exit(1);
	}
	pid = ft_atoi(v[1]);
	msg = v[2];
	ft_send(pid, msg);
	exit(0);
}
