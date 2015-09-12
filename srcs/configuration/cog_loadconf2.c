/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cog_loadconf2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/12 09:34:39 by ngoguey           #+#    #+#             */
/*   Updated: 2015/09/12 09:38:36 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <string.h>

#define TCSHADER(N, F) {TCSHD_PATH(N), (F), 0}
#define TESHADER(N, F) {TESHD_PATH(N), (F), 0}

/*
**	[[[cog
**	import cog
**	cog.outl("*" "/")
**	from confloader import output_cconf2
**	output_cconf2()
**	cog.outl("/" "*")
**	]]]
*/
int			sp_loadconf_tcshaders(t_env *e)
{
	t_tcshader const		tmp[sp_num_tcshaders] = {

	TCSHADER("test.tesc", NULL),
	};
	memcpy(&e->tcshaders, &tmp, sizeof(tmp));
	return (0);
}

int			sp_loadconf_teshaders(t_env *e)
{
	t_teshader const		tmp[sp_num_teshaders] = {

	TESHADER("test.tese", NULL),
	};
	memcpy(&e->teshaders, &tmp, sizeof(tmp));
	return (0);
}

/*
**	[[[end]]]
*/
