/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tga.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/17 12:00:25 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/28 13:15:57 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include "fterror.h"
#include "libft.h"
#include "ft_vector.h"

static int	parse_header(int fd, t_ui dim[2])
{
	t_byte	buf[18];
	int		ret;

	if ((ret = read(fd, buf, 18)) != 18)
	{
		if (ret < 0)
			return (ERRORNO("read(fd, buf, 18)"), 1);
		else
			return (ERRORF("read %d/18 bytes", ret), 1);
	}
	if (buf[0x02] != 0x2)
		return (ERRORF("Wrong image type (%#x)", buf[0x02]), 1);
	if (buf[0x10] != 0x20)
		return (ERRORF("Wrong image bpp (%#x)", buf[0x10]), 1);
	dim[0] = buf[0x0c] + (buf[0x0d] << 0x8);
	dim[1] = buf[0x0e] + (buf[0x0f] << 0x8);
	if (dim[0] == 0 || dim[1] == 0)
		return (ERRORF("Wrong image size %u/%u", dim[0] == 0, dim[1]), 1);
	return (0);
}

static int	parse_pix(int fd, t_ftvector *v, int npix)
{
	t_byte	buf[1024];

	while (npix >= (int)sizeof(buf) / 4)
	{
		if (read(fd, buf, sizeof(buf)) != (int)sizeof(buf))
			return (ERROR("Unexpected end of file"), 1);
		if (ftv_insert_range(v, buf, sizeof(buf) / 4))
			sp_enomem();
		npix -= sizeof(buf) / 4;
	}
	while (npix > 0)
	{
		if (read(fd, buf, 4) != 4)
			return (ERROR("Unexpected end of file"), 1);
		ftv_push_back_unsafe(v, &buf);
		npix--;
	}
	return (0);
}

int			parse_tga(char const *filepath, t_ftvector *v, t_ui dim[2])
{
	int const	fd = open(filepath, O_RDONLY);

	if (fd < 0)
		return (ERRORNOF("open(%s, O_RDONLY)", filepath), 1);
	if (parse_header(fd, dim))
		return (ERROR("parse_header(...)"), 1);
	if (ftv_reserve(v, dim[0] * dim[1]))
		sp_enomem();
	if (parse_pix(fd, v, dim[0] * dim[1]))
		return (ERROR("parse_pix(...)"), 1);
	close(fd);
	return (0);
}
