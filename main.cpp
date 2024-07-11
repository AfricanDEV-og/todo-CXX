#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPRequestHandler.h"

#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPServerParams.h"

#include "Poco/Util/ServerApplication.h"

#include "Poco/Data/MySQL/Connector.h"

#include "Appstate.h"
#include "homeHandler.h"
#include "homeService.h"
#include "notfoundHandler.h"

#include "actionArranger.h"

#include <regex>

class HTTPFactory : public HTTPRequestHandlerFactory {
public:
	HTTPFactory(Appstate state) : globalstate(state) {}

	HTTPRequestHandler* createRequestHandler(const HTTPServerRequest& request) {
		std::string expr = "(\\/api\\/task)+";
		std::string uri = request.getURI();

		std::cout << uri << std::endl;
		if (std::regex_search(uri, std::regex(expr))) {
			std::cout << "entered arranger\n";
			return actionArranger(request, globalstate);
		}
		else if (uri == "/") {
			homeService service(globalstate);
			return new homeHandler(service);
		}
		else {
			return new notfoundHandler();
		}
		
	}
private:
	Appstate globalstate;
};

class MainApplication : public Poco::Util::ServerApplication {
public:
	MainApplication() {
		main();
	}

	int main() {

		Poco::Data::MySQL::Connector::registerConnector();

		Poco::Data::Session session("MySQL", "host=localhost;port=3306;db=tasks;user=root;password=djsebbe1012;compress=true;auto-reconnect=true");
		Appstate state = { session };
		
		int port = 1334;
		ServerSocket socket(port);
		HTTPServerParams* pparams = new HTTPServerParams;

		pparams->setMaxThreads(1000);
		pparams->setMaxQueued(1000);

		HTTPServer svs(new HTTPFactory(state), socket, pparams);

		svs.start();
		
		waitForTerminationRequest();

		svs.stop();

		return 0;
	}
};

POCO_SERVER_MAIN(MainApplication);
