workspace "forgotten_blood"
    configurations { "debug", "release" }
    architecture "x86_64"

    targetdir "%{wks.location}/out/%{prj.name}"
    objdir    "%{wks.location}/out/obj/%{prj.name}"

    pic "on"

    include "src/core"

    include "ext/glad"
    include "ext/GLFW"
