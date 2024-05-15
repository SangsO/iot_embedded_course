#pragma comment(lib, "ws2_32.lib")

#include "IMG_com.h"
#include <string>
#include <iostream>

////////////////////////////////////////////////////////////////////////////
static const char MimeBase64[] = {
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
	'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
	'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
	'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
	'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
	'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
	'w', 'x', 'y', 'z', '0', '1', '2', '3',
	'4', '5', '6', '7', '8', '9', '+', '/'
};

static int DecodeMimeBase64[256] = {
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,62,-1,-1,-1,63,
	52,53,54,55,56,57,58,59,60,61,-1,-1,-1,-1,-1,-1,
	-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,
	15,16,17,18,19,20,21,22,23,24,25,-1,-1,-1,-1,-1,
	-1,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,
	41,42,43,44,45,46,47,48,49,50,51,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
};

typedef union {
	struct {
		unsigned char c1, c2, c3;
	};
	struct {
		unsigned int e1 : 6, e2 : 6, e3 : 6, e4 : 6;
	};
} BF;
///////////////////////////////////////////////////////////////////////////

IMG_com::IMG_com()
{
//	strcpy(path[0], "c:\\down\\glass\\");
//	strcpy(path[1], "c:\\down\\lip\\");

	strcpy(path[0], "c:\\test_projects\\lineDetection\\lineDetection\\new_image\\glasses\\");
	strcpy(path[1], "c:\\test_projects\\lineDetection\\lineDetection\\new_image\\lips\\");

	SOCK_setting();
	
}

IMG_com::~IMG_com() {}

void IMG_com::base64d(char *src, char *result, int *length) {
	int i, j = 0, src_length, blank = 0;
	BF temp;

	src_length = strlen(src);

	for (i = 0; i < src_length; i = i + 4, j = j + 3) {
		temp.e4 = DecodeMimeBase64[src[i]];
		temp.e3 = DecodeMimeBase64[src[i + 1]];
		if (src[i + 2] == '=') {
			temp.e2 = 0;
			blank++;
		}
		else temp.e2 = DecodeMimeBase64[src[i + 2]];
		if (src[i + 3] == '=') {
			temp.e1 = 0;
			blank++;
		}
		else temp.e1 = DecodeMimeBase64[src[i + 3]];

		result[j] = temp.c3;
		result[j + 1] = temp.c2;
		result[j + 2] = temp.c1;
	}
	*length = j - blank;
}

void IMG_com::SOCK_setting() {

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		std::cout << "SOCK_setting error" << std::endl;
		return;
	}

	hServSock = socket(PF_INET, SOCK_STREAM, 0);
	if (hServSock == INVALID_SOCKET) {
		std::cout << "SOCK_setting error" << std::endl;
		return;
	}

	memset(&servAddr, 0, sizeof(servAddr));

	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(portnum);

	if (bind(hServSock, (SOCKADDR*)& servAddr, sizeof(servAddr)) == SOCKET_ERROR) {
		std::cout << "SOCK_setting error" << std::endl;
		return;
	}

	if (listen(hServSock, 5) == SOCKET_ERROR) {
		std::cout << "SOCK_setting error" << std::endl;
		return;
	}
}

void IMG_com::SOCK_conn() {

	int szClntAddr;

	szClntAddr = sizeof(clntAddr);
	hClntSock = accept(hServSock, (SOCKADDR*)&clntAddr, &szClntAddr);

	if (hClntSock == INVALID_SOCKET) {
		std::cout << "[[ 안드로이드와 TCP 통신 연결 실패.. ]]" << std::endl;
		return;
	}

	std::cout << "[[ 안드로이드와 TCP 통신 연결 되었습니다. ]]" << std::endl;

	while(1)
		SOCK_recv_mode();

}

void IMG_com::SOCK_recv_mode() {
	int Str_len;
	char Data_info[100];
	int Item_num, File_size;
	int start = 0;
	char alarm[3] = "1\n";

	for (int i = 0; i < 3; i++) {
		Str_len = recv(hClntSock, Data_info, sizeof(Data_info), 0);
		if (Data_info[Str_len - 1] == '\n')
			Data_info[Str_len - 1] = 0;
		else
			Data_info[Str_len] = 0;

		switch (i)
		{
		case 0 :
			Item_num = std::stoi(Data_info);
			send(hClntSock, alarm, 2, 0);
			break;
		case 1 :
			strcat(path[Item_num - 1], Data_info);
			myfile.open(path[Item_num - 1], std::ios::in | std::ios::binary | std::ios::app);
			send(hClntSock, alarm, 2, 0);
			break;
		case 2 :
			File_size = std::stoi(Data_info);
			break;
		}

	}
	std::cout << path[Item_num - 1] << " 파일 받는 중.." << "( 크기 : "<< File_size << " )"<<std::endl;

	File_size++;

	int File_size_cp = File_size;
	char *gdata = new char[File_size];
	char *gdata_cp = new char[File_size];
	char *result_data = new char[File_size];
	char *gdata_filter = new char[File_size];

	send(hClntSock, alarm, 2, 0);

	while (true) {

		Str_len = recv(hClntSock, gdata, File_size - 1, 0);
		for (int i = 0; i < Str_len; i++)
			gdata_cp[start + i] = gdata[i];

		start += Str_len;

		File_size_cp -= Str_len;

		if (File_size_cp == 0)
			break;
	}

	gdata_cp[File_size-1] = 0;

	int size = 0;
	for (int i = 0; gdata_cp[i] != 0; i++) {
		if (gdata_cp[i] != 0x0a) {
			gdata_filter[size] = gdata_cp[i];
			size++;
		}
	}

	gdata_filter[size + 1] = 0;

	base64d(gdata_filter, result_data, &size);

	for (int i = 0; i <= size; i++)
		myfile << (unsigned char)result_data[i];

	myfile.close();
	std::cout << "이미지 다운 완료 !" << std::endl;


	delete gdata;
	delete gdata_cp;
	delete result_data;
	delete gdata_filter;

}

std::thread IMG_com::recv_th() {
	return std::thread(&IMG_com::SOCK_conn, this);
}