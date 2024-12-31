#pragma once

#include <cstdio>
#include <format>
#include <string>
#include <vector>
#include <span>
#include <sstream>

class File
{
	public:
		typedef enum 
		{
			Read   = 0b00001,
			Write  = 0b00010,
			Append = 0b00100,
			Binary = 0b01000,
			Update = 0b10000
		}FileMode;
	public:
		File(const std::string& filename, uint8_t mode);
		~File();

		FILE* file() const;

		File(File&& other) noexcept;
		File& operator=(File&& other) noexcept;

		std::vector<char> readBytes(size_t count);
		std::string readLine();
		std::string readAll();

		size_t writeBytes(std::span<const char> data);
		size_t writeLine(const std::string& line);
		size_t writeAll(const std::string& lines);

		size_t read(void* buffer, size_t size, size_t count);
		size_t write(void* buffer, size_t size, size_t count);

		File(const File&) = delete;
		File& operator=(const File&) = delete;

	private:
		FILE* m_file;
		std::string m_filename;
		uint8_t m_filemode;
};