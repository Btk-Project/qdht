#include "session.hpp"

#include <cstdio>

#include "private/log.hpp"

#define USER_AGENT "qdht/v1.0.0"

auto QBErrorCategory::instance() -> const QBErrorCategory& {
    static QBErrorCategory instance;
    return instance;
}

auto QBErrorCategory::message(uint32_t value) const -> std::string {
    switch (value) {
        case QBittorrentSession::Error::NoError:
            return "No error";
        case QBittorrentSession::Error::ERROR403:
            return "Forbidden";
        case QBittorrentSession::Error::NoPermissions:
            return "No permissions";
        case QBittorrentSession::Error::UnknownError:
            return "Unknown error";
        case QBittorrentSession::Error::Timeout:
            return "Timeout";
        case QBittorrentSession::Error::UnknownMethod:
            return "Unknown method";
        default:
            break;
    }
    return "Unknown error";
}

auto QBErrorCategory::name() const -> std::string_view { return "QBittorrent"; }
auto QBErrorCategory::equivalent(uint32_t self, const ILIAS_NAMESPACE::Error& other) const -> bool {
    return other.category().name() == name() && self == static_cast<uint32_t>(other.value());
}

QBittorrentSession::QBittorrentSession(Ilias::IoContext& ioContext) : mIoCtxt(&ioContext), mHttpSession(ioContext) {
    mHttpSession.setCookieJar(&mCookies);
}

QBittorrentSession::QBittorrentSession() : mIoCtxt(Ilias::IoContext::instance()), mHttpSession(*mIoCtxt) {
    mHttpSession.setCookieJar(&mCookies);
}

auto QBittorrentSession::login(const LoginParameters& loginInfo) -> QBittorrentSession::Error {
    auto ret = ilias_wait request(QB_LOGIN, LoginParameters::makeProto(loginInfo).toData());
    if (!ret) {
        return UnknownError;
    }
    auto allCookies = mCookies.allCookies();
    for (auto& cookie : allCookies) NEKO_LOG_INFO("cookie: {}:{}", cookie.name(), cookie.value());
    auto it = std::find_if(allCookies.begin(), allCookies.end(),
                           [this](const Ilias::HttpCookie& cookie) { return cookie.name() == "SID"; });
    if (it == allCookies.end()) {
        NEKO_LOG_ERROR("login failed: no sid cookie");
        return UnknownError;
    }
    mToken = it->value();

    return NoError;
}

auto QBittorrentSession::logout() -> QBittorrentSession::Error {
    auto ret = ilias_wait request(QB_LOGOUT);
    if (!ret) {
        return UnknownError;
    }
    return NoError;
}

void QBittorrentSession::setHost(std::string host) { mHost = host; }

void QBittorrentSession::setPort(int port) { mPort = port; }

void QBittorrentSession::setTimeout(int timeout) { mTimeout = timeout; }

auto QBittorrentSession::token() const -> std::string { return mToken; }

auto QBittorrentSession::request(std::string_view path, const std::vector<char>& data) -> Ilias::Task<std::string> {
    Ilias::HttpRequest request(makeRequestUrl(path).c_str());
    request.setOperation(Ilias::HttpRequest::Operation::POST);
    request.setHeader(Ilias::HttpRequest::Referer, mHost);
    request.setHeader(Ilias::HttpRequest::ContentType, "application/x-www-form-urlencoded");
    request.setHeader(Ilias::HttpRequest::Accept, "*/*");
    request.setHeader(Ilias::HttpRequest::UserAgent, USER_AGENT);
    auto ret = co_await mHttpSession.post(
        request, data.size() > 0 ? std::string_view{data.data(), data.size()} : std::string_view());
    if (!ret) {
        NEKO_LOG_ERROR("request {} failed: {}", path, ret.error().message());
        co_return ILIAS_NAMESPACE::Unexpected(ret.error());
    } else if (ret.value().statusCode() == 403) {
        NEKO_LOG_ERROR("request {} failed: {}", path, (ilias_wait ret.value().text()).value());
        co_return Ilias::Unexpected(Error::ERROR403);
    } else if (ret.value().statusCode() != 200) {
        NEKO_LOG_ERROR("request {} failed: {}", path, (ilias_wait ret.value().text()).value());
        co_return Ilias::Unexpected(Error::UnknownError);
    }
    auto ret1 = co_await ret.value().text();
    if (!ret1) {
        NEKO_LOG_ERROR("request {} failed: {}", path, ret1.error().message());
        co_return ILIAS_NAMESPACE::Unexpected(ret1.error());
    }
    co_return ret1.value();
}

auto QBittorrentSession::makeRequestUrl(std::string_view path) const -> std::string {
    return mHost + ":" + std::to_string(mPort) + std::string(path);
}
