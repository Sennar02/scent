workspace "forgotten_blood"
    configurations { "debug", "release" }

    startproject "memory_test"

    pic "on"

    include "ext/glad"
    include "ext/GLFW"
    include "src/core"
