// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   landrender.frag                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/19 08:51:15 by ngoguey           #+#    #+#             //
//   Updated: 2015/09/19 13:59:28 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

in StPoCoNo
{
	vec2						st;
	vec3						pos;
	vec3						col;
	vec3						nor;
}                               fs_in;

// uniform sampler2D                normap;
uniform sampler2D                colmap;
// uniform samplerCube         depthMap;
uniform float               far;
uniform vec3                viewPos;
uniform struct Light {
	vec3 pos;
	vec3 col;
}                           l;

out vec4						color;

void	main()
{
	// color = vec4(fs_in.col, 1.f);
	// color = vec4(1.f, 1.f, 0.f, 1.f);
	vec3    vLiToFra = fs_in.pos - l.pos;
	vec3    vFraToLi = -vLiToFra;
	vec3    vnFraToLi = normalize(vFraToLi);
	vec3    vFraToCam = viewPos - fs_in.pos;
	vec3    vnFraToCam = normalize(vFraToCam);
	vec3    vFraNormal = fs_in.nor;
	// vFraNormal = texture(normap, fs_in.st, 10.1f).xyz;
	vec3    vnFraNormal = normalize(vFraNormal);
	float   dFraLi = length(vLiToFra);
	float   dnFraLi = dFraLi / far;
	float   dFraCam = length(vFraToCam);
	float   attenuation = 1.f - (dFraLi / far);
	float   ambient = G_AMBIENT_STRENGTH;
	float   diffuse = max(dot(vnFraNormal, vnFraToLi), 0.f)
		* G_DIFFUSE_STRENGTH;
	vec3    vnLiCamHalfway = normalize(vnFraToLi + vnFraToCam);
	float   specular =
			pow(max(dot(vnFraNormal, vnLiCamHalfway), 0.0), G_SPECULAR_POWER)
		* G_SPECULAR_STRENGTH;
	// float   shadow = compute_shadows(dnFraLi, dFraLi, vLiToFra);
	float   shadow = 0.f;
	vec3    cLight = G_COL_TO_SRGB(l.col);

	color = texture(colmap, fs_in.st);
	// color = vec4(fs_in.col, 1.f);
	// color.rgb = vnFraNormal;
	// color.r = abs(color.r);
	// color.g = abs(color.g);
	// color.b = abs(color.b);
	
	color.rgb = G_COL_TO_SRGB(color.rgb);
	color = vec4(
		(ambient + (diffuse
					// + specular
			) * (1.f - shadow) * attenuation)
			        * cLight * color.xyz
		, color.w);
	color.rgb = G_COL_TO_LINEAR(color.rgb);




	
	// color.rgb = (-vnFraNormal);;
	// color.rgb = vnFraNormal;
	// color.r = abs(color.r);
	// color.g = abs(color.g);
	// color.b = abs(color.b);
	
	return ;
}
