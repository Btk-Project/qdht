#include <iostream>
#include <string_view>

#include "../bittorrent/session.hpp"
#include "ilias.hpp"
#include "ilias_async.hpp"
#include "ilias_http.hpp"
#include "ilias_networking.hpp"
#include "json_serializer.hpp"
#include "to_string.hpp"

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
        std::cout << "successfully logged in , token: " << session.token() << std::endl;
    }

    auto reply = ilias_wait session.request(QB_GET_BUILD_INFO);
    if (reply) {
        GetBuildInfoReturns buildInfo;
        buildInfo.makeProto().formData(
            std::vector<char>{reply.value().data(), reply.value().data() + reply.value().size()});
        std::cout << NEKO_NAMESPACE::SerializableToString(buildInfo) << std::endl;
    } else {
        std::cout << "failed to get build info" << reply.error().message() << std::endl;
    }

    GetTorrentListParameters params;
    params.filter = "all";
    params.limit  = 30;
    auto d        = params.makeProto().toData();
    d.push_back('\0');
    std::cout << "data size " << d.size() << " d : " << d.data() << std::endl;
    auto reply1 = ilias_wait session.request(QB_GET_TORRENT_LIST, params.makeProto().toData());
    if (reply1) {
        std::ofstream out("TorrentList.json", std::ios::out | std::ios::binary);
        out.write(reply1.value().data(), reply1.value().size());
        out.close();

        std::vector<GetTorrentListReturns> list;
        NEKO_NAMESPACE::JsonSerializer::InputSerializer is(reply1.value().data(), reply1.value().size());
        load(is, list);
        for (const auto& f : list) {
            std::cout << NEKO_NAMESPACE::SerializableToString(f) << std::endl;
        }
    } else {
        std::cout << "failed to get torrent list" << reply1.error().message() << std::endl;
    }

    GetApplicationPreferencesReturns prefs;
    auto reply2 = ilias_wait session.request(QB_GET_APPLICATION_PREFERENCES);
    if (reply2) {
        std::ofstream out("prefs.json", std::ios::out | std::ios::binary);
        out.write(reply2.value().data(), reply2.value().size());
        out.close();
        prefs.makeProto().formData(
            std::vector<char>{reply2.value().data(), reply2.value().data() + reply2.value().size()});
        std::cout << NEKO_NAMESPACE::SerializableToString(prefs) << std::endl;
    } else {
        std::cout << "failed to get application preferences " << reply2.error().message() << std::endl;
    }

    SetApplicationPreferencesParameters sprefs;
    prefs.web_ui_custom_http_headers = "";
    sprefs.json                      = prefs;
    auto reply3 = ilias_wait session.request(QB_SET_APPLICATION_PREFERENCES, sprefs.makeProto().toData());
    if (reply3) {
        std::cout << "successfully set application preferences " << reply3.value() << std::endl;
    } else {
        std::cout << "failed to set application preferences " << reply3.error().message() << std::endl;
    }

    GetLogParameters logParams;
    auto reply4 = ilias_wait session.request(QB_GET_LOG, logParams.makeProto().toData());
    if (reply4) {
        std::vector<GetLogReturns> logs;
        NEKO_NAMESPACE::JsonSerializer::InputSerializer is(reply4.value().data(), reply4.value().size());
        load(is, logs);
        for (const auto& f : logs) {
            std::cout << NEKO_NAMESPACE::SerializableToString(f) << std::endl;
        }
    } else {
        std::cout << "failed to get log " << reply4.error().message() << std::endl;
    }

    ret = session.logout();
    if (ret != QBittorrentSession::NoError) {
        std::cout << "failed to logout: " << ret << std::endl;
    } else {
        std::cout << "success logout" << std::endl;
    }
    return 0;
}