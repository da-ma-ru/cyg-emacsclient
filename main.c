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
	char *posix;
	char *cbuf;
	ssize_t size;
	int i;
	char emacsclient_cmd[] = "/bin/emacsclient -n '%s'";

	for (i = 1; i < argc; i++) {
	  if (*argv[i] == '"' && *(argv[i] + strlen(argv[i]) - 1) == '"') {
		argv[i]++;
		argv[i][strlen(argv[i]) - 1] = '\0';
	  }
	  size = cygwin_conv_path(CCP_WIN_A_TO_POSIX, argv[i], NULL, 0);
	  if (size > 0) {
		posix = (char *)malloc(size);
		cbuf = (char *)malloc(size + sizeof(emacsclient_cmd));
		if (cygwin_conv_path(CCP_WIN_A_TO_POSIX, argv[i], posix, size) == 0) {
		  sprintf(cbuf, emacsclient_cmd, posix);
		  system(cbuf);
		  // printf("%s\n", cbuf);
		}
		free(posix);
		free(cbuf);
	  }
	}
	return 0;
}
