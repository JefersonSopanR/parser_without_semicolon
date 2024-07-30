#include "minishell.h"

void	ft_id_redir_input(t_token **token ,char *line, int *i)
{
	if (line[*i + 1] == '<')
	{
		ft_add_back(token, ft_new_token(T_REDIR_HEREDOC, ft_strdup("<<")));
		(*i) += 2;
	}
	else
	{
		ft_add_back(token, ft_new_token(T_REDIR_IN, ft_strdup("<")));
		(*i)++;
	}
}

void	ft_id_redir_output(t_token **token, char *line, int *i)
{
	if (line[*i + 1] == '>')
	{
		ft_add_back(token, ft_new_token(T_REDIR_APPEND, ft_strdup(">>")));
		(*i) += 2;
	}
	else
	{
		ft_add_back(token, ft_new_token(T_REDIR_OUT, ft_strdup(">")));
		(*i)++;
	}
}

void	ft_identify_redir(t_token **token, char *line, int *i)
{
	if (line[*i] == '<')
		ft_id_redir_input(token, line, i);
	else if (line[*i] == '>')
		ft_id_redir_output(token, line, i);
}
