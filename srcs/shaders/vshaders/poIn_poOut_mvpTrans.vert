// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   poIn_poOut_mvpTrans.vert                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/12 07:39:04 by ngoguey           #+#    #+#             //
//   Updated: 2015/09/12 13:53:30 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#version 410 core

layout (location = 0) in vec3	pos;

out Po
{
	vec3						pos;
}								vs_out;

void main()
{
	vs_out.pos = pos;
}
