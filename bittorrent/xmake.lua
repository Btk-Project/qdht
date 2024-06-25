target("bittorrent")
    set_kind("static")
    add_packages("spdlog", "rapidjson")
    add_defines("NEKO_PROTO_STATIC")
    add_includedirs("../modules/Ilias/include/", "../modules/NekoProtoTools/core/")
    add_files("./*.cpp")
target_end()


