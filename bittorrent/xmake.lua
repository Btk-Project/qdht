target("bittorrent")
    set_kind("static")
    add_includedirs("../modules/Ilias/include/", "../modules/NekoProtoTools/core/")
    add_files("./*.cpp")
target_end()


