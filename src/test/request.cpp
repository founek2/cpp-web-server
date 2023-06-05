//
// Created by Martin Skalický on 2019-05-22.
//

#include "request.h"
#include "../network/Request.h"

namespace requestTest {
    void testParsing() {
        Request req("GET / HTTP/1.1\r\n"
                    "Host: localhost:8081\r\n"
                    "Connection: keep-alive\r\n"
                    "Cache-Control: max-age=0\r\n"
                    "Upgrade-Insecure-Requests: 1\r\n"
                    "User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_14_4) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/71.0.3578.98 Safari/537.36 OPR/58.0.3135.132\r\n"
                    "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8\r\n"
                    "Accept-Encoding: gzip, deflate, br\r\n"
                    "Accept-Language: cs-CZ,cs;q=0.9\r\n\r\n", 456);

        try {
            Request req("GET / HTTP/15\r\n"
                        "Host: localhost:8081\r\n"
                        "Connection: keep-alive\r\n"
                        "Cache-Control: max-age=0\r\n"
                        "Upgrade-Insecure-Requests: 1\r\n"
                        "User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_14_4) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/71.0.3578.98 Safari/537.36 OPR/58.0.3135.132\r\n"
                        "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8\r\n"
                        "Accept-Encoding: gzip, deflate, br\r\n"
                        "Accept-Language: cs-CZ,cs;q=0.9\r\n\r\n"
                        "", 456);
        } catch (UnsupportedHttpVersion) {};

        try {
            Request req("POST / HTTP/1.1\r\n"
                        "Host: localhost:8081\r\n"
                        "Connection: keep-alive\r\n"
                        "Cache-Control: max-age=0\r\n"
                        "Upgrade-Insecure-Requests: 1\r\n"
                        "User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_14_4) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/71.0.3578.98 Safari/537.36 OPR/58.0.3135.132\r\n"
                        "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8\r\n"
                        "Accept-Encoding: gzip, deflate, br\r\n"
                        "Accept-Language: cs-CZ,cs;q=0.9\r\n\r\n"
                        "", 456);
        } catch (UnsupportedMethod) {};

        try {
            Request req("GET / HTTP/1.1\r\n"
                        "Host: localhost:8081\r\n"
                        "Connection keep-alive\r\n" // missing ':'
                        "Cache-Control: max-age=0\r\n"
                        "Upgrade-Insecure-Requests: 1\r\n"
                        "User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_14_4) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/71.0.3578.98 Safari/537.36 OPR/58.0.3135.132\r\n"
                        "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8\r\n"
                        "Accept-Encoding: gzip, deflate, br\r\n"
                        "Accept-Language: cs-CZ,cs;q=0.9\r\n\r\n"
                        "", 455);
        } catch (InvalidHeader) {};
    }
}


