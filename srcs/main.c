/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/20 12:08:19 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/20 14:04:42 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <stdlib.h>

static int		begin(t_env *e)
{
	if (sp_init_env(e))
		return (ERROR("sp_init_env(e)"), 1);
	if (sp_init_glfw(e))
		return (ERROR("sp_init_glfw(e)"), 1);
	if (sp_init_shaders(e))
		return (ERROR("sp_init_shaders(e)"), 1);
	if (sp_init_programs(e))
		return (ERROR("sp_init_programs(e)"), 1);
	return (0);
}

static void		loop(t_env *e)
{
	while (!glfwWindowShouldClose(e->win))
	{
		
	}
	return ;
}

static void		end(t_env *e)
{
	
	return ;
}


int				main(void)
{
	t_env					*e;

	qprintf("sizeof(t_env) = %u\n", sizeof(*e));
	e = malloc(sizeof(*e));
	if (e == NULL)
		return (1);
	if (begin(e))
		return (1);
	loop(e);
	end(e);
	free(e);
	/* ft_leaks(); */
	return (0);
}
