#pragma once

#include <iostream>
#include <string>
#include <fstream>

#include "../pivar.h"

// >> MAKE THIS CLASS THREAD-SAFE << 
namespace pilib {
#define OMODE std::ios::openmode
	class olstream {
	private:
		bool fmode;	//true for file, false for stream
		std::ofstream file;
		std::ostream* stream;
		const char* fname;
		OMODE omodes;
	protected:
		inline bool checkStream();	//changes stored stream variable to be safe
		std::ostream& streamGuard();	//doesn't change stored stream variable, just returns safe one
	public:
		olstream();
		olstream(const char* file, const OMODE modes = std::ios::out);
		olstream(const OMODE modes);
		olstream(std::ostream* stream);
		olstream(std::ostream* stream, const char* file, const OMODE modes = std::ios::out);
		olstream(const olstream& other);
		olstream(olstream&& other);

		void operator=(const olstream& other);
		void operator=(olstream&& other);

		void setModes(const OMODE modes);
		void addModes(const OMODE modes);
		void setStream(const char* file);
		void setStream(const char* file, const OMODE modes);
		void setStream(std::ostream* stream = &std::cout);

		std::ostream& getStream();
		const char* getPath();

		std::ostream& open();
		void close();

		//void test();

		template<typename t>
		olstream& operator<<(t item) {
			if (this->fmode) {
				this->file.open(this->fname, ((this->omodes | std::ios::out) & ~std::ios::in));
				this->file << item;
				this->file.close();
			}
			else {
				this->streamGuard() << item;
			}
			return *this;
		}

		//for more efficient file operations
		template<typename t>
		olstream& operator<<=(t item) {	//opens file and doesn't close 
			if (this->fmode) {
				this->file.open(this->fname, ((this->omodes | std::ios::out) & ~std::ios::in));
				this->file << item;
			}
			else {
				this->streamGuard() << item;
			}
			return *this;
		}
		template<typename t>
		olstream& operator<=(t item) {	//outputs to open file and doesn't close
			if ((this->fmode) && this->file.is_open()) {
				this->file << item;
			}
			else {
				this->streamGuard() << item;
			}
			return *this;
		}
		template<typename t>
		olstream& operator<(t item) {	//closes file
			if (this->fmode && this->file.is_open()) {
				this->file << item;
				this->file.close();
			}
			else {
				this->streamGuard() << item;
			}
			return *this;
		}
	};



	//template to pass to superclasses?
	class lstream : public std::basic_fstream<char> {
	private:
		const char* file;
		OMODE modes;
	public:
		lstream();
		lstream(const char* file, const OMODE modes = (std::ios::in | std::ios::out));
		lstream(const char* file, void* init, const OMODE modes = (std::ios::in | std::ios::out));
		lstream(const lstream& other);
		lstream(lstream&& other);

		void operator=(const lstream& other);
		void operator=(lstream&& other);

		template<typename ct>	//probably don't use this function
		std::streambuf* rdbuf(std::basic_streambuf<char, ct>* sb) {
			std::streambuf* ret = this->std::basic_fstream<char>::rdbuf();
			this->set_rdbuf(sb);
			return ret;
		}

		void setFile(const char* file, OMODE modes = (std::ios::in | std::ios::out));
		void setMode(OMODE modes);
		void addMode(OMODE modes);
		const char* getFile();
		OMODE getModes();

		void openFile(const char* file, OMODE modes = (std::ios::in | std::ios::out));
		void openInput();
		void openOutput();
	};
#undef OMODE

	template<typename t>
	lstream& operator<<(lstream& stream, t& item) {
		//std::cout << "overloaded!\n";
		stream.openOutput();
		static_cast<std::ostream&>(stream) << item;
		stream.close();
		return stream;
	}
}