// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   item.vert                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/07/18 15:04:28 by ngoguey           #+#    #+#             //
//   Updated: 2015/07/23 13:19:23 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#version 410 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec2 normal;

out vec2 texUV;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	texUV = texCoord;
	gl_Position = projection * view * model * vec4(position, 1.f);
}
