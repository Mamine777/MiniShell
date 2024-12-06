/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 17:49:07 by mokariou          #+#    #+#             */
/*   Updated: 2024/12/03 18:11:31 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free(char **strs)
{
	int	i;

	i = -1;
	while (strs[++i])
		free(strs[i]);
	free(strs);
}

void	free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->pwd)
		free(data->pwd);
	if (data->old_pwd)
		free(data->old_pwd);
	if (data->temp_pwd)
		free(data->temp_pwd);
	if (data->new_env)
		ft_free(data->new_env);
	if (data)
		free(data);
}

void	init(t_data *data)
{
	data->old_pwd = NULL;
	data->pwd = NULL;
	data->new_env = NULL;
	data->new_env = NULL;
	data->temp_pwd = NULL;
	if (!data->pwd)
		data->pwd = ft_strdup("");
	data->pwd = ft_strjoin(data->pwd, get_pwd_current());
	if (!data->old_pwd)
		data->old_pwd = ft_strdup("");
	if (!data->pwd || !data->old_pwd)
	{
		free(data->pwd);
		free(data->old_pwd);
		perror("malloc");
		free(data);
		return ;
	}
}

void	init_stack(t_stack *stack, void *content)
{
	t_nodes	*new_node;
	t_nodes	*current;

	new_node = malloc(sizeof(t_nodes));
	if (!new_node)
		return ;
	new_node->str = ft_strdup((char *)content);
	if (!new_node->str)
		return (free(new_node));
	new_node->next = NULL;
	if (!stack->top)
	{
		stack->top = new_node;
		return ;
	}
	current = stack->top;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

void	fill_stack(t_stack *stack, t_data *data)
{
	int	i;
	int	len;

	if (!stack || !data || !data->new_env)
		return ;
	len = -1;
	while (data->new_env[++len])
		;
	i = -1;
	while (++i < len)
		init_stack(stack, data->new_env[i]);
}
