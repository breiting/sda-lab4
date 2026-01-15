/*
Pattern: Builder (Gamma et al.)
-------------------------------
Intent:
    Separate the construction of a complex object from its representation,
    so the same construction process can create different representations.

Use case (example):
    Building an HTTP request with many optional parts (headers, body, timeout,
etc.).
*/

#include <iostream>
#include <map>
#include <optional>
#include <string>
#include <utility>

namespace patterns {

struct HttpRequest {
    std::string Method;
    std::string Url;
    std::map<std::string, std::string> Headers;
    std::optional<std::string> Body;
    int TimeoutMs{1000};
};

class HttpRequestBuilder {
   public:
    explicit HttpRequestBuilder(std::string url) {
        m_Request.Url = std::move(url);
    }

    HttpRequestBuilder &WithMethod(std::string method) {
        m_Request.Method = std::move(method);
        return *this;
    }

    HttpRequestBuilder &AddHeader(std::string key, std::string value) {
        m_Request.Headers.emplace(std::move(key), std::move(value));
        return *this;
    }

    HttpRequestBuilder &WithBody(std::string body) {
        m_Request.Body = std::move(body);
        return *this;
    }

    HttpRequestBuilder &WithTimeoutMs(int timeoutMs) {
        m_Request.TimeoutMs = timeoutMs;
        return *this;
    }

    HttpRequest Build() const {
        HttpRequest out = m_Request;
        if (out.Method.empty()) {
            out.Method = "GET";
        }
        return out;
    }

   private:
    HttpRequest m_Request;
};

static void Print(const HttpRequest &r) {
    std::cout << r.Method << " " << r.Url << "\n";
    std::cout << "Timeout: " << r.TimeoutMs << "ms\n";
    for (const auto &[k, v] : r.Headers) {
        std::cout << "Header: " << k << ": " << v << "\n";
    }
    if (r.Body.has_value()) {
        std::cout << "Body: " << r.Body.value() << "\n";
    }
}

}  // namespace patterns

int main() {
    using namespace patterns;

    HttpRequest req = HttpRequestBuilder("https://example.com/api/items")
                          .WithMethod("POST")
                          .AddHeader("Content-Type", "application/json")
                          .WithBody(R"({"name":"SDA"})")
                          .WithTimeoutMs(2500)
                          .Build();

    Print(req);
}
