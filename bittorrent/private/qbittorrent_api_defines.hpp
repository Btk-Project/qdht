
#pragma once

#include <cstdint>
#include <string>

#include "json_serializer.hpp"
#include "proto_base.hpp"
#include "qbittorrent_api_helpers.hpp"
#include "serializer_base.hpp"
#include "types/map.hpp"
#include "types/variant.hpp"
#include "types/vector.hpp"

// All Authentication API methods are under path: /api/v2/auth/
#define QB_LOGIN  "/api/v2/auth/login"
#define QB_LOGOUT "/api/v2/auth/logout"

// All Application API methods are under path: /api/v2/app/
#define QB_GET_APPLICATION_VERSION     "/api/v2/app/version"
#define QB_GET_API_VERSION             "/api/v2/app/webapiVersion"
#define QB_GET_BUILD_INFO              "/api/v2/app/buildInfo"
#define QB_SHUTDOWN_APPLICATION        "/api/v2/app/shutdown"
#define QB_GET_APPLICATION_PREFERENCES "/api/v2/app/preferences"
#define QB_SET_APPLICATION_PREFERENCES "/api/v2/app/setPreferences"
#define QB_GET_DEFAULT_SAVE_PATH       "/api/v2/app/defaultSavePath"

// All Log API methods are under path: /api/v2/log/
#define QB_GET_LOG      "/api/v2/log/main"
#define QB_GET_PEER_LOG "/api/v2/log/peers"

// All Sync API methods are under path: /api/v2/sync/
#define QB_GET_MAIN_DATA          "/api/v2/sync/maindata"
#define QB_GET_TORRENT_PEERS_DATA "/api/v2/sync/torrentPeers"

// All Transfer info API methods are under path: /api/v2/transfer/
#define QB_GET_GLOBAL_TRANSFER_INFO           "/api/v2/transfer/info"
#define QB_GET_ALTERNATIVE_SPEED_LIMITS_STATE "/api/v2/transfer/speedLimitsMode"
#define QB_TOGGLE_ALTERNATIVE_SPEED_LIMITS    "/api/v2/transfer/toggleSpeedLimitsMode"
#define QB_GET_GLOBAL_DOWNLOAD_LIMIT          "/api/v2/transfer/downloadLimit"
#define QB_SET_GLOBAL_DOWNLOAD_LIMIT          "/api/v2/transfer/setDownloadLimit"
#define QB_GET_GLOBAL_UPLOAD_LIMIT            "/api/v2/transfer/uploadLimit"
#define QB_SET_GLOBAL_UPLOAD_LIMIT            "/api/v2/transfer/setUploadLimit"
#define QB_BAN_PEERS                          "/api/v2/transfer/banPeers"

// All Torrent management API methods are under path: /api/v2/torrents/
#define QB_GET_TORRENT_LIST               "/api/v2/torrents/info"
#define QB_GET_TORRENT_GENERIC_PROPERTIES "/api/v2/torrents/properties"
#define QB_GET_TORRENT_TRACKERS           "/api/v2/torrents/trackers"
#define QB_GET_TORRENT_WEB_SEEDS          "/api/v2/torrents/webseeds"
#define QB_GET_TORRENT_CONTENTS           "/api/v2/torrents/files"
#define QB_GET_TORRENT_PIECES_STATES      "/api/v2/torrents/pieceStates"
#define QB_GET_TORRENT_PIECES_HASHES      "/api/v2/torrents/pieceHashes"
#define QB_PAUSE_TORRENTS                 "/api/v2/torrents/pause"
#define QB_RESUME_TORRENTS                "/api/v2/torrents/resume"
#define QB_DELETE_TORRENTS                "/api/v2/torrents/delete"
#define QB_RECHECK_TORRENTS               "/api/v2/torrents/recheck"
#define QB_REANNOUNCE_TORRENTS            "/api/v2/torrents/reannounce"
#define QB_EDIT_TRACKERS                  "/api/v2/torrents/editTracker"
#define QB_REMOVE_TRACKERS                "/api/v2/torrents/removeTrackers"
#define QB_ADD_PEERS                      "/api/v2/torrents/addPeers"
#define QB_INCREASE_TORRENT_PRIORITY      "/api/v2/torrents/increasePrio"
#define QB_DECREASE_TORRENT_PRIORITY      "/api/v2/torrents/decreasePrio"
#define QB_MAXIMAL_TORRENT_PRIORITY       "/api/v2/torrents/topPrio"
#define QB_MINIMAL_TORRENT_PRIORITY       "/api/v2/torrents/bottomPrio"
#define QB_SET_FILE_PRIORITY              "/api/v2/torrents/filePrio"
#define QB_GET_ALL_CATEGORIES             "/api/v2/torrents/categories"
#define QB_GET_ALL_TAGS                   "/api/v2/torrents/tags"
#define QB_TOGGLE_SEQUENTIAL_DOWNLOAD     "/api/v2/torrents/toggleSequentialDownload"
#define QB_SET_FIRST_LAST_PIECE_PRIORITY  "/api/v2/torrents/toggleFirstLastPiecePrio"
#define QB_RENAME_FILE                    "/api/v2/torrents/renameFile"
#define QB_RENAME_FOLDER                  "/api/v2/torrents/renameFolder"

// All RSS (experimental) API methods are under path: /api/v2/rss/
#define QB_ADD_FOLDER                       "/api/v2/rss/addFolder"
#define QB_ADD_FEED                         "/api/v2/rss/addFeed"
#define QB_REMOVE_ITEM                      "/api/v2/rss/removeItem"
#define QB_MOVE_ITEM                        "/api/v2/rss/moveItem"
#define QB_GET_ALL_ITEMS                    "/api/v2/rss/items"
#define QB_MARK_AS_READ                     "/api/v2/rss/markAsRead"
#define QB_REFRESH_ITEM                     "/api/v2/rss/refreshItem"
#define QB_SET_AUTO_DOWNLOADING_RULE        "/api/v2/rss/setRule"
#define QB_RENAME_AUTO_DOWNLOADING_RULE     "/api/v2/rss/renameRule"
#define QB_REMOVE_AUTO_DOWNLOADING_RULE     "/api/v2/rss/removeRule"
#define QB_GET_ALL_AUTO_DOWNLOADING_RULES   "/api/v2/rss/rules"
#define QB_GET_ALL_ARTICLES_MATCHING_A_RULE "/api/v2/rss/matchingArticles"

// All Search API methods are under path: /api/v2/search/
#define QB_START_SEARCH            "/api/v2/search/start"
#define QB_STOP_SEARCH             "/api/v2/search/stop"
#define QB_GET_SEARCH_STATUS       "/api/v2/search/status"
#define QB_GET_SEARCH_RESULTS      "/api/v2/search/results"
#define QB_DELETE_SEARCH           "/api/v2/search/delete"
#define QB_GET_SEARCH_PLUGINS      "/api/v2/search/plugins"
#define QB_INSTALL_SEARCH_PLUGIN   "/api/v2/search/installPlugin"
#define QB_UNINSTALL_SEARCH_PLUGIN "/api/v2/search/uninstallPlugin"
#define QB_ENABLE_SEARCH_PLUGIN    "/api/v2/search/enablePlugin"
#define QB_UPDATE_SEARCH_PLUGINS   "/api/v2/search/updatePlugins"

// define struct for Login
struct LoginParameters {
    std::string username = {};  // Username used to access the WebUI
    std::string password = {};  // Password used to access the WebUI
    NEKO_SERIALIZER(username, password)
    NEKO_DECLARE_PROTOCOL(LoginParameters, NEKO_NAMESPACE::ParametersSerializer)
};  // the end of Login Parameters

