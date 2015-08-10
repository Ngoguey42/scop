/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obs_fill.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/22 13:44:32 by ngoguey           #+#    #+#             */
/*   Updated: 2015/08/10 18:09:09 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <math.h>
#include <stdarg.h>
#include <string.h>

#ifndef NARG
# define NARG2(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Z,...) Z
# define NARG1(...) NARG2(__VA_ARGS__,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0)
# define NARG(...) NARG1(42, ##__VA_ARGS__)
#endif

#define OB(T,...) push_ob(e,(t_ob[1]){dob((T),NARG(__VA_ARGS__),##__VA_ARGS__)})

static void	push_ob(t_env *e, t_ob const *ob)
{
	t_program_index const	pi = MEOFOB(e, ob)->program;

	if (ftl_push_back(e->obs + pi, (t_ftlist_node const*)ob))
		sp_enomem();
	return ;
}

typedef enum		e_ob_param
{
	ob_hid,
	ob_mov,
	ob_pos,
	ob_rot,
	ob_sca,
	ob_up,
	ob_vf,
	ob_vi,
	ob_num_param,
}					t_ob_param;

static size_t const		g_obdata[][2] =
{
	{offsetof(t_ob, hidden), sizeof(t_bool)},
	{offsetof(t_ob, moved), sizeof(t_bool)},
	{offsetof(t_ob, position), sizeof(t_vector3)},
	{offsetof(t_ob, rotation), sizeof(t_vector3)},
	{offsetof(t_ob, scale), sizeof(t_vector3)},
	{offsetof(t_ob, update), sizeof(void(*)())},
	{offsetof(t_ob, valf), sizeof(float[1])},
	{offsetof(t_ob, vali), sizeof(float[1])},
};

 //doesnt handle valf and vali
void		retreive_varg(va_list *ap, t_ob_param id, void *buf)
{
	if (id == ob_hid)
		(*(t_bool*)buf) = va_arg(*ap, t_bool);
	else if (id == ob_mov)
		(*(t_bool*)buf) = va_arg(*ap, t_bool);
	else if (id == ob_pos)
		(*(t_vector3*)buf) = va_arg(*ap, t_vector3);
	else if (id == ob_rot)
		(*(t_vector3*)buf) = va_arg(*ap, t_vector3);
	else if (id == ob_sca)
		(*(t_vector3*)buf) = va_arg(*ap, t_vector3);
	else if (id == ob_up)
		(*(void(**)())buf) = va_arg(*ap, void(*)());
	return ;
}

t_ob		dob(t_model_index moi, int narg, ...)
{
	va_list		ap;
	t_ob		tmp;
	t_ob_param	paramid;
	t_byte		buf[sizeof(t_vector3)];

	tmp = sp_default_ob(moi);
	va_start(ap, narg);
	while (narg >= 2)
	{
		paramid = va_arg(ap, t_ob_param);
		retreive_varg(&ap, paramid, buf);
		memcpy(((void*)&tmp) + g_obdata[paramid][0], buf, g_obdata[paramid][1]);
		narg -= 2;
	}
	va_end(ap);
	return (tmp);
}

int			sp_fill_obs(t_env *e)
{
	OB(sp_plane_model);
	OB(sp_square_model, ob_sca, ATOV3SCAL(4.f), ob_pos, ATOV3(0.f, -5.f, 2.f));
	OB(sp_land_model);
	OB(sp_ptn_model, ob_rot, ATOV3(0.f, 0.f, -M_PI / 2.f)
		, ob_pos, ATOV3(-45.f, -0.f, -40.f));
	OB(sp_sun_model, ob_up, &sp_obupdate_sun, ob_mov, false);
	return (0);
}
