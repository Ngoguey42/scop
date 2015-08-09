/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/09 13:09:52 by ngoguey           #+#    #+#             */
/*   Updated: 2015/08/09 14:09:08 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VERTEX_H
# define VERTEX_H

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
	t_byte						npos;
	t_byte						ncol;
	t_byte						ntex;
	t_byte						nnor;
}								t_vbo_basic;

#endif
