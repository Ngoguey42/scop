/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/20 12:08:19 by ngoguey           #+#    #+#             */
/*   Updated: 2015/08/18 17:08:55 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define PSIZEOF(T) qprintf("sizeof(%s) = %zuBytes\n", #T, sizeof(T))
#define VERBOSE(STR) lprintf("\033[36mInitializing %s...\033[0m", (STR))

static int		begin(t_env *e)
{
	if (VERBOSE("env"), sp_init_env(e))
		return (ERROR("sp_init_env(e)"), 1);
	if (VERBOSE("glfw"), sp_init_glfw(e))
		return (ERROR("sp_init_glfw(e)"), 1);
	if (VERBOSE("shaders"), sp_init_shaders(e))
		return (ERROR("sp_init_shaders(e)"), 1);
	if (VERBOSE("programs"), sp_init_programs(e))
		return (ERROR("sp_init_programs(e)"), 1);
	if (VERBOSE("textures"), sp_init_textures(e))
		return (ERROR("sp_init_textures(e)"), 1);
	if (VERBOSE("meshes"), sp_init_meshes(e))
		return (ERROR("sp_init_meshes(e)"), 1);
	if (VERBOSE("obs"), sp_init_obs(e))
		return (ERROR("sp_init_obs(e)"), 1);
	return (0);
}

#include <math.h>

static void		loop(t_env *e)
{
	double		last_time;
	double		sleep_time;

	//lol
	// Configure depth map FBO
	const GLuint SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
	GLuint depthMapFBO;
	glGenFramebuffers(1, &depthMapFBO);
	// Create depth cubemap texture
	GLuint depthCubemap;
	glGenTextures(1, &depthCubemap);
	glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap);
	for (GLuint i = 0; i < 6; ++i)
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i
					 , 0, GL_DEPTH_COMPONENT
					 , SHADOW_WIDTH, SHADOW_HEIGHT, 0
					 , GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	//lol
		//lol
		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthCubemap, 0);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			/* std::cout << "Framebuffer not complete!" << std::endl; */
			qprintf("Framebuffer not complete!\n");
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		//lol
	

	
	
	e->time_start = glfwGetTime();
	e->time_cur = e->time_start;
	last_time = e->time_start;
	while (!glfwWindowShouldClose(e->win))
	{
		e->time_cur = glfwGetTime();
		e->time_el = e->time_cur - last_time;
		sp_update_states(e);
		sp_update_obs(e);


		//lol
        GLfloat aspect = (GLfloat)SHADOW_WIDTH / (GLfloat)SHADOW_HEIGHT;
		GLfloat near = 1.0f;
		GLfloat far = 25.0f;
		/* glm::mat4 shadowProj = glm::perspective(90.0f, aspect, near, far); */
		t_matrix4	shadowProj = m4_fovprojection(M_PI / 2.f, aspect, near, far);
		/* std::vector<glm::mat4> shadowTransforms; */
		t_vector3	lightPos = e->sunpos_cartesian;

#define CONV(V) (t_matrix4[]){V}
#define LOOKATPTR(V1, V2) CONV(m4_lookat(lightPos, v3_add(lightPos, (V1)), (V2)))
		
		t_matrix4	shadowTransforms[6] = {
m4_dotprod(LOOKATPTR(ATOV3(+1.0, 0.0, 0.0), ATOV3(0.0, -1.0, 0.0)), &shadowProj),
m4_dotprod(LOOKATPTR(ATOV3(-1.0, 0.0, 0.0), ATOV3(0.0, -1.0, 0.0)), &shadowProj),
m4_dotprod(LOOKATPTR(ATOV3(0.0, +1.0, 0.0), ATOV3(0.0, 0.0, +1.0)), &shadowProj),
m4_dotprod(LOOKATPTR(ATOV3(0.0, -1.0, 0.0), ATOV3(0.0, 0.0, -1.0)), &shadowProj),
m4_dotprod(LOOKATPTR(ATOV3(0.0, 0.0, +1.0), ATOV3(0.0, -1.0, 0.0)), &shadowProj),
m4_dotprod(LOOKATPTR(ATOV3(0.0, 0.0, -1.0), ATOV3(0.0, -1.0, 0.0)), &shadowProj),
			
		};
		/* shadowTransforms.push_back( */
		/* 	shadowProj * glm::lookAt(lightPos, lightPos */
		/* 							 + glm::vec3( 1.0,  0.0,  0.0) */
		/* 							 , glm::vec3(0.0, -1.0,  0.0))); */
		/* shadowTransforms.push_back( */
		/* 	shadowProj * glm::lookAt(lightPos, lightPos */
		/* 							 + glm::vec3(-1.0,  0.0,  0.0) */
		/* 							 , glm::vec3(0.0, -1.0,  0.0))); */
		/* shadowTransforms.push_back( */
		/* 	shadowProj * glm::lookAt(lightPos, lightPos */
		/* 							 + glm::vec3( 0.0,  1.0,  0.0) */
		/* 							 , glm::vec3(0.0,  0.0,  1.0))); */
		/* shadowTransforms.push_back( */
		/* 	shadowProj * glm::lookAt(lightPos, lightPos */
		/* 							 + glm::vec3( 0.0, -1.0,  0.0), */
		/* 							 glm::vec3(0.0,  0.0, -1.0))); */
		/* shadowTransforms.push_back( */
		/* 	shadowProj * glm::lookAt(lightPos, lightPos */
		/* 							 + glm::vec3( 0.0,  0.0,  1.0) */
		/* 							 , glm::vec3(0.0, -1.0,  0.0))); */
		/* shadowTransforms.push_back( */
		/* 	shadowProj * glm::lookAt(lightPos, lightPos */
		/* 							 + glm::vec3( 0.0,  0.0, -1.0) */
		/* 							 , glm::vec3(0.0, -1.0,  0.0))); */
		// 1. Render scene to depth cubemap
		glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glClear(GL_DEPTH_BUFFER_BIT);
		/* simpleDepthShader.Use(); */
		/* for (GLuint i = 0; i < 6; ++i) */
		/* 	glUniformMatrix4fv( */
		/* 		glGetUniformLocation( */
		/* 			simpleDepthShader.Program */
		/* 			, ("shadowMatrices[" + std::to_string(i) */
		/* 			   + "]").c_str()), 1, GL_FALSE */
		/* 		, glm::value_ptr(shadowTransforms[i])); */
		/* glUniform1f(glGetUniformLocation( */
		/* 				simpleDepthShader.Program, "far_plane"), far); */
		/* glUniform3fv(glGetUniformLocation( */
		/* 				 simpleDepthShader.Program, "lightPos"), 1, &lightPos[0]); */
		/* RenderScene(simpleDepthShader); */
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		//lol


		glViewport(0, 0, WIN_WIDTHI, WIN_HEIGHTI);
		//lol
		
		
		glClearColor(155. / 256., 216. / 256., 220. / 256., 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		sp_render_obs(e);
		glfwSwapBuffers(e->win);
		glfwPollEvents();
		if (e->states[sp_window_focused_state] == 0
			&& (sleep_time = 0.5 - (glfwGetTime() - e->time_cur)) < 0.5)
			usleep(sleep_time * 1000000.);
		last_time = e->time_cur;
	}
	return ;
}

static void		end(t_env *e)
{
	sp_delete_obs(e);
	sp_delete_textures(e);
	sp_delete_meshes(e);
	sp_delete_programs(e);
	sp_delete_shaders(e);
	sp_disable_glfw(e);
	sp_clean_env(e);
	return ;
}

int				main(void)
{
	t_env					*e;

	srand(time(NULL));
	PSIZEOF(t_env);
	PSIZEOF(t_ob);
	e = malloc(sizeof(*e));
	if (e == NULL)
		return (ERROR("Env allocation failed"), 1);
	if (begin(e))
		return (1);
	/* return (0); */
	loop(e);
	end(e);
	free(e);
	/* ft_leaks(); */
	return (0);
}
