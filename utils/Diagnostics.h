#ifndef DIAGNOSTICS_H
#define DIAGNOSTICS_H

#include <cstdio>
#include <cassert>

#define DIAG_TRACE std::fprintf(stderr, "In function [%s] %s:%d\n", __func__, __FILE__, __LINE__)

#define DIAG_MESSAGE(...) std::fprintf(stderr, __VA_ARGS__)

#define DIAG_ERROR_EXIT(...)\
    do {\
        std::fprintf(stderr, __VA_ARGS__);\
        exit(1);\
    } while(0)

#define DIAG_ASSERT(macro_arg_condition) assert(macro_arg_condition)

#define DIAG_GL_ERROR \
    do {\
        GLenum error = glGetError();\
        if (error == GL_NO_ERROR) {\
            break;\
        } else {\
            switch (error) {\
            case GL_INVALID_ENUM:\
                DIAG_ERROR_EXIT("OpenGL Error : invalid enum.\n");\
                break;\
            case GL_INVALID_VALUE:\
                DIAG_ERROR_EXIT("OpenGL Error : invalid value.\n");\
                break;\
            case GL_INVALID_OPERATION:\
                DIAG_ERROR_EXIT("OpenGL Error : invalid operation.\n");\
                break;\
            case GL_INVALID_FRAMEBUFFER_OPERATION:\
                DIAG_ERROR_EXIT("OpenGL Error : invalid framebuffer operation.\n");\
                break;\
            case GL_OUT_OF_MEMORY:\
                DIAG_ERROR_EXIT("OpenGL Error : out of memory.\n");\
                break;\
            }\
        }\
    } while(0);

#endif