// define struct for Get build info
struct GetBuildInfoReturns {
    std::string qt         = {};  // QT version
    std::string libtorrent = {};  // libtorrent version
    std::string boost      = {};  // Boost version
    std::string openssl    = {};  // OpenSSL version
    int bitness            = {};  // Application bitness (e.g. 64-bit)
    NEKO_SERIALIZER(qt, libtorrent, boost, openssl, bitness)
    NEKO_DECLARE_PROTOCOL(GetBuildInfoReturns, NEKO_NAMESPACE::JsonSerializer)
};  // the end of Shutdown application Returns
    // clang-format off

typedef std::map<std::string, ScanDir> ScanDirs;

// define struct for Get application preferences
struct GetApplicationPreferencesReturns {
    std::string locale =
        {};  // Currently selected language (e.g. en_GB for English)
    std::optional<bool> create_subfolder_enabled =
        {};  // True if a subfolder should be created when adding a torrent
    bool start_paused_enabled =
        {};  // True if torrents should be added in a Paused state
    int64_t auto_delete_mode = {};  // TODO
    bool preallocate_all =
        {};  // True if disk space should be pre-allocated for all files
    bool incomplete_files_ext =
        {};  // True if ".!qB" should be appended to incomplete files
    bool auto_tmm_enabled =
        {};  // True if Automatic Torrent Management is enabled by default
    bool torrent_changed_tmm_enabled =
        {};  // True if torrent should be relocated when its Category changes
    bool save_path_changed_tmm_enabled =
        {};  // True if torrent should be relocated when the default save path
             // changes
    bool category_changed_tmm_enabled =
        {};  // True if torrent should be relocated when its Category's save
             // path changes
    std::string save_path =
        {};  // Default save path for torrents, separated by slashes
    bool temp_path_enabled =
        {};  // True if folder for incomplete torrents is enabled
    std::string temp_path =
        {};  // Path for incomplete torrents, separated by slashes
    ScanDirs scan_dirs =
        {};  // Property: directory to watch for torrent files, value: where
    // torrents loaded from this directory should be downloaded to (see
    // list of possible values below). Slashes are used as path
    // separators; multiple key/value pairs can be specified
    std::string export_dir = {};  // Path to directory to copy .torrent files
                                  // to. Slashes are used as path separators
    std::string export_dir_fin =
        {};  // Path to directory to copy .torrent files of completed downloads
             // to. Slashes are used as path separators
    bool mail_notification_enabled =
        {};  // True if e-mail notification should be enabled
    std::string mail_notification_sender =
        {};  // e-mail where notifications should originate from
    std::string mail_notification_email =
        {};  // e-mail to send notifications to
    std::string mail_notification_smtp =
        {};  // smtp server for e-mail notifications
    bool mail_notification_ssl_enabled =
        {};  // True if smtp server requires SSL connection
    bool mail_notification_auth_enabled =
        {};  // True if smtp server requires authentication
    std::string mail_notification_username =
        {};  // Username for smtp authentication
    std::string mail_notification_password =
        {};                     // Password for smtp authentication
    bool autorun_enabled = {};  // True if external program should be run after
                                // torrent has finished downloading
    std::string autorun_program =
        {};  // Program path/name/arguments to run if `autorun_enabled` is
             // enabled; path is separated by slashes; you can use `%f` and `%n`
             // arguments, which will be expanded by qBittorent as
             // path_to_torrent_file and torrent_name (from the GUI; not the
             // .torrent file name) respectively
    bool queueing_enabled = {};  // True if torrent queuing is enabled
    int64_t max_active_downloads =
        {};  // Maximum number of active simultaneous downloads
    int64_t max_active_torrents =
        {};  // Maximum number of active simultaneous downloads and uploads
    int64_t max_active_uploads =
        {};  // Maximum number of active simultaneous uploads
    bool dont_count_slow_torrents =
        {};  // If true torrents w/o any activity (stalled ones) will not be
             // counted towards `max_active_*` limits; see
             // [dont_count_slow_torrents](https://www.libtorrent.org/reference-Settings.html#dont_count_slow_torrents)
             // for more information
    int64_t slow_torrent_dl_rate_threshold =
        {};  // Download rate in KiB/s for a torrent to be considered "slow"
    int64_t slow_torrent_ul_rate_threshold =
        {};  // Upload rate in KiB/s for a torrent to be considered "slow"
    int64_t slow_torrent_inactive_timer =
        {};  // Seconds a torrent should be inactive before considered "slow"
    bool max_ratio_enabled = {};  // True if share ratio limit is enabled
    std::optional<double> max_ratio       = {};  // Get the global share ratio limit
    int64_t max_ratio_act =
        {};  // Action performed when a torrent reaches the maximum share ratio.
             // See list of possible values here below.
    int64_t listen_port = {};  // Port for incoming connections
    bool upnp           = {};  // True if UPnP/NAT-PMP is enabled
    bool random_port    = {};  // True if the port is randomly selected
    int64_t dl_limit = {};  // Global download speed limit in KiB/s; `-1` means
                            // no limit is applied
    int64_t up_limit = {};  // Global upload speed limit in KiB/s; `-1` means no
                            // limit is applied
    int64_t max_connec =
        {};  // Maximum global number of simultaneous connections
    int64_t max_connec_per_torrent =
        {};  // Maximum number of simultaneous connections per torrent
    int64_t max_uploads = {};  // Maximum number of upload slots
    int64_t max_uploads_per_torrent =
        {};  // Maximum number of upload slots per torrent
    int64_t stop_tracker_timeout =
        {};  // Timeout in seconds for a `stopped` announce request to trackers
    bool enable_piece_extent_affinity =
        {};  // True if the advanced libtorrent option `piece_extent_affinity`
             // is enabled
    int64_t bittorrent_protocol =
        {};  // Bittorrent Protocol to use (see list of possible values below)
    bool limit_utp_rate =
        {};  // True if `[du]l_limit` should be applied to uTP connections; this
             // option is only available in qBittorent built against libtorrent
             // version 0.16.X and higher
    bool limit_tcp_overhead =
        {};  // True if `[du]l_limit` should be applied to estimated TCP
             // overhead (service data: e.g. packet headers)
    bool limit_lan_peers =
        {};  // True if `[du]l_limit` should be applied to peers on the LAN
    int64_t alt_dl_limit =
        {};  // Alternative global download speed limit in KiB/s
    int64_t alt_up_limit =
        {};  // Alternative global upload speed limit in KiB/s
    bool scheduler_enabled = {};      // True if alternative limits should be
                                      // applied according to schedule
    int64_t schedule_from_hour = {};  // Scheduler starting hour
    int64_t schedule_from_min  = {};  // Scheduler starting minute
    int64_t schedule_to_hour   = {};  // Scheduler ending hour
    int64_t schedule_to_min    = {};  // Scheduler ending minute
    int64_t scheduler_days =
        {};                   // Scheduler days. See possible values here below
    bool dht           = {};  // True if DHT is enabled
    bool pex           = {};  // True if PeX is enabled
    bool lsd           = {};  // True if LSD is enabled
    int64_t encryption = {};  // See list of possible values here below
    bool anonymous_mode =
        {};  // If true anonymous mode will be enabled; read more
             // [here](Anonymous-Mode); this option is only available in
             // qBittorent built against libtorrent version 0.16.X and higher
    std::optional<std::string> proxy_type   = {};  // See list of possible values here below
    std::string proxy_ip = {};  // Proxy IP address or domain name
    int64_t proxy_port   = {};  // Proxy port
    bool proxy_peer_connections =
        {};  // True if peer and web seed connections should be proxified; this
             // option will have any effect only in qBittorent built against
             // libtorrent version 0.16.X and higher
    bool proxy_auth_enabled = {};     // True proxy requires authentication;
                                      // doesn't apply to SOCKS4 proxies
    std::string proxy_username = {};  // Username for proxy authentication
    std::string proxy_password = {};  // Password for proxy authentication
    std::optional<bool> proxy_torrents_only   = {};  // True if proxy is only used for torrents
    bool ip_filter_enabled =
        {};  // True if external IP filter should be enabled
    std::string ip_filter_path =
        {};  // Path to IP filter file (.dat, .p2p, .p2b files are supported);
             // path is separated by slashes
    bool ip_filter_trackers = {};  // True if IP filters are applied to trackers
    std::string web_ui_domain_list =
        {};  // Semicolon-separated list of domains to accept when performing
             // Host header validation
    std::string web_ui_address = {};  // IP address to use for the WebUI
    int64_t web_ui_port        = {};  // WebUI port
    bool web_ui_upnp           = {};  // True if UPnP is used for the WebUI port
    std::string web_ui_username = {};  // WebUI username
    std::optional<std::string> web_ui_password =
        {};  // For API ≥ v2.3.0: Plaintext WebUI password, not readable,
             // write-only. For API < v2.3.0: MD5 hash of WebUI password, hash
             // is generated from the following string: `username:Web UI
             // Access:plain_text_web_ui_password`
    bool web_ui_csrf_protection_enabled =
        {};  // True if WebUI CSRF protection is enabled
    bool web_ui_clickjacking_protection_enabled =
        {};  // True if WebUI clickjacking protection is enabled
    bool web_ui_secure_cookie_enabled =
        {};  // True if WebUI cookie `Secure` flag is enabled
    int64_t web_ui_max_auth_fail_count =
        {};  // Maximum number of authentication failures before WebUI access
             // ban
    int64_t web_ui_ban_duration = {};  // WebUI access ban duration in seconds
    int64_t web_ui_session_timeout =
        {};  // Seconds until WebUI is automatically signed off
    bool web_ui_host_header_validation_enabled =
        {};  // True if WebUI host header validation is enabled
    bool bypass_local_auth =
        {};  // True if authentication challenge for loopback address
             // (127.0.0.1) should be disabled
    bool bypass_auth_subnet_whitelist_enabled =
        {};  // True if webui authentication should be bypassed for clients
             // whose ip resides within (at least) one of the subnets on the
             // whitelist
    std::string bypass_auth_subnet_whitelist =
        {};  // (White)list of ipv4/ipv6 subnets for which webui authentication
             // should be bypassed; list entries are separated by commas
    bool alternative_webui_enabled =
        {};  // True if an alternative WebUI should be used
    std::string alternative_webui_path =
        {};               // File path to the alternative WebUI
    bool use_https = {};  // True if WebUI HTTPS access is enabled
    std::optional<std::string> ssl_key =
        {};  // For API < v2.0.1: SSL keyfile contents (this is a not a path)
    std::optional<std::string> ssl_cert = {};  // For API < v2.0.1: SSL certificate contents
                                // (this is a not a path)
    std::string web_ui_https_key_path =
        {};  // For API ≥ v2.0.1: Path to SSL keyfile
    std::string web_ui_https_cert_path =
        {};  // For API ≥ v2.0.1: Path to SSL certificate
    bool dyndns_enabled =
        {};  // True if server DNS should be updated dynamically
    int64_t dyndns_service      = {};  // See list of possible values here below
    std::string dyndns_username = {};  // Username for DDNS service
    std::string dyndns_password = {};  // Password for DDNS service
    std::string dyndns_domain   = {};  // Your DDNS domain name
    int64_t rss_refresh_interval      = {};  // RSS refresh interval
    int64_t rss_max_articles_per_feed = {};  // Max stored articles per RSS feed
    bool rss_processing_enabled       = {};  // Enable processing of RSS feeds
    bool rss_auto_downloading_enabled =
        {};  // Enable auto-downloading of torrents from the RSS feeds
    bool rss_download_repack_proper_episodes =
        {};  // For API ≥ v2.5.1: Enable downloading of repack/proper Episodes
    std::string rss_smart_episode_filters =
        {};  // For API ≥ v2.5.1: List of RSS Smart Episode Filters
    bool add_trackers_enabled =
        {};  // Enable automatic adding of trackers to new torrents
    std::string add_trackers = {};  // List of trackers to add to new torrent
    bool web_ui_use_custom_http_headers_enabled =
        {};  // For API ≥ v2.5.1: Enable custom http headers
    std::string web_ui_custom_http_headers =
        {};  // For API ≥ v2.5.1: List of custom http headers
    bool max_seeding_time_enabled = {};  // True enables max seeding time
    int64_t max_seeding_time      = {};  // Number of minutes to seed a torrent
    std::string announce_ip       = {};  // TODO
    bool announce_to_all_tiers    = {};  // True always announce to all tiers
    bool announce_to_all_trackers =
        {};  // True always announce to all trackers in a tier
    int64_t async_io_threads = {};  // Number of asynchronous I/O threads
    std::string banned_IPs   = {};  // List of banned IPs
    int64_t checking_memory_use =
        {};  // Outstanding memory when checking torrents in MiB
    std::string current_interface_address =
        {};  // IP Address to bind to. Empty String means All addresses
    std::string current_network_interface = {};  // Network Interface used
    int64_t disk_cache                    = {};  // Disk cache used in MiB
    int64_t disk_cache_ttl = {};  // Disk cache expiry interval in seconds
    int64_t embedded_tracker_port = {};  // Port used for embedded tracker
    bool enable_coalesce_read_write =
        {};                             // True enables coalesce reads & writes
    bool enable_embedded_tracker = {};  // True enables embedded tracker
    bool enable_multi_connections_from_same_ip =
        {};  // True allows multiple connections from the same IP address
    std::optional<bool> enable_os_cache = {};  // True enables os cache
    bool enable_upload_suggestions =
        {};  // True enables sending of upload piece suggestions
    int64_t file_pool_size     = {};  // File pool size
    int64_t outgoing_ports_max = {};  // Maximal outgoing port (0: Disabled)
    int64_t outgoing_ports_min = {};  // Minimal outgoing port (0: Disabled)
    bool recheck_completed_torrents =
        {};  // True rechecks torrents on completion
    bool resolve_peer_countries       = {};  // True resolves peer countries
    int64_t save_resume_data_interval = {};  // Save resume data interval in min
    int64_t send_buffer_low_watermark = {};  // Send buffer low watermark in KiB
    int64_t send_buffer_watermark     = {};  // Send buffer watermark in KiB
    int64_t send_buffer_watermark_factor =
        {};  // Send buffer watermark factor in percent
    int64_t socket_backlog_size = {};  // Socket backlog size
    int64_t upload_choking_algorithm =
        {};  // Upload choking algorithm used (see list of possible values
             // below)
    int64_t upload_slots_behavior =
        {};  // Upload slots behavior used (see list of possible values below)
    int64_t upnp_lease_duration =
        {};  // UPnP lease duration (0: Permanent lease)
    int64_t utp_tcp_mixed_mode =
        {};  // μTP-TCP mixed mode algorithm (see list of possible values below)
    NEKO_SERIALIZER(
        locale, create_subfolder_enabled, start_paused_enabled,
        auto_delete_mode, preallocate_all, incomplete_files_ext,
        auto_tmm_enabled, torrent_changed_tmm_enabled,
        save_path_changed_tmm_enabled, category_changed_tmm_enabled, save_path,
        temp_path_enabled, temp_path, scan_dirs, export_dir, export_dir_fin,
        mail_notification_enabled, mail_notification_sender,
        mail_notification_email, mail_notification_smtp,
        mail_notification_ssl_enabled, mail_notification_auth_enabled,
        mail_notification_username, mail_notification_password, autorun_enabled,
        autorun_program, queueing_enabled, max_active_downloads,
        max_active_torrents, max_active_uploads, dont_count_slow_torrents,
        slow_torrent_dl_rate_threshold, slow_torrent_ul_rate_threshold,
        slow_torrent_inactive_timer, max_ratio_enabled, max_ratio,
        max_ratio_act, listen_port, upnp, random_port, dl_limit, up_limit,
        max_connec, max_connec_per_torrent, max_uploads,
        max_uploads_per_torrent, stop_tracker_timeout,
        enable_piece_extent_affinity, bittorrent_protocol, limit_utp_rate,
        limit_tcp_overhead, limit_lan_peers, alt_dl_limit, alt_up_limit,
        scheduler_enabled, schedule_from_hour, schedule_from_min,
        schedule_to_hour, schedule_to_min, scheduler_days, dht, pex, lsd,
        encryption, anonymous_mode, proxy_type, proxy_ip, proxy_port,
        proxy_peer_connections, proxy_auth_enabled, proxy_username,
        proxy_password, proxy_torrents_only, ip_filter_enabled, ip_filter_path,
        ip_filter_trackers, web_ui_domain_list, web_ui_address, web_ui_port,
        web_ui_upnp, web_ui_username, web_ui_password,
        web_ui_csrf_protection_enabled, web_ui_clickjacking_protection_enabled,
        web_ui_secure_cookie_enabled, web_ui_max_auth_fail_count,
        web_ui_ban_duration, web_ui_session_timeout,
        web_ui_host_header_validation_enabled, bypass_local_auth,
        bypass_auth_subnet_whitelist_enabled, bypass_auth_subnet_whitelist,
        alternative_webui_enabled, alternative_webui_path, use_https, ssl_key,
        ssl_cert, web_ui_https_key_path, web_ui_https_cert_path, dyndns_enabled,
        dyndns_service, dyndns_username, dyndns_password, dyndns_domain,
        rss_refresh_interval, rss_max_articles_per_feed, rss_processing_enabled,
        rss_auto_downloading_enabled, rss_download_repack_proper_episodes,
        rss_smart_episode_filters, add_trackers_enabled, add_trackers,
        web_ui_use_custom_http_headers_enabled, web_ui_custom_http_headers,
        max_seeding_time_enabled, max_seeding_time, announce_ip,
        announce_to_all_tiers, announce_to_all_trackers, async_io_threads,
        banned_IPs, checking_memory_use, current_interface_address,
        current_network_interface, disk_cache, disk_cache_ttl,
        embedded_tracker_port, enable_coalesce_read_write,
        enable_embedded_tracker, enable_multi_connections_from_same_ip,
        enable_os_cache, enable_upload_suggestions, file_pool_size,
        outgoing_ports_max, outgoing_ports_min, recheck_completed_torrents,
        resolve_peer_countries, save_resume_data_interval,
        send_buffer_low_watermark, send_buffer_watermark,
        send_buffer_watermark_factor, socket_backlog_size,
        upload_choking_algorithm, upload_slots_behavior, upnp_lease_duration,
        utp_tcp_mixed_mode)
    NEKO_DECLARE_PROTOCOL(GetApplicationPreferencesReturns,
                          NEKO_NAMESPACE::JsonSerializer)
};  // the end of Set application preferences Returns

