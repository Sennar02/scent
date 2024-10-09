project "core"
    kind       "staticlib"
    language   "c++"
    cppdialect "c++14"

    includedirs { ".." }

    files {
        "expect.hpp",
        "types.hpp",
        "array.hpp",
        "str8.hpp",
        "buff.hpp",
        "writer.hpp",
        "alloc.hpp",
        "arena.hpp",
        "slice.hpp",
        "file.hpp",

        "str8.cpp",
        "buff.cpp",
        "writer.cpp",
        "alloc.cpp",
        "arena.cpp",
        "file.cpp",
    }

    filter { "configurations:debug" }
        symbols "on"

    filter { "configurations:release" }
        optimize "on"
