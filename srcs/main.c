/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/30 11:48:41 by ngoguey           #+#    #+#             */
/*   Updated: 2015/06/30 13:12:39 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int						main(int ac, char *av[])
{
	t_env		e[1];

	if (sp_init_env(e))
		return (DEBUG("Could not init env"), 1);
	if (sp_init_glfw(e))
		return (DEBUG("Could not init glfw"), 1);
	(void)ac;
	(void)av;
	while (e->loop)
	{
		
	}
	sp_disable_glfw(e);
	return (0);
}
