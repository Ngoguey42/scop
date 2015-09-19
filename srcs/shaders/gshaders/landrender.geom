// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   landrender.geom                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/19 09:54:51 by ngoguey           #+#    #+#             //
//   Updated: 2015/09/19 12:07:26 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

layout                 	 		(triangles) in;
layout                  		(triangle_strip, max_vertices = 3) out;

uniform mat4            		viewproj;
uniform sampler2D               ymap;
uniform vec3                    posfactors;
// uniform sampler2D                normap;
// uniform sampler2D                colmap;
									
in St
{
	vec2				st;
	// vec3                pos;
}                       gs_in[];

out StPoCo
{
	vec2				st;
	vec3				pos;
	vec3                col;
}                       gs_out;

#define NSHADES 24
#define DELTA (125 / NSHADES)

void		main()
{
	float		val = (50.f + (gl_PrimitiveIDIn % NSHADES) * DELTA) / 255.f;

	// gs_out.col = vec3(val);
	gs_out.col = vec3(0.5f, 0.5f, 0.f);
	for (int i = 0; i < 3; i++)
	{
		gs_out.st = gs_in[i].st;
		gs_out.pos = vec3(
			gs_in[i].st.x * posfactors.x
			, texture(ymap, gs_in[i].st).x
			, gs_in[i].st.y * posfactors.z
			);
		gl_Position = viewproj * vec4(gs_out.pos, 1.f);
		EmitVertex();
	}
	EndPrimitive();
	return ;
}
