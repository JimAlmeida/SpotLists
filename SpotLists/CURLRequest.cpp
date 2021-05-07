#include  "CURLRequest.h"

void CURLRequest::setHeader(std::string key, std::string value) {
	header_name = key;
	header_value = value;
}
void CURLRequest::setPayload(std::string key, std::string value) {
	payload_name = key;
	payload_value = value;
}
void CURLRequest::addParameter(std::string key, std::string value) {
	parameters.emplace_back(key, value);
}
void CURLRequest::setUrl(std::string _url) {
	url = _url;
}
void CURLRequest::enableHTTPS(bool is_enabled = true) {
	enable_ssl = is_enabled;
}
void CURLRequest::setBearerToken(std::string token) {
	bearer_token = token;
}

std::pair<std::string, std::string> CURLRequest::getHeader() {
	return std::make_pair(header_name, header_value);
}
std::vector<std::pair<std::string, std::string>> CURLRequest::getParameters() {
	return parameters;
}
std::pair<std::string, std::string> CURLRequest::getPayload() {
	return {payload_name, payload_value};
}
std::string CURLRequest::getUrl() {
	return url;
}

void CURLRequest::clearParameters() {
	parameters.clear();
}