#include "CURLDispatcher.h"

NetworkReply CURLDispatcher::post(IHTTPRequest* r) {
	CURLRequest* nr = dynamic_cast<CURLRequest*>(r);

	if (nr != nullptr) {
		cpr::Session session;
		session.SetHeader(cpr::Header{ r->getHeader() });
		session.SetUrl(cpr::Url{ r->getUrl() });
		session.SetVerifySsl(cpr::VerifySsl{ r->httpsEnabled() });
		session.SetPayload(cpr::Payload{ {r->getPayload().first, r->getPayload().second} });

		cpr::Response resp = session.Post();

		NetworkReply reply;
		reply.content = resp.text;
		reply.status_code = resp.status_code;
		reply.header = resp.raw_header;

		return reply;
	}
	else {
		throw std::invalid_argument("You need to pass a base pointer to the derived CURLRequest object");
	}
}

NetworkReply CURLDispatcher::get(IHTTPRequest* r) {
	CURLRequest* nr = dynamic_cast<CURLRequest*>(r);

	if (nr != nullptr) {

		cpr::Session session;

		session.SetUrl(cpr::Url{ r->getUrl() });
		session.SetVerifySsl(cpr::VerifySsl{ r->httpsEnabled() });

		std::string header_name = r->getHeader().first;
		std::string header_value = r->getHeader().second;

		bool check1 = header_name.empty();


		if (!header_name.empty() && !header_value.empty()) {
			session.SetHeader(cpr::Header{ {header_name, header_value} });
		}

		auto _parameters = r->getParameters();
		if (_parameters.size() > 0) {
			cpr::Parameters p = cpr::Parameters();
			auto holder = cpr::CurlHolder();

			for (auto& _p : _parameters) {
				p.AddParameter(cpr::Parameter(std::move(_p.first), std::move(_p.second)), holder);
			}

			session.SetParameters(p);
		}

		cpr::Response resp = session.Get();
		
		NetworkReply reply;
		reply.content = resp.text;
		reply.status_code = resp.status_code;
		reply.header = resp.raw_header;

		return reply;
	}
	else {
		throw std::invalid_argument("You need to pass a base pointer to the derived CURLRequest object");
	}
}

