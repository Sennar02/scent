project('scent', 'cpp',
    default_options: [
        'cpp_std=c++11',
        'warning_level=3',
        'werror=true',
    ],
    version: '0.1.0',
)

cpp = meson.get_compiler('cpp')

link = [cpp.find_library('SDL3')]

executable('scent_main',
    sources: [
        'src/main.cpp',
        'src/alloc.cpp',
        'src/empty_alloc.cpp',
        'src/arena_alloc.cpp',
        'src/clock.cpp',
        'src/window.cpp',
        'src/keyboard.cpp',
        'src/application.cpp',
    ],
    dependencies: link,
)
