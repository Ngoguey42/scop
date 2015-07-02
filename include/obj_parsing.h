/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parsing.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/02 15:48:15 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/02 17:37:03 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_PARSING_H
# define OBJ_PARSING_H

# include "scop.h"
# include "ft_vector.h"

typedef struct			s_token
{
	char				*header;
	int					(*fun)();
	size_t				pad;
}						t_token;

int		skip_line(FILE *stream);
int		parse_word(FILE *stream, char **dst);
int		parse_state(FILE *stream, t_bool *dst);
int		parse_3float(FILE *stream, t_ftvector *dst);
int		parse_3uint(FILE *stream, t_ftvector *dst);

#define BADEOF DEBUGF("Unexpected EOF")
#define BADSTREAM DEBUGF("Error on stream: \"%s\"", strerror(errno))
#define STREAM_STATUS_BAD2 (ferror(stream) || feof(stream))
#define STREAM_STATUS_BAD (ferror(stream))
#define STREAM_ERR_MSG ferror(stream) ? BADSTREAM : BADEOF

#endif
