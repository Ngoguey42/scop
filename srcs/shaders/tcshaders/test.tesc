// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   test.tesc                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/12 09:58:17 by ngoguey           #+#    #+#             //
//   Updated: 2015/09/12 14:30:50 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#version 410 core

layout						(vertices = 3) out;

in Po
{
	vec3					pos;
}							tec_in[];

out Po
{
	vec3					pos;
}							tec_out[];
#define LOL 4
void	main()
{
	tec_out[gl_InvocationID].pos = tec_in[gl_InvocationID].pos;
	if (gl_InvocationID == 0) //lol?
	{
		gl_TessLevelOuter[0] = 4;
		gl_TessLevelOuter[1] = 1;
		gl_TessLevelOuter[2] = 2;
		gl_TessLevelInner[0] = 3;
	}
	return ;
}
