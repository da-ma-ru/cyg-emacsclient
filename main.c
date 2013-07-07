/* -*- mode: c; c-set-style: "stroustrup"; tab-width: 4; -*-
 *
 * main.c
 *
 * Copyright (C) 2005 Koji Nakamaru
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 */

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/unistd.h>
#include <sys/cygwin.h>

int main(
	int argc,
	char *argv[])
{
	char path[1024];
	char cmd[1024];
	int i;
	for (i = 1; i < argc; i++) {
		cygwin_conv_to_full_posix_path(argv[i], path);
		sprintf(cmd, "/bin/emacsclient -n '%s'", path);
		system(cmd);
	}
	return 0;
}
