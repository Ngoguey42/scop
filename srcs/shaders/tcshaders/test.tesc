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

uniform float				tessLevelOut0;
uniform float				tessLevelOut1;
uniform float				tessLevelOut2;
uniform float				tessLevelIn;

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
	gl_TessLevelOuter[0] = tessLevelOut0;
	gl_TessLevelOuter[1] = tessLevelOut1;
	gl_TessLevelOuter[2] = tessLevelOut2;
	gl_TessLevelInner[0] = tessLevelIn;
	return ;
}
