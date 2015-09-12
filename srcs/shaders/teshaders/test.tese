// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   test.tese                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/12 09:58:28 by ngoguey           #+#    #+#             //
//   Updated: 2015/09/12 14:32:33 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#version 410 core

layout						(triangles, equal_spacing, ccw) in;

															uniform mat4                    viewproj;
															uniform mat4                    model;
															
in Po
{
	vec3					pos;
}							tec_in[];

out Po
{
	vec3					pos;
}							tec_out;
/*
vec2	interpolate2D(vec2 v0, vec2 v1, vec2 v2)
{
	return vec2(gl_TessCoord.x) * v0
		+ vec2(gl_TessCoord.y) * v1
		+ vec2(gl_TessCoord.z) * v2;
}
*/

#define EPS 0.1f
#define ISZERO(V) (V < EPS && V > -EPS)

vec3	interpolate3D(vec3 v0, vec3 v1, vec3 v2)
{
	return vec3(gl_TessCoord.x) * v0
		+ vec3(gl_TessCoord.y) * v1
		+ vec3(gl_TessCoord.z) * v2;
}

void	main()
{
	vec4	vWpos =
		(
		vec4(interpolate3D(tec_in[0].pos, tec_in[1].pos, tec_in[2].pos), 1.f)
			);
	tec_out.pos = vec3(vWpos);
	return ;
}
