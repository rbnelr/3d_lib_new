#include "parse.hpp"

namespace n_parse {
	bool character (char** pcur, char c) {
		if (**pcur != c)
			return false;
		*pcur += 1;
		return true;
	}

	bool whitespace (char** pcur) {
		char* cur = *pcur;

		char c = *cur;
		if (!is_whitespace_c(c))
			return false;

		while (is_whitespace_c(*cur))
			++cur;

		*pcur = cur;
		return true;
	}

	bool newline (char** pcur) {
		char* cur = *pcur;

		char c = *cur;
		if (!is_newline_c(c))
			return false;

		++cur;

		char c2 = *cur;
		if (is_newline_c(c2) && c2 != c) {
			++cur; // skip '\n\r' and '\r\n'
		}

		*pcur = cur;
		return true;
	}

	bool string (char** pcur, cstr str) {
		char* cur = *pcur;

		while (*str != '\0') {
			if (*str != *cur) return false;
			++str;
			++cur;
		}

		*pcur = cur;
		return true;
	}
	bool string_ignore_case (char** pcur, cstr str) {
		char* cur = *pcur;

		while (*str != '\0') {
			if (to_upper(*str) != to_upper(*cur)) return false;
			++str;
			++cur;
		}

		*pcur = cur;
		return true;
	}

	bool identifier (char** pcur, cstr identifier_string) { // checks if *pcur points to a string equal to identifier_string that ends on a non identifer char
		char* cur = *pcur;

		if (!string(&cur, identifier_string))
			return false;

		if (is_identifier_c(*cur))
			return false;

		*pcur = cur;
		return true;
	}
	bool identifier_ignore_case (char** pcur, cstr identifier_string) { // checks if *pcur points to a string equal to identifier_string that ends on a non identifer char
		char* cur = *pcur;

		if (!string_ignore_case(&cur, identifier_string))
			return false;

		if (is_identifier_c(*cur))
			return false;

		*pcur = cur;
		return true;
	}

	bool quoted_string (char** pcur) {
		char* cur = *pcur;

		if (!character(&cur, '"'))
			return false;

		while (*cur != '"' && *cur != '\0')
			++cur;

		if (!character(&cur, '"'))
			return false;

		*pcur = cur;
		return true;
	}
	bool quoted_string (char** pcur, char** out_begin, int* out_length) {
		char* cur = *pcur;

		char* begin = cur;

		if (!quoted_string(&cur))
			return false;

		char* end = cur;

		begin += 1; // string begins after '"'
		end -= 1; // string ends before '"'

		*out_begin = begin;
		*out_length = (int)(end -begin);

		*pcur = cur;
		return true;
	}

	bool quoted_string_copy (char** pcur, std::string* out) {
		char* begin;
		int length;
		if (!quoted_string(pcur, &begin, &length))
			return false;

		out->assign(begin, length);

		return true;
	}

	bool unsigned_int (char** pcur, unsigned int* out) {
		char* cur = *pcur;

		if (!is_digit_c(*cur))
			return false;

		unsigned int i = 0;

		while (is_digit_c(*cur)) {
			char c = *cur;

			i *= 10;
			i += c -'0';

			++cur;
		}

		*out = i;
		*pcur = cur;
		return true;
	}
	bool signed_int (char** pcur, int* out) {
		char* cur = *pcur;

		bool negative = false;

		if (		*cur == '-' ) {
			negative = true;
			++cur;
		} else if ( *cur == '+' ) {
			negative = false;
			++cur;
		}

		whitespace(&cur);

		unsigned int i;

		if (!unsigned_int(&cur, &i))
			return false;

		*out = negative ? -(int)i : (int)i;
		*pcur = cur;
		return true;
	}

	bool float32 (char** pcur, float* out) {
		char* cur = *pcur;

		char* endptr;
		float ret = strtof(cur, &endptr);

		if (endptr == cur)
			return false;

		cur = endptr;

		*out = ret;
		*pcur = cur;
		return true;
	}
	bool bool_ (char** pcur, bool* out) {
		char* cur = *pcur;

		if (		character(&cur, '1') || identifier_ignore_case(&cur, "true") )
			*out = true;
		else if (	character(&cur, '0') || identifier_ignore_case(&cur, "false") )
			*out = false;
		else
			return false;

		*pcur = cur;
		return true;
	}

	bool end_of_input (char* cur) {
		return *cur == '\0';
	}

	bool line_comment (char** pcur) { // consumes the newline too
		char* cur = *pcur;

		if (!(cur[0] == '/' && cur[1] == '/'))
			return false;
		cur += 2;

		while (!(newline(&cur) || *cur == '\0'))
			++cur;

		*pcur = cur;
		return true;
	}

	bool end_of_line (char** pcur) { // consume following whitespace, line comment and newline
		char* cur = *pcur;

		whitespace(&cur);

		if (!(line_comment(&cur) || newline(&cur) || end_of_input(cur)))
			return false;

		*pcur = cur;
		return true;
	}

}
