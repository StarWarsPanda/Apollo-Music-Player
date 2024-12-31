#include "FileSelector.h"

/* https://stackoverflow.com/questions/2896600/how-to-replace-all-occurrences-of-a-character-in-string */
void replaceAll(std::wstring& source, const std::wstring& from, const std::wstring& to)
{
    std::wstring newString;
    newString.reserve(source.length());  // avoids a few memory allocations

    std::wstring::size_type lastPos = 0;
    std::wstring::size_type findPos;

    while (std::wstring::npos != (findPos = source.find(from, lastPos)))
    {
        newString.append(source, lastPos, findPos - lastPos);
        newString += to;
        lastPos = findPos + from.length();
    }

    // Care for the rest after last occurrence
    newString += source.substr(lastPos);

    source.swap(newString);
}

std::wstring Apollo::FileSelector::SelectFile()
{
    return SelectFile(L"", L'\0');
}

std::wstring Apollo::FileSelector::SelectFile(std::wstring filters, wchar_t nullSymbol)
{
    OPENFILENAMEW ofn;
    wchar_t szFile[260] = { 0 };

    std::wstring filterSymbol(1, nullSymbol);
    std::wstring filterNull(1, L'\0');

    replaceAll(filters, filterSymbol, filterNull);

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = filters.empty() ? L"Music(*.mp3)\0 * .mp3\0All Files(*.*)\0 * .*\0\0" : filters.c_str();
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
    
    if (GetOpenFileNameW(&ofn) == TRUE) {
        return ofn.lpstrFile;
    }

    return L"";
}
