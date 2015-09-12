// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   po_facegrey.geom                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/12 07:32:38 by ngoguey           #+#    #+#             //
//   Updated: 2015/09/12 13:22:46 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#version 410 core

layout					(triangles) in;
layout					(triangle_strip, max_vertices = 3) out;

uniform mat4                    viewproj;

in Po
{
	vec3				pos;
}						gs_in[];

out Co
{
	vec3				col;
}						gs_out;

#define NSHADESI int(36)
#define FIRST_COLORF 25.f
#define LAST_COLORF 230.f


#define NSHADES_THIRDI int(NSHADESI / 3)
#define NSHADESF float(NSHADESI)
#define NSHADES_THIRDF float(NSHADESI / 3)
#define DELTA ((LAST_COLORF - FIRST_COLORF) / NSHADES_THIRDF)

void main()
{
	int			i;
	int			col_index = gl_PrimitiveIDIn % NSHADESI;
	float		val = (FIRST_COLORF + (col_index % NSHADES_THIRDI) * DELTA)
		/ 255.f;

	if (col_index < NSHADES_THIRDI)
		gs_out.col = vec3(val, 0.f, 0.f);
	else if (col_index < NSHADES_THIRDI * 2)
		gs_out.col = vec3(0.f, val, 0.f);
	else
		gs_out.col = vec3(0.f, 0.f, val);
	for (i = 0; i < 3; i++)
	{
		gl_Position = viewproj * gl_in[i].gl_Position;
		EmitVertex();
	}
	EndPrimitive();
}
