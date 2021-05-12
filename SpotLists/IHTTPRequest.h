#pragma once
#ifndef IHTTPREQUEST_H
#define IHTTPREQUEST_H
#include <utility>
#include "NetworkReply.h"
#include <string>
#include <vector>


//Usually I could've used templates (like below) in order to have more flexibility between Std::String and QString but its use would feel unnatural
//and I can't say for certain how it would impact the code or its compilation (e.g. when calling the constructor: IHTTPRequest<> - C++11 vs. IHTTPRequest - C++17)
//Thus, I chose to use the STL library over the Qt framework whenever I can, giving it a place of preference over Qt.
//Plus, it would just complicate the code over something simple.
//The same consideration goes for the IHTTPDispatcher class.

/*template<typename S = std::string>
class IHTTPRequest {
	public:
		virtual void setHeader(S key, S value) = 0;
		virtual void addParameter(S key, S value) = 0;
		virtual void setPayload(S key, S value) = 0;
		virtual void setUrl(S url) = 0;
		virtual void setBearerToken(S token) = 0;

		virtual std::pair<S, S> getHeader() = 0;
		virtual std::vector<std::pair<S, S>> getParameters() = 0;
		virtual std::pair<S, S> getPayload() = 0;
		virtual S getUrl() = 0;

		virtual bool httpsEnabled() = 0;
		virtual void enableHTTPS(bool is_enabled) = 0;

		virtual void clearParameters() = 0;
};*/

class IHTTPRequest {
public:
	virtual void setHeader(std::string key, std::string value) = 0;
	virtual void addParameter(std::string key, std::string value) = 0;
	virtual void setPayload(std::string key, std::string value) = 0;
	virtual void setUrl(std::string url) = 0;
	virtual void setBearerToken(std::string token) = 0;

	virtual std::pair<std::string, std::string> getHeader() = 0;
	virtual std::vector<std::pair<std::string, std::string>> getParameters() = 0;
	virtual std::pair<std::string, std::string> getPayload() = 0;
	virtual std::string getUrl() = 0;

	virtual bool httpsEnabled() = 0;
	virtual void enableHTTPS(bool is_enabled) = 0;

	virtual void clearParameters() = 0;
};
#endif