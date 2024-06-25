#include <iostream>
#include <string_view>

#include "../bittorrent/session.hpp"
#include "ilias.hpp"
#include "ilias_async.hpp"
#include "ilias_http.hpp"
#include "ilias_networking.hpp"

int main(int argc, char** argv) {
    ILIAS_NAMESPACE::PlatformIoContext ioContext;
    QBittorrentSession session(ioContext);
    session.setHost("http://localhost");
    session.setPort(8080);
    auto ret = session.login({"admin", "qwe@123"});
    if (ret != QBittorrentSession::NoError) {
        std::cout << "failed to login: " << ret << std::endl;
        return 0;
    } else {
        std::cout << "successfully logged in , token: " << session.token()
                  << std::endl;
    }

    GetBuildInfoReturns buildInfo;
    auto reply = ilias_wait session.request(QB_GET_BUILD_INFO);
    if (reply) {
        buildInfo.makeProto().formData(std::vector<char>{
            reply.value().data(), reply.value().data() + reply.value().size()});
    }
    std::cout << reply.value() << std::endl;
    std::cout << NEKO_NAMESPACE::SerializableToString(buildInfo) << std::endl;

    GetTorrentListParameters params;
    params.filter = "all";
    params.limit  = 30;
    auto reply1   = ilias_wait session.request(QB_GET_TORRENT_LIST,
                                               params.makeProto().toData());
    if (reply1) {
        std::vector<GetTorrentListReturns> list =
            NEKO_NAMESPACE::ListFromData<GetTorrentListReturns>(reply1.value());
        for (const auto& f : list) {
            std::cout << NEKO_NAMESPACE::SerializableToString(f) << std::endl;
        }
    }

    ret = session.logout();
    if (ret != QBittorrentSession::NoError) {
        std::cout << "failed to logout: " << ret << std::endl;
    } else {
        std::cout << "successfully logged out" << std::endl;
    }
    return 0;
}