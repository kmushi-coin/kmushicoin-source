
Debian
====================
This directory contains files used to package ktvd/ktv-qt
for Debian-based Linux systems. If you compile ktvd/ktv-qt yourself, there are some useful files here.

## ktv: URI support ##


ktv-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install ktv-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your ktv-qt binary to `/usr/bin`
and the `../../share/pixmaps/pivx128.png` to `/usr/share/pixmaps`

ktv-qt.protocol (KDE)

