project "core"
    kind       "staticlib"
    language   "c++"
    cppdialect "c++11"

    files {
        "assert.hpp",
        "types.hpp",
        "arena.hpp",
        "memory.hpp",

        "arena.cpp",
    }

    filter { "configurations:debug" }
        symbols "on"

    filter { "configurations:release" }
        optimize "on"

project "opengl_test"
    kind       "consoleapp"
    language   "c++"
    cppdialect "c++11"

    includedirs {
        "../../ext/glad/include",
        "../../ext/GLFW/include",
    }

    links { "core", "glad", "GLFW" }

    files {
        "main_opengl.cpp",
    }

    filter { "configurations:debug" }
        symbols "on"

    filter { "configurations:release" }
        optimize "on"

project "memory_test"
    kind       "consoleapp"
    language   "c++"
    cppdialect "c++11"

    includedirs {
        "../../ext/glad/include",
        "../../ext/GLFW/include",
    }

    links { "core", "glad", "GLFW" }

    files {
        "main_memory.cpp",
    }

    filter { "configurations:debug" }
        symbols "on"

    filter { "configurations:release" }
        optimize "on"
