/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_sho.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:27:49 by mokariou          #+#    #+#             */
/*   Updated: 2024/12/02 18:18:14 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	check_is_exist(const char *s, int c)
{
	int				i;
	unsigned char	d;

	if (!s)
		return (0);
	d = (unsigned char)c;
	i = 0;
	while (s[i] || d == '\0')
	{
		if (s[i] == d && s[i + 1] != '\0')
			return (1);
		else if (!ft_isalnum(s[i]) && s[i + 1])
			return (ft_printf("export: `%s': not a valid identifier", s), 0);
		i++;
	}
	return (0);
}

void	update_pwd(t_stack *stack, t_data *data)
{
	t_nodes	*current;

	current = stack->top;
	while (current)
	{
		if (check_if(current->str, "PWD="))
		{
			current->str = ft_strdup(ft_strjoin("PWD=", get_pwd_current()));
			if (!current->str)
				return (free_stack(stack));
		}
		else if (check_if(current->str, "OLDPWD="))
		{
			current->str = ft_strdup(ft_strjoin("OLDPWD=", data->old_pwd));
			if (!current->str)
				return (free_stack(stack));
		}
		current = current->next;
	}
}
