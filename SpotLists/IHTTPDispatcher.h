#pragma once
#ifndef IHTTPDISPATCHER_H
#define IHTTPDISPATCHER_H
#include <variant>
#include <cpr/cpr.h>
#include "NetworkReply.h"
#include "IHTTPRequest.h"

class IHTTPDispatcher {
public:
	virtual NetworkReply get(IHTTPRequest* r) = 0;
	virtual NetworkReply post(IHTTPRequest* r) = 0;
};
#endif


