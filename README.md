# Tetribit

#	Tetris implementation using bit operations only

#	The most important thing about this game is the fact that the memory it
uses for describing the map is just a long variable that occupies 8 bytes of memory.
The elements that arrive on the map are described by another long variable.

#	The visual representation of the parts depend on the binary representation of
the variables that stores them. The size of the map is 8 x 8, so, if we wanted tp bring
on the map a square, we would pick a number with a binary representation like this:
0.0.0.0.1.1.1.1. This variable has the last four bytes full of one, so it would fill
half of the map.
