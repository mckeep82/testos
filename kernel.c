#include "console.h"
#include "keyboard.h"

void main() {
	clear_terminal();
	print_string("c:/>");
	unsigned char byte;
	while (1) {
		while (byte = scan()) {

			print_character(charmap[byte]);
		}
	}	

	return;
}
