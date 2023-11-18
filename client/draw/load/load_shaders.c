#include "load_shaders.h"

char* get_shader_code(const char* file_name)
{
    // printf("file_name == %s\n", file_name);
    char *shader_code = NULL;
    FILE *shader_file = fopen(file_name, "r");
    if(shader_file != NULL) {
        fseek(shader_file, 0, SEEK_END);
        long fileSize = ftell(shader_file);
        fseek(shader_file, 0, SEEK_SET);
        shader_code = (char*)calloc(fileSize + 1, 1);
        if(shader_code != NULL) {
            fread(shader_code, 1, fileSize, shader_file);
            shader_code[fileSize] = '\0';
        }
        fclose(shader_file);
    }
    else printf("Shader code == %s\n", shader_code);
    
    return shader_code;
}

void compile_and_check(GLuint shader_id, const char* shader_code)
{
    GLint result = GL_FALSE;
    int infoLogLength;

    // Компилируем шейдер
    const char* ptr = shader_code;
    glShaderSource(shader_id, 1, &ptr, NULL);
    glCompileShader(shader_id);
    
    // Проверяем результат компиляции шейдера
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
    glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &infoLogLength);

    // #ifdef _DEBUG
    if(infoLogLength > 0) {
        char *vertexShaderErrorMessage = (char*)malloc(infoLogLength + 1);
        glGetShaderInfoLog(shader_id, infoLogLength, NULL, vertexShaderErrorMessage);
        printf("%s\n", vertexShaderErrorMessage);
        free(vertexShaderErrorMessage);
    }
    // #endif
}

GLuint load_shaders_geom(const char * vertex_file_path, const char * geometry_file_path, const char * fragment_file_path) 
{
    // Создаем шейдерные объекты вершинного и фрагментного шейдеров
    GLuint vertexShaderID   = glCreateShader(GL_VERTEX_SHADER);
    GLuint geometryShaderID = glCreateShader(GL_GEOMETRY_SHADER);
    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    
    // Читаем код шейдеров из файла
    char *vertexShaderCode   = get_shader_code(vertex_file_path  );
    char *geometryShaderCode = get_shader_code(geometry_file_path);
    char *fragmentShaderCode = get_shader_code(fragment_file_path);

    compile_and_check(vertexShaderID  , vertexShaderCode  );
    compile_and_check(geometryShaderID, geometryShaderCode);
    compile_and_check(fragmentShaderID, fragmentShaderCode);
    // printf("%s\nNEW\n%s\nEND\n", vertexShaderCode, fragmentShaderCode);

    // Связываем вершинный и фрагментный шейдеры в программу шейдеров
    GLuint programID = glCreateProgram();
    glAttachShader(programID, vertexShaderID  );
    glAttachShader(programID, geometryShaderID);
    glAttachShader(programID, fragmentShaderID);
    glLinkProgram(programID);


    GLint result = GL_FALSE;
    int infoLogLength;
    // Проверяем результат связывания программы шейдеров
    glGetProgramiv(programID, GL_LINK_STATUS, &result);
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if(infoLogLength > 0) {
        char *programErrorMessage = (char*)malloc(infoLogLength + 1);
        glGetProgramInfoLog(programID, infoLogLength, NULL, programErrorMessage);
        printf("%s\n", programErrorMessage);
        free(programErrorMessage);
    }

    // Освобождаем ресурсы
    if(vertexShaderCode   != NULL)
        free(vertexShaderCode);
    if(geometryShaderCode != NULL)
        free(geometryShaderCode);
    if(fragmentShaderCode != NULL)
        free(fragmentShaderCode);
    glDeleteShader(vertexShaderID  );
    glDeleteShader(geometryShaderID);
    glDeleteShader(fragmentShaderID);

    return programID;
}


GLuint load_shaders(const char * vertex_file_path, /*const char * geometry_file_path,*/ const char * fragment_file_path)
{
    // Создаем шейдерные объекты вершинного и фрагментного шейдеров
    GLuint vertexShaderID   = glCreateShader(GL_VERTEX_SHADER);
    // GLuint geometryShaderID = glCreateShader(GL_GEOMETRY_SHADER);
    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    
    // Читаем код шейдеров из файла
    char *vertexShaderCode   = get_shader_code(vertex_file_path  );
    // char *geometryShaderCode = get_shader_code(geometry_file_path);
    char *fragmentShaderCode = get_shader_code(fragment_file_path);

    compile_and_check(vertexShaderID  , vertexShaderCode  );
    // compile_and_check(geometryShaderID, geometryShaderCode);
    compile_and_check(fragmentShaderID, fragmentShaderCode);
    // printf("%s\nNEW\n%s\nEND\n", vertexShaderCode, fragmentShaderCode);

    // Связываем вершинный и фрагментный шейдеры в программу шейдеров
    GLuint programID = glCreateProgram();
    glAttachShader(programID, vertexShaderID  );
    // glAttachShader(programID, geometryShaderID);
    glAttachShader(programID, fragmentShaderID);
    glLinkProgram(programID);


    GLint result = GL_FALSE;
    int infoLogLength;
    // Проверяем результат связывания программы шейдеров
    glGetProgramiv(programID, GL_LINK_STATUS, &result);
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if(infoLogLength > 0) {
        char *programErrorMessage = (char*)malloc(infoLogLength + 1);
        glGetProgramInfoLog(programID, infoLogLength, NULL, programErrorMessage);
        printf("%s\n", programErrorMessage);
        free(programErrorMessage);
    }

    // Освобождаем ресурсы
    if(vertexShaderCode   != NULL)
        free(vertexShaderCode);
    // if(geometryShaderCode != NULL)
    //     free(geometryShaderCode);
    if(fragmentShaderCode != NULL)
        free(fragmentShaderCode);
    glDeleteShader(vertexShaderID  );
    // glDeleteShader(geometryShaderID);
    glDeleteShader(fragmentShaderID);

    return programID;
}