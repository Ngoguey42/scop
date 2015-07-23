// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   item.vert                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/07/18 15:04:28 by ngoguey           #+#    #+#             //
//   Updated: 2015/07/23 13:06:30 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#version 410 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec2 normal;

// out vec3 ourColor;
out vec2 texUV;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	// gl_Position = model * vec4(position, 1.0);
	// if (gl_Position.y > 2.f)
	// {
	// 	if (gl_VertexID % 3 == 0)
	// 		ourColor = vec3(1.f, 0.f, 0.f);
	// 	else if (gl_VertexID % 3 == 1)
	// 		ourColor = vec3(0.f, 1.f, 0.f);
	// 	else
	// 		ourColor = vec3(0.f, 0.f, 1.f);
	// }
	// else if (gl_Position.y > 1.f)
	// 	ourColor = vec3(1.f, 0.f, 0.f);
	// else if (gl_Position.y < -1.f)
	// 	ourColor = vec3(0.f, 1.f, 0.f);
	// else
	// {
	// 	float ratio = (gl_Position.y + 1.f) / 2.f;
	// 	ourColor = vec3(ratio, 1.f - ratio, 0.f);
	// }
	// ourColor = vec3(texCoord, 0.f);
	texUV = texCoord;
	gl_Position = projection * view * model * vec4(position, 1.f);
}
