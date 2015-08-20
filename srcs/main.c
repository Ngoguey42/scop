/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/20 12:08:19 by ngoguey           #+#    #+#             */
/*   Updated: 2015/08/20 14:42:44 by ngoguey          ###   ########.fr       */
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

GLuint depthCubemap;//sha
static void		loop(t_env *e)
{
	double		last_time;
	double		sleep_time;

	GLuint SHADOW_WIDTH, SHADOW_HEIGHT;
	SHADOW_HEIGHT = SHADOW_WIDTH = 1024; //sha
	GLuint depthMapFBO; //sha
	glGenFramebuffers(1, &depthMapFBO); //sha
	glGenTextures(1, &depthCubemap);//sha
	glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap);//sha
	for (GLuint i = 0; i < 6; ++i)//sha
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i//sha
					 , 0, GL_DEPTH_COMPONENT//sha
					 , SHADOW_WIDTH, SHADOW_HEIGHT, 0//sha
					 , GL_DEPTH_COMPONENT, GL_FLOAT, NULL);//sha
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);//s
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);//s
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);//s
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);//s
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);//s

	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);//s
	glFramebufferTexture(GL_FRAMEBUFFER
						 , GL_DEPTH_ATTACHMENT, depthCubemap, 0);//s
	glDrawBuffer(GL_NONE);//s
	glReadBuffer(GL_NONE);//s
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)//s
		qprintf("Framebuffer not complete!\n");
	glBindFramebuffer(GL_FRAMEBUFFER, 0); //s
	
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
        GLfloat aspect = (GLfloat)SHADOW_WIDTH / (GLfloat)SHADOW_HEIGHT; //s
		GLfloat near = 1.0f;//s
		GLfloat far = 250.0f;//s
		t_matrix4	shadowProj = m4_fovprojection(
			M_PI / 2.f, aspect, near, far); //s

		t_vector3	lightPos = e->sunpos_cartesian;
#define CONV(V) (t_matrix4[]){V}
#define LOOKATPTR(V1, V2) CONV(m4_lookat(lightPos, v3_add(lightPos, (V1)), (V2)))
		t_matrix4	shadowTransforms[6] = {
m4_dotprod(&shadowProj, LOOKATPTR(ATOV3(+1.0, 0.0, 0.0), ATOV3(0.0, -1.0, 0.0))),
m4_dotprod(&shadowProj, LOOKATPTR(ATOV3(-1.0, 0.0, 0.0), ATOV3(0.0, -1.0, 0.0))),
m4_dotprod(&shadowProj, LOOKATPTR(ATOV3(0.0, +1.0, 0.0), ATOV3(0.0, 0.0, +1.0))),
m4_dotprod(&shadowProj, LOOKATPTR(ATOV3(0.0, -1.0, 0.0), ATOV3(0.0, 0.0, -1.0))),
m4_dotprod(&shadowProj, LOOKATPTR(ATOV3(0.0, 0.0, +1.0), ATOV3(0.0, -1.0, 0.0))),
m4_dotprod(&shadowProj, LOOKATPTR(ATOV3(0.0, 0.0, -1.0), ATOV3(0.0, -1.0, 0.0))),
		   };
		glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glClear(GL_DEPTH_BUFFER_BIT);
		t_program *p;
		p = e->programs + sp_pointshadow_program;
		glUseProgram(p->handle);

#define LOC(N)  glGetUniformLocation(p->handle, N)
#define PREFIX(T) glUniform ## T
#define U(T, N, ...) PREFIX(T)(LOC(N), __VA_ARGS__)
		
		int i;
		for (i = 0; i < 6; i++)
		{
			char	truc[32] = "shadowMatrices[6]";

			truc[15] = i + '0';
			U(Matrix4fv, truc, 1, GL_TRUE, (float*)(shadowTransforms + i));
		}
		U(1f, "far", far);
		U(3fv, "lpos", 1, (float*)&lightPos);
		U(Matrix4fv, "model", 1, GL_TRUE, (float*)&e->mainob->mat);
 
		p = POFOB(e, e->mainob);
		glBindVertexArray(MEOFOB(e, e->mainob)->handles[0]);
		glDrawElements(GL_TRIANGLES, 3 * MEOFOB(e, e->mainob)->faces.size
					   , GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, WIN_WIDTHI, WIN_HEIGHTI);
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
