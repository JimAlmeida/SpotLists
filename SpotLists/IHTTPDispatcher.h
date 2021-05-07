#pragma once
#include <variant>
#include <cpr/cpr.h>
#include <QtNetwork/qnetworkreply.h>
#include "NetworkReply.h"
#include "IHTTPRequest.h"

class IHTTPDispatcher {
public:
	virtual NetworkReply get(IHTTPRequest* r) = 0;
	virtual NetworkReply post(IHTTPRequest* r) = 0;
};


