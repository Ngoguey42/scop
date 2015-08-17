// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   face_rgb.geom                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/08/17 13:18:02 by ngoguey           #+#    #+#             //
//   Updated: 2015/08/17 13:18:03 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#version 410 core

layout					(triangles) in;
layout					(triangle_strip, max_vertices = 3) out;

in PoUvNo
{
	vec3				pos;
	vec2				tex;
	vec3				nor;
}						gs_in[];

out PoCoUvNo
{
	vec3				pos;
	vec3				col;
	vec2				tex;
	vec3				nor;
}						gs_out;

#define NSHADES 24
#define THIRD (NSHADES / 3)
#define DELTA (200 / THIRD)

void main()
{
	int			i;
	int			colorid = gl_PrimitiveIDIn % NSHADES;

	if (colorid < THIRD)
		gs_out.col = vec3((colorid % THIRD * DELTA + 50) / 255.f, 0.f, 0.f);
	else if (colorid < THIRD * 2)
		gs_out.col = vec3(0.f, (colorid % THIRD * DELTA + 50) / 255.f, 0.f);
	else
		gs_out.col = vec3(0.f, 0.f, (colorid % THIRD * DELTA + 50) / 255.f);
	for (i = 0; i < 3; i++)
	{
		gs_out.tex = gs_in[i].tex;
		gs_out.nor = gs_in[i].nor;
		gs_out.pos = gs_in[i].pos;
		gl_Position = gl_in[i].gl_Position;
		EmitVertex();
	}
	EndPrimitive();
}
