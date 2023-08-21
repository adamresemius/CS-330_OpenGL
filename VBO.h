#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glad/glad.h>

class VBO
{
public:
    GLuint ID;

    // Constructor that generates a Vertex Buffer Object and links it to vertices
    VBO(GLfloat* vertices, GLsizeiptr size);

    // Binds the VBO to the current context
    void Bind();

    // Unbinds the VBO from the current context
    void Unbind();

    // Deletes the VBO and frees the associated memory
    void Delete();
};

#endif
