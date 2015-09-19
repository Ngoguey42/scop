// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   landrender.tesc                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/19 17:26:06 by ngoguey           #+#    #+#             //
//   Updated: 2015/09/19 18:45:22 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

layout                      (vertices = 3) out;

uniform vec3                vCamPos;
uniform float				dRangeTess;
uniform float				tessLevelInRange;

#define	DNEARESTTESS		1.f
#define MINTESSLEVELIN		1.f
#define POWERTESS			4.f
// uniform vec3                posfactor;
// uniform sampler2D               ymap;
// uniform sampler2D               normap;

in	StPoNo
{
	vec2					st;
	vec3					pos;
	vec3					nor;
}							tc_in[];

out	St
{
	vec2					st;
}							tc_out[];

float	tess_from_dist(float d)
{
	return (pow(1.f - max(min((d - DNEARESTTESS)
							  / dRangeTess, 1.f), 0.f), POWERTESS))
		* tessLevelInRange + MINTESSLEVELIN;
}

void	calc_tess_levels()
{
	float	d0 = distance((tc_in[1].pos + tc_in[2].pos) / 2.f, vCamPos);
	float	d1 = distance((tc_in[2].pos + tc_in[0].pos) / 2.f, vCamPos);
	float	d2 = distance((tc_in[0].pos + tc_in[1].pos) / 2.f, vCamPos);
	// float	d0 = distance((tc_in[0].pos + tc_in[1].pos) / 2.f, vCamPos);
	// float	d1 = distance((tc_in[1].pos + tc_in[2].pos) / 2.f, vCamPos);
	// float	d2 = distance((tc_in[2].pos + tc_in[0].pos) / 2.f, vCamPos);
	float	dVerCam = (d0 + d1 + d2) / 3.f;

	gl_TessLevelInner[0] = tess_from_dist(dVerCam);
		// pow(1.f - max(min((dVerCam - DNEARESTTESS) / dRangeTess, 1.f), 0.f), POWERTESS)
		// * tessLevelInRange + MINTESSLEVELIN;
	gl_TessLevelOuter[0] = max(tess_from_dist(d0) / 2.f, 1.f);
	gl_TessLevelOuter[1] = max(tess_from_dist(d1) / 2.f, 1.f);
	gl_TessLevelOuter[2] = max(tess_from_dist(d2) / 2.f, 1.f);
	// gl_TessLevelOuter[1] = gl_TessLevelOuter[2]
	// 	= max(gl_TessLevelInner[0] / 2.f, 1.f);
	return ;
}

void	main()
{
	tc_out[gl_InvocationID].st = tc_in[gl_InvocationID].st;
	if (gl_InvocationID != 0)
		return ;
	calc_tess_levels();
	return ;
}
