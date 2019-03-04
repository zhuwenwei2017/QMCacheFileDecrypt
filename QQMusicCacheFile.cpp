// QQMusicCacheFile.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <Windows.h>
#include <shlobj_core.h>
#pragma comment (lib, "Shell32.lib")

char  rol(char value, char shift)
{
	__asm
	{
		push ecx
		mov cl, shift
		rol value, cl
		pop ecx
	}
	return value;
}

char  ror(char value, char shift)
{
	__asm
	{
		push ecx
		mov cl, shift
		ror value, cl
		pop ecx
	}
	return value;
}
void DecryptCacheFile(int a1 , const char *in , char *out, char a4)
{
	char *v4; // esi
	char v5; // al
	char v6; // al

	v4 = out;
	if (a1 > 0)
	{
		do
		{
			v5 = *in;
			if (a4)
				v6 = ror(v5 ^ 0x9A, 2) ^ 0x52;
			else
				v6 = rol((v5 ^ 0x52), 2) ^ 0x9A;
			*v4++ = v6;
			++in;
			--a1;
		} while (a1);
	}
}

void DoTest()
{
	std::ifstream inFile;
	std::string cachePath;
	char tmp[MAX_PATH];
	SHGetSpecialFolderPathA(NULL, tmp, CSIDL_APPDATA, FALSE);
	cachePath = tmp;
	cachePath.append("\\Tencent\\QQMusic\\QQMusicCache\\QMDL\\O600004UbyuM1bcVtx.ogg.cache");
	inFile.open(cachePath, std::ifstream::binary | std::ifstream::in);
	assert(inFile.good());

	inFile.seekg(0, inFile.end);
	int fileSize = inFile.tellg();
	inFile.seekg(0, std::ifstream::beg);
	std::vector<char> cacheData(fileSize);
	inFile.read(cacheData.data(), cacheData.size());

	DecryptCacheFile(cacheData.size(), (const char*)cacheData.data(), (char*)cacheData.data(), false);
	std::ofstream outFile;
	outFile.open("D:\\Out.ogg", std::ofstream::out | std::ofstream::binary);
	outFile.write(cacheData.data(), cacheData.size());
	outFile.close();
}
int main()
{
	DoTest();
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
