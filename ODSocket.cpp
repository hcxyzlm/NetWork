#include "ODSocket.h"
#include <stdio.h>
#ifdef WIN32
	#pragma comment(lib, "wsock32")
#endif


ODSocket::ODSocket(SOCKET sock)
{
	m_sock = sock;
}

ODSocket::~ODSocket()
{
}

int ODSocket::Init()
{
#ifdef WIN32
	/*
	http://msdn.microsoft.com/zh-cn/vstudio/ms741563(en-us,VS.85).aspx

	typedef struct WSAData { 
		WORD wVersion;								//winsock version
		WORD wHighVersion;							//The highest version of the Windows Sockets specification that the Ws2_32.dll can support
		char szDescription[WSADESCRIPTION_LEN+1]; 
		char szSystemStatus[WSASYSSTATUS_LEN+1]; 
		unsigned short iMaxSockets; 
		unsigned short iMaxUdpDg; 
		char FAR * lpVendorInfo; 
	}WSADATA, *LPWSADATA; 
	*/
	WSADATA wsaData;
	//#define MAKEWORD(a,b) ((WORD) (((BYTE) (a)) | ((WORD) ((BYTE) (b))) << 8)) 
	WORD version = MAKEWORD(2, 0);
	int ret = WSAStartup(version, &wsaData);//win sock start up
	if ( ret )
	{
		return -1;
	}
#endif
	
	return 0;
}
//this is just for windows
int ODSocket::Clean()
{
#ifdef WIN32
		return (WSACleanup());
#endif
		return 0;
}

ODSocket& ODSocket::operator = (SOCKET s)
{
	m_sock = s;
	return (*this);
}

ODSocket::operator SOCKET ()
{
	return m_sock;
}
//create a socket object win/lin is the same
// af:
bool ODSocket::Create(int af, int type, int protocol)
{
	m_sock = socket(af, type, protocol);
	if ( m_sock == INVALID_SOCKET ) {
		return false;
	}
	return true;
}

/*
1．建立socket
2．将该socket设置为非阻塞模式
3．调用connect()
4．使用select()检查该socket描述符是否可写（注意，是可写）
5．根据select()返回的结果判断connect()结果
6．将socket设置为阻塞模式（如果你的程序不需要用阻塞模式的，这步就省了，不过一般情况下都是用阻塞模式的，这样也容易管理）
*/
bool ODSocket::Connect(const char* ip, unsigned short port, int timeOut)
{
	struct sockaddr_in svraddr;
	struct hostent *pHost;
	svraddr.sin_family = AF_INET;
	svraddr.sin_addr.s_addr = inet_addr(ip);
	svraddr.sin_port = htons(port);

	if(svraddr.sin_addr.s_addr == INADDR_NONE)
	{
		//如果输入的是域名
		pHost = (struct hostent*)gethostbyname(ip);
		if(pHost==NULL)
		{
			printf("Init socket s_addr error!");
			return false;
		}
		svraddr.sin_addr.s_addr =((struct in_addr*)pHost->h_addr)->s_addr;
	}

	unsigned long ul = 1;

#ifdef _WIN32
	ioctlsocket(m_sock, FIONBIO, &ul); //设置为非阻塞模式
#else
	ioctl(m_sock, FIONBIO, &ul);  //设置为非阻塞模式
#endif

	int error = -1;
	int len = sizeof(int);
	timeval tm;
	fd_set set;
	bool ret = false;
	if(connect(m_sock, (struct sockaddr *)&svraddr, sizeof(svraddr)) == -1)
	{

#ifdef _WIN32

#else
		if (errno != EINPROGRESS)
		{
			return false;
		}
#endif
		tm.tv_sec  = timeOut;
		tm.tv_usec = 0;
		FD_ZERO(&set);
		FD_SET(m_sock, &set);
		if( select(m_sock+1, NULL, &set, NULL, &tm) > 0)
		{
			getsockopt(m_sock, SOL_SOCKET, SO_ERROR, (char *)&error, (socklen_t *)&len);
			if(error == 0) 
				ret = true;
			else 
				ret = false;
		} 
		else 
			ret = false;
	}
	else 
		ret = true;
	ul = 0;
#ifdef _WIN32 
	//ioctlsocket(m_sock, FIONBIO, &ul); //设置为阻塞模式
#else
	//ioctl(m_sock, FIONBIO, &ul);  //设置为阻塞模式
#endif
	return ret;
}

bool ODSocket::Bind(unsigned short port)
{
	struct sockaddr_in svraddr;
	svraddr.sin_family = AF_INET;
	svraddr.sin_addr.s_addr = INADDR_ANY;
	svraddr.sin_port = htons(port);

	int opt =  1;
	if ( setsockopt(m_sock, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt)) < 0 ) 
		return false;

	int ret = bind(m_sock, (struct sockaddr*)&svraddr, sizeof(svraddr));
	if ( ret == SOCKET_ERROR ) {
		return false;
	}
	return true;
}
//for server
bool ODSocket::Listen(int backlog)
{
	int ret = listen(m_sock, backlog);
	if ( ret == SOCKET_ERROR ) {
		return false;
	}
	return true;
}

bool ODSocket::Accept(ODSocket& s, char* fromip)
{
	struct sockaddr_in cliaddr;
	socklen_t addrlen = sizeof(cliaddr);
	SOCKET sock = accept(m_sock, (struct sockaddr*)&cliaddr, &addrlen);
	if ( sock == SOCKET_ERROR ) {
		return false;
	}

	s = sock;
	if ( fromip != NULL )
		sprintf(fromip, "%s", inet_ntoa(cliaddr.sin_addr));

	return true;
}

int ODSocket::Send(const char* buf, int len, int flags)
{
	if (m_sock < 0)
	{
		return 0;
	}

	int bytes;
	int count = 0;

	while ( count < len ) {

		bytes = send(m_sock, buf + count, len - count, flags);
		if ( bytes == -1 || bytes == 0 )
			return -1;
		count += bytes;
	} 

	return count;
}

int ODSocket::Recv(char* buf, int len, int flags)
{
	if (m_sock < 0)
	{
		return 0;
	}

    fd_set read;
    timeval tm;
    FD_ZERO(&read);
    FD_SET(m_sock, &read);
    tm.tv_sec=0;
    tm.tv_usec=0;
    select(m_sock+1, &read, NULL, NULL, &tm);
	if(FD_ISSET(m_sock,&read))  
	{
		int ret = recv(m_sock, buf, len, flags);
		if (ret<=0)
		{
			return -1;
		}
		return ret;
	}
    return 0;
}

int ODSocket::Close()
{
	m_sock = -1;
#ifdef WIN32
	return (closesocket(m_sock));
#else
	return (close(m_sock));
#endif
}

int ODSocket::GetError()
{
#ifdef WIN32
	return (WSAGetLastError());
#else
	return (errno);
#endif
}

bool ODSocket::DnsParse(const char* domain, char* ip)
{
	struct hostent* p;
	if ( (p = gethostbyname(domain)) == NULL )
		return false;
		
	sprintf(ip, 
		"%u.%u.%u.%u",
		(unsigned char)p->h_addr_list[0][0], 
		(unsigned char)p->h_addr_list[0][1], 
		(unsigned char)p->h_addr_list[0][2], 
		(unsigned char)p->h_addr_list[0][3]);
	
	return true;
}
