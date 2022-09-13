cyg-emacsclient
===============

This code is forked from [otsuka512/cyg-emacsclient](https://github.com/otsuka512/cyg-emacsclient).

cyg-emacsclient is a wrapper for emacsclient in cygwin environment. It
convert arguments into the posix form and passes them to the real
emacsclient. By making a symbolic link to the binary in your SendTo
directory, you can send files to cygwin emacs from Windows Explorer.

Note: The resource.ico was converted from gnu.xpm originally bundled
with emacs.

To Do
=====

1. Emacs (server)が立ち上がっていないときは、自動的に立ち上げるようにする
2. cygwinのパッケージとしてインストールできるようにする
