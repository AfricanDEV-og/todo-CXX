#pragma once

#include "actionShared.h"

#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"

#include "Poco/JSON/Parser.h"
#include "Poco/JSON/Object.h"
#include "Poco/Dynamic/Var.h"

using namespace Poco::Net;

class deleteHandler : public HTTPRequestHandler {
public:
	deleteHandler(actionShared service);

	void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response);
private:
	actionShared internalservice;
};

