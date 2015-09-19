// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   landrender.geom                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/19 09:54:51 by ngoguey           #+#    #+#             //
//   Updated: 2015/09/19 09:57:12 by ngoguey          ###   ########.fr       //
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

void		main()
{
	for (int i; i < 3; i++)
	{
		gl_Position = viewproj * vec4(gs_in[i].pos, 1.f);
		EmitVertex();
	}
	EndPrimitive();
	return ;
}