struct SetApplicationPreferencesParameters {
    GetApplicationPreferencesReturns json;
    NEKO_SERIALIZER(json)
    NEKO_DECLARE_PROTOCOL(SetApplicationPreferencesParameters,
                          NEKO_NAMESPACE::ParametersSerializer);
};

// define struct for Get log
struct GetLogParameters {
    bool normal           = {true};  // Include normal messages (default: `true`)
    bool info             = {true};  // Include info messages (default: `true`)
    bool warning          = {true};  // Include warning messages (default: `true`)
    bool critical         = {true};  // Include critical messages (default: `true`)
    int64_t last_known_id = {-1};  // Exclude messages with "message id" <=
                                 // `last_known_id` (default: `-1`)
    NEKO_SERIALIZER(normal, info, warning, critical, last_known_id)
    NEKO_DECLARE_PROTOCOL(GetLogParameters, NEKO_NAMESPACE::ParametersSerializer)
};  // the end of Get log Parameters

// define struct for Get log
struct GetLogReturns {
    int64_t id          = {};  // ID of the message
    std::string message = {};  // Text of the message
    int64_t timestamp   = {};  // Seconds since epoch (Note: switched from
                               // milliseconds to seconds in v4.5.0)
    int64_t type = {};  // Type of the message: Log::NORMAL: `1`, Log::INFO:
                        // `2`, Log::WARNING: `4`, Log::CRITICAL: `8`
    NEKO_SERIALIZER(id, message, timestamp, type)
    NEKO_DECLARE_PROTOCOL(GetLogReturns, NEKO_NAMESPACE::JsonSerializer)
};  // the end of Get peer log Returns

