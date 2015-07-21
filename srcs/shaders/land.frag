// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   scop.frag                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/06/30 17:44:08 by ngoguey           #+#    #+#             //
//   Updated: 2015/07/01 15:09:16 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#version 410 core

in vec3 ourColor;

out vec4 color;

void main()
{
	color = vec4(ourColor, 1.0f);
} 
