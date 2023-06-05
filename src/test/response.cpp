//
// Created by Martin Skalický on 2019-05-22.
//

#include "response.h"
#include "../network/Response.h"

namespace responseTest{
    void testParsing(){
        Response res;
        res.body << "<html><head></head><body><h2>Juhuu</h2></body></html>";
        res.setContentType("text/html; charset=UTF-8");

        assert(res.str() == "HTTP/1.1 200 OK\r\n"
                            "Content-Type: text/html; charset=UTF-8\r\n"
                            "Content-Length: 53\r\n\r\n"
                            "<html><head></head><body><h2>Juhuu</h2></body></html>");

        res.setStatusCode(404);
        assert(res.str() == "HTTP/1.1 404 Not Found\r\n");

        Response res2;
        res2.setContentType("text/plain");
        res2.body << "Jeeeeej it's a funny way of trolling";
        assert(res2.str() == "HTTP/1.1 200 OK\r\n"
                            "Content-Type: text/plain\r\n"
                            "Content-Length: 36\r\n\r\n"
                            "Jeeeeej it's a funny way of trolling");
    }
}