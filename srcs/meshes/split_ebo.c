/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_ebo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/25 15:52:54 by ngoguey           #+#    #+#             */
/*   Updated: 2015/08/25 16:44:22 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <stdlib.h>

typedef struct s_transposed_ebo
{
	t_ui        count;
	t_ui        *faces;
} t_transposed_ebo;

typedef struct s_facenormals
{
	t_ui        indices[3];
	t_vector3	normal;
} t_facenormals;

void		sp_split_ebo(t_vbo_basic *vbo, t_ftvector *faces, int (*fun)())
{
	t_ftvector		transposed[1];
	t_ftvector		facenormals[1];

	/* ftv_print(faces, "uuu"); */
	sp_transpose_ebo(transposed, faces);
	sp_get_facenormals(facenormals, vbo, faces);
	(void)fun;
	return ;
}
