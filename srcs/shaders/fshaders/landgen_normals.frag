// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   landgen_normals.frag                               :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/19 07:51:34 by ngoguey           #+#    #+#             //
//   Updated: 2015/09/19 12:22:27 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

// uniform float				land_width_canonical;
// uniform float				land_width_half_canonical;
uniform float				height_factor;
uniform sampler2D			ymap;

out vec3					normap;

vec3	get_vertex_0(float map_width)
{
	return (vec3(
		gl_FragCoord.x
		, texture(ymap, vec2(gl_FragCoord.x, gl_FragCoord.y) / map_width).x
			* height_factor
		, gl_FragCoord.y
	));
}

vec3	get_vertex(float map_width, vec2 offsets)
{
	vec2	frag = vec2(gl_FragCoord.x + offsets.x, gl_FragCoord.y + offsets.y);

	return (vec3(
		frag.x
		, texture(ymap, vec2(frag.x, frag.y) / map_width).x
			* height_factor
		, frag.y
	));
}

vec3	calc_weighted_normal(vec3 a, vec3 b)
{
	return (cross(a, b) * acos(dot(a, b)));
}

void	main()
{
	float			map_width = textureSize(ymap, 0).x;
	vec3			center = get_vertex_0(map_width);
	vec3			vecsave1;
	vec3			vecsave2;
	vec3			vecsave3;

	// normap = vec3(0.f);
	vecsave1 = normalize(center - get_vertex(map_width, vec2(+1.f, +0.f)));
	vecsave3 = normalize(center - get_vertex(map_width, vec2(+0.f, +1.f)));
	normap = calc_weighted_normal(vecsave3, vecsave1);
	vecsave2 = normalize(center - get_vertex(map_width, vec2(-1.f, +0.f)));
	normap += calc_weighted_normal(vecsave2, vecsave3);
	vecsave3 = normalize(center - get_vertex(map_width, vec2(+0.f, -1.f)));
	normap += calc_weighted_normal(vecsave3, vecsave2);
	normap += calc_weighted_normal(vecsave1, vecsave3);
	normap = normalize(normap);
	// normap = vec3(1.f, 1.f, 0.f);
	return ;
}
