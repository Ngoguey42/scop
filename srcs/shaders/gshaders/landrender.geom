// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   landrender.geom                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/19 09:54:51 by ngoguey           #+#    #+#             //
//   Updated: 2015/09/19 10:17:30 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

layout                  (triangles) in;
layout                  (triangle_strip, max_vertices = 3) out;

uniform mat4            viewproj;

in PoNo
{
	vec3                pos;
	vec3                nor;
}                       gs_in[];

out CoNo
{
	vec3				pos;
	vec3                col;
	vec3                nor;
}                       gs_out;

#define NSHADES 24
#define DELTA (125 / NSHADES)

void		main()
{
	float		val = (50.f + (gl_PrimitiveIDIn % NSHADES) * DELTA) / 255.f;

	gs_out.col = vec3(val);
	for (int i = 0; i < 3; i++)
	{
		gs_out.pos = gs_in[i].pos;
		gs_out.nor = gs_in[i].nor;
		gl_Position = viewproj * vec4(gs_in[i].pos, 1.f);
		EmitVertex();
	}
	EndPrimitive();
	return ;
}
