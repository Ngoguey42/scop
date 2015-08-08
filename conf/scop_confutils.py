# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    scop_confutils.py                                  :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/08/08 11:56:14 by ngoguey           #+#    #+#              #
#    Updated: 2015/08/08 11:56:15 by ngoguey          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import cog
import math

DOTH_INDENT_COLUMN = 28
DOTH_INDENT_TABCOLUMN = DOTH_INDENT_COLUMN / 4
assert DOTH_INDENT_TABCOLUMN * 4 == DOTH_INDENT_COLUMN

def output_doth_indent_2str(lhs, rhs):
	num_tabs = DOTH_INDENT_TABCOLUMN - int(math.ceil(float(len(lhs)) / 4.))
	assert num_tabs > 0
	cog.outl(lhs + ('\t' * num_tabs) + rhs)

DOTC_INDENT_COLUMN = 16
DOTC_INDENT_TABCOLUMN = DOTC_INDENT_COLUMN / 4
assert DOTC_INDENT_TABCOLUMN * 4 == DOTC_INDENT_COLUMN

def output_dotc_indent_2str(lhs, rhs):
	num_tabs = DOTC_INDENT_TABCOLUMN - int(math.ceil(float(len(lhs)) / 4.))
	assert num_tabs > 0
	cog.outl(lhs + ('\t' * num_tabs) + rhs)

def output_cconf_start(singular, plural):
	output_dotc_indent_2str("int", "sp_loadconf_" + plural + "(t_env *e)")
	cog.outl("{\n\tt_" + singular + " const\t\ttmp[sp_num_"
		+ plural + "] = {\n")

def output_cconf_end(plural):
	cog.outl("""\t};
	memcpy(&e->""" + plural + """, &tmp, sizeof(tmp));
	return (0);\n}""")
