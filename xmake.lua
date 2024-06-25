add_rules("mode.debug", "mode.release")
add_requires("qt6base", "spdlog", "rapidjson", "zlib")

includes("bittorrent")
set_languages("c++20")

add_defines("ILIAS_COROUTINE_LIFETIME_CHECK")

target("qdht")
    add_rules("qt.quickapp")
        if is_plat("linux") then 
        add_cxxflags("-fcoroutines")
    end
    if is_plat("windows") then
        add_files("./modules/Ilias/include/ilias_iocp.cpp")
    end
    add_packages("qt6base", "zlib", "spdlog", "rapidjson")
    add_defines("NEKO_PROTO_STATIC")
    add_includedirs("./modules/Ilias/include/", "./modules/NekoProtoTools/core/")
    add_files("./modules/NekoProtoTools/src/proto_base.cpp")
    add_files("bittorrent/session.cpp")
    add_headerfiles("src/*.h")
    add_files("src/*.cpp")
    add_files("src/qml.qrc")
target_end()

target("test_bittorrent")
    set_kind("binary")
    if is_plat("linux") then 
        add_cxxflags("-fcoroutines")
    end
    if is_plat("windows") then
        add_files("./modules/Ilias/include/ilias_iocp.cpp")
    end
    add_deps("bittorrent")
    add_packages("zlib", "spdlog", "rapidjson")
    add_defines("NEKO_PROTO_STATIC")
    add_includedirs("./modules/Ilias/include/", "./modules/NekoProtoTools/core/")
    add_files("./modules/NekoProtoTools/src/proto_base.cpp")
    add_files("tests/test_bittorrent.cpp")
target_end()

--
-- If you want to known more usage about xmake, please see https://xmake.io
--
-- ## FAQ
--
-- You can enter the project directory firstly before building project.
--
--   $ cd projectdir
--
-- 1. How to build project?
--
--   $ xmake
--
-- 2. How to configure project?
--
--   $ xmake f -p [macosx|linux|iphoneos ..] -a [x86_64|i386|arm64 ..] -m [debug|release]
--
-- 3. Where is the build output directory?
--
--   The default output directory is `./build` and you can configure the output directory.
--
--   $ xmake f -o outputdir
--   $ xmake
--
-- 4. How to run and debug target after building project?
--
--   $ xmake run [targetname]
--   $ xmake run -d [targetname]
--
-- 5. How to install target to the system directory or other output directory?
--
--   $ xmake install
--   $ xmake install -o installdir
--
-- 6. Add some frequently-used compilation flags in xmake.lua
--
-- @code
--    -- add debug and release modes
--    add_rules("mode.debug", "mode.release")
--
--    -- add macro definition
--    add_defines("NDEBUG", "_GNU_SOURCE=1")
--
--    -- set warning all as error
--    set_warnings("all", "error")
--
--    -- set language: c99, c++11
--    set_languages("c99", "c++11")
--
--    -- set optimization: none, faster, fastest, smallest
--    set_optimize("fastest")
--
--    -- add include search directories
--    add_includedirs("/usr/include", "/usr/local/include")
--
--    -- add link libraries and search directories
--    add_links("tbox")
--    add_linkdirs("/usr/local/lib", "/usr/lib")
--
--    -- add system link libraries
--    add_syslinks("z", "pthread")
--
--    -- add compilation and link flags
--    add_cxflags("-stdnolib", "-fno-strict-aliasing")
--    add_ldflags("-L/usr/local/lib", "-lpthread", {force = true})
--
-- @endcode
--

