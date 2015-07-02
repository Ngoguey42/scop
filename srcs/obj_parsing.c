/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/02 13:21:56 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/02 13:55:32 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
/* #include <fcntl.h> */

#define BADLOAD_FMT "Could not open %s \"\033[35m%s\033[0m\""
#define BADREAD_FMT "Error while reading %s \"\033[35m%s\033[0m\""
#define BADFACE_FMT "Corruped face in %s: %u %u %u"

int				sp_parse_obj(t_objmodel *m)
{
	FILE	*stream;
	float		f[3];
	unsigned int		ui[3];
	unsigned int		nv;
	
	stream = fopen(m->filepath, "r");
	if (stream == NULL)
		return (DEBUGF(BADLOAD_FMT, m->filepath, strerror(errno)), 1);

	while (fscanf(stream, "v %f %f %f\n", f, f + 1, f + 2) > 0)
	{
		if (ftv_push_back(&m->vertices, f))
			sp_enomem();
	}
	if (ferror(stream))
		return (DEBUGF(BADREAD_FMT, m->filepath, strerror(errno)), 1);
	nv = m->vertices.size;
	qprintf("Found %u vertices\n", m->vertices.size);
	while (fscanf(stream, "f %u %u %u\n", ui, ui + 1, ui + 2) > 0)
	{
		if (ui[0] == 0 || ui[1] == 0 || ui[2] == 0 ||
			ui[0] > nv || ui[1] > nv || ui[2] > nv)
			return (DEBUGF(BADFACE_FMT, m->filepath, ui[0], ui[1], ui[2]), 1);
		if (ftv_push_back(&m->faces, ui))
			sp_enomem();
	}	
	if (ferror(stream))
		return (DEBUGF(BADREAD_FMT, m->filepath, strerror(errno)), 1);
	qprintf("Found %u faces\n", m->faces.size);
	fclose(stream);
	return (0);
}
