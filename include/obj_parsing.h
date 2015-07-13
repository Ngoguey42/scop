/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parsing.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/02 15:48:15 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/13 09:42:31 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_PARSING_H
# define OBJ_PARSING_H

# include "scop.h"
# include "ft_vector.h"


typedef struct				s_token
{
	char*					h;
	int						(*fun)();
	size_t					pad;
}							t_token;

int     op_match_str(FILE *stream, char const *h, char **dst);
int     op_match_comment(FILE *stream);
int     op_match_bool(FILE *stream, char const *h, t_bool *dst);
int     op_match_vertices(FILE *stream, char const *h, t_objmodel *m);
int     op_match_faces(FILE *stream, char const *h, t_objmodel *m);

#endif
