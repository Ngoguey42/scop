// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   scop.vert                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/30 17:43:59 by ngoguey           #+#    #+#             //
//   Updated: 2015/06/30 17:44:01 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#version 410 core

layout (location = 0) in vec3 position;

void main()
{
	gl_Position = vec4(position.x, position.y, position.z, 1.0);
}
