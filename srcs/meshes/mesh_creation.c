/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/03 14:25:20 by ngoguey           #+#    #+#             */
/*   Updated: 2015/09/03 15:24:22 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#incude "scop.h"

t_byte const		g_vbo_offsets[][2] = {
	{offsetof(t_vertex_basic, pos), offsetof(t_vbo_basic, npos)},
	{offsetof(t_vertex_basic, col), offsetof(t_vbo_basic, ncol)},
	{offsetof(t_vertex_basic, tex), offsetof(t_vbo_basic, ntex)},
	{offsetof(t_vertex_basic, nor), offsetof(t_vbo_basic, nnor)}
};

char const			*g_locations_str[] = {
	"pos",
	"col",
	"tex",
	"nor"
};

static int	validate_vbo(t_vbo_basic const *vbo, t_vshader const *vs)
{
	size_t		i;
	int			error;
	t_byte		num_elt_vbo;
	t_byte		num_elt_vs;

	error = 0;
	i = 0;
	while (i < SIZE_ARRAY(g_vbo_offsets))
	{
		num_elt_vbo = *REACH_OFFSET(t_byte, vbo, g_vbo_offsets[i][1]);
		num_elt_vs = vs[i];//get_num_elt_vs(vs, i);
		if (num_elt_vbo != num_elt_vs)
		{
			ERRORF("%s(%hhu/%hhu)"
				   , g_locations_str[i], num_elt_vbo, num_elt_vs);
			error = 1;
		}
		i++;
	}
	return (error);
}

int		sp_new_mesh(t_env const *e, t_mesh *me)
{
	t_vao_basic				vao[1];
	t_vshader const *const	vs = VSOFME(e, me);
	t_ftvector				vbo_final[1];
	t_ftvector				ebo_final[1];

	if (sp_build_vao_primary(vao, vs))
		return (ERROR("sp_build_vao_primary(vao, vs)"), 1);
	if (validate_vbo(&vao->vbo, vs))
		return (ERROR("validate_vbo(...)"), 1);
	sp_build_vao_final(vbo_final, ebo_final, vao);
	sp_push_vao(me, vs, vbo_final, ebo_final);
	ftv_release(&vao->vbo.vertices, NULL);
	ftv_release(&vao->ebo.faces, NULL);
	ftv_release(vbo_final, NULL);
	ftv_release(ebo_final, NULL);
	return (0);
}
