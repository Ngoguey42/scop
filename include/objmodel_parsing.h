/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objmodel_parsing.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/15 08:49:22 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/22 18:13:03 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJMODEL_PARSING_H
# define OBJMODEL_PARSING_H

# include "libft.h"
# include "fterror.h"
# include "ft_vector.h"
# include "objmodel.h"
# include <stdio.h>

typedef struct	s_token
{
	char		*h;
	int			(*fun)();
	size_t		pad;
}				t_token;

int				op_build_vertices(t_objmodel *m);
void			op_init_faces(t_objmodel *m);
int				op_parse_obj(t_objmodel *m);
int				op_match_str(FILE *stream, char const *h, char **dst);
int				op_match_comment(FILE *stream);
int				op_match_bool(FILE *stream, char const *h, t_bool *dst);
int				op_match_v(FILE *stream, char const *h, t_objmodel *m);
int				op_match_vt(FILE *stream, char const *h, t_objmodel *m);
int				op_match_vn(FILE *stream, char const *h, t_objmodel *m);
int				op_match_faces(FILE *stream, char const *h, t_objmodel *m);

#endif
