/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vbo.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/10 11:42:30 by ngoguey           #+#    #+#             */
/*   Updated: 2015/08/10 11:42:37 by ngoguey          ###   ########.fr       */
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

#define ZERO_V4 {0.f, 0.f, 0.f, 0.f}
#define ZERO_V3 {0.f, 0.f, 0.f}

#define BVERT_POS(X, Y, Z) {{(X), (Y), (Z)}, ZERO_V4, {0.f, 0.f}, ZERO_V3}

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
