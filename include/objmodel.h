/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objmodel.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/20 16:15:35 by ngoguey           #+#    #+#             */
/*   Updated: 2015/08/09 16:42:13 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJMODEL_H
# define OBJMODEL_H

# include "ft_vector.h"
# include "vertex.h"

typedef struct  s_objmodel
{
	t_ftvector  coords;
	t_ftvector  textures;
	t_ftvector  normals;
	t_ftvector  faces;
	size_t		width;
	t_ftvector  vertices;
}               t_objmodel;

int				op_parse_obj(t_objmodel *m, char const *filepath);
void			sp_clean_objmodel(t_objmodel *m);
void			op_retreive_data(t_objmodel const *m, t_vbo_basic *v
									, t_ftvector *f);

#endif
