/*
 *  mon.h - cxmon main program
 *
 *  cxmon (C) 1997-2004 Christian Bauer, Marc Hellwig
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef MON_H
#define MON_H

#include <stdio.h>
#include <set>
#include <stdint.h>

typedef uint32_t mon_addr_t;

/*
 *  Initialization, deinitialization and invocation
 */

void mon_init();
void mon_exit();
void mon(int argc, const char **argv);

// Break points prompt
const char STR_ACTIVE_BREAK_POINTS[]	= "Active Break Points:\n";
const char STR_DISABLED_BREAK_POINTS[]	= "Disabled Break Points:\n";

/*
 *  Definitions for adding commands to mon
 */

// Input tokens
enum Token {
	T_NULL,		// Invalid token
	T_END,		// End of line
	T_NUMBER,	// Hexadecimal/decimal number (uint32_t)
	T_STRING,	// String enclosed in ""
	T_NAME,		// Variable name
	T_DOT,		// '.'
	T_COLON,	// ':'
	T_COMMA,	// ','
	T_LPAREN,	// '('
	T_RPAREN,	// ')'
	T_PLUS,		// '+'
	T_MINUS,	// '-'
	T_MUL,		// '*'
	T_DIV,		// '/'
	T_MOD,		// '%'
	T_AND,		// '&'
	T_OR,		// '|'
	T_EOR,		// '^'
	T_SHIFTL,	// '<<'
	T_SHIFTR,	// '>>'
	T_NOT,		// '~'
	T_ASSIGN	// '='
};

// Scanner variables
extern enum Token mon_token;  // Last token read
extern mon_addr_t mon_number;    // Contains the number if mon_token==T_NUMBER
extern char *mon_string;      // Contains the string if mon_token==T_STRING
extern char *mon_name;        // Contains the variable name if mon_token==T_NAME

// Streams for input, output and error messages
extern FILE *monin, *monout, *monerr;

// Current address, value of '.' in expressions
extern mon_addr_t mon_dot_address;

extern bool mon_use_real_mem;  // Flag: mon is using real memory
extern uint32_t mon_mem_size;    // Size of mon buffer (if mon_use_real_mem = false)

extern bool mon_macos_mode;    // Flag: enable features in the disassembler for working with MacOS code

typedef std::set<mon_addr_t> BREAK_POINT_SET;
extern BREAK_POINT_SET active_break_points;
extern BREAK_POINT_SET disabled_break_points;

// Add command to mon
extern void mon_add_command(const char *name, void (*func)(), const char *help_text);

// Functions for commands
extern void mon_error(const char *s);         // Print error message
extern enum Token mon_get_token();            // Get next token
extern bool mon_expression(mon_addr_t *number);  // Parse expression
extern bool mon_aborted();                    // Check if Ctrl-C was pressed

// Memory access
extern uint32_t (*mon_read_byte)(mon_addr_t adr);
extern void (*mon_write_byte)(mon_addr_t adr, uint32_t b);
extern uint32_t mon_read_half(mon_addr_t adr);
extern void mon_write_half(mon_addr_t adr, uint32_t w);
extern uint32_t mon_read_word(mon_addr_t adr);
extern void mon_write_word(mon_addr_t adr, uint32_t l);

// Check if break point is set
#define IS_BREAK_POINT(address) (active_break_points.find(address) != active_break_points.end())
// Add break point
extern void mon_add_break_point(mon_addr_t addr);
extern void mon_load_break_point(const char* file_path);

#endif
