// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   pos_to_cubemap.geom                                :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/08/18 15:51:58 by ngoguey           #+#    #+#             //
//   Updated: 2015/08/18 15:54:36 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#version 410 core

layout				(triangles) in;
layout				(triangle_strip, max_vertices=18) out;
				   
uniform mat4		shadowMatrices[6];

out vec4			pos;

void main()
{
	for (int face = 0; face < 6; ++face)
	{
		gl_Layer = face;
		for (int i = 0; i < 3; ++i)
		{
			pos = gl_in[i].gl_Position;
			gl_Position = shadowMatrices[face] * pos;
			EmitVertex();
		}
		EndPrimitive();
	}
} 
