#pragma once
#include <string>
#include <string_view>

#include "ilias.hpp"
#include "ilias_async.hpp"
#include "ilias_http.hpp"
#include "private/qbittorrent_api_defines.hpp"

class QBErrorCategory : public ILIAS_NAMESPACE::ErrorCategory {
public:
    static auto instance() -> const QBErrorCategory&;
    auto message(uint32_t value) const -> std::string override;
    auto name() const -> std::string_view override;
    auto equivalent(uint32_t self, const ILIAS_NAMESPACE::Error& other) const
        -> bool override;
};

class QBittorrentSession {
public:
    enum Error {
        NoError,
        ERROR403,
        UnknownMethod,
        NoPermissions,
        Timeout,
        UnknownError
    };

public:
    QBittorrentSession(Ilias::IoContext& ioContext);
    QBittorrentSession();
    auto login(const LoginParameters& loginInfo = {}) -> Error;
    auto logout() -> Error;
    void setHost(std::string host);
    void setPort(int port);
    void setTimeout(int timeout);
    auto token() const -> std::string;

    // TODO: Add methods to interact with qBittorrent API
    auto request(std::string_view method, const std::vector<char>& data = {})
        -> Ilias::Task<std::string>;

private:
    auto makeRequestUrl(std::string_view path) const -> std::string;

private:
    Ilias::IoContext* mIoCtxt       = {};
    std::string mHost               = {};
    int mPort                       = {};
    int mTimeout                    = {};
    std::string mToken              = {};
    Ilias::HttpCookieJar mCookies   = {};
    Ilias::HttpSession mHttpSession = {};
};

ILIAS_NS_BEGIN
ILIAS_DECLARE_ERROR(QBittorrentSession::Error, QBErrorCategory);
ILIAS_NS_END