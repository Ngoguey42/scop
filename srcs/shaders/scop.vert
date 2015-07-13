// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   scop.vert                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/30 17:43:59 by ngoguey           #+#    #+#             //
//   Updated: 2015/07/13 11:20:28 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#version 410 core

layout (location = 0) in vec3 position;
// layout (location = 1) in vec3 color;

out vec3 ourColor;

// uniform mat4 transform;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0);
	if (gl_VertexID % 3 == 0)
		ourColor = vec3(1.f, 0.f, 0.f);
	else if (gl_VertexID % 3 == 1)
		ourColor = vec3(0.f, 1.f, 0.f);
	else
		ourColor = vec3(0.f, 0.f, 1.f);
}