// define struct for Get peer log
struct GetPeerLogParameters {
    int64_t last_known_id = {-1};  // Exclude messages with "message id" <=
                                 // `last_known_id` (default: `-1`)
    NEKO_SERIALIZER(last_known_id)
    NEKO_DECLARE_PROTOCOL(GetPeerLogParameters, NEKO_NAMESPACE::ParametersSerializer)
};  // the end of Get peer log Parameters

// define struct for Get peer log
struct GetPeerLogReturns {
    int64_t id         = {};  // ID of the peer
    std::string ip     = {};  // IP of the peer
    int64_t timestamp  = {};  // Seconds since epoch
    bool blocked       = {};  // Whether or not the peer was blocked
    std::string reason = {};  // Reason of the block
    NEKO_SERIALIZER(id, ip, timestamp, blocked, reason)
    NEKO_DECLARE_PROTOCOL(GetPeerLogReturns, NEKO_NAMESPACE::JsonSerializer)
};  // the end of Get peer log Returns

// define struct for Get main data
struct GetMainDataParameters {
    int64_t rid = {};  // Response ID. If not provided, `rid=0` will be assumed.
                       // If the given `rid` is different from the one of last
                       // server reply, `full_update` will be `true` (see the
                       // server reply details for more info)
    NEKO_SERIALIZER(rid)
    NEKO_DECLARE_PROTOCOL(GetMainDataParameters, NEKO_NAMESPACE::ParametersSerializer)
};  // the end of Get main data Parameters

// define struct for Get torrent peers data
struct GetTorrentPeersDataParameters {
    std::string hash = {};  // Torrent hash
    int64_t rid = {};  // Response ID. If not provided, `rid=0` will be assumed.
                       // If the given `rid` is different from the one of last
                       // server reply, `full_update` will be `true` (see the
                       // server reply details for more info)
    NEKO_SERIALIZER(hash, rid)
    NEKO_DECLARE_PROTOCOL(GetTorrentPeersDataParameters,
                          NEKO_NAMESPACE::ParametersSerializer)
};  // the end of Get torrent peers data Parameters

// define struct for Get global transfer info
struct GetGlobalTransferInfoReturns {
    int64_t dl_info_speed = {};  // Global download rate (bytes/s)
    int64_t dl_info_data  = {};  // Data downloaded this session (bytes)
    int64_t up_info_speed = {};  // Global upload rate (bytes/s)
    int64_t up_info_data  = {};  // Data uploaded this session (bytes)
    int64_t dl_rate_limit = {};  // Download rate limit (bytes/s)
    int64_t up_rate_limit = {};  // Upload rate limit (bytes/s)
    int64_t dht_nodes     = {};  // DHT nodes connected to
    std::string connection_status =
        {};  // Connection status. See possible values here below
    NEKO_SERIALIZER(dl_info_speed, dl_info_data, up_info_speed, up_info_data,
                    dl_rate_limit, up_rate_limit, dht_nodes, connection_status)
    NEKO_DECLARE_PROTOCOL(GetGlobalTransferInfoReturns,
                          NEKO_NAMESPACE::JsonSerializer)
};  // the end of Get global transfer info Returns

// define struct for Get global transfer info
struct GetGlobalTransferInfoReturns1 {
    bool queueing = {};  // True if torrent queueing is enabled
    bool use_alt_speed_limits =
        {};  // True if alternative speed limits are enabled
    int64_t refresh_interval =
        {};  // Transfer list refresh interval (milliseconds)
    NEKO_SERIALIZER(queueing, use_alt_speed_limits, refresh_interval)
    NEKO_DECLARE_PROTOCOL(GetGlobalTransferInfoReturns1,
                          NEKO_NAMESPACE::JsonSerializer)
};  // the end of Get alternative speed limits state Returns1

