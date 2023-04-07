#include "console.h"
#include <stdint.h>
#include "portmap.h"

char* const VGA_BUFFER = (char*) 0xb8000;
VGA_Color terminal_font_color = LIGHT_GRAY;
VGA_Color terminal_background_color = BLACK;

uint16_t terminal_position = 0;

void clear_terminal() {

	for (int i=0; i < VGA_WIDTH*VGA_HEIGHT*VGA_BYTES_PER_CHARACTER; i+=2) {
		VGA_BUFFER[i] = 0;
		VGA_BUFFER[i+1] = 0x07;
	}

	terminal_position=0;
	update_cursor();

}

void set_terminal_font_color(VGA_Color col) {

	terminal_font_color = col;
}

void set_terminal_background_color(VGA_Color col) {
	terminal_background_color = col;
}

void print_character(char c) {

	print_character_with_color(c, terminal_background_color, terminal_font_color);
}

void print_string(char* str) {

	print_string_with_color(str, terminal_background_color, terminal_font_color);
}

void print_line(char* str) {

	print_line_with_color(str, terminal_background_color, terminal_font_color);
}

void print_line_with_color(char* str, VGA_Color bg_color, VGA_Color font_color) {

	print_string_with_color(str, bg_color, font_color);
	print_character_with_color('\n', bg_color, font_color);
}

void print_string_with_color(char* str, VGA_Color bg_color, VGA_Color font_color) {

	for (int i=0; str[i] != '\0'; i++) {
		print_character_with_color(str[i], bg_color, font_color);
	}
}

void print_character_with_color(char c, VGA_Color bg_color, VGA_Color font_color) {

	if (c == '\n') {

		terminal_position = (terminal_position+(VGA_WIDTH*VGA_BYTES_PER_CHARACTER)) - (terminal_position % (VGA_WIDTH*VGA_BYTES_PER_CHARACTER));
		return;
	}

	VGA_BUFFER[terminal_position++] = c;
	VGA_BUFFER[terminal_position++] = (bg_color << 4) | font_color;
	update_cursor();
}


void enable_cursor(uint8_t cursor_start, uint8_t cursor_end) {

	outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);
	
	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3D5) & 0xE0) | cursor_end);
}

void disable_cursor() {

	outb(0x3D4, 0x0A);
	outb(0x3D5, 0x20);
}

void update_cursor() {

	uint16_t pos = terminal_position/2;

	outb(0x3D4, 0x0F); // CURSOR LOW REGISTER
	outb(0x3D5, (uint8_t) (pos));// & 0xFF)); // SIGN-UNSIGN so 0xFF unsigns it
	outb(0x3D4, 0x0E); // CURSOR HIGH REGISTER
	outb(0x3D5, (uint8_t) ((pos >> 8)));// & 0xFF));
}

uint16_t get_cursor_position(void) {

	uint16_t pos = 0;
	outb(0x3D4, 0x0F);
	pos |= inb(0x3D5);
	outb(0x3D4, 0x0E);
	pos |= ((uint16_t)inb(0x3D5)) << 8;
	return pos;
}

uint8_t inb(uint16_t port) {

	uint8_t ret;
	__asm__ __volatile__("inb %1, %0" : "=a" (ret) : "Nd" (port));
	return ret;
}

void outb(uint16_t port, uint8_t val) {

	__asm__ __volatile__("outb %0, %1" : : "a" (val), "Nd" (port));

}
