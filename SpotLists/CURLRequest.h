#pragma once
#ifndef CURLREQUEST_H
#define CURLREQUEST_H
#include "IHTTPRequest.h"
#include <cpr/cpr.h>
#include <string>
#include <utility>

class CURLRequest : public IHTTPRequest {
	std::vector<std::pair<std::string, std::string>> parameters;
	std::string header_name;
	std::string header_value;
	std::string payload_name;
	std::string payload_value;
	std::string url;
	std::string bearer_token;
	bool enable_ssl;
	
public:
	void setHeader(std::string key, std::string value) override;
	void addParameter(std::string key, std::string value) override;
	void setPayload(std::string key, std::string value) override;
	void setUrl(std::string url) override;
	void setBearerToken(std::string token) override;

	std::pair<std::string, std::string> getHeader() override;
	std::vector<std::pair<std::string, std::string>> getParameters() override;
	std::pair<std::string, std::string> getPayload() override;
	std::string getUrl() override;

	void enableHTTPS(bool is_enabled) override;
	inline bool httpsEnabled() override { return enable_ssl; }

	void clearParameters() override;
};
#endif