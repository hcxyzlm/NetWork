#ifndef _MSG_HEAD_H
#define _MSG_HEAD_H

#include <iostream>
using namespace std;

#ifdef _WIN32
#include "WinSock.h"
#pragma   comment(lib, "WS2_32.lib")
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include "errno.h"
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <arpa/inet.h>
#endif


const int MSG_HEAD_LEN = 16;   //协议头的长度


#pragma pack(1)

enum MsgOption
{
	OPTION_STRING = 1,  //字符串
	OPTION_PROTO = 2   //protobuf对象
};

enum MsgTYPE
{
	MSG_UP = 1,  //上行
	MSG_DOWN = 2,  //下行
	MSG_ERROR = 3,   //错误信息
};

class  MsgHead 
{
public:
	int msgLen;   //接收为协议整体长度， 发送为协议body长度
	char msgType;
	char option;
	short reserve;
	int cmdID;
	int reqID;

	bool decodeHead(const char* data);
	bool encodeHead(char *buffer);
};

#pragma pack()


#endif