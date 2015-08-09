// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   pocote_to_couv.vert                                :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/07/27 14:20:47 by ngoguey           #+#    #+#             //
//   Updated: 2015/08/09 13:27:50 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#version 410 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 col;
layout (location = 2) in vec2 tex;

out vec3 ourColor;
out vec2 texUV;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	ourColor = col;
	texUV = tex;
	gl_Position = projection * view *model * vec4(pos, 1.0);
}
