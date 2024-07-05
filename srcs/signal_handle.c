/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lraggio <lraggio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:43:07 by lraggio           #+#    #+#             */
/*   Updated: 2024/07/05 15:43:48 by lraggio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handle(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
		return ;
}

void	setup_signal_handling(void)
{
	struct sigaction	sa;

	//ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = signal_handle;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		handle_sig_error(SIGINT);
	sa.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		handle_sig_error(SIGQUIT);
}

void	handle_sig_error(int sig)
{
	if (sig == SIGINT)
	{
		perror(("Error setting up SIGINT handler\n"));
		exit(EXIT_FAILURE);
	}
	else if (sig == SIGQUIT)
	{
		perror(("Error setting up SIGQUIT handler\n"));
		exit(EXIT_FAILURE);
	}
	else
		return ;
}