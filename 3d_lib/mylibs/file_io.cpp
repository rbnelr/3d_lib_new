#include "file_io.hpp"

namespace file_io {

	bool load_text_file (cstr filepath, std::string* text) {

		FILE* f = fopen(filepath, "rb"); // i don't want "\r\n" to "\n" conversion, because it interferes with my file size calculation and i usually handle \r\n anyway
		if (!f)
			return false;
		defer {
			fclose(f);
		};

		fseek(f, 0, SEEK_END);
		int filesize = ftell(f);
		fseek(f, 0, SEEK_SET);

		text->resize(filesize);

		uptr ret = fread(&(*text)[0], 1,text->size(), f);
		if (ret != (uptr)filesize) return false;

		return true;
	}

	bool load_binary_file (cstr filepath, Blob* blob) {

		FILE* f = fopen(filepath, "rb"); // we don't want "\r\n" to "\n" conversion
		if (!f)
			return false;
		defer {
			fclose(f);
		};

		fseek(f, 0, SEEK_END);
		int filesize = ftell(f);
		fseek(f, 0, SEEK_SET);

		auto tmp = Blob::alloc(filesize);

		uptr ret = fread(tmp.data, 1,tmp.size, f);
		if (ret != (uptr)filesize) return false;

		*blob = std::move(tmp);
		return true;
	}

	bool load_fixed_size_binary_file (cstr filepath, void* data, uptr sz) {

		FILE* f = fopen(filepath, "rb");
		if (!f)
			return false;
		defer {
			fclose(f);
		};

		fseek(f, 0, SEEK_END);
		int filesize = ftell(f);
		fseek(f, 0, SEEK_SET);

		if (filesize != sz)
			return false;

		uptr ret = fread(data, 1,sz, f);
		if (ret != sz)
			return false;

		return true;
	}

	bool write_fixed_size_binary_file (cstr filepath, void const* data, uptr sz) {

		FILE* f = fopen(filepath, "wb");
		if (!f)
			return false;
		defer {
			fclose(f);
		};

		uptr ret = fwrite(data, 1,sz, f);
		if (ret != sz)
			return false;

		return true;
	}

	bool write_text_file (cstr filepath, std::string const& text) {
		return write_fixed_size_binary_file(filepath, &text[0], text.size());
	}
}
