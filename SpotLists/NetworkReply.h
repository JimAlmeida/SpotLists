#pragma once
#ifndef NETWORKREPLY_H
#define NETWORKREPLY_H
#include <string>

struct NetworkReply {
	std::string content;
	std::string status_code;
	std::string header;
};
#endif