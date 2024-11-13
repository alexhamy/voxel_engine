#ifndef SHADERCLASS_H
#define SHADERCLASS_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
    GLuint ID;

    // Constructor that builds the Shader Program from two shader source files
    Shader(const char* vertexFile, const char* fragmentFile);

    // Activate the Shader Program
    void Activate();
    // Delete the Shader Program
    void Delete();

    // Utility function to set a mat4 uniform in the shader
    void setMat4(const std::string& name, const glm::mat4& matrix) const;

    void setVec3(const std::string& name, const glm::vec3& vector) const;

private:
    // Utility function to check shader compilation/linking errors
    void compileErrors(unsigned int shader, const char* type);
};

#endif // SHADERCLASS_H
