/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/30 11:48:41 by ngoguey           #+#    #+#             */
/*   Updated: 2015/06/30 11:51:01 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <GLFW/glfw3.h>

static void error_callback(int error, const char* description)
{
	(void)error;
	(void)description;
}

static void key_callback(GLFWwindow* window, int key, int a, int action, int b)
{
	(void)window;
	(void)key;
	(void)action;
	(void)a;
	(void)b;
}

int							main(int ac, char *av[])
{
	
	(void)ac;
	(void)av;
	return (0);
}
