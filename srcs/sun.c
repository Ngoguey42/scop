
#include "scop.h"
#include <limits.h>

void			sp_sunskin_tessout(t_env *e, int action)
{
	float const	way = 1 - (action & 0x8 ? 2 : 0);

	if (action & 0x1)
	{
		e->sunskin_tessout[0] += way;
		if (e->sunskin_tessout[0] < 1.f)
			e->sunskin_tessout[0] = 1.f;
	}
	if (action & 0x2)
	{
		e->sunskin_tessout[1] += way;
		if (e->sunskin_tessout[1] < 1.f)
			e->sunskin_tessout[1] = 1.f;
	}
	if (action & 0x4)
	{
		e->sunskin_tessout[2] += way;
		if (e->sunskin_tessout[2] < 1.f)
			e->sunskin_tessout[2] = 1.f;
	}
	return ;
}

void			sp_sunskin_tessin(t_env *e, int way)
{
	e->sunskin_tessin += (float)way;
	if (e->sunskin_tessin < 1.f)
		e->sunskin_tessin = 1.f;
	return ;
}
