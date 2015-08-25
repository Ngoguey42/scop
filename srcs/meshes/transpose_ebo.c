/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transpose_ebo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/24 18:23:03 by ngoguey           #+#    #+#             */
/*   Updated: 2015/08/25 15:45:30 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <stdlib.h>

typedef struct s_transposed_ebo
{
	t_ui		count;
	t_ui		*faces;
} t_transposed_ebo;

static void		fill_count(t_ftvector *occurances, t_ui const vindices[3])
{
	t_transposed_ebo const	def = {0, NULL};
	size_t					i;
	t_ui					vindex;

	i = 0;
	while (i < 3)
	{
		vindex = vindices[i];
		if (vindex >= occurances->size)
			if (ftv_insert_count(occurances, &def
				, vindex - occurances->size + 1))
				ft_enomem();
		((t_transposed_ebo*)occurances->data)[vindex].count++;
		i++;
	}
	return ;
}

static void		init_alloc(void *ptr, t_transposed_ebo *tebo)
{
	t_ui		i;

	if ((tebo->faces = malloc(sizeof(t_ui) * tebo->count)) == NULL)
		ft_enomem();
	i = 0;
	while (i < tebo->count)
	{
		tebo->faces[i] = -1;
		i++;
	}
	tebo->count = 0;
	return ;
	(void)ptr;
}

static void		fill_alloc(t_ftvector *occurances, t_ui const vindices[3]
								, t_ui faceid)
{
	size_t				i;
	t_transposed_ebo	*vertptr;
	
	i = 0;
	while (i < 3)
	{
		vertptr = ((t_transposed_ebo*)occurances->data) + vindices[i];
		vertptr->faces[vertptr->count++] = faceid;
		i++;
	}
	return ;
}

void debug(void *ptr, t_transposed_ebo const *tebo)
{
	size_t	i;

	i = 0;
	while (i < tebo->count)
	{
		qprintf("(%2u)", tebo->faces[i]);
		i++;
	}
	qprintf("\n");
	(void)ptr;
	return ;
}

void			sp_transpose_ebo(t_ftvector *dst, t_ftvector const *faces)
{
	ftv_init_instance(dst, sizeof(t_transposed_ebo));
	ftv_foreach(faces, &fill_count, dst);
	ftv_foreach(dst, &init_alloc, NULL);
	ftv_foreachi(faces, &fill_alloc, dst);
	ftv_foreach(dst, &debug, NULL);
	return ;
}
