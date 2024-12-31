#pragma once

#include <string>
#include <vector>

#include "Application.h"

#ifdef WINDOWS
#include <shobjidl.h>
#endif


namespace Apollo
{
	class FileSelector
	{
		public:
			static std::wstring SelectFile();
			static std::wstring SelectFile(std::wstring filters, wchar_t nullSymbol);
	};
}

