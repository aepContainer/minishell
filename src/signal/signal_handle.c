#include "../../inc/minishell.h"

void	ctrl_output(t_mshell *mshell, char state)
{
	if (state == 1)
	{
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &mshell->termios);
		return ;
	}
	tcgetattr(STDIN_FILENO, &mshell->termios);
	mshell->termios->c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &mshell->termios);
	mshell->termios->c_lflag &= ~ECHOCTL;
}

void	reset_prompt(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	reset_prompt_exec(int signal)
{
	(void)signal;
	write(1, "\n", 1);
}

void	signal_handle_general(t_mshell *mshell)
{
	signal(SIGQUIT, &reset_prompt);
	signal(SIGINT, &reset_prompt);
	ctrl_output(mshell, 1);
}

void	signal_handle_exec(t_mshell *mshell)
{
	signal(SIGQUIT, &reset_prompt);
	signal(SIGINT, &reset_prompt_exec);
	ctrl_output(mshell, 0);
}
