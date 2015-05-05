ti
==

Ti-82 stats simulator for LibreCalc project

Building the Software
---------------------

To build this emulator, you must have the developer files and shared objects
for SDL 2. On Debian GNU/Linux and derivatives, you can install this with:

    # apt-get install libsdl2-dev

You must also have a the GNU C++ compiler (g++) which on Debian is part of the
`build-essential` package. In order to use the build script, you will need GNU
Make, which is in the `make` package.

You can build the software by running:

    $ make
