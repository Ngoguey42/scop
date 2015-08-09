/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cogconf1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/08 14:03:36 by ngoguey           #+#    #+#             */
/*   Updated: 2015/08/09 14:09:51 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <string.h>

#ifndef NARG
# define NARG_(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,N,...) N
# define NARG(...) NARG_(__VA_ARGS__,11,10,9,8,7,6,5,4,3,2,1)
#endif
#define LOC(T, S) ((t_location){(T), (S)})
#define VSHADER(N,F,...) {VSHD_PATH(N), F, NARG(__VA_ARGS__), {__VA_ARGS__}, 0}
#define FSHADER(N, F) {FSHD_PATH(N), (F), 0}
#define GSHADER(N, F) {GSHD_PATH(N), (F), 0}
#define PROG(VS,FS,GS) {VS, FS, GS, 0}

/*
**	[[[cog
**	import cog
**	cog.outl("*" "/")
**	from scop_confloader import output_cconf1
**	output_cconf1()
**	cog.outl("/" "*")
**	]]]
*/
int			sp_loadconf_vshaders(t_env *e)
{
	t_vshader const		tmp[sp_num_vshaders] = {

	VSHADER("po_to_co.vert", &sp_unif_viewproj2,
	LOC(sp_pos_loc, 3)),
	VSHADER("pocote_to_couv.vert", &sp_unif_viewproj2,
	LOC(sp_pos_loc, 3), LOC(sp_col_loc, 3), LOC(sp_tex_loc, 2)),
	VSHADER("pote_to_couv.vert", &sp_unif_viewproj2,
	LOC(sp_pos_loc, 3), LOC(sp_tex_loc, 2)),
	VSHADER("poco_to_co.vert", &sp_unif_viewproj,
	LOC(sp_pos_loc, 3), LOC(sp_col_loc, 3)),
	VSHADER("poteno_to_uv.vert", &sp_unif_viewproj,
	LOC(sp_pos_loc, 3), LOC(sp_tex_loc, 2), LOC(sp_nor_loc, 3)),
	VSHADER("pocono_to_co.vert", &sp_unif_viewproj,
	LOC(sp_pos_loc, 3), LOC(sp_col_loc, 3), LOC(sp_nor_loc, 3)),
	VSHADER("po_to_noop.vert", &sp_unif_viewproj,
	LOC(sp_pos_loc, 3)),
	};
	memcpy(&e->vshaders, &tmp, sizeof(tmp));
	return (0);
}

int			sp_loadconf_fshaders(t_env *e)
{
	t_fshader const		tmp[sp_num_fshaders] = {

	FSHADER("co_identity.frag", NULL),
	FSHADER("uv_identity.frag", NULL),
	FSHADER("couv_blend.frag", NULL),
	FSHADER("couv_uv.frag", NULL),
	FSHADER("uvno_uvli.frag", &sp_unif_light),
	FSHADER("cono_coli.frag", &sp_unif_light),
	FSHADER("couvno_blendli.frag", &sp_unif_light),
	FSHADER("co_sun.frag", &sp_unif_suncolor),
	};
	memcpy(&e->fshaders, &tmp, sizeof(tmp));
	return (0);
}

int			sp_loadconf_gshaders(t_env *e)
{
	t_gshader const		tmp[sp_num_gshaders] = {

	GSHADER("test.geom", NULL),
	};
	memcpy(&e->gshaders, &tmp, sizeof(tmp));
	return (0);
}

int			sp_loadconf_programs(t_env *e)
{
	t_program const		tmp[sp_num_programs] = {

	PROG(sp_po_to_co_vshader, sp_co_identity_fshader, sp_no_gshader),
	PROG(sp_pocote_to_couv_vshader, sp_couv_uv_fshader, sp_no_gshader),
	PROG(sp_pote_to_couv_vshader, sp_couv_uv_fshader, sp_no_gshader),
	PROG(sp_pocono_to_co_vshader, sp_cono_coli_fshader, sp_no_gshader),
	PROG(sp_poteno_to_uv_vshader, sp_couvno_blendli_fshader, sp_test_gshader),
	PROG(sp_pocono_to_co_vshader, sp_cono_coli_fshader, sp_no_gshader),
	PROG(sp_po_to_noop_vshader, sp_co_sun_fshader, sp_no_gshader),
	};
	memcpy(&e->programs, &tmp, sizeof(tmp));
	return (0);
}

/*
**	[[[end]]]
*/
