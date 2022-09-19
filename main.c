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
#include <unistd.h>

/* CONSTS  */
#define EMACSCLIENT_COMMAND "/bin/emacsclient"

/* ERROR CODE DEFINE */
#define EXIT_ON_MEMORY_ALLOCATION_ERROR 1
#define EXIT_ON_CONVERSION_FAILURE 2

int main(
	int argc,
	char *argv[])
{
	/* argv pointer for execv() */
	char **posix_args;
	ssize_t size;
	int i;

	/* posic_args additionally included '-n' option and terminal NULL */
	posix_args = (char **)malloc(argc + 2);
	if (posix_args == NULL) {
	  exit(EXIT_ON_MEMORY_ALLOCATION_ERROR);
	}

	/* Set arg-0 which is command path */
	posix_args[0] = EMACSCLIENT_COMMAND;
	/* Set arg-1 which is no wait option */
	posix_args[1] = "-n";
	/* Set TERMINAL NULL */
	posix_args[argc + 1] = NULL;

	for (i = 1; i < argc; i++) {
	  /* Remove double quotes */
	  if (*argv[i] == '"' && *(argv[i] + strlen(argv[i]) - 1) == '"') {
		argv[i]++;
		argv[i][strlen(argv[i]) - 1] = '\0';
	  }
	  size = cygwin_conv_path(CCP_WIN_A_TO_POSIX, argv[i], NULL, 0);
	  if (size <=0) {
		exit(EXIT_ON_CONVERSION_FAILURE);
	  }
	  posix_args[i+1] = (char *)malloc(size);
	  if (posix_args[i+1] == NULL) {
		exit(EXIT_ON_MEMORY_ALLOCATION_ERROR);
	  }
	  if (cygwin_conv_path(CCP_WIN_A_TO_POSIX, argv[i], posix_args[i+1], size) != 0) {
		exit(EXIT_ON_CONVERSION_FAILURE);
	  }
	}
	execv(EMACSCLIENT_COMMAND, posix_args);
}
