#include "minishell.h"

extern t_global global;

t_redir	*ft_fill_redir(t_redir **redir)
{
	while (global.cur_token && ft_is_redir(global.cur_token->type))
	{
		ft_add_redir_back(redir, ft_new_redir());
	}
	return (*redir);
}

t_node	*ft_get_cmd_node(void)
{
	t_node	*node;
	char	*tmp;
	char	*new_data;

	node = ft_new_node(NODE_CMD);
	if (!node)
		return (NULL);
	node->data = ft_strdup(global.cur_token->data);
	global.cur_token = global.cur_token->next;
	while (global.cur_token && (global.cur_token->type == T_WORD || ft_is_redir(global.cur_token->type)))
	{
		if (global.cur_token->type == T_WORD)
		{
			tmp = ft_strjoin(node->data, " ");
			new_data = ft_strjoin(tmp, global.cur_token->data);
			free(tmp);
			free(node->data);
			node->data = new_data;
			global.cur_token = global.cur_token->next;
		}
		else if (ft_is_redir(global.cur_token->type))
			node->redir = ft_fill_redir(&node->redir);
	}
	return (node);
}

t_node	*ft_primary(void)
{
	t_node	*node;

	node = NULL;
	if (!global.cur_token || !ft_is_cmd(global.cur_token))
	{
		global.error_type = E_SYNTAX;
		return (NULL);
	}
	if (global.cur_token && global.cur_token->type == T_O_PARENTHESIS)
	{
		global.cur_token = global.cur_token->next;
		if (!global.cur_token)
		{
			global.error_type = E_SYNTAX;
			return (node);
		}
		node = ft_expression(0);
		if (!global.cur_token || global.cur_token->type != T_C_PARENTHESIS)
			global.error_type = E_SYNTAX;
		global.cur_token = global.cur_token->next;
		return (node);
	}
	if (global.cur_token && (global.cur_token->type == T_WORD || ft_is_redir(global.cur_token->type)))
		return (ft_get_cmd_node());
	return (node);
}

t_node	*ft_expression(int	min_prec)
{
	t_node			*left;
	t_node			*right;
	int				next_prec;
	t_token_type	op;

	left = ft_primary();
	if (!left)
		return (NULL);
	while (global.cur_token && !ft_is_cmd(global.cur_token) && ft_prec(global.cur_token->type) >= min_prec)
	{
		op = global.cur_token->type;
		global.cur_token = global.cur_token->next;
		if (!global.cur_token || !ft_is_cmd(global.cur_token))
		{
			global.error_type = E_SYNTAX;
			return (left);
		}
		next_prec = ft_prec(global.cur_token->type) + 1;
		right = ft_expression(next_prec);
		if (!right)
			return (left);
		left = ft_connect_nodes(op, left, right);
	}
	return (left);
}

t_node	*ft_create_ast(t_token *token)
{
	t_node	*ast;

	global.cur_token = token;
	ast = ft_expression(0);
	if (global.cur_token)
	{
		global.error_type = E_SYNTAX;
		return (ast);
	}
	return (ast);
}