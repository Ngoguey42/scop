// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   couvno_blendli.frag                                :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/07/30 10:07:14 by ngoguey           #+#    #+#             //
//   Updated: 2015/07/30 13:03:00 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#version 410 core

in COUVNOFP
{
	vec3	Color;
	vec2	texUV;
	vec3	Normal;
	vec3	fragPos;
}		fs_in;

out vec4			color;

uniform sampler2D	ourTexture;
uniform vec3		lightPos;
uniform vec3		viewPos;
uniform vec3		lightColor;

void main()
{
	// color = vec4(fs_in.Color, 1.f);
	// color = mix(vec4(fs_in.Color, 1.f), texture(ourTexture, fs_in.texUV), 0.45);
	// color = vec4(0.7, 0.7, 0.7, 1.);
	color = texture(ourTexture, fs_in.texUV);
	// Ambient
	float ambientStrength = 0.25f;
	vec3 ambient = ambientStrength * lightColor;

	// Diffuse
	vec3 norm = normalize(fs_in.Normal);
	vec3 lightDir = normalize(lightPos - fs_in.fragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	// Specular
	float specularStrength = 0.6f;
	vec3 viewDir = normalize(viewPos - fs_in.fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;
	
	vec3 result = (ambient + diffuse + specular) * color.xyz;
	color = vec4(result, color.w);
} 
