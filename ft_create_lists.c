#include "minishell.h"

extern t_global global;

t_token	*ft_new_token(t_token_type type, char *data)
{
	t_token	*token;

	token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->data = data;
	token->type = type;
	return (token);
}

void	ft_add_back(t_token **token, t_token *new)
{
	t_token	*cur;

	if (!*token)
	{
		(*token) = new;
		return ;
	}
	cur = *token;
	while (cur && cur->next)
		cur = cur->next;
	cur->next = new;
}

t_node	*ft_new_node(t_node_type type)
{
	t_node	*node;

	node = (t_node *)ft_calloc(1, sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = type;
	return (node);
}

t_redir	*ft_new_redir(void)
{
	t_redir	*redir;
	t_token_type	type;

	redir = (t_redir *)ft_calloc(1, sizeof(t_redir));
	if (!redir)
		return (NULL);
	type = global.cur_token->type;
	redir->type = type;
	global.cur_token = global.cur_token->next;
	redir->file = ft_strdup(global.cur_token->data);
	global.cur_token = global.cur_token->next;
	return (redir);
}

void	ft_add_redir_back(t_redir **redir, t_redir *new)
{
	t_redir	*cur;

	if (!*redir)
	{
		*redir = new;
		return ;
	}
	cur = *redir;
	while (cur && cur->next)
		cur = cur->next;
	cur->next = new;
}

