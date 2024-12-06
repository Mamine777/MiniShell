/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 19:54:50 by mokariou          #+#    #+#             */
/*   Updated: 2024/12/02 20:00:13 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	print_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	return (0);
}

void	printf_stack(t_stack *stack)
{
	t_nodes	*current;

	if (!stack || !stack->top)
		return ;
	current = stack->top;
	while (current != NULL)
	{
		if (check_is_exist2(current->str, '='))
			printf("%s\n", current->str);
		current = current->next;
	}
}

void	printf_second(t_lst *stack)
{
	t_lol	*current;

	if (!stack || !stack->top)
		return ;
	current = stack->top;
	while (current)
	{
		printf("%s\n", current->str);
		current = current->next;
	}
}

int	extract(char *str, t_stack *stack)
{
	t_nodes	*current;
	size_t	key_len;
	char	*key;

	if (!str || !stack || !stack->top)
		return (0);
	key = ft_substr(str, 0, ft_strchr(str, '=') - str);
	if (!key)
		return (perror("malloc"), 0);
	key_len = ft_strlen(key);
	current = stack->top;
	while (current)
	{
		if (!ft_strncmp(current->str, key, key_len)
			&& current->str[key_len] == '=')
		{
			free(current->str);
			current->str = ft_strdup(str);
			free(key);
			return (1);
		}
		current = current->next;
	}
	free(key);
	return (0);
}
