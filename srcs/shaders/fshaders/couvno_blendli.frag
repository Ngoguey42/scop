// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   couvno_blendli.frag                                :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/07/30 10:07:14 by ngoguey           #+#    #+#             //
//   Updated: 2015/08/15 19:19:30 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#version 410 core

in COUVNOFP
{
	vec3					Color;
	vec2					texUV;
	vec3					Normal;
	vec3					fragPos;
}							fs_in;

out vec4					color;

uniform sampler2D			ourTexture;
uniform vec3				viewPos;

uniform struct Light {
	vec3 pos;

	vec3 a;
	vec3 d;
	vec3 s;

	float linear;
	float quadratic;
}							l;

void main()
{
	float distance    = length(l.pos - fs_in.fragPos);
	float attenuation = 1.0f / (1.f + l.linear * distance +
								l.quadratic * (distance * distance));
	// color = vec4(fs_in.Color, 1.f);
	// color = mix(vec4(fs_in.Color, 1.f), texture(ourTexture, fs_in.texUV), 0.45);
	// color = vec4(0.7, 0.7, 0.7, 1.);
	color = texture(ourTexture, fs_in.texUV);
	// Ambient
	float ambientStrength = 0.25f;
	vec3 ambient = ambientStrength * l.a;

	// Diffuse
	vec3 norm = normalize(fs_in.Normal);
	vec3 lightDir = normalize(l.pos - fs_in.fragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * l.d;

	// Specular
	float specularStrength = 0.6f;
	vec3 viewDir = normalize(viewPos - fs_in.fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * l.s;
	
	vec3 result = (ambient + diffuse + specular) * color.xyz * attenuation;
	color = vec4(result, color.w);
} 
