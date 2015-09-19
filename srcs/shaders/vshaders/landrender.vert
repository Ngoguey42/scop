// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   landrender.vert                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/19 08:51:18 by ngoguey           #+#    #+#             //
//   Updated: 2015/09/19 08:53:04 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

layout (location = 0) in vec3	pos;
layout (location = 1) in vec3	nor;

out PoNo
{
	vec3						pos;
	vec3						nor;
}								vs_out;

void	main()
{
	vs_out.pos = pos;
	vs_out.nor = nor;
	return ;
}
