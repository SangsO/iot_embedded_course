
#include "User.h"


void stop_work() {

}


int main()
{	
	_finddata_t fd;
	long handle;
	int result = 1;
	string path="";

		handle = _findfirst("d:\\image\\*.*", &fd);  //���� ���� �� ��� ������ ã�´�.

		if (handle == -1)
			return false;

		while (result != -1)
		{
			if (strcmp(fd.name, ".") != 0 && strcmp(fd.name, "..") != 0) {
				path = fd.name;
				
				if (path[path.length() - 3] == 'p') {
					cout << "Filepath: d:\\image\\ " << path << endl;//�Լ� png ó���ϴ� �κ�
				}
				////�׳� �̹��� ó��
			}
			result = _findnext(handle, &fd);
		}
}