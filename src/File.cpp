#include "File.h"

File::File(const std::string& filename, uint8_t mode)
	:m_filename(filename), m_filemode(mode)
{
	/* Assume default reading mode */
	std::string s_mode = "r";

	if (mode & FileMode::Read)
	{
		s_mode = "r";
	}
	else if (mode & FileMode::Write)
	{
		s_mode = "w";
	}
	else if (mode & FileMode::Append)
	{
		s_mode = "a";
	}

	if (mode & FileMode::Update)
	{
		s_mode += "+";
	}

	if (mode & FileMode::Binary)
	{
		s_mode += "b";
	}

	fopen_s(&m_file, filename.c_str(), s_mode.c_str());
}

File::~File()
{
	fclose(m_file);
}

FILE* File::file() const
{
	return m_file;
}

File::File(File&& other) noexcept
	:m_file(other.m_file), m_filename(std::move(other.m_filename)), m_filemode(other.m_filemode)
{
	other.m_file = nullptr;
}

File& File::operator=(File&& other) noexcept
{
	if (this != &other)
	{
		if (m_file)
		{
			this->~File();
		}

		m_file = other.m_file;
		m_filename = std::move(other.m_filename);
		m_filemode = other.m_filemode;
		other.m_file = nullptr;
	}

	return *this;
}

std::vector<char> File::readBytes(size_t count)
{
	std::vector<char> buffer(count);

	size_t bytes = fread(buffer.data(), 1, count, m_file);
	buffer.resize(bytes);

	return buffer;
}

std::string File::readLine()
{
	std::string line;

	int character;

	while (!((character = fgetc(m_file)) == EOF || character == '\n'))
	{
		line += static_cast<char>(character);
	}

	if (line.empty() && character == EOF)
	{
		return std::string();
	}

	return line;
}

std::string File::readAll()
{
	std::string lines;

	std::string line;
	while ((line = readLine()) != std::string())
	{
		lines += line;
	}

	return lines;
}

size_t File::writeBytes(std::span<const char> data)
{
	return fwrite(data.data(), 1, data.size(), m_file);
}

size_t File::writeLine(const std::string& line)
{
	size_t data = fwrite(line.c_str(), 1, line.length(), m_file);

	if (data == line.length())
	{
		if (fputc('\n', m_file) != EOF)
		{
			data++;
		}
	}

	return data;
}

size_t File::writeAll(const std::string& lines)
{
	size_t data = 0;

	std::istringstream iss(lines);
	std::string line;

	while (std::getline(iss, line))
	{
		data += writeLine(line);
	}

	return data;
}

[[deprecated("read is deprecated. Only use for compatibility, otherwise use readBytes, readLine or readAll")]]
size_t File::read(void* buffer, size_t size, size_t count)
{
	return fread(buffer, size, count, m_file);
}

[[deprecated("write is deprecated. Only use for compatibility, otherwise use writeBytes, writeLine or writeAll")]]
size_t File::write(void* buffer, size_t size, size_t count)
{
	return fwrite(buffer, size, count, m_file);
}
