#include "Diagnostics.h"
#include "ResShader.h"

namespace res {

void ResShader::m_PrintShaderErrorLog(GLuint shader)
{
    GLint log_size;
    char *log_buffer;

    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_size);
    log_buffer = (char*)malloc(log_size);

    glGetShaderInfoLog(shader, log_size, &log_size, log_buffer);
    fprintf(stderr, "Shader error : %s\n", log_buffer);

    free(log_buffer);
}

void ResShader::m_PrintProgramErrorLog(GLuint program)
{
    GLint log_size;
    char *log_buffer;

    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_size);
    log_buffer = (char*)malloc(log_size);

    glGetProgramInfoLog(program, log_size, &log_size, log_buffer);
    fprintf(stderr, "Shader error : %s\n", log_buffer);

    free(log_buffer);
}

void ResShader::m_LoadSources(
        const std::string& vsource,
        const std::string& fsource)
{
    GLint result;

    const char *vsource_array[1] { vsource.c_str() };
    const char *fsource_array[1] { fsource.c_str() };

    vshader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vshader, 1, vsource_array, NULL);
    glCompileShader(vshader);
    glGetShaderiv(vshader, GL_COMPILE_STATUS, &result);
    if (!result) {
        m_PrintShaderErrorLog(vshader);
        glDeleteShader(vshader);
        DIAG_ERROR_EXIT("Failed initializing GLSL vertex shader.\n");
    }

    DIAG_GL_ERROR;

    fshader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fshader, 1, fsource_array, NULL);
    glCompileShader(fshader);
    glGetShaderiv(fshader, GL_COMPILE_STATUS, &result);
    if (!result) {
        m_PrintShaderErrorLog(fshader);
        glDeleteShader(vshader);
        glDeleteShader(fshader);
        DIAG_ERROR_EXIT("Failed initializing GLSL fragment shader.\n");
    }

    DIAG_GL_ERROR;

    program = glCreateProgram();
    glAttachShader(program, vshader);
    glAttachShader(program, fshader);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &result);
    if (!result) {
        m_PrintProgramErrorLog(program);
        glDeleteShader(vshader);
        glDeleteShader(fshader);
        glDeleteProgram(program);
        DIAG_ERROR_EXIT("Failed initializing GLSL program.\n");
    }

    DIAG_GL_ERROR;

    glDetachShader(program, vshader);
    glDetachShader(program, fshader);
}

void ResShader::m_GetLocations()
{
    glUseProgram(program);

    model_loc = glGetUniformLocation(program, "uni_model");
    view_loc = glGetUniformLocation(program, "uni_view");
    projection_loc = glGetUniformLocation(program, "uni_projection");

    t_AssertLocations(model_loc, view_loc, projection_loc);
}

ResShader::ResShader(const std::string& vsource, const std::string& fsource)
{
    m_LoadSources(vsource, fsource);
    m_GetLocations();
}

ResShader::~ResShader()
{
    glDeleteShader(vshader);
    glDeleteShader(fshader);
    glDeleteProgram(program);
}

}
