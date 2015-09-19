// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   landrender.vert                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/19 08:51:18 by ngoguey           #+#    #+#             //
//   Updated: 2015/09/19 11:28:49 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

// layout (location = 0) in vec3	pos;
layout (location = 0) in vec2	tex;
// layout (location = 1) in vec3	nor;

// uniform sampler2D				ymap;
// uniform vec3					posfactors;
// uniform sampler2D				normap;
// uniform sampler2D				colmap;

out St
{
	vec2						st;
	// vec3						pos;
	// vec3						nor;
}								vs_out;

void	main()
{
	// vs_out.st = tex;
	vs_out.st = tex;
	// vs_out.pos = vec3(
	// 	st.x * posfactors.x
	// 	, texture(ymap, st)
	// 	, st.y * posfactors.z
	// 	);
	return ;
}
