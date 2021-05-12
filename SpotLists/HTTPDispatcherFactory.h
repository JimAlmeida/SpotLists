#pragma once
#ifndef HTTPDISPATCHERFACTORY_H
#define HTTPDISPATCHERFACTORY_H
#include "IHTTPDispatcher.h"
#include "CURLDispatcher.h"


//Why this factory method? Although now it only returns an instance of the CURLDispatcher class, when in a typical factory there's at least some choices as to what instance to return, 
//this design anticipates future extensions, say performing network requests with the QT framework classes instead of the CPR library.

class HTTPDispatcherFactory {
public:
	static IHTTPDispatcher* createInstance() {
		return new CURLDispatcher();
	}
};
#endif