#pragma once

#include "basic_typedefs.hpp"
#include "math.hpp"

#include <string>
#include <cstdarg>
#include "assert.h"

#include "windows.h"

namespace string {
	using namespace basic_typedefs;
	using namespace math;
	
	#define ANSI_COLOUR_CODE_RED	"\033[1;31m"
	#define ANSI_COLOUR_CODE_YELLOW	"\033[1;33m"
	#define ANSI_COLOUR_CODE_NC		"\033[0m"

	// Printf that outputs to a std::string
	void vprints (std::string* s, cstr format, va_list vl);
	void prints (std::string* s, cstr format, ...);
	std::string prints (cstr format, ...);

	inline bool is_lower (char c) {
		return c >= 'a' && c <= 'z';
	}
	inline bool is_upper (char c) {
		return c >= 'A' && c <= 'Z';
	}

	inline char to_lower (char c) {
		return is_upper(c) ? c +('a' -'A') : c;
	}
	inline char to_upper (char c) {
		return is_lower(c) ? c +('A' -'a') : c;
	}

	std::basic_string<wchar_t> utf8_to_wchar (std::string const& utf8);
	std::string wchar_to_utf8 (std::basic_string<wchar_t> const& wchar);
}
