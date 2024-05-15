
#include "User.h"


void stop_work() {

}


int main()
{	
	_finddata_t fd;
	long handle;
	int result = 1;
	string path="";

		handle = _findfirst("d:\\image\\*.*", &fd);  //현재 폴더 내 모든 파일을 찾는다.

		if (handle == -1)
			return false;

		while (result != -1)
		{
			if (strcmp(fd.name, ".") != 0 && strcmp(fd.name, "..") != 0) {
				path = fd.name;
				
				if (path[path.length() - 3] == 'p') {
					cout << "Filepath: d:\\image\\ " << path << endl;//입술 png 처리하는 부분
				}
				////그냥 이미지 처리
			}
			result = _findnext(handle, &fd);
		}
}