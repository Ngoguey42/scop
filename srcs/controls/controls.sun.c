/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.sun.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/30 15:27:27 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/31 10:05:07 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "scop.h"

#define SPH(E) ((E)->sunpos_spherical)
#define RADIUS(E) SPH((E)).x
#define THETA(E) SPH((E)).y
#define PHI(E) SPH((E)).z

#define CAR(E) ((E)->sunpos_cartesian)

static void		update_radius(t_env *e, t_bool *update)
{
	int const	mvr = e->keystates[sp_r_key] - e->keystates[sp_y_key];

	if (mvr)
	{
		*update = true;
		RADIUS(e) += e->time_el * SUN_RSPEED * (float)mvr;
	}
	return ;
}

static void		update_inclination(t_env *e, t_bool *update)
{
	int const	mvt = e->keystates[sp_f_key] - e->keystates[sp_h_key];

	if (mvt)
	{
		*update = true;
		THETA(e) += e->time_el * SUN_ASPEED * (float)mvt;
	}
	return ;
}

static void		update_azimuth(t_env *e, t_bool *update)
{
	int const	mvp = e->keystates[sp_t_key] - e->keystates[sp_g_key];

	if (mvp)
	{
		*update = true;
		PHI(e) += e->time_el * SUN_ASPEED * (float)mvp;
	}
	return ;
}

void			sp_update_sun(t_env *e, t_bool force)
{
	t_bool	update;

	update = false;
	update_radius(e, &update);
	update_inclination(e, &update);
	update_azimuth(e, &update);
	if (update || force)
	{
		if (RADIUS(e) < SUN_RBOUNDF)
			RADIUS(e) = SUN_RBOUNDF;
		CAR(e).x = RADIUS(e) * sin(PHI(e)) * cos(THETA(e));
		CAR(e).z = RADIUS(e) * sin(PHI(e)) * sin(THETA(e));
		CAR(e).y = RADIUS(e) * cos(PHI(e));
	}
	return ;
}
