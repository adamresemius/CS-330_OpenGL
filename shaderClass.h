#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

// Function to read the contents of a text file and return them as a string
std::string get_file_contents(const char* filename);

class Shader
{
public:
    // Reference ID of the Shader Program
    GLuint ID;

    // Constructor that builds the Shader Program from two different shaders
    Shader(const char* vertexFile, const char* fragmentFile);

    // Activates the Shader Program
    void Activate();

    // Deletes the Shader Program
    void Delete();

private:
    // Checks if the different Shaders have compiled properly
    void compileErrors(unsigned int shader, const char* type);
};

#endif
