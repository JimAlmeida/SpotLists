#pragma once
#ifndef CURLDISPATCHER_H
#define CURLDISPATCHER_H
#include "IHTTPDispatcher.h"
#include "IHTTPRequest.h"
#include "CURLRequest.h"

#include <utility>
#include <cpr/cpr.h>
#include <string>


class CURLDispatcher : public IHTTPDispatcher {
public:
	NetworkReply post(IHTTPRequest* r) override;
	NetworkReply get(IHTTPRequest* r) override;
};
#endif
