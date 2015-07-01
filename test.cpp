

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "glm/gtx/string_cast.hpp"

# define WIN_WIDTHI 1000
# define WIN_RATIOF (4.f / 4.f)
/* # define WIN_RATIOF (4.f / 3.f) */

/*
** CALCULATED MACROES
*/
# define WIN_WIDTHF ((float)WIN_WIDTHI)
# define WIN_HEIGHTF (WIN_WIDTHF / WIN_RATIOF)
# define WIN_HEIGHTI ROUND_FTOI(WIN_HEIGHTF)

int							main(void)
{
	//perspective (T const &fovy, T const &aspect, T const &near, T const &far)
//(45.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
	glm::mat4 projection;	
	// glm::mat4 perspective(45.f, WIN_RATIOF, 0.1f, 100.f);

projection = glm::perspective(45.0f, WIN_RATIOF, 0.1f, 100.0f);

std::cout << glm::to_string(projection) << std::endl;

	return (0);
}
