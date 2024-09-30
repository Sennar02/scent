project "core"
    kind       "staticlib"
    language   "c++"
    cppdialect "c++11"

    targetdir "%{wks.location}/bin/%{prj.name}"
    objdir    "%{wks.location}/obj/%{prj.name}"

    files {
        "assert.hpp",
        "types.hpp",
        "buffer.hpp",
        "region.hpp",
        "memory.hpp",

        "buffer.cpp",
        "region.cpp",
        "memory.cpp",
    }

    filter { "configurations:debug" }
        symbols "on"

    filter { "configurations:release" }
        optimize "on"

project "opengl_test"
    kind       "consoleapp"
    language   "c++"
    cppdialect "c++11"

    targetdir "%{wks.location}/bin/%{prj.name}"
    objdir    "%{wks.location}/obj/%{prj.name}"

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

    targetdir "%{wks.location}/bin/%{prj.name}"
    objdir    "%{wks.location}/obj/%{prj.name}"

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
