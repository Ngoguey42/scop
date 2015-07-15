/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/30 11:48:41 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/15 10:44:24 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <math.h>
#include <stdlib.h>

void					build_mesh_cube(t_env *e)
{
	GLfloat vertices[] = {
		-0.1f,  0.1f,  0.1f,	1.0f, 0.0f, 0.0f,		//F	TL
		+0.1f,  0.1f,  0.1f,	0.7f, 0.15f, 0.15f,		//F TR
		-0.1f, -0.1f,  0.1f,	0.4f, 0.3f, 0.3f,		//F BL

		-0.1f,  0.1f, -0.1f,	0.0f, 1.0f, 0.0f,		//R TL
		+0.1f,  0.1f, -0.1f,	0.15f, 0.7f, 0.15f,		//R TR
		-0.1f, -0.1f, -0.1f,	0.3f, 0.4f, 0.3f,		//R BL

		
	};

	
	GLuint indices[] = {
		0, 1, 2,
		3, 4, 5,
		0, 3, 4,
		4, 0, 1,
	};

	
	glGenVertexArrays(1, &e->vao);	// array object
	glGenBuffers(1, &e->vab); // vab = vbo array buffer / buffer object
	glGenBuffers(1, &e->ebo); //
	
	
	glBindVertexArray(e->vao);
	{		
		glBindBuffer(GL_ARRAY_BUFFER, e->vab);
		glBufferData(GL_ARRAY_BUFFER,
					 sizeof(vertices),
					 vertices,
					 GL_STATIC_DRAW
			);
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, e->ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
					 sizeof(indices),
					 indices,
					 GL_STATIC_DRAW
			);
		
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
							  (GLvoid*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
							  (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
	}
	glBindVertexArray(0);
	return ;
}
#define NUMINDICES ((t_objmodel*)e->models.data)->faces.size * 3
/* #define NUMINDICES (e->faces.size * 3) */
void					build_mesh(t_env *e)
{
	t_objmodel	*m = e->models.data;
	GLfloat		*vertices = m->vertices.data;
	GLuint		*indices = m->faces.data;
	
	glGenVertexArrays(1, &e->vao);	// array object
	glGenBuffers(1, &e->vab); // vab = vbo array buffer / buffer object
	glGenBuffers(1, &e->ebo); //
	
	
	glBindVertexArray(e->vao);
	{		
		glBindBuffer(GL_ARRAY_BUFFER, e->vab);
		glBufferData(GL_ARRAY_BUFFER,
					 sizeof(float) * 3 * m->vertices.size,
					 vertices,
					 GL_STATIC_DRAW
			);
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, e->ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
					 sizeof(unsigned int) * 3 * m->faces.size,
					 indices,
					 GL_STATIC_DRAW
			);
		
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
							  (GLvoid*)0);
		glEnableVertexAttribArray(0);
	}
	glBindVertexArray(0);
	
	return ;
}


int						main(int ac, char *av[])
{
	t_env		e[1];
	double		last_time;
	double		cur_time;
	double		el_time;

	if (sp_init_env(e))
		return (ERROR("sp_init_env()"), 1);
	if (sp_init_glfw(e))
		return (ERROR("sp_init_glfw()"), 1);
	if (sp_init_shaders(e))
		return (ERROR("sp_init_shaders()"), 1);
	if (sp_init_programs(e))
		return (ERROR("sp_init_programs()"), 1);
	/* sp_register_objmodel(e, OBJ_PATH "42.obj"); */
	/* sp_register_objmodel(e, OBJ_PATH "teapot.obj"); */
	sp_register_objmodel(e, OBJ_PATH "teapot2.obj");
	/* sp_register_objmodel(e, OBJ_PATH "teapot2.obj"); */
	if (sp_init_objmodels(e))
		return (ERROR("sp_init_objmodels()"), 1);
	T;
	/* exit(0); */
	(void)ac;
	(void)av;

	/* t_vector3	test; */
	/* test.x = 1.f; */
	/* test.y = 2.f; */
	/* test.z = 3.f; */
	/* v3_print(test); */
	/* test = v3_normalize(test); */
	/* v3_print(test); */

	
	
	build_mesh(e);
	t_matrix4 const	projection_mat = m4_fovprojection(WIN_FOVF, WIN_RATIOF,
													  WIN_NEARF, WIN_FARF);
	last_time = glfwGetTime();
	while (!glfwWindowShouldClose(e->win))
	{
		cur_time = glfwGetTime();
		el_time = cur_time - last_time;
		sp_update_states(e, el_time);
		glClearColor(0.3f, 0.3f, 0.3f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(PROG0);
	
		t_matrix4		mat = m4_scale_uniform(1.f);
		/* t_matrix4 model_mat = m4_scale_uniform(1.f); */
		
		/* mat = m4_translateref_nonuniform(&mat, (float [3]){-0.55f, 0.0f, 0.0f}); */
		
		/* mat = m4_rotationref_axis(&mat, y_axis, 1.2 * (GLfloat)glfwGetTime()); */
		/* mat = m4_rotationref_axis(&mat, z_axis, 1.4 * (GLfloat)glfwGetTime()); */
		/* mat = m4_rotationref_axis(&mat, z_axis, 1.6 * (GLfloat)glfwGetTime()); */
	
		/* mat = m4_scaleref_uniform(&mat, 4.f); */

		GLuint modelLoc = glGetUniformLocation(PROG0, "model");
		GLuint viewLoc = glGetUniformLocation(PROG0, "view");
		GLuint projectionLoc = glGetUniformLocation(PROG0, "projection");

		t_matrix4 view_mat =  m4_scale_uniform(1.f);




		view_mat = m4_invtranslateref_nonuniform(
			&view_mat, e->pos);

		/* qprintf("Yaw %f ", e->cangles[0]); */
		/* qprintf("Pitch %f\n", e->cangles[1]); */
		/* t_vector3	test2 = 	v3_frontnormed(e->cangles); */
		/* v3_print(test2); */
		
		/* m4_print(view_mat); */
		view_mat = m4_lookat(
			(t_vector3){e->pos[0], e->pos[1], e->pos[2]},
			v3_add((t_vector3){e->pos[0], e->pos[1], e->pos[2]},
				   v3_frontnormed(e->cangles))
			);
		/* qprintf("\n"); */
		/* m4_print(view_mat); */
		/* view_mat = m4_rotationref_axis(&view_mat, x_axis, */
		/* 0.2 * (GLfloat)glfwGetTime()); */
		
		glUniformMatrix4fv(modelLoc, 1, GL_TRUE, (float*)&mat);
		glUniformMatrix4fv(viewLoc, 1, GL_TRUE, (float*)&view_mat);
		glUniformMatrix4fv(projectionLoc, 1, GL_TRUE, (float*)&projection_mat);
		
		
		
		/* draw mesh */
		glBindVertexArray(e->vao);
		/* glDrawArrays(GL_TRIANGLES, 0, 3); */
		glDrawElements(GL_TRIANGLES, NUMINDICES, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		/* /draw mesh */
		
		glfwSwapBuffers(e->win);
		glfwPollEvents();
		last_time = cur_time;
	}
	sp_delete_programs(e);
	sp_delete_shaders(e);
	sp_disable_glfw(e);
	sp_clean_env(e);
	/* ft_leaks(); */
	return (0);
}
