# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    scop_confloader.py                                 :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/08/08 11:56:11 by ngoguey           #+#    #+#              #
#    Updated: 2015/08/08 12:33:58 by ngoguey          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import cog
from scop_conf import *

cstructs = [vshaders, fshaders, gshaders, programs, textures, meshes, models]

def output_enums():
	for cstruct in cstructs:
		if len(cstruct) == 0:
			continue
		cstruct[0].output_enum_start()
		for elt in cstruct:
			elt.output_enum_line()
		cstruct[0].output_enum_end()
		cog.outl("")

def output_meshfill_prototypes():        
	for mesh in meshes:
		output_doth_indent_2str("int", "sp_meshfill_" + mesh.name
                                        + "(t_env const *e, t_mesh *me);")

def output_cconf():
	for cstruct in cstructs:
		assert len(cstruct) > 0
		cstruct[0].output_cconf_start()
		for elt in cstruct:
			elt.output_cconf_entry()
		cstruct[0].output_cconf_end()
		cog.outl("")

def output_meshfill(first_index):
	cog.outl("")
	for mesh in meshes:
		mesh.output_meshfill(first_index)
