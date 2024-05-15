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
	cout << "1. 새로운 이미지 저장" << endl;
	cout << "2. 스티커 이미지 선택" << endl;
	cout << "3. 프로그램 종료" << endl;
	cout << "----------------------------------------------------------------------------------------" << endl << endl;
	int num;
	cout << "번호 선택 >>";
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

	case 1:	//새 이미지 추가의 경우
		cout << "----------------------------------------------------------------------------------------" << endl;
		cout << "1. 안경 이미지 저장" << endl;
		cout << "2. 입술 이미지 저장" << endl;
		cout << "----------------------------------------------------------------------------------------" << endl << endl;
		cout << "번호 선택>>";
		cin >> img_type;

		switch (img_type) {
		case 1:	//안경 이미지의 경우
			handle = _findfirst("new_image\\glasses\\*.jpg", &fd);  //새이미지 저장된 안경폴더 내 모든 파일을 찾는다.
			//TODO : *.*로 하면 파일이 없어도 인식 못함(경로가 아예 없는 경우만 인식) --> 일단 jpg로 하자
			file_path = "new_image\\glasses\\";
			save_path = "saved_image\\glasses\\";
			list_name = "안경 ";
			break;
		case 2: //입술 이미지의 경우
			handle = _findfirst("new_image\\lips\\*.jpg", &fd);  //새이미지 저장된 안경폴더 내 모든 파일을 찾는다.
			//TODO : *.*로 하면 파일이 없어도 인식 못함(경로가 아예 없는 경우만 인식) --> 일단 jpg로 하자
			file_path = "new_image\\lips\\";
			save_path = "saved_image\\lips\\";
			list_name = "입술 ";
			break;
		}

		if (handle == -1)
		{
			//printf("There were no files.\n");
			cout << "폴더에 이미지 없음" << "\n";
			return;
		}
		else
		{
			cout << "----------------------------------------------------------------------------------------" << "\n";
			cout << list_name << "이미지 목록" << "\n";
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
			cout << "파일명 입력(확장자까지 입력해주세요) >>";
			cin >> file_name;

			while (!IO::file_check(num, file_name)) {
				cout << "--------------------------------------------------------------------------------------------" << endl << endl;
				cout << "파일명 다시 입력(확장자까지 입력해주세요) >>";
				cin >> file_name;
			}

			file_path = file_path + file_name;
			save_path = save_path + file_name;
			_findclose(handle);

			//이미지 저장함
			cv::Mat save_img = cv::imread(file_path);
			cv::imwrite(save_path, save_img);
			cout << "\n" << save_path << " 에 저장되었습니다.\n\n";

			//task(); //TODO: 2번 작업은 기존 이미지 로드쪽에서 해도 될것같음(로드는 계속 가능, 그리고 init() 재귀는 위험함..), 3번 작업은 초반으로 병합
		}
		break;
	case 2: //기존의 이미지 선택하는 경우
		cout << "----------------------------------------------------------------------------------------" << endl;
		cout << "1. 안경 이미지 선택" << endl;
		cout << "2. 입술 이미지 선택" << endl;
		cout << "----------------------------------------------------------------------------------------" << endl << endl;
		cout << "번호 선택>>";
		cin >> img_type;

		switch (img_type) {
		case 1:	//안경 이미지의 경우
			handle = _findfirst("saved_image\\glasses\\*.jpg", &fd);  //이미지가 저장된 안경폴더 내 모든 파일을 찾는다.
			//TODO : *.*로 하면 파일이 없어도 인식 못함(경로가 아예 없는 경우만 인식) --> 일단 jpg로 하자
			load_path = "saved_image\\glasses\\";
			list_name = "안경 ";
			break;
		case 2: //입술 이미지의 경우
			handle = _findfirst("saved_image\\lips\\*.jpg", &fd);  //이미지가 저장된 안경폴더 내 모든 파일을 찾는다.
			 //TODO : *.*로 하면 파일이 없어도 인식 못함(경로가 아예 없는 경우만 인식) --> 일단 jpg로 하자
			load_path = "saved_image\\lips\\";
			list_name = "입술 ";
			break;
		}
		if (handle == -1)
		{
			//printf("There were no files.\n");
			cout << "폴더에 이미지 없음" << "\n";
			return;
		}
		else
		{
			cout << "----------------------------------------------------------------------------------------" << "\n";
			cout << list_name << "이미지 목록" << "\n";
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
			cout << "파일명 입력(확장자까지 입력해주세요) >>";
			cin >> file_name;

			while (!IO::file_check(num, file_name)) {
				cout << "--------------------------------------------------------------------------------------------" << endl << endl;
				cout << "파일명 다시 입력(확장자까지 입력해주세요) >>";
				cin >> file_name;
			}

			load_path = load_path + file_name;
			_findclose(handle);


			//출력, 삭제 결정해야함
			//이미지 벡터에 저장해야함
			//cv::Mat save_img = cv::imread(load_path);
			IO::item_setting(load_path, img_type);
			User::sticker_attach();

			//task(); //TODO: 2번 작업은 기존 이미지 로드쪽에서 해도 될것같음(로드는 계속 가능, 그리고 init() 재귀는 위험함..), 3번 작업은 초반으로 병합
		}
		break;
	case 3:	//프로그램 종료
	exit(0);
		break;
	}
}

void User::sticker_attach()
{
	int choice;
	std::cout << "출력(1)/삭제(0) : ";
	std::cin >> choice;
	IO::item_IO_data[User::img_type - 1].first = choice;
}




