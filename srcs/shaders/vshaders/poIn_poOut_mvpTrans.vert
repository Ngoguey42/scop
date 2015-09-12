// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   poIn_poOut_mvpTrans.vert                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/12 07:39:04 by ngoguey           #+#    #+#             //
//   Updated: 2015/09/12 10:54:48 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#version 410 core

layout (location = 0) in vec3	pos;

out Po
{
	vec3						pos;
}								vs_out;

uniform mat4					model;

void main()
{
	vec4		vWpos = model * vec4(pos, 1.f);

	vs_out.pos = vec3(vWpos);
	gl_Position = vWpos;
}
