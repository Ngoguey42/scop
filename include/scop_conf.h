/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop_conf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/20 10:33:54 by ngoguey           #+#    #+#             */
/*   Updated: 2015/08/10 13:02:46 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_CONF_H
# define SCOP_CONF_H

# include "libft.h"
# include "ftmath.h"
# include "cog_enums.h"

# define SHD_PATH(FILENAME) ("srcs/shaders/" FILENAME)
# define VSHD_PATH(FILENAME) (SHD_PATH("vshaders/" FILENAME))
# define FSHD_PATH(FILENAME) (SHD_PATH("fshaders/" FILENAME))
# define GSHD_PATH(FILENAME) (SHD_PATH("gshaders/" FILENAME))

/*
** RESSOURCES
*/
# define RESSOURCES_PATH "res/"
# define TEXTURE_PATH(FILENAME) (RESSOURCES_PATH FILENAME)

/*
** CONFIG MACROES
*/
# define WIN_WIDTHI 1600
/* # define WIN_RATIOF (4.f / 4.f) */
# define WIN_RATIOF (4.f / 3.f)
/* # define WIN_RATIOF (16.f / 9.f) */
/* # define WIN_RATIOF (2.39f / 1.f) */
# define WIN_FOVF 45.f
# define WIN_NEARF 0.1f
# define WIN_FARF 200.f

# define LAND_SIDEF 100.f
# define LAND_RANGEF 28.f
# define LAND_COLORRAND 0.05f
# define POINTS_DEPTHI 9
# define LAND_YF -15.f

# define MOUSE_SENSITIVITYF 0.005f
# define MOVEMENT_SPEEDF 40.f

/*
** CALCULATED MACROES
*/
# define WIN_WIDTHF ((float)WIN_WIDTHI)
# define WIN_HEIGHTF (WIN_WIDTHF / WIN_RATIOF)
# define WIN_HEIGHTI ROUND_FTOI(WIN_HEIGHTF)

# define CAMERA_POSBOUNDF (M_PI / 2 * 0.98)
# define SUN_THETABOUNDF (M_PI / 2 * 0.98)
# define SUN_RBOUNDF (0.1f)
# define SUN_RSPEED (45.f)
# define SUN_ASPEED (3.f)

# define LAND_SIDEHALFF (LAND_SIDEF / 2.f)

#endif
