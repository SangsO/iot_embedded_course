#include "User.h"

User::User() {}

User::~User() {}

void User::item_select()
{
	while (1)
	{
		while (item_select_wait);
		if (item_select_end == 1)
			break;

		User::user_interface();

		item_select_wait = 1;
	}
}

void User::user_interface() {
	cout << "----------------------------------------------------------------------------------------" << endl;
	cout << "1. ���ο� �̹��� ����" << endl;
	cout << "2. ��ƼĿ �̹��� ����" << endl;
	cout << "3. ���α׷� ����" << endl;
	cout << "----------------------------------------------------------------------------------------" << endl << endl;
	int num;
	cout << "��ȣ ���� >>";
	cin >> num;
	select_file(num);
}

int User::img_type;
void User::select_file(int num) {
	_finddata_t fd;
	long handle;
	int result = 1;
	string file_name;
	string file_path;
	string save_path;
	string list_name;
	string load_path;

	switch (num) {

	case 1:	//�� �̹��� �߰��� ���
		cout << "----------------------------------------------------------------------------------------" << endl;
		cout << "1. �Ȱ� �̹��� ����" << endl;
		cout << "2. �Լ� �̹��� ����" << endl;
		cout << "----------------------------------------------------------------------------------------" << endl << endl;
		cout << "��ȣ ����>>";
		cin >> img_type;

		switch (img_type) {
		case 1:	//�Ȱ� �̹����� ���
			handle = _findfirst("new_image\\glasses\\*.jpg", &fd);  //���̹��� ����� �Ȱ����� �� ��� ������ ã�´�.
			//TODO : *.*�� �ϸ� ������ ��� �ν� ����(��ΰ� �ƿ� ���� ��츸 �ν�) --> �ϴ� jpg�� ����
			file_path = "new_image\\glasses\\";
			save_path = "saved_image\\glasses\\";
			list_name = "�Ȱ� ";
			break;
		case 2: //�Լ� �̹����� ���
			handle = _findfirst("new_image\\lips\\*.jpg", &fd);  //���̹��� ����� �Ȱ����� �� ��� ������ ã�´�.
			//TODO : *.*�� �ϸ� ������ ��� �ν� ����(��ΰ� �ƿ� ���� ��츸 �ν�) --> �ϴ� jpg�� ����
			file_path = "new_image\\lips\\";
			save_path = "saved_image\\lips\\";
			list_name = "�Լ� ";
			break;
		}

		if (handle == -1)
		{
			//printf("There were no files.\n");
			cout << "������ �̹��� ����" << "\n";
			return;
		}
		else
		{
			cout << "----------------------------------------------------------------------------------------" << "\n";
			cout << list_name << "�̹��� ���" << "\n";
			cout << "----------------------------------------------------------------------------------------" << "\n";
			int file_num = 1;
			while (result != -1)
			{
				//printf("File: %s\n", fd.name);
				//cout << "Filename: " << fd.name << endl;
				printf("File%02d : %s\n", file_num, fd.name);
				file_num++;
				result = _findnext(handle, &fd);
			}

			cout << "--------------------------------------------------------------------------------------------" << endl << endl;
			cout << "���ϸ� �Է�(Ȯ���ڱ��� �Է����ּ���) >>";
			cin >> file_name;

			while (!IO::file_check(num, file_name)) {
				cout << "--------------------------------------------------------------------------------------------" << endl << endl;
				cout << "���ϸ� �ٽ� �Է�(Ȯ���ڱ��� �Է����ּ���) >>";
				cin >> file_name;
			}

			file_path = file_path + file_name;
			save_path = save_path + file_name;
			_findclose(handle);

			//�̹��� ������
			cv::Mat save_img = cv::imread(file_path);
			cv::imwrite(save_path, save_img);
			cout << "\n" << save_path << " �� ����Ǿ����ϴ�.\n\n";

			//task(); //TODO: 2�� �۾��� ���� �̹��� �ε��ʿ��� �ص� �ɰͰ���(�ε�� ��� ����, �׸��� init() ��ʹ� ������..), 3�� �۾��� �ʹ����� ����
		}
		break;
	case 2: //������ �̹��� �����ϴ� ���
		cout << "----------------------------------------------------------------------------------------" << endl;
		cout << "1. �Ȱ� �̹��� ����" << endl;
		cout << "2. �Լ� �̹��� ����" << endl;
		cout << "----------------------------------------------------------------------------------------" << endl << endl;
		cout << "��ȣ ����>>";
		cin >> img_type;

		switch (img_type) {
		case 1:	//�Ȱ� �̹����� ���
			handle = _findfirst("saved_image\\glasses\\*.jpg", &fd);  //�̹����� ����� �Ȱ����� �� ��� ������ ã�´�.
			//TODO : *.*�� �ϸ� ������ ��� �ν� ����(��ΰ� �ƿ� ���� ��츸 �ν�) --> �ϴ� jpg�� ����
			load_path = "saved_image\\glasses\\";
			list_name = "�Ȱ� ";
			break;
		case 2: //�Լ� �̹����� ���
			handle = _findfirst("saved_image\\lips\\*.jpg", &fd);  //�̹����� ����� �Ȱ����� �� ��� ������ ã�´�.
			 //TODO : *.*�� �ϸ� ������ ��� �ν� ����(��ΰ� �ƿ� ���� ��츸 �ν�) --> �ϴ� jpg�� ����
			load_path = "saved_image\\lips\\";
			list_name = "�Լ� ";
			break;
		}
		if (handle == -1)
		{
			//printf("There were no files.\n");
			cout << "������ �̹��� ����" << "\n";
			return;
		}
		else
		{
			cout << "----------------------------------------------------------------------------------------" << "\n";
			cout << list_name << "�̹��� ���" << "\n";
			cout << "----------------------------------------------------------------------------------------" << "\n";
			int file_num = 1;
			while (result != -1)
			{
				//printf("File: %s\n", fd.name);
				//cout << "Filename: " << fd.name << endl;
				printf("File%02d : %s\n", file_num, fd.name);
				file_num++;
				result = _findnext(handle, &fd);
			}

			cout << "--------------------------------------------------------------------------------------------" << endl << endl;
			cout << "���ϸ� �Է�(Ȯ���ڱ��� �Է����ּ���) >>";
			cin >> file_name;

			while (!IO::file_check(num, file_name)) {
				cout << "--------------------------------------------------------------------------------------------" << endl << endl;
				cout << "���ϸ� �ٽ� �Է�(Ȯ���ڱ��� �Է����ּ���) >>";
				cin >> file_name;
			}

			load_path = load_path + file_name;
			_findclose(handle);


			//���, ���� �����ؾ���
			//�̹��� ���Ϳ� �����ؾ���
			//cv::Mat save_img = cv::imread(load_path);
			IO::item_setting(load_path, img_type);
			User::sticker_attach();

			//task(); //TODO: 2�� �۾��� ���� �̹��� �ε��ʿ��� �ص� �ɰͰ���(�ε�� ��� ����, �׸��� init() ��ʹ� ������..), 3�� �۾��� �ʹ����� ����
		}
		break;
	case 3:	//���α׷� ����
	exit(0);
		break;
	}
}

void User::sticker_attach()
{
	int choice;
	std::cout << "���(1)/����(0) : ";
	std::cin >> choice;
	IO::item_IO_data[User::img_type - 1].first = choice;
}




