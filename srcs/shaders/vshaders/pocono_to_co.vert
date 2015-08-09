// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   pocono_to_co.vert                                  :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/07/27 18:22:28 by ngoguey           #+#    #+#             //
//   Updated: 2015/08/09 13:29:01 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#version 410 core

layout (location = 0) in vec3	pos;
layout (location = 1) in vec3	col;
layout (location = 2) in vec3	nor;

out vec3						ourColor;
out vec3						Normal;
out vec3						fragPos;

uniform mat4					model;
uniform mat4					viewproj;

void main()
{
	Normal = mat3(transpose(inverse(model))) * nor;
	ourColor = col;
	gl_Position = model * vec4(pos, 1.f);
	fragPos = vec3(gl_Position);	
	gl_Position = viewproj * gl_Position;
}
