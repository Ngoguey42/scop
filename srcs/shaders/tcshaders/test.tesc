// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   test.tesc                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/12 09:58:17 by ngoguey           #+#    #+#             //
//   Updated: 2015/09/12 10:51:18 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#version 410 core

layout						(vertices = 3) out;
uniform vec3				cpos;

in Po
{
	vec3					pos;
}							tec_in[];

out Po
{
	vec3					pos;
}							tec_out[];

void	main()
{
	tec_out[gl_InvocationID].pos = tec_in[gl_InvocationID].pos;
	// if (gl_InvocationID == 0) //lol?
	{
		gl_TessLevelOuter[0] = 7.f;
		gl_TessLevelOuter[1] = 7.f;
		gl_TessLevelOuter[2] = 7.f;
		gl_TessLevelInner[0] = gl_TessLevelOuter[2];
	}
	return ;
}
