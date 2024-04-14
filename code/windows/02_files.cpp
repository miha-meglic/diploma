#include <Windows.h>

int main() {
	HANDLE hFile = CreateFile(L"test.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	char c;
	for (int i = 0; i < 500; i++) {
		c = i % 26 + 97;
		WriteFile(hFile, &c, 1, NULL, NULL);
	}

	SetFilePointer(hFile, 250, NULL, FILE_BEGIN);

	for (int i = 0; i < 500; i++) {
		c = i % 26 + 97;
		WriteFile(hFile, &c, 1, NULL, NULL);
	}

    SetFilePointer(hFile, 0, NULL, FILE_BEGIN);

	char buf[100];
	ReadFile(hFile, buf, 100, NULL, NULL);

	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	WriteFile(hOut, buf, 100, NULL, NULL);

	CloseHandle(hFile);

	DeleteFile(L"test.txt");
}
