/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objmodel_parsing.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/15 08:49:22 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/20 12:03:28 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJMODEL_PARSING_H
# define OBJMODEL_PARSING_H

# include "scop.h"
# include "ft_vector.h"
# include <stdio.h>


typedef struct	s_objmodel
{
	char		*filepath;
	t_ftvector	vertices;
	t_ftvector	faces;
	char		*mtllib;
	char		*name;
	char		*usemtl;
	t_bool		smooth;
}				t_objmodel;

typedef struct	s_token
{
	char		*h;
	int			(*fun)();
	size_t		pad;
}				t_token;

int				op_parse_obj(t_objmodel *m);
int				op_match_str(FILE *stream, char const *h, char **dst);
int				op_match_comment(FILE *stream);
int				op_match_bool(FILE *stream, char const *h, t_bool *dst);
int				op_match_vertices(FILE *stream, char const *h, t_objmodel *m);
int				op_match_faces(FILE *stream, char const *h, t_objmodel *m);

#endif
