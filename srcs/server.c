/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:38:04 by alsiavos          #+#    #+#             */
/*   Updated: 2024/05/22 14:21:19 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

void	start_server(int pid)
{
	ft_printf("\n\e[1;94m");
	ft_printf("███████╗███████╗██████╗ ██╗   ██╗███████╗██████╗ \n");
	ft_printf("██╔════╝██╔════╝██╔══██╗██║   ██║██╔════╝██╔══██╗\n");
	ft_printf("███████╗█████╗  ██████╔╝██║   ██║█████╗  ██████╔╝\n");
	ft_printf("╚════██║██╔══╝  ██╔══██╗╚██╗ ██╔╝██╔══╝  ██╔══██╗\n");
	ft_printf("███████║███████╗██║  ██║ ╚████╔╝ ███████╗██║  ██║\n");
	ft_printf("╚══════╝╚══════╝╚═╝  ╚═╝  ╚═══╝  ╚══════╝╚═╝  ╚═╝\n");
	ft_printf("Process ID: \e[0;91m%d\033[1;30m\t", pid);
	ft_printf("     \e[1;32m Created By: alsiavos \e[0m\n\n>>");
}

void	ft_handler(int signal, siginfo_t *info, void *context)
{
	static int	current_char;
	static int	bit_index;

	(void)context;
	if (!info->si_pid)
		exit(0);
	if (signal == SIGUSR1)
		current_char |= (1 << bit_index);
	bit_index++;
	if (bit_index == 8)
	{
		if (current_char == END_TRANSMISSION)
		{
			ft_printf("\n");
			kill(info->si_pid, SIGUSR2);
		}
		else
			ft_putchar(current_char);
		bit_index = 0;
		current_char = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	start_server(getpid());
	sa.sa_sigaction = &ft_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	exit(0);
}
