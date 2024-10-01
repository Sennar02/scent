project "glad"
    kind     "StaticLib"
    language "C"

    includedirs { "include"  }

    files {
        "src/glad.c",
    }