// define struct for Set global download limit
struct SetGlobalDownloadLimitParameters {
    int64_t limit =
        {};  // The global download speed limit to set in bytes/second
    NEKO_SERIALIZER(limit)
    NEKO_DECLARE_PROTOCOL(SetGlobalDownloadLimitParameters,
                          NEKO_NAMESPACE::ParametersSerializer)
};  // the end of Set global download limit Parameters

// define struct for Set global upload limit
struct SetGlobalUploadLimitParameters {
    int64_t limit = {};  // The global upload speed limit to set in bytes/second
    NEKO_SERIALIZER(limit)
    NEKO_DECLARE_PROTOCOL(SetGlobalUploadLimitParameters,
                          NEKO_NAMESPACE::ParametersSerializer)
};  // the end of Set global upload limit Parameters

// define struct for Ban peers
struct BanPeersParameters {
    std::string peers =
        {};  // The peer to ban, or multiple peers separated by a pipe `\|`.
             // Each peer is a colon-separated `host:port`
    NEKO_SERIALIZER(peers)
    NEKO_DECLARE_PROTOCOL(BanPeersParameters, NEKO_NAMESPACE::ParametersSerializer)
};  // the end of Ban peers Parameters

// define struct for Get torrent list
struct GetTorrentListParameters {
    std::optional<std::string> filter =
        {};  // Filter torrent list by state. Allowed state filters: `all`,
             // `downloading`, `seeding`, `completed`, `paused`, `active`,
             // `inactive`, `resumed`, `stalled`, `stalled_uploading`,
             // `stalled_downloading`, `errored`
    std::optional<std::string> category =
        {};  // Get torrents with the given category (empty string means
             // "without category"; no "category" parameter means "any
             // category"). Remember to URL-encode the category name. For
             // example, `My category` becomes `My%20category`
    std::optional<std::string> tag =
        {};  // Get torrents with the given tag (empty string means "without
             // tag"; no "tag" parameter means "any tag". Remember to URL-encode
             // the category name. For example, `My tag` becomes `My%20tag`
    std::optional<std::string> sort = {};  // Sort torrents by given key. They can be sorted
                            // using any field of the response's JSON array
                            // (which are documented below) as the sort key.
    std::optional<bool> reverse   = {};    // Enable reverse sorting. Defaults to `false`
    std::optional<int64_t> limit  = {};    // Limit the number of torrents returned
    std::optional<int64_t> offset = {};    // Set offset (if less than 0, offset from end)
    std::optional<std::string> hashes =
        {};  // Filter by hashes. Can contain multiple hashes separated by `\|`
    NEKO_SERIALIZER(filter, category, tag, sort, reverse, limit, offset, hashes)
    NEKO_DECLARE_PROTOCOL(GetTorrentListParameters,
                          NEKO_NAMESPACE::ParametersSerializer)
};  // the end of Get torrent list Parameters

// define struct for Get torrent list
struct GetTorrentListReturns {
    int64_t added_on =
        {};  // Time (Unix Epoch) when the torrent was added to the client
    int64_t amount_left = {};  // Amount of data left to download (bytes)
    bool auto_tmm =
        {};  // Whether this torrent is managed by Automatic Torrent Management
    double availability  = {};  // Percentage of file pieces currently available
    std::string category = {};  // Category of the torrent
    int64_t completed    = {};  // Amount of transfer data completed (bytes)
    int64_t completion_on = {};  // Time (Unix Epoch) when the torrent completed
    std::string content_path =
        {};  // Absolute path of torrent content (root path for multifile
             // torrents, absolute file path for singlefile torrents)
    int64_t dl_limit =
        {};  // Torrent download speed limit (bytes/s). `-1` if unlimited.
    int64_t dlspeed            = {};  // Torrent download speed (bytes/s)
    int64_t downloaded         = {};  // Amount of data downloaded
    int64_t downloaded_session = {};  // Amount of data downloaded this session
    int64_t eta                = {};  // Torrent ETA (seconds)
    bool f_l_piece_prio = {};  // True if first last piece are prioritized
    bool force_start = {};  // True if force start is enabled for this torrent
    std::string hash = {};  // Torrent hash
    std::optional<bool> isPrivate =
        {};  // True if torrent is from a private tracker (added in 5.0.0)
    int64_t last_activity =
        {};  // Last time (Unix Epoch) when a chunk was downloaded/uploaded
    std::string magnet_uri = {};  // Magnet URI corresponding to this torrent
    double max_ratio = {};  // Maximum share ratio until torrent is stopped from
                            // seeding/uploading
    int64_t max_seeding_time = {};  // Maximum seeding time (seconds) until
                                    // torrent is stopped from seeding
    std::string name       = {};    // Torrent name
    int64_t num_complete   = {};    // Number of seeds in the swarm
    int64_t num_incomplete = {};    // Number of leechers in the swarm
    int64_t num_leechs     = {};    // Number of leechers connected to
    int64_t num_seeds      = {};    // Number of seeds connected to
    int64_t priority       = {};  // Torrent priority. Returns -1 if queuing is
                                  // disabled or torrent is in seed mode
    double progress       = {};   // Torrent progress (percentage/100)
    double ratio          = {};   // Torrent share ratio. Max ratio value: 9999.
    double ratio_limit    = {};   // TODO (what is different from `max_ratio`?)
    std::string save_path = {};   // Path where this torrent's data is stored
    int64_t seeding_time = {};  // Torrent elapsed time while complete (seconds)
    int64_t seeding_time_limit =
        {};  // TODO (what is different from `max_seeding_time`?)
             // seeding_time_limit is a per torrent setting, when Automatic
             // Torrent Management is disabled, furthermore then
             // max_seeding_time is set to seeding_time_limit for this torrent.
             // If Automatic Torrent Management is enabled, the value is -2. And
             // if max_seeding_time is unset it have a default value -1.
    int64_t seen_complete =
        {};  // Time (Unix Epoch) when this torrent was last seen complete
    bool seq_dl  = {};  // True if sequential download is enabled
    int64_t size = {};  // Total size (bytes) of files selected for download
    std::string state =
        {};  // Torrent state. See table here below for the possible values
    bool super_seeding  = {};  // True if super seeding is enabled
    std::string tags    = {};  // Comma-concatenated tag list of the torrent
    int64_t time_active = {};  // Total active time (seconds)
    int64_t total_size  = {};  // Total size (bytes) of all file in this torrent
                               // (including unselected ones)
    std::string tracker = {};  // The first tracker with working status. Returns
                               // empty string if no tracker is working.
    int64_t up_limit =
        {};  // Torrent upload speed limit (bytes/s). `-1` if unlimited.
    int64_t uploaded         = {};  // Amount of data uploaded
    int64_t uploaded_session = {};  // Amount of data uploaded this session
    int64_t upspeed          = {};  // Torrent upload speed (bytes/s)
    NEKO_SERIALIZER(added_on, amount_left, auto_tmm, availability, category,
                    completed, completion_on, content_path, dl_limit, dlspeed,
                    downloaded, downloaded_session, eta, f_l_piece_prio,
                    force_start, hash, isPrivate, last_activity, magnet_uri,
                    max_ratio, max_seeding_time, name, num_complete,
                    num_incomplete, num_leechs, num_seeds, priority, progress,
                    ratio, ratio_limit, save_path, seeding_time,
                    seeding_time_limit, seen_complete, seq_dl, size, state,
                    super_seeding, tags, time_active, total_size, tracker,
                    up_limit, uploaded, uploaded_session, upspeed)
    NEKO_DECLARE_PROTOCOL(GetTorrentListReturns, NEKO_NAMESPACE::JsonSerializer)
};  // the end of Get torrent generic properties Returns

