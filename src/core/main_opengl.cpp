#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>

#include "expect.hpp"
#include "types.hpp"

#define LINE(x) \
    x "\n"

using namespace gr;

const byte* vert_module =
    LINE("#version 330 core")
    LINE("")
    LINE("layout (location = 0) in vec4 vert_point;")
    LINE("layout (location = 1) in vec4 vert_color;")
    LINE("")
    LINE("out vec4 frag_color;")
    LINE("")
    LINE("void main()")
    LINE("{")
    LINE(    "gl_Position = vert_point;")
    LINE(    "frag_color  = vert_color;")
    LINE("}");

const byte* frag_module =
    LINE("#version 330 core")
    LINE("")
    LINE("in  vec4 frag_color;")
    LINE("out vec4 disp_color;")
    LINE("")
    LINE("void main()")
    LINE("{")
    LINE(    "disp_color = frag_color;")
    LINE("}");

u32
shader_module_init(u32 type, const byte* source)
{
    u32 module = glCreateShader(type);
    i32 status = 0;

    glShaderSource(module, 1, &source, 0);
    glCompileShader(module);

    glGetShaderiv(module, GL_COMPILE_STATUS, &status);

    if ( status == GL_TRUE )
        return module;

    glDeleteShader(module);

    return 0;
}

void
shader_module_drop(u32 module)
{
    gr_expect(module != 0, "The module does not exist");

    glDeleteShader(module);
}

u32
shader_init()
{
    return glCreateProgram();
}

void
shader_give_module(u32 shader, u32 module)
{
    gr_expect(shader != 0, "The shader does not exist");
    gr_expect(module != 0, "The module does not exist");

    glAttachShader(shader, module);
}

bool
shader_link(u32 shader)
{
    i32 status = 0;

    gr_expect(shader != 0, "The shader does not exist");

    glLinkProgram(shader);
    glGetProgramiv(shader, GL_LINK_STATUS, &status);

    return status == GL_TRUE;
}

void
shader_drop(u32 shader)
{
    gr_expect(shader != 0, "The shader does not exist");

    glDeleteProgram(shader);
}

void
exit_callback()
{
    glfwTerminate();
}

int
main()
{
    atexit(&exit_callback);

    if ( glfwInit() == 0 )
        exit(EXIT_FAILURE);

    glfwSetErrorCallback([](int value, const char* error) {
        fprintf(stderr, "\x1b[31m[ERROR]\x1b[0m GLFW(%i): %s\n", value, error);
    });

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#if _MACOS
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(640, 360, "Prova OpenGL", 0, 0);

    if ( window == 0 )
        exit(EXIT_FAILURE);

    glfwMakeContextCurrent(window);

    if ( gladLoadGLLoader((GLADloadproc) &glfwGetProcAddress) == 0 )
        exit(EXIT_FAILURE);

    glDebugMessageCallback((GLDEBUGPROC) ([](u32, u32, u32 value, u32, i32, const byte* error, const void*) {
        fprintf(stderr, "\x1b[31m[ERROR]\x1b[0m OpenGL(%i): %s\n", value, error);
    }), 0);

    fprintf(stdout, "\x1b[34m[INFO]\x1b[0m OpenGL version: %s\n", glGetString(GL_VERSION));
    fprintf(stdout, "\x1b[34m[INFO]\x1b[0m GLFW version: %u.%u.%u\n",
        GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR, GLFW_VERSION_REVISION);

    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int, int, int) {
        if ( key == GLFW_KEY_ESCAPE )
            glfwSetWindowShouldClose(window, GLFW_TRUE);
    });

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow*, int width, int height) {
        glViewport(0, 0, width, height);
    });

    u32 layout = 0;
    u32 buffer = 0;

    f32 vertices[] = {
         0.0f,  0.5f, 1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
    };

    glGenVertexArrays(1, &layout);
    glGenBuffers(1, &buffer);

    glBindVertexArray(layout);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);

    glBufferData(GL_ARRAY_BUFFER, 15 * sizeof(f32), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(f32), 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(f32), (void*) (2 * sizeof(f32)));

    u32 shader = shader_init();
    u32 vert   = shader_module_init(GL_VERTEX_SHADER, vert_module);
    u32 frag   = shader_module_init(GL_FRAGMENT_SHADER, frag_module);

    shader_give_module(shader, vert);
    shader_give_module(shader, frag);

    if ( shader_link(shader) == false )
        exit(EXIT_FAILURE);

    shader_module_drop(vert);
    shader_module_drop(frag);

    glUseProgram(shader);

    while ( glfwWindowShouldClose(window) == 0 ) {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    exit(EXIT_SUCCESS);
}
