# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    scop_confclasses.py                                :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/08/08 11:56:07 by ngoguey           #+#    #+#              #
#    Updated: 2015/08/08 12:24:57 by ngoguey          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import cog
from scop_confutils import *

class Cstruct:
	def __init__(self):
		pass
	@staticmethod
	def output_enum_start():
		raise NotImplementedError("Subclass must implement abstract method")
	@staticmethod
	def output_enum_end():
		raise NotImplementedError("Subclass must implement abstract method")
	def output_enum_line(self):
		raise NotImplementedError("Subclass must implement abstract method")
	@staticmethod
	def output_cconf_start():
		raise NotImplementedError("Subclass must implement abstract method")
	@staticmethod
	def output_cconf_end():
		raise NotImplementedError("Subclass must implement abstract method")
	def output_cconf_entry(self):
		raise NotImplementedError("Subclass must implement abstract method")

class Vshader(Cstruct):
	def __init__(self, name, filename, unif_funname, *args):
		self.name = name
		self.filename = filename
		self.unif_funname = unif_funname
		self.locations = args
	@staticmethod
	def output_enum_start():
		output_doth_indent_2str("typedef enum", "e_vshader_index\n{")
	@staticmethod
	def output_enum_end():
		cog.outl("\t" + "sp_" + "num" + "_vshaders")
		output_doth_indent_2str("}", "t_vshader_index;")
	def output_enum_line(self):
		cog.outl("\t" + "sp_" + self.name + "_vshader,")
	@staticmethod
	def output_cconf_start():
		output_cconf_start("vshader", "vshaders")
	@staticmethod
	def output_cconf_end():
		output_cconf_end("vshaders")
	def output_cconf_entry(self):
		cog.out("\tVSHADER(\"" + self.filename
			+ "\", &sp_unif_" + self.unif_funname + ",\n\t")
		for loc in self.locations[0:-1]:
			cog.out("LOC(\"" + loc[0] + "\", " + str(loc[1]) + "), ")
		loc = self.locations[-1]
		cog.out("LOC(\"" + loc[0] + "\", " + str(loc[1]) + ")")
		cog.outl("),")

class Fshader(Cstruct):
	def __init__(self, name, filename, unif_funname):
		self.name = name
		self.filename = filename
		self.unif_funname = unif_funname
	@staticmethod
	def output_enum_start():
		output_doth_indent_2str("typedef enum", "e_fshader_index\n{")
	@staticmethod
	def output_enum_end():
		cog.outl("\t" + "sp_" + "num" + "_fshaders")
		output_doth_indent_2str("}", "t_fshader_index;")
	def output_enum_line(self):
		cog.outl("\t" + "sp_" + self.name + "_fshader,")
	@staticmethod
	def output_cconf_start():
		output_cconf_start("fshader", "fshaders")
	@staticmethod
	def output_cconf_end():
		output_cconf_end("fshaders")
	def output_cconf_entry(self):
		cog.out("\tFSHADER(\"" + self.filename + "\", ")
		if self.unif_funname != "":
			cog.out("&sp_unif_" + self.unif_funname + "),\n")
		else:
			cog.out("NULL" + "),\n")

class Gshader(Cstruct):
	def __init__(self, name, filename, unif_funname):
		self.name = name
		self.filename = filename
		self.unif_funname = unif_funname
	@staticmethod
	def output_enum_start():
		output_doth_indent_2str("typedef enum", "e_gshader_index\n{")
	@staticmethod
	def output_enum_end():
		cog.outl("\t" + "sp_" + "num" + "_gshaders,")
		cog.outl("\t" + "sp_" + "no" + "_gshader")
		output_doth_indent_2str("}", "t_gshader_index;")
	def output_enum_line(self):
		cog.outl("\t" + "sp_" + self.name + "_gshader,")
	@staticmethod
	def output_cconf_start():
		output_cconf_start("gshader", "gshaders")
	@staticmethod
	def output_cconf_end():
		output_cconf_end("gshaders")
	def output_cconf_entry(self):
		cog.out("\tGSHADER(\"" + self.filename + "\", ")
		if self.unif_funname != "":
			cog.out("&sp_unif_" + self.unif_funname + "),\n")
		else:
			cog.out("NULL" + "),\n")

