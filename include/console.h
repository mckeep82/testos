#ifndef H_CONSOLE
#define H_CONSOLE

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_BYTES_PER_CHARACTER 2
#define VGA_BYTES_PER_ROW (VGA_WIDTH*VGA_BYTES_PER_CHARACTER)
#define VGA_TOTAL_BYTES (VGA_WIDTH*VGA_HEIGHT*VGA_BYTES_PER_CHARACTER)

typedef enum {
	BLACK=0,
	BLUE,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	BROWN,
	LIGHT_GRAY,
	DARK_GRAY,
	LIGHT_BLUE,
	LIGHT_GREEN,
	LIGHT_CYAN,
	LIGHT_RED,
	LIGHT_MAGENTA,
	YELLOW,
	WHITE
} VGA_Color;
void clear_terminal();
void print_character(char c);
void print_string(char* str1);
void print_line(char* str1);
void print_character_with_color(char c, VGA_Color background, VGA_Color font_color);
void print_string_with_color(char* str, VGA_Color background, VGA_Color font_color);
void print_line_with_color(char* str, VGA_Color background, VGA_Color font_color);
void update_cursor();
#endif
