#include "ImageLoader.h"

QPixmap ImageLoader::loadImageFromURL(std::string url, const int height) {
    QPixmap p;
    if (!url.empty()) {
        IHTTPRequest* get_request = HTTPRequestFactory::createInstance();
        IHTTPDispatcher* dispatcher = HTTPDispatcherFactory::createInstance();
        bool has_loaded;
        get_request->setUrl(url);
        get_request->enableHTTPS(true);

        NetworkReply response = dispatcher->get(get_request);

        QByteArray dx = QByteArray::fromStdString(response.content);
        has_loaded = p.loadFromData(dx);
        //This operation is synchronous, meaning the memory allocated for these objects will not be freed until after they have completed their purpose.
        //In other words, I will not be deleting these objects half-way through an operation.
        delete get_request;
        delete dispatcher;
    }
    
    return p.scaledToHeight(height, Qt::TransformationMode::SmoothTransformation);
}