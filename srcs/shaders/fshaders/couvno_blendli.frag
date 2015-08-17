// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   couvno_blendli.frag                                :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/07/30 10:07:14 by ngoguey           #+#    #+#             //
//   Updated: 2015/08/17 13:10:56 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#version 410 core

in PoCoUvNo
{
	vec3					pos;
	vec3					col;
	vec2					tex;
	vec3					nor;
}							fs_in;

uniform sampler2D			ourTexture;
uniform vec3				viewPos;
uniform float				mixval;

uniform struct Light {
	vec3 pos;

	vec3 a;
	vec3 d;
	vec3 s;

	float linear;
	float quadratic;
}							l;

out vec4					color;

void main()
{
	float	distance = length(l.pos - fs_in.pos);
	float	attenuation = 1.0f / (1.0f + l.linear * distance +
								l.quadratic * (distance * distance));

	// color = vec4(fs_in.col, 1.f);
	color = mix(vec4(fs_in.col, 1.f), texture(ourTexture, fs_in.tex), mixval);
	// color = vec4(0.7, 0.7, 0.7, 1.);
	// color = texture(ourTexture, fs_in.tex);
	// Ambient
	float ambientStrength = 0.25f;
	vec3 ambient = ambientStrength * l.a;

	// Diffuse
	vec3 norm = normalize(fs_in.nor);
	vec3 lightDir = normalize(l.pos - fs_in.pos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * l.d;

	// Specular
	float specularStrength = 0.6f;
	vec3 viewDir = normalize(viewPos - fs_in.pos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * l.s;
	
	vec3 result = (ambient + diffuse + specular) * color.xyz * attenuation;
	color = vec4(result, color.w);
} 
