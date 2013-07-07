#
# Makefile
#
# Copyright (C) 2005 Koji Nakamaru
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2, or (at your option)
# any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software Foundation,
# Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
#

TARGET=cyg-emacsclient.exe

$(TARGET): main.c resource.rc resource.ico
	windres -i resource.rc -o resource.o
	gcc -O2 -Wall -mwindows -c main.c
	gcc -O2 -Wall -mwindows *.o -o $(TARGET) -Wl,--subsystem,windows

install: $(TARGET)
	install -s $(TARGET) /bin
	path=`cygpath -u "$$USERPROFILE/SendTo/"`; \
	rm -f "$$path/Emacs" "$$path/Emacs.lnk"; \
	ln -s /bin/cyg-emacsclient.exe "$$path/Emacs"

clean:
	rm -f *.o *.exe *~