// define struct for Get torrent generic properties
struct GetTorrentGenericPropertiesParameters {
    std::string hash = {};  // The hash of the torrent you want to get the
                            // generic properties of
    NEKO_SERIALIZER(hash)
    NEKO_DECLARE_PROTOCOL(GetTorrentGenericPropertiesParameters,
                          NEKO_NAMESPACE::ParametersSerializer)
};  // the end of Get torrent generic properties Parameters

// define struct for Get torrent generic properties
struct GetTorrentGenericPropertiesReturns {
    std::string save_path  = {};  // Torrent save path
    int64_t creation_date  = {};  // Torrent creation date (Unix timestamp)
    int64_t piece_size     = {};  // Torrent piece size (bytes)
    std::string comment    = {};  // Torrent comment
    int64_t total_wasted   = {};  // Total data wasted for torrent (bytes)
    int64_t total_uploaded = {};  // Total data uploaded for torrent (bytes)
    int64_t total_uploaded_session =
        {};                         // Total data uploaded this session (bytes)
    int64_t total_downloaded = {};  // Total data downloaded for torrent (bytes)
    int64_t up_limit         = {};  // Torrent upload limit (bytes/s)
    int64_t dl_limit         = {};  // Torrent download limit (bytes/s)
    int64_t time_elapsed     = {};  // Torrent elapsed time (seconds)
    int64_t seeding_time = {};  // Torrent elapsed time while complete (seconds)
    int64_t nb_connections       = {};  // Torrent connection count
    int64_t nb_connections_limit = {};  // Torrent connection count limit
    double share_ratio           = {};  // Torrent share ratio
    int64_t addition_date = {};  // When this torrent was added (unix timestamp)
    int64_t completion_date = {};  // Torrent completion date (unix timestamp)
    std::string created_by  = {};  // Torrent creator
    int64_t dl_speed_avg = {};  // Torrent average download speed (bytes/second)
    int64_t dl_speed     = {};  // Torrent download speed (bytes/second)
    int64_t eta          = {};  // Torrent ETA (seconds)
    int64_t last_seen    = {};  // Last seen complete date (unix timestamp)
    int64_t peers        = {};  // Number of peers connected to
    int64_t peers_total  = {};  // Number of peers in the swarm
    int64_t pieces_have  = {};  // Number of pieces owned
    int64_t pieces_num   = {};  // Number of pieces of the torrent
    int64_t reannounce   = {};  // Number of seconds until the next announce
    int64_t seeds        = {};  // Number of seeds connected to
    int64_t seeds_total  = {};  // Number of seeds in the swarm
    int64_t total_size   = {};  // Torrent total size (bytes)
    int64_t up_speed_avg = {};  // Torrent average upload speed (bytes/second)
    int64_t up_speed     = {};  // Torrent upload speed (bytes/second)
    bool isPrivate       = {};  // True if torrent is from a private tracker
    NEKO_SERIALIZER(save_path, creation_date, piece_size, comment, total_wasted,
                    total_uploaded, total_uploaded_session, total_downloaded,
                    up_limit, dl_limit, time_elapsed, seeding_time,
                    nb_connections, nb_connections_limit, share_ratio,
                    addition_date, completion_date, created_by, dl_speed_avg,
                    dl_speed, eta, last_seen, peers, peers_total, pieces_have,
                    pieces_num, reannounce, seeds, seeds_total, total_size,
                    up_speed_avg, up_speed, isPrivate)
    NEKO_DECLARE_PROTOCOL(GetTorrentGenericPropertiesReturns,
                          NEKO_NAMESPACE::JsonSerializer)
};  // the end of Get torrent trackers Returns

// define struct for Get torrent trackers
struct GetTorrentTrackersParameters {
    std::string hash =
        {};  // The hash of the torrent you want to get the trackers of
    NEKO_SERIALIZER(hash)
    NEKO_DECLARE_PROTOCOL(GetTorrentTrackersParameters,
                          NEKO_NAMESPACE::ParametersSerializer)
};  // the end of Get torrent trackers Parameters

// define struct for Get torrent trackers
struct GetTorrentTrackersReturns {
    std::string url = {};  // Tracker url
    int64_t status =
        {};  // Tracker status. See the table below for possible values
    int64_t tier = {};  // Tracker priority tier. Lower tier trackers are tried
                        // before higher tiers. Tier numbers are valid when `>=
                        // 0`, `< 0` is used as placeholder when `tier` does not
                        // exist for special entries (such as DHT).
    int64_t num_peers =
        {};  // Number of peers for current torrent, as reported by the tracker
    int64_t num_seeds =
        {};  // Number of seeds for current torrent, asreported by the tracker
    int64_t num_leeches = {};     // Number of leeches for current torrent, as
                                  // reported by the tracker
    int64_t num_downloaded = {};  // Number of completed downloads for current
                                  // torrent, as reported by the tracker
    std::string msg = {};  // Tracker message (there is no way of knowing what
                           // this message is - it's up to tracker admins)
    NEKO_SERIALIZER(url, status, tier, num_peers, num_seeds, num_leeches,
                    num_downloaded, msg)
    NEKO_DECLARE_PROTOCOL(GetTorrentTrackersReturns,
                          NEKO_NAMESPACE::JsonSerializer)
};  // the end of Get torrent web seeds Returns

// define struct for Get torrent web seeds
struct GetTorrentWebSeedsParameters {
    std::string hash =
        {};  // The hash of the torrent you want to get the webseeds of
    NEKO_SERIALIZER(hash)
    NEKO_DECLARE_PROTOCOL(GetTorrentWebSeedsParameters,
                          NEKO_NAMESPACE::ParametersSerializer)
};  // the end of Get torrent web seeds Parameters

// define struct for Get torrent web seeds
struct GetTorrentWebSeedsReturns {
    std::string url = {};  // URL of the web seed
    NEKO_SERIALIZER(url)
    NEKO_DECLARE_PROTOCOL(GetTorrentWebSeedsReturns,
                          NEKO_NAMESPACE::JsonSerializer)
};  // the end of Get torrent contents Returns

// define struct for Get torrent contents
struct GetTorrentContentsParameters {
    std::string hash =
        {};  // The hash of the torrent you want to get the contents of
    std::string indexes =
        {};  // The indexes of the files you want to retrieve. `indexes` can
             // contain multiple values separated by `\|`.
    NEKO_SERIALIZER(hash, indexes)
    NEKO_DECLARE_PROTOCOL(GetTorrentContentsParameters,
                          NEKO_NAMESPACE::ParametersSerializer)
};  // the end of Get torrent contents Parameters

// define struct for Get torrent contents
struct GetTorrentContentsReturns {
    int64_t index    = {};  // File index
    std::string name = {};  // File name (including relative path)
    int64_t size     = {};  // File size (bytes)
    double progress  = {};  // File progress (percentage/100)
    int64_t priority = {};  // File priority. See possible values here below
    bool is_seed     = {};  // True if file is seeding/complete
    std::vector<int64_t> piece_range =
        {};  // The first number is the starting piece index and the second
             // number is the ending piece index (inclusive)
    double availability =
        {};  // Percentage of file pieces currently available (percentage/100)
    NEKO_SERIALIZER(index, name, size, progress, priority, is_seed, piece_range,
                    availability)
    NEKO_DECLARE_PROTOCOL(GetTorrentContentsReturns,
                          NEKO_NAMESPACE::JsonSerializer)
};  // the end of Get torrent pieces states Returns

// define struct for Get torrent pieces states
struct GetTorrentPiecesStatesParameters {
    std::string hash =
        {};  // The hash of the torrent you want to get the pieces' states of
    NEKO_SERIALIZER(hash)
    NEKO_DECLARE_PROTOCOL(GetTorrentPiecesStatesParameters,
                          NEKO_NAMESPACE::ParametersSerializer)
};  // the end of Get torrent pieces states Parameters