class Program(Cstruct):
	def __init__(self, name, vsname, fsname, gsname):
		self.name = name
		self.vsname = vsname
		self.fsname = fsname
		self.gsname = gsname
	@staticmethod
	def output_enum_start():
		output_doth_indent_2str("typedef enum", "e_program_index\n{")
	@staticmethod
	def output_enum_end():
		cog.outl("\t" + "sp_" + "num" + "_programs")
		output_doth_indent_2str("}", "t_program_index;")
	def output_enum_line(self):
		cog.outl("\t" + "sp_" + self.name + "_program,")
	@staticmethod
	def output_cconf_start():
		output_cconf_start("program", "programs")
	@staticmethod
	def output_cconf_end():
		output_cconf_end("programs")
	def output_cconf_entry(self):
		cog.outl("\tPROG(sp_" + self.vsname + "_vshader, sp_"
			+ self.fsname + "_fshader, sp_"
			 + self.gsname + "_gshader" + "),")

class Texture(Cstruct):
	def __init__(self, name, filename):
		self.name = name
		self.filename = filename
	@staticmethod
	def output_enum_start():
		output_doth_indent_2str("typedef enum", "e_texture_index\n{")
	@staticmethod
	def output_enum_end():
		cog.outl("\t" + "sp_" + "num" + "_textures,")
		cog.outl("\t" + "sp_" + "no" + "_texture")
		output_doth_indent_2str("}", "t_texture_index;")
	def output_enum_line(self):
		cog.outl("\t" + "sp_" + self.name + "_texture,")
	@staticmethod
	def output_cconf_start():
		output_cconf_start("texture", "textures")
	@staticmethod
	def output_cconf_end():
		output_cconf_end("textures")
	def output_cconf_entry(self):
		cog.outl("\tTEXTURE(\"" + self.filename + "\"),")

class Mesh(Cstruct):
	g_index = 0
	def __init__(self, name, program, usage, fill_funbody):
		self.name = name
		self.program = program
		self.usage = usage
		self.fill_funbody = fill_funbody
		self.index = Mesh.g_index
		Mesh.g_index += 1
	@staticmethod
	def output_enum_start():
		output_doth_indent_2str("typedef enum", "e_mesh_index\n{")
	@staticmethod
	def output_enum_end():
		cog.outl("\t" + "sp_" + "num" + "_meshes")
		output_doth_indent_2str("}", "t_mesh_index;")
	def output_enum_line(self):
		cog.outl("\t" + "sp_" + self.name + "_mesh,")
	@staticmethod
	def output_cconf_start():
		output_cconf_start("mesh", "meshes")
	@staticmethod
	def output_cconf_end():
		output_cconf_end("meshes")
	def output_cconf_entry(self):
		cog.outl("\tMESH(sp_" + self.program + "_program, " + self.usage
		+ ", &sp_meshfill_" + self.name + "),")
	def output_meshfill(self, index_first):
		if self.index >= index_first and self.index < index_first + 5:
			output_dotc_indent_2str("int", "sp_meshfill_" + self.name
			+ "(t_env const *e, t_mesh *me)")
			cog.outl(self.fill_funbody + "\n")

class Model(Cstruct):
	def __init__(self, name, mename, tename, unif_funname):
		self.name = name
		self.mename = mename
		self.tename = tename
		self.unif_funname = unif_funname
	@staticmethod
	def output_enum_start():
		output_doth_indent_2str("typedef enum", "e_model_index\n{")
	@staticmethod
	def output_enum_end():
		cog.outl("\t" + "sp_" + "num" + "_models")
		output_doth_indent_2str("}", "t_model_index;")
	def output_enum_line(self):
		cog.outl("\t" + "sp_" + self.name + "_model,")
	@staticmethod
	def output_cconf_start():
		output_cconf_start("model", "models")
	@staticmethod
	def output_cconf_end():
		output_cconf_end("models")
	def output_cconf_entry(self):
		cog.outl("\tMODEL(sp_" + self.mename + "_mesh, sp_"
		+ self.tename + "_texture, &sp_unif_" + self.unif_funname + "),")