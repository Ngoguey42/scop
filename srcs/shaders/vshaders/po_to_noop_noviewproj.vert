// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   po_to_noop_noviewproj.vert                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/08/18 15:50:56 by ngoguey           #+#    #+#             //
//   Updated: 2015/08/18 15:51:10 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#version 410 core

layout (location = 0) in vec3	pos;

uniform mat4					model;

void main()
{
	gl_Position = model * vec4(pos, 1.f);
}
