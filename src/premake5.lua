include "core"

project "test_opengl"
    kind       "consoleapp"
    language   "c++"
    cppdialect "c++14"

    includedirs {
        "../ext/glad/include",
        "../ext/GLFW/include",
        ".",
    }

    links { "core", "glad", "GLFW" }

    files {
        "test_opengl.cpp",
    }

    filter { "configurations:debug" }
        symbols "on"

    filter { "configurations:release" }
        optimize "on"

project "test_memory"
    kind       "consoleapp"
    language   "c++"
    cppdialect "c++14"

    includedirs { "." }

    links { "core" }

    files {
        "test_memory.cpp",
    }

    filter { "configurations:debug" }
        symbols "on"

    filter { "configurations:release" }
        optimize "on"

project "test_file"
    kind       "consoleapp"
    language   "c++"
    cppdialect "c++14"

    includedirs { "." }

    links { "core" }

    files {
        "test_file.cpp",
    }

    filter { "configurations:debug" }
        symbols "on"

    filter { "configurations:release" }
        optimize "on"
