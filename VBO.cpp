#include "VBO.h"

// Constructor that generates a Vertex Buffer Object and links it to vertices
VBO::VBO(GLfloat* vertices, GLsizeiptr size)
{
    glGenBuffers(1, &ID);           // Generate a unique buffer ID
    glBindBuffer(GL_ARRAY_BUFFER, ID); // Bind the buffer to the GL_ARRAY_BUFFER target
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW); // Fill the buffer with vertex data
}

// Binds the VBO to the current context
void VBO::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, ID); // Bind the buffer to the GL_ARRAY_BUFFER target
}

// Unbinds the VBO from the current context
void VBO::Unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind the buffer by binding 0 to the GL_ARRAY_BUFFER target
}

// Deletes the VBO and frees the associated memory
void VBO::Delete()
{
    glDeleteBuffers(1, &ID); // Delete the buffer with the specified buffer ID
}
