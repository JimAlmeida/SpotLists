#pragma once

#ifndef HTTPREQUESTFACTORY_H
#define HTTPREQUESTFACTORY_H
#include "IHTTPRequest.h"
#include "CURLRequest.h"


//Why this factory method? Although now it only returns an instance of the CURLRequest class, when in a typical factory there's at least some choices as to what instance to return, 
//this design anticipates future extensions, say performing network requests with the QT framework classes instead of the CPR library.

class HTTPRequestFactory {
public:
	static IHTTPRequest* createInstance() {
		return new CURLRequest();
	}
};
#endif