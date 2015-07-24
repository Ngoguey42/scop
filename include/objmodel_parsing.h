/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objmodel_parsing.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/15 08:49:22 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/24 11:24:57 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJMODEL_PARSING_H
# define OBJMODEL_PARSING_H

# include "libft.h"
# include "fterror.h"
# include "ft_vector.h"
# include "objmodel.h"
# include <stdio.h>

# define BFSZ 256

typedef struct	s_token
{
	char 		*str;
	size_t		len;
	int			(*fun)();
}				t_token;


int				op_match_f(t_objmodel *m, char const *buf);
int				op_match_v(t_objmodel *m, char const *buf);
int				op_match_vt(t_objmodel *m, char const *buf);
int				op_match_vn(t_objmodel *m, char const *buf);

int				op_match_comment(t_objmodel *m, char const *buf);
int				op_match_smooth(t_objmodel *m, char const *buf);

int				op_match_group(t_objmodel *m, char const *buf);
int				op_match_mtllib(t_objmodel *m, char const *buf);
int				op_match_usemtl(t_objmodel *m, char const *buf);
int				op_match_name(t_objmodel *m, char const *buf);

// int				op_parse_obj(t_objmodel *m);
// int				op_match_str(FILE *stream, char *h, char **dst);
// int				op_match_comment(FILE *stream);
// int				op_match_bool(FILE *stream, char *h, t_bool *dst);
// int				op_match_v(FILE *stream, char *h, t_objmodel *m);
// int				op_match_vt(FILE *stream, char *h, t_objmodel *m);
// int				op_match_vn(FILE *stream, char *h, t_objmodel *m);
// int				op_match_faces(FILE *stream, char *h, t_objmodel *m);

void			op_init_meshvectors(t_objmodel *m);
void			op_insert_face(t_objmodel *m, t_ui const oldind[9]);

#endif
