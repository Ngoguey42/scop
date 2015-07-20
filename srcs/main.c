/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/20 12:08:19 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/20 12:15:48 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static int		begin(t_env *e)
{
	
	return (0);
}

static void		loop(t_env *e)
{
	
	return ;
}

static void		end(t_env *e)
{
	
	return ;
}


int				main(void)
{
	t_env					e[1];

	if (begin(e))
		return (1);
	loop(e);
	end(e);
	/* ft_leaks(); */
	return (0);
}
