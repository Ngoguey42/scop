/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objmodel.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/20 16:15:35 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/23 08:41:23 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJMODEL_H
# define OBJMODEL_H

# include "ft_vector.h"

typedef struct  s_objmodel
{
	char        *filepath;
	t_ftvector  vertices;
	t_ftvector  coords;
	t_ftvector  textures;
	t_ftvector  normals;
	t_ftvector  faces;
	char        *mtllib;
	char        *name;
	char        *usemtl;
	size_t		width;
	t_bool      smooth;
}               t_objmodel;

void			op_init_instance(t_objmodel *m, char const *filepath);
int				op_parse_obj(t_objmodel *m);
void			op_swap_vectors(t_objmodel *m, t_ftvector *v, t_ftvector *f);
void        sp_wrap_texture_planxy(t_objmodel *m, float scale, float imgratio);

#endif
