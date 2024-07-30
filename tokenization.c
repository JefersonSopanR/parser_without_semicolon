#include "minishell.h"

t_global global = {NULL, E_NONE};

void	ft_append_quoted_word(t_token **token, char *line, int *i)
{
	char	quote;
	int		start;
	char	*data;

	quote = line[*i];
	(*i)++;
	start = (*i);
	while (line[*i] && line[*i] != quote)
		(*i)++;
	if (line[*i] == quote)
		(*i)++;
	if (((*i) - start) > 1)
	{
		data = ft_substr(line, start, (*i) - start - 1);
		ft_add_back(token, ft_new_token(T_WORD, data));
	}
	else
		return ;
}

void	ft_strcpy_data(char *data, char *data_1)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data[i])
	{
		if (data[i] != '\'' && data[i] != '"')
			data_1[j++] = data[i++]; 
		else
			i++;
	}
	data_1[j] = '\0';
}

void	ft_append_word(t_token **token, char *line, int *i)
{
	int		start;
	char	*data;
	char	*data_1;
	int		j;

	j = 0;
	if (line[*i] == '\'' || line[*i] == '"')
	{
		ft_append_quoted_word(token, line, i);
		return ;
	}
	start = (*i);
	while (line[*i] && !ft_is_not_op(line, i))
	{
		(*i)++;
		if (line[*i] == '\'' || line[*i] == '"')
			j++;
	}
	data = ft_substr(line, start, (*i) - start);
	if (j > 0)
	{
		data_1 = (char *)malloc(ft_strlen(data) - j + 1);
		if (!data_1)
			return ;
		ft_strcpy_data(data, data_1);
		free(data);
		ft_add_back(token, ft_new_token(T_WORD, data_1));
	}
	else
		ft_add_back(token, ft_new_token(T_WORD, data));
}

t_token *ft_procces_line(char *line)
{
	t_token	*token;
	int		i;
	
	i = 0;
	token = NULL;
	while (line[i])
	{
		if (line[i] == ' ')
			i++;
		else if (line[i] == '>' || line[i] == '<' || line[i] == '(' || line[i] == ')' || line[i] == '|'
			|| !ft_strncmp(&line[i], "&&", 2))
			ft_identify_operators(&token, line, &i);
		else
			ft_append_word(&token, line, &i);
	}
	return (token);
}

t_token *ft_get_tokens(char *line)
{
	t_token *token;

	if (ft_check_quotes(line))
	{
		free(line);
		return (NULL);
	}
	token = ft_procces_line(line);
	free(line);
	return (token);
}

int main()
{
	char    *line;
	t_token *token;
	t_node	*ast;

	ast = NULL;
	token = NULL;
	while (1)
	{
		line = readline("--> ");
		if (!ft_strlen(line))
		{
			free(line);
			continue ;
		}
		if (!ft_strncmp(line, "exit", 4))
		{
			free(line);
			break ;
		}
		if (line[0])
			add_history(line);
		token = ft_get_tokens(line);
		ft_print_tokens(token);
		ast = ft_create_ast(token);
		if (!token)
			continue ;
		if (ast && !global.error_type)
			ft_print_ast(ast, 0);
		else if (global.error_type)
			ft_print_error(token);
		ft_free_tokens(&token);
		ft_free_ast(ast);
		global.error_type = E_NONE;
	}
	clear_history();
	return 0;
}
