/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fterror.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/20 12:04:26 by ngoguey           #+#    #+#             */
/*   Updated: 2015/07/20 12:05:01 by ngoguey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTERROR_H
# define FTERROR_H

# include "libft.h"

/*
** ERRORS
*/
void				sp_enomem(void);
# define PERR_H qprintf("Error l%d: ", __LINE__)
# define PERRNO_ENDL qprintf(", (%s)\n", strerror(errno))

# define ERRORF(...) PERR_H, qprintf(__VA_ARGS__), ft_putchar_fd('\n', 2)
# define ERROR(ARG) ERRORF("%s", (ARG))

# define ERRORNOF(...) PERR_H, qprintf(__VA_ARGS__), PERRNO_ENDL
# define ERRORNO(ARG) ERRORNOF("%s", (ARG))

#endif
