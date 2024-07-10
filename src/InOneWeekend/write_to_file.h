#include "rtweekend.h"

#define NOMINMAX
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <filesystem>

#include "color.h"
#include <windows.h>
#include <string>
#include <winnt.rh>

inline std::wstring inner_GetExecutableDirectory() {
	wchar_t buffer[MAX_PATH];
	GetModuleFileNameW(NULL, buffer, MAX_PATH);
	std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
	return std::wstring(buffer).substr(0, pos);
};


inline double inner_linear_to_gamma(double linear_component)
{
	if (linear_component > 0)
		return sqrt(linear_component);

	return 0;
};

inline void inner_write_color(std::ofstream& InOutFileSteam, const double InColor)
{
	static const interval intensity(0.000, 0.999);
	InOutFileSteam << uint8_t(256.f * intensity.clamp(inner_linear_to_gamma(InColor)));
};

void write_to_file(double* InColors, const int32_t InWidth, const int32_t InHeight, bool bInVerbose)
{
	std::wstring filepath = inner_GetExecutableDirectory().append(L"/result.ppm");

	std::ofstream MyFile(filepath, std::ios::out | std::ios::binary);
	MyFile << "P6\n" << InWidth << " " << InHeight << "\n255\n";// << ByteView(&m_pixels[0].RGB[0], sizeof(PixelData) * GetTotalSize());

	const int totalSize = InWidth * InHeight * 3;
	for (int i = 0; i < totalSize; ++i)
	{
		inner_write_color(MyFile, InColors[i]);
	}
	MyFile.close();
	if (bInVerbose)
	{
		std::cout << "Picture written to disk at : " << filepath.c_str() << std::endl;
	}
};