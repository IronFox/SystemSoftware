#include <iostream>
#include <Windows.h>


void PrintIndent(int indent)
{
	for (int i = 0; i < indent; i++)
		wprintf(L"  ");
}

bool EndsWith(const wchar_t*name, const wchar_t*ext)
{
	size_t len = wcslen(name);
	size_t elen = wcslen(ext);
	if (len < elen)
		return false;
	return !wcscmp(name+len-elen,ext);


	//return wcsstr(name,ext) != NULL;	//(strstr)
}

bool doReadFile = true;

void Scan(const wchar_t*folder, int depth=0)
{
	PrintIndent(depth);
	wprintf(L"[%s]\n",folder);

	wchar_t path[0x1000];
	swprintf_s(path,sizeof(path)/sizeof(wchar_t),L"%s\\*",folder);
	WIN32_FIND_DATA data;
	HANDLE find = FindFirstFile(path,&data);
	if (find!=NULL)
	{
		do
		{
			if ((data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
			{
				if (!wcscmp(data.cFileName,L".") || !wcscmp(data.cFileName,L".."))
					continue;
				wchar_t sub[0x1000];
				swprintf_s(sub,sizeof(sub)/sizeof(wchar_t),L"%s\\%s",folder,data.cFileName);
				Scan(sub,depth+1);
			}
			else
			{
				PrintIndent(depth+1);
				wprintf(L"%s",data.cFileName);
				bool isTXT = EndsWith(data.cFileName,L".txt");
				if (isTXT)
				{
					wprintf(L" (!!!)");
				}
				wprintf(L"\n");

				if (isTXT && doReadFile)
				{
					doReadFile = false;
					wchar_t path[0x1000];
					swprintf_s(path,sizeof(path)/sizeof(wchar_t),L"%s\\%s",folder,data.cFileName);
					FILE*f = _wfopen(path,L"rb");
					if (f)
					{
						while(!feof(f))
						{
							char buffer[0x1000];
							size_t read = fread(buffer,1,sizeof(buffer)-1,f);
							buffer[read] = 0;
							printf("%s",buffer);
						}
						fclose(f);
					}

				}
			}
		}
		while (FindNextFile(find,&data));
		FindClose(find);
	}
}


int main(int argc, char**argv)
{
	Scan(L"D:\\tmp");
	system("PAUSE");
}

