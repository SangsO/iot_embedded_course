#pragma once

#include <fstream>
#include <stdlib.h>
#include <WinSock2.h>
#include <string>
#include <thread>


class IMG_com {
private :

	const int portnum = 5555;

	std::ofstream myfile;
	char path[2][1000];

	WSADATA wsaData;
	SOCKET hServSock, hClntSock;
	SOCKADDR_IN servAddr, clntAddr;

	int szclntaddr;


	

public :
	IMG_com();
	~IMG_com();

	void SOCK_setting();

	void SOCK_conn();

	void SOCK_recv_mode();

	void base64d(char *, char *, int *);

	std::thread recv_th();
};