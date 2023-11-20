#pragma once


#define _DEBUG
#ifdef _DEBUG
#define prind(...) printf(__VA__ARGS__)
// #define print printf("File %s\nLine: %d\n\n", __FILE__, __LINE__);
#define print printf("%d\n", __LINE__);
#else
#define print(...)  
#endif


// void CheckOpenGLError(const char* stmt, const char* fname, int line)
// {
//     GLenum err = glGetError();
//     if (err != GL_NO_ERROR)
//     {
//         printf("OpenGL error %08x, at %s:%i - for %s\n", err, fname, line, stmt);
//         abort();
//     }
// }

#ifdef _DEBUG
    #define GL_CHECK(stmt) do { \
            stmt; \
            GLenum err = glGetError(); \
            if (err != GL_NO_ERROR)\
            {\
                printf("OpenGL error %08x, at %s:%i - for %s\n", err, __FILE__, __LINE__, #stmt); \
                abort(); \
            }\
        } while (0)
#else
    #define GL_CHECK(stmt) stmt
#endif