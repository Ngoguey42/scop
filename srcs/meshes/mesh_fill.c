/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_fill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/09 14:15:56 by ngoguey           #+#    #+#             */
/*   Updated: 2015/08/09 14:50:31 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <string.h>

#define NORM_AT_42_IS_WTF(E, ME) (ME)->fill((E), (ME))

static t_locations_backup_fill const	g_backup_fill[] = {
	{offsetof(t_vbo_basic, pos), offsetof(t_vbo_basic, npos), NULL},
	{offsetof(t_vbo_basic, col), offsetof(t_vbo_basic, ncol), NULL},
	{offsetof(t_vbo_basic, tex), offsetof(t_vbo_basic, ntex), NULL},
	{offsetof(t_vbo_basic, nor), offsetof(t_vbo_basic, nnor), NULL},
};

#define TAB_SIZE (sizeof(g_vbo_basic_offsets) / sizeof(*g_vbo_basic_offsets))

static int		fill_gab(t_env const *e, t_mesh const *me
						 , t_vbo_basic raw_vbo[1])
{
	t_vshader const *const	vshader = VSOFME(e, me);
	t_location const		*loc = vshader->locations;
	t_location const *const	locend = loc + vshader->n_locations;
	t_byte					s_cur;
	t_byte					s_wished;

	while (loc < locend)
	{
		s_cur = *(t_byte*)((void*)raw_vbo + g_backup_fill[loc->type].noff);
		s_wished = loc->size;
		if (s_cur == 0 && g_backup_fill[loc->type].fun != NULL)
		{
			//fill
			s_cur = *(t_byte*)((void*)raw_vbo + g_backup_fill[loc->type].noff);
		}
		if (s_cur != s_wished)
			return (ERRORF("s_cur == %hhu", s_cur), 1);
		/* qprintf("HELLO: %hhu/%hhu\n", s_cur, s_wished); */
		loc++;
	}
	return (0);
}

int				sp_fill_mesh(t_env const *e, t_mesh *me)
{
	t_vbo_basic          raw_vbo[1];

	bzero(raw_vbo, sizeof(t_vbo_basic));
	if (NORM_AT_42_IS_WTF(e, me))
		return (ERROR("me->fill(e, me)"), 1);
	fill_gab(e, me, raw_vbo);
	return (0);
}
