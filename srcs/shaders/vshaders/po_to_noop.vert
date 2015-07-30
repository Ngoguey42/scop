// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   po_to_noop.vert                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/07/30 13:19:05 by ngoguey           #+#    #+#             //
//   Updated: 2015/07/30 13:56:25 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#version 410 core

layout (location = 0) in vec3 position;

uniform mat4 viewproj;
uniform mat4 model;

void main()
{
	gl_Position = viewproj * model * vec4(position, 1.f);
}