// define struct for Get torrent pieces hashes
struct GetTorrentPiecesHashesParameters {
    std::string hash =
        {};  // The hash of the torrent you want to get the pieces' hashes of
    NEKO_SERIALIZER(hash)
    NEKO_DECLARE_PROTOCOL(GetTorrentPiecesHashesParameters,
                          NEKO_NAMESPACE::ParametersSerializer)
};  // the end of Get torrent pieces hashes Parameters

// define struct for Pause torrents
struct PauseTorrentsParameters {
    std::string hashes =
        {};  // The hashes of the torrents you want to pause. `hashes` can
             // contain multiple hashes separated by `\|`, to pause multiple
             // torrents, or set to `all`, to pause all torrents.
    NEKO_SERIALIZER(hashes)
    NEKO_DECLARE_PROTOCOL(PauseTorrentsParameters,
                          NEKO_NAMESPACE::ParametersSerializer)
};  // the end of Pause torrents Parameters

// define struct for Resume torrents
struct ResumeTorrentsParameters {
    std::string hashes =
        {};  // The hashes of the torrents you want to resume. `hashes` can
             // contain multiple hashes separated by `\|`, to resume multiple
             // torrents, or set to `all`, to resume all torrents.
    NEKO_SERIALIZER(hashes)
    NEKO_DECLARE_PROTOCOL(ResumeTorrentsParameters,
                          NEKO_NAMESPACE::ParametersSerializer)
};  // the end of Resume torrents Parameters

// define struct for Delete torrents
struct DeleteTorrentsParameters {
    std::string hashes =
        {};  // The hashes of the torrents you want to delete. `hashes` can
             // contain multiple hashes separated by `\|`, to delete multiple
             // torrents, or set to `all`, to delete all torrents.
    NEKO_SERIALIZER(hashes)
    NEKO_DECLARE_PROTOCOL(DeleteTorrentsParameters,
                          NEKO_NAMESPACE::ParametersSerializer)
};  // the end of Delete torrents Parameters

// define struct for Recheck torrents
struct RecheckTorrentsParameters {
    std::string hashes =
        {};  // The hashes of the torrents you want to recheck. `hashes` can
             // contain multiple hashes separated by `\|`, to recheck multiple
             // torrents, or set to `all`, to recheck all torrents.
    NEKO_SERIALIZER(hashes)
    NEKO_DECLARE_PROTOCOL(RecheckTorrentsParameters,
                          NEKO_NAMESPACE::ParametersSerializer)
};  // the end of Recheck torrents Parameters

// define struct for Reannounce torrents
struct ReannounceTorrentsParameters {
    std::string hashes =
        {};  // The hashes of the torrents you want to reannounce. `hashes` can
             // contain multiple hashes separated by `\|`, to reannounce
             // multiple torrents, or set to `all`, to reannounce all torrents.
    NEKO_SERIALIZER(hashes)
    NEKO_DECLARE_PROTOCOL(ReannounceTorrentsParameters,
                          NEKO_NAMESPACE::ParametersSerializer)
};  // the end of Reannounce torrents Parameters

// define struct for Edit trackers
struct EditTrackersParameters {
    std::string hash    = {};  // The hash of the torrent
    std::string origUrl = {};  // The tracker URL you want to edit
    std::string newUrl  = {};  // The new URL to replace the `origUrl`
    NEKO_SERIALIZER(hash, origUrl, newUrl)
    NEKO_DECLARE_PROTOCOL(EditTrackersParameters,
                          NEKO_NAMESPACE::ParametersSerializer)
};  // the end of Edit trackers Parameters

// define struct for Remove trackers
struct RemoveTrackersParameters {
    std::string hash = {};  // The hash of the torrent
    std::string urls = {};  // URLs to remove, separated by `\|`
    NEKO_SERIALIZER(hash, urls)
    NEKO_DECLARE_PROTOCOL(RemoveTrackersParameters,
                          NEKO_NAMESPACE::ParametersSerializer)
};  // the end of Remove trackers Parameters

// define struct for Add peers
struct AddPeersParameters {
    std::string hashes = {};  // The hash of the torrent, or multiple hashes
                              // separated by a pipe `\|`
    std::string peers =
        {};  // The peer to add, or multiple peers separated by a pipe `\|`.
             // Each peer is a colon-separated `host:port`
    NEKO_SERIALIZER(hashes, peers)
    NEKO_DECLARE_PROTOCOL(AddPeersParameters, NEKO_NAMESPACE::ParametersSerializer)
};  // the end of Add peers Parameters

// define struct for Increase torrent priority
struct IncreaseTorrentPriorityParameters {
    std::string hashes =
        {};  // The hashes of the torrents you want to increase the priority of.
             // `hashes` can contain multiple hashes separated by `\|`, to
             // increase the priority of multiple torrents, or set to `all`, to
             // increase the priority of all torrents.
    NEKO_SERIALIZER(hashes)
    NEKO_DECLARE_PROTOCOL(IncreaseTorrentPriorityParameters,
                          NEKO_NAMESPACE::ParametersSerializer)
};  // the end of Increase torrent priority Parameters

// define struct for Decrease torrent priority
struct DecreaseTorrentPriorityParameters {
    std::string hashes =
        {};  // The hashes of the torrents you want to decrease the priority of.
             // `hashes` can contain multiple hashes separated by `\|`, to
             // decrease the priority of multiple torrents, or set to `all`, to
             // decrease the priority of all torrents.
    NEKO_SERIALIZER(hashes)
    NEKO_DECLARE_PROTOCOL(DecreaseTorrentPriorityParameters,
                          NEKO_NAMESPACE::ParametersSerializer)
};  // the end of Decrease torrent priority Parameters

// define struct for Maximal torrent priority
struct MaximalTorrentPriorityParameters {
    std::string hashes =
        {};  // The hashes of the torrents you want to set to the maximum
             // priority. `hashes` can contain multiple hashes separated by
             // `\|`, to set multiple torrents to the maximum priority, or set
             // to `all`, to set all torrents to the maximum priority.
    NEKO_SERIALIZER(hashes)
    NEKO_DECLARE_PROTOCOL(MaximalTorrentPriorityParameters,
                          NEKO_NAMESPACE::ParametersSerializer)
};  // the end of Maximal torrent priority Parameters

// define struct for Minimal torrent priority
struct MinimalTorrentPriorityParameters {
    std::string hashes =
        {};  // The hashes of the torrents you want to set to the minimum
             // priority. `hashes` can contain multiple hashes separated by
             // `\|`, to set multiple torrents to the minimum priority, or set
             // to `all`, to set all torrents to the minimum priority.
    NEKO_SERIALIZER(hashes)
    NEKO_DECLARE_PROTOCOL(MinimalTorrentPriorityParameters,
                          NEKO_NAMESPACE::ParametersSerializer)
};  // the end of Minimal torrent priority Parameters

// define struct for Set file priority
struct SetFilePriorityParameters {
    std::string hash  = {};  // The hash of the torrent
    std::string id    = {};  // File ids, separated by `\|`
    uint64_t priority = {};  // File priority to set (consult [torrent contents
                             // API](#get-torrent-contents) for possible values)
    NEKO_SERIALIZER(hash, id, priority)
    NEKO_DECLARE_PROTOCOL(SetFilePriorityParameters,
                          NEKO_NAMESPACE::ParametersSerializer)
};  // the end of Set file priority Parameters

// define struct for Set torrent share limit
struct SetTorrentShareLimitParameters {
    int64_t hashes = {};  // The hashes of the torrents for which you want to
                          // set the share limits. Multiple hashes need to be
                          // separated by `\|` or set to `all`.
    double ratioLimit =
        {};  // The maximum seeding ratio for the torrent. `-2` means the global
             // limit should be used, `-1` means no limit.
    int64_t seedingTimeLimit =
        {};  // The maximum seeding time (minutes) for the torrent. `-2` means
             // the global limit should be used, `-1` means no limit.
    int64_t inactiveSeedingTimeLimit =
        {};  // The maximum amount of time (minutes) the torrent is allowed to
             // seed while being inactive. `-2` means the global limit should be
             // used, `-1` means no limit.
    NEKO_SERIALIZER(hashes, ratioLimit, seedingTimeLimit,
                    inactiveSeedingTimeLimit)
    NEKO_DECLARE_PROTOCOL(SetTorrentShareLimitParameters,
                          NEKO_NAMESPACE::ParametersSerializer)
};  // the end of Set torrent share limit Parameters

