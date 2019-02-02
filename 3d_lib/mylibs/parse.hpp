#pragma once

#include "basic_typedefs.hpp"
#include "string.hpp"

namespace n_parse {
	using namespace basic_typedefs;
	using namespace string;

	inline bool is_whitespace_c (char c) {		return c == ' ' || c == '\t'; }
	inline bool is_newline_c (char c) {			return c == '\n' || c == '\r'; }
	inline bool is_lower_c (char c) {				return c >= 'a' && c <= 'z'; }
	inline bool is_upper_c (char c) {				return c >= 'A' && c <= 'Z'; }
	inline bool is_alpha_c (char c) {				return is_lower_c(c) || is_upper_c(c); }
	inline bool is_digit_c (char c) {				return c >= '0' && c <= '9'; }

	inline bool is_identifier_start_c (char c) {	return is_alpha_c(c) || c == '_'; }
	inline bool is_identifier_c (char c) {		return is_alpha_c(c) || is_digit_c(c) || c == '_'; }

	bool character (char** pcur, char c);

	bool whitespace (char** pcur);

	bool newline (char** pcur);

	bool string (char** pcur, cstr str);
	bool string_ignore_case (char** pcur, cstr str);

	bool identifier (char** pcur, cstr identifier_string);
	bool identifier_ignore_case (char** pcur, cstr identifier_string);

	bool quoted_string (char** pcur);
	bool quoted_string (char** pcur, char** out_begin, int* out_length);

	bool quoted_string_copy (char** pcur, std::string* out);

	bool unsigned_int (char** pcur, unsigned int* out);
	bool signed_int (char** pcur, int* out);

	bool float32 (char** pcur, float* out);
	bool bool_ (char** pcur, bool* out);

	bool end_of_input (char* cur);

	bool line_comment (char** pcur);

	bool end_of_line (char** pcur);

}
