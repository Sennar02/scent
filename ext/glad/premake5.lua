project "glad"
    kind     "StaticLib"
    language "C"

    includedirs { "include"  }

    files {
        "include/KHR/khrplatform.h",
        "include/glad/glad.h",

        "src/glad.c",
    }
