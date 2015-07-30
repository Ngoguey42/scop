// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   test.geom                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/07/30 08:53:45 by ngoguey           #+#    #+#             //
//   Updated: 2015/07/30 11:03:39 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#version 410 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in UVNOFP
{
	vec2	texUV;
	vec3	Normal;
	vec3	fragPos;
}       gs_in[];

out COUVNOFP
{
	vec3	Color;
	vec2	texUV;
	vec3	Normal;
	vec3	fragPos;
}	gs_out;

#define NSHADES 24
#define THIRD (NSHADES / 3)
#define DELTA (200 / THIRD)

void main()
{
	int		i;
	int		colorid = gl_PrimitiveIDIn % NSHADES;

	if (colorid < THIRD)
		gs_out.Color = vec3((colorid % THIRD * DELTA + 50) / 255.f, 0.f, 0.f);
	else if (colorid < THIRD * 2)
		gs_out.Color = vec3(0.f, (colorid % THIRD * DELTA + 50) / 255.f, 0.f);
	else
		gs_out.Color = vec3(0.f, 0.f, (colorid % THIRD * DELTA + 50) / 255.f);	
	for (i = 0; i < 3; i++)
	{
		gs_out.texUV = gs_in[i].texUV;
		gs_out.Normal = gs_in[i].Normal;
		gs_out.fragPos = gs_in[i].fragPos;
		gl_Position = gl_in[i].gl_Position;
		EmitVertex();
	}
	EndPrimitive();
}