// define struct for Toggle sequential download
struct ToggleSequentialDownloadParameters {
    std::string hashes =
        {};  // The hashes of the torrents you want to toggle sequential
             // download for. `hashes` can contain multiple hashes separated by
             // `\|`, to toggle sequential download for multiple torrents, or
             // set to `all`, to toggle sequential download for all torrents.
    NEKO_SERIALIZER(hashes)
    NEKO_DECLARE_PROTOCOL(ToggleSequentialDownloadParameters,
                          NEKO_NAMESPACE::ParametersSerializer)
};  // the end of Toggle sequential download Parameters

// define struct for Set first last piece priority
struct SetFirstLastPiecePriorityParameters {
    std::string hashes =
        {};  // The hashes of the torrents you want to toggle the first/last
             // piece priority for. `hashes` can contain multiple hashes
             // separated by `\|`, to toggle the first/last piece priority for
             // multiple torrents, or set to `all`, to toggle the first/last
             // piece priority for all torrents.
    NEKO_SERIALIZER(hashes)
    NEKO_DECLARE_PROTOCOL(SetFirstLastPiecePriorityParameters,
                          NEKO_NAMESPACE::ParametersSerializer)
};  // the end of Set first last piece priority Parameters

// define struct for Rename file
struct RenameFileParameters {
    std::string hash    = {};  // The hash of the torrent
    std::string oldPath = {};  // The old path of the torrent
    std::string newPath = {};  // The new path to use for the file
    NEKO_SERIALIZER(hash, oldPath, newPath)
    NEKO_DECLARE_PROTOCOL(RenameFileParameters, NEKO_NAMESPACE::ParametersSerializer)
};  // the end of Rename file Parameters

// define struct for Rename folder
struct RenameFolderParameters {
    std::string hash    = {};  // The hash of the torrent
    std::string oldPath = {};  // The old path of the torrent
    std::string newPath = {};  // The new path to use for the file
    NEKO_SERIALIZER(hash, oldPath, newPath)
    NEKO_DECLARE_PROTOCOL(RenameFolderParameters,
                          NEKO_NAMESPACE::ParametersSerializer)
};  // the end of Rename folder Parameters

// define struct for Start search
struct StartSearchParameters {
    std::string pattern = {};  // Pattern to search for (e.g. "Ubuntu 18.04")
    std::string plugins =
        {};  // Plugins to use for searching (e.g. "legittorrents"). Supports
             // multiple plugins separated by `\|`. Also supports `all` and
             // `enabled`
    std::string category =
        {};  // Categories to limit your search to (e.g. "legittorrents").
             // Available categories depend on the specified `plugins`. Also
             // supports `all`
    NEKO_SERIALIZER(pattern, plugins, category)
    NEKO_DECLARE_PROTOCOL(StartSearchParameters, NEKO_NAMESPACE::ParametersSerializer)
};  // the end of Start search Parameters

// define struct for Stop search
struct StopSearchParameters {
    uint64_t id = {};  // ID of the search job
    NEKO_SERIALIZER(id)
    NEKO_DECLARE_PROTOCOL(StopSearchParameters, NEKO_NAMESPACE::ParametersSerializer)
};  // the end of Stop search Parameters

// define struct for Get search status
struct GetSearchStatusParameters {
    uint64_t id = {};  // ID of the search job. If not specified, all search
                       // jobs are returned
    NEKO_SERIALIZER(id)
    NEKO_DECLARE_PROTOCOL(GetSearchStatusParameters,
                          NEKO_NAMESPACE::ParametersSerializer)
};  // the end of Get search status Parameters

// define struct for Get search results
struct GetSearchResultsParameters {
    uint64_t id = {};  // ID of the search job
    uint64_t limit =
        {};  // max number of results to return. 0 or negative means no limit
    uint64_t offset =
        {};  // result to start at. A negative number means count backwards
             // (e.g. `-2` returns the 2 most recent results)
    NEKO_SERIALIZER(id, limit, offset)
    NEKO_DECLARE_PROTOCOL(GetSearchResultsParameters,
                          NEKO_NAMESPACE::ParametersSerializer)
};  // the end of Get search results Parameters

// define struct for Delete search
struct DeleteSearchParameters {
    uint64_t id = {};  // ID of the search job
    NEKO_SERIALIZER(id)
    NEKO_DECLARE_PROTOCOL(DeleteSearchParameters,
                          NEKO_NAMESPACE::ParametersSerializer)
};  // the end of Delete search Parameters

// define struct for Install search plugin
struct InstallSearchPluginParameters {
    std::string sources =
        {};  // Url or file path of the plugin to install (e.g.
             // "[https://raw.githubusercontent.com/qbittorrent/search-plugins/master/nova3/engines/legittorrents.py](https://raw.githubusercontent.com/qbittorrent/search-plugins/master/nova3/engines/legittorrents.py)").
             // Supports multiple sources separated by `\|`
    NEKO_SERIALIZER(sources)
    NEKO_DECLARE_PROTOCOL(InstallSearchPluginParameters,
                          NEKO_NAMESPACE::ParametersSerializer)
};  // the end of Install search plugin Parameters

// define struct for Uninstall search plugin
struct UninstallSearchPluginParameters {
    std::string names =
        {};  // Name of the plugin to uninstall (e.g. "legittorrents"). Supports
             // multiple names separated by `\|`
    NEKO_SERIALIZER(names)
    NEKO_DECLARE_PROTOCOL(UninstallSearchPluginParameters,
                          NEKO_NAMESPACE::ParametersSerializer)
};  // the end of Uninstall search plugin Parameters

// define struct for Enable search plugin
struct EnableSearchPluginParameters {
    std::string names =
        {};  // Name of the plugin to enable/disable (e.g. "legittorrents").
             // Supports multiple names separated by `\|`
    bool enable = {};  // Whether the plugins should be enabled
    NEKO_SERIALIZER(names, enable)
    NEKO_DECLARE_PROTOCOL(EnableSearchPluginParameters,
                          NEKO_NAMESPACE::ParametersSerializer)
};  // the end of Enable search plugin Parameters

struct Category {
    std::string name = {};  // Name of the category
    std::string path = {};  // Path of the category
    NEKO_SERIALIZER(name, path)
    NEKO_DECLARE_PROTOCOL(Category, NEKO_NAMESPACE::JsonSerializer)
};

// define struct for Get main data
struct GetMainDataReturns {
    int64_t rid = {};  // Response ID
    bool full_update =
        {};  // Whether the response contains all the data or partial data
    GetTorrentListReturns torrents =
        {};  // Property: torrent hash, value: same as [torrent
             // list](#get-torrent-list)
    std::vector<GetTorrentListReturns> torrents_removed =
        {};  // List of hashes of torrents removed since last request
    std::map<std::string, Category> categories =
        {};  // Info for categories added since last request
    std::vector<std::map<std::string, Category>> categories_removed =
        {};  // List of categories removed since last request
    std::vector<std::string> tags =
        {};  // List of tags added since last request
    std::vector<std::vector<std::string>> tags_removed =
        {};  // List of tags removed since last request
    GetGlobalTransferInfoReturns server_state = {};  // Global transfer info
    NEKO_SERIALIZER(rid, full_update, torrents, torrents_removed, categories,
                    categories_removed, tags, tags_removed, server_state)
    NEKO_DECLARE_PROTOCOL(GetMainDataReturns, NEKO_NAMESPACE::JsonSerializer)
};  // the end of Get torrent peers data Returns
