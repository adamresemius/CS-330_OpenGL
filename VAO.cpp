#include "VAO.h"

// Constructor that generates a VAO ID
VAO::VAO()
{
    glGenVertexArrays(1, &ID); // Generate a unique VAO ID
}

// Links a VBO Attribute such as a position or color to the VAO
void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
    VBO.Bind(); // Bind the VBO to set its attributes
    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset); // Link the VBO attribute to the VAO
    glEnableVertexAttribArray(layout); // Enable the VAO attribute
    VBO.Unbind(); // Unbind the VBO
}

// Binds the VAO
void VAO::Bind()
{
    glBindVertexArray(ID); // Bind the VAO
}

// Unbinds the VAO
void VAO::Unbind()
{
    glBindVertexArray(0); // Unbind the VAO by binding 0
}

// Deletes the VAO
void VAO::Delete()
{
    glDeleteVertexArrays(1, &ID); // Delete the VAO with the specified ID
}
