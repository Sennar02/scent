project "glad"
    kind     "StaticLib"
    language "C"

    targetdir "%{wks.location}/bin/%{prj.name}"
    objdir    "%{wks.location}/obj/%{prj.name}"

    includedirs { "include"  }

    files {
        "src/glad.c",
    }
