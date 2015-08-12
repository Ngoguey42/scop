/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vbo.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/10 11:42:30 by ngoguey           #+#    #+#             */
/*   Updated: 2015/08/12 17:15:56 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VBO_H
# define VBO_H

enum							e_location_type
{
	sp_pos_loc,
	sp_col_loc,
	sp_tex_loc,
	sp_nor_loc,
	sp_num_locs,
};
typedef struct					s_location
{
	enum e_location_type		type:8;
	t_byte						size;
}								t_location;
typedef struct					s_locations_backup_fill
{
	t_byte						noff;
	void						(*fun)();
}								t_locations_backup_fill;

# define V4Z {0.f, 0.f, 0.f, 0.f}
# define V3Z {0.f, 0.f, 0.f}
# define V2Z {0.f, 0.f}

# define BVERT_POS(X, Y, Z) {{(X), (Y), (Z)}, V4Z, V2Z, V3Z}
# define BVERT_POSCOL(X,Y,Z,R,G,B) {{(X),(Y),(Z)}, {(R),(G),(B),0.f}, V2Z, V3Z}

typedef struct					s_vertex_basic
{
	struct
	{
		float					x;
		float					y;
		float					z;
	}							pos;
	struct
	{
		float					r;
		float					g;
		float					b;
		float					a;
	}							col;
	struct
	{
		float					u;
		float					v;
	}							tex;
	struct
	{
		float					x;
		float					y;
		float					z;
	}							nor;
}								t_vertex_basic;

typedef struct					s_vbo_basic
{
	t_ftvector					vertices;
	t_byte						npos;
	t_byte						ncol;
	t_byte						ntex;
	t_byte						nnor;
}								t_vbo_basic;

#endif
