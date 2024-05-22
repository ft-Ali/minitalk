/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:37:14 by alsiavos          #+#    #+#             */
/*   Updated: 2024/05/21 10:59:19 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "../.libft/printf/ft_printf.h"
# include "../.libft/libft.h"
# include <signal.h>
# include <stdio.h>
# include <sys/wait.h>
# include <unistd.h>
# define END_TRANSMISSION '\0'

void	ft_handler(int signal, siginfo_t *info, void *context);
void	ft_signal(int pid, unsigned char character);
void	signal_handler(int signum, siginfo_t *siginfo, void *context);
void	error_sigaction(struct sigaction *sa, int signum);

#endif
