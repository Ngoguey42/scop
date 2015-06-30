/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/30 12:07:31 by ngoguey           #+#    #+#             */
/*   Updated: 2015/06/30 12:49:53 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H


# include "libft.h"

# include "ftmath.h"
# include "scop_structs.h"


/*
** CONFIG MACROES
*/
#define WIN_WIDTHI 1000
#define WIN_RATIOF (4.f / 3.f)

/*
** CALCULATED MACROES
*/
#define WIN_WIDTHF ((float)WIN_WIDTHI)
#define WIN_HEIGHTF (WIN_WIDTHF / WIN_RATIOF)
#define WIN_HEIGHTI ROUND_FTOI(WIN_HEIGHTF)

#endif
