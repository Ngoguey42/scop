/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objmodel.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/20 16:15:35 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/27 11:15:01 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJMODEL_H
# define OBJMODEL_H

# include "ft_vector.h"

typedef struct  s_objmodel
{
	char        *filepath;
	t_ftvector  coords;
	t_ftvector  textures;
	t_ftvector  normals;
	t_ftvector  faces;
	size_t		width;
	t_ftvector  vertices;
}               t_objmodel;

void			op_init_instance(t_objmodel *m, char const *filepath);
int				op_parse_obj(t_objmodel *m);
void			sp_clean_objmodel(t_objmodel *m);
void			op_swap_vectors(t_objmodel *m, t_ftvector *v, t_ftvector *f);

#endif
