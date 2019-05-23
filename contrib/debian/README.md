
Debian
====================
This directory contains files used to package DeepOniond/DeepOnion-qt
for Debian-based Linux systems. If you compile DeepOniond/DeepOnion-qt yourself, there are some useful files here.

## DeepOnion: URI support ##


deeponion-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install deeponion-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your DeepOnion-qt binary to `/usr/bin`
and the `../../share/pixmaps/deeponion128.png` to `/usr/share/pixmaps`

deeponion-qt.protocol (KDE)

