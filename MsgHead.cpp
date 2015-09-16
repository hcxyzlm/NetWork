#include "MsgHead.h"

bool MsgHead::encodeHead(char *buffer)
{
	if (!buffer)
	{
		return false;
	}

	int offset = 0;
	msgLen = htonl(msgLen);
	memcpy(&buffer[offset], &msgLen, sizeof(msgLen));
	offset += sizeof(msgLen);

	memcpy(&buffer[offset], &msgType, sizeof(msgType));
	offset += sizeof(msgType);

	memcpy(&buffer[offset], &option, sizeof(option));
	offset += sizeof(option);

	memcpy(&buffer[offset], &reserve, sizeof(reserve));
	offset += sizeof(reserve);

	cmdID = htonl(cmdID);
	memcpy(&buffer[offset], &cmdID, sizeof(cmdID));
	offset += sizeof(cmdID);

	reqID = htonl(reqID);
	memcpy(&buffer[offset], &reqID, sizeof(reqID));
	offset += sizeof(reqID);
	return true;
}


bool MsgHead::decodeHead(const char *data)
{
	if (!data)
	{
		return false;
	}

	int offset = 0;
	msgLen = *((int*)&data[offset]);
	msgLen = ntohl(msgLen);
	offset += sizeof(msgLen);

	msgType = *((char*)&data[offset]);
	offset += sizeof(msgType);

	option = *((char*)&data[offset]);
	offset += sizeof(option);

	reserve = *((short*)&data[offset]);
	offset += sizeof(reserve);

	cmdID = *((int*)&data[offset]);
	cmdID = ntohl(cmdID);
	offset += sizeof(cmdID);

	reqID = *((int*)&data[offset]);
	reqID = ntohl(reqID);
	offset += sizeof(reqID);

	return true;
}