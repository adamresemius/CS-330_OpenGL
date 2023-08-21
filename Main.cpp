#include <cmath>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb/stb_image.h>

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Camera.h"
/*
======================
WINDOW SIZE
======================
*/
const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 800;

/* 
=====================
LOAD TEXTURE
=====================
*/
// Function to load and create the texture
std::unique_ptr<unsigned char[]> loadTexture(const char* filename, int& width, int& height, int& numColCh)
{
    return std::unique_ptr<unsigned char[]>(stbi_load(filename, &width, &height, &numColCh, 0));
}

int main()
{
    /*
    ====================
    */
    // Initialize GLFW and create a window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Adam Resemius CS 330", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Load OpenGL functions using GLAD
    gladLoadGL();

    // Set the viewport
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    // Create the shader program
    Shader shaderProgram("default.vert", "default.frag");
    /*
    ==================
    Object One
    ==================
    */
    // Vertex data for the soundbar
    GLfloat soundbarVerts[] = {
        // Position            // Color              // Texture Coordinates
      -0.25f, -0.25f, -0.25f,        0.0f, 1.0f, 0.0f,    0.0f, 0.0f, 0.0f, // Bottom left back vertex
       0.25f * 8, -0.25f, -0.25f,    0.0f, 0.0f, 1.0f,    1.0f, 0.0f, 0.0f, // Bottom right back vertex
       0.25f * 8, -0.25f,  0.25f,    1.0f, 1.0f, 0.0f,    1.0f, 1.0f, 0.0f, // Bottom front right vertex
      -0.25f, -0.25f,  0.25f,        1.0f, 0.0f, 1.0f,    0.0f, 1.0f, 0.0f, // Bottom front left vertex
      -0.25f,  0.25f, -0.25f,        0.0f, 1.0f, 1.0f,    0.0f, 0.0f, 1.0f, // Top left back vertex
       0.25f * 8,  0.25f, -0.25f,    1.0f, 0.0f, 0.0f,    1.0f, 0.0f, 1.0f, // Top right back vertex
       0.25f * 8,  0.25f,  0.25f,    0.5f, 0.5f, 0.5f,    1.0f, 1.0f, 1.0f, // Top front right vertex
      -0.25f,  0.25f,  0.25f,        0.5f, 0.5f, 0.5f,    0.0f, 1.0f, 1.0f  // Top front left vertex
    };


    GLuint soundbarIndices[] = {
        0, 1, 2,    // Bottom face
        2, 3, 0,
        4, 5, 6,    // Top face
        6, 7, 4,
        0, 3, 7,    // Left face
        7, 4, 0,
        1, 2, 6,    // Right face
        6, 5, 1,
        3, 2, 6,    // Front face
        6, 7, 3,
        0, 1, 5,    // Back face
        5, 4, 0
    };

    /*
   ==================
   Object Two
   ==================
   */
    // Vertex data for the vase
    GLfloat vaseVerts[] = {
            // Position                // Color              // Texture Coordinates
            // Bottom face
            (-0.25f - 0.25f) * 4,  0.00f, (-0.25f) * 4, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, // Bottom left back vertex
            (0.25f - 0.25f) * 4,   0.00f, (-0.25f) * 4, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, // Bottom right back vertex
            (0.25f - 0.25f) * 4,   0.00f, (0.25f) * 4,  1.0f, 1.0f, 0.0f, 1.0f, 1.0f, // Bottom front right vertex
            (-0.25f - 0.25f) * 4,  0.00f, (0.25f) * 4,  1.0f, 0.0f, 1.0f, 0.0f, 1.0f, // Bottom front left vertex

            // Top face
            (-0.1875f - 0.25f) * 4,  0.75f * 4, (-0.1875f) * 4, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, // Top left back vertex
            (0.1875f - 0.25f) * 4,   0.75f * 4, (-0.1875f) * 4, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // Top right back vertex
            (0.1875f - 0.25f) * 4,   0.75f * 4, (0.1875f) * 4,  0.5f, 0.5f, 0.5f, 1.0f, 1.0f, // Top front right vertex
            (-0.1875f - 0.25f) * 4,  0.75f * 4, (0.1875f) * 4,  0.5f, 0.5f, 0.5f, 0.0f, 1.0f  // Top front left vertex
        };




    // Indices data for the vase
    GLuint vaseIndices[] = {
        0, 1, 2,    // Bottom face
        2, 3, 0,
        4, 5, 6,    // Top face
        6, 7, 4,
        0, 3, 7,    // Left face
        7, 4, 0,
        1, 2, 6,    // Right face
        6, 5, 1,
        3, 2, 6,    // Front face
        6, 7, 3,
        0, 1, 5,    // Back face
        5, 4, 0
    };


    //creating the entertainment Center based on measurements from the soundbar, this is going to be a plane:

    // Vertex data for the entertainment center
    GLfloat entertainmentCenterVerts[] = {
        // Position            // Color              // Texture Coordinates
        -0.25f * 1.33f, 0.0f, -0.25f , 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, // Bottom left back vertex
        0.25f * 1.33f, 0.0f, -0.25f , 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, // Bottom right back vertex
        0.25f * 1.33f, 0.0f, 0.25f * 3.5f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, // Bottom front right vertex
        -0.25f * 1.33f, 0.0f, 0.25f * 3.5f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, // Bottom front left vertex
    };

    // Indices data for the plane
    GLuint entertainmentCenterIndices[] = {
        0, 1, 2,    
        2, 3, 0
    };

    // Vertex data for the wall
    GLfloat wallVerts[] = {
        // Position            // Color              // Texture Coordinates
        0.25f * 1.33f, 0.0f, -0.25f , 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, // Bottom left back vertex
        0.5f * 1.33f,  0.0f, -0.25f , 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, // Bottom right back vertex
        0.5f * 1.33f,  2.5f * 0.5f, -0.25f , 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, // Bottom front right vertex
        0.25f * 1.33f, 2.5f * 0.5f, -0.25f , 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, // Bottom front left vertex
    };


    // Indices data for the wall
    GLuint wallIndices[] = {
        0, 1, 2,
        2, 3, 0
    };


    /*
   ==================
   Object Three
   ==================
   */
    // Vertex data for the lightswitch
    GLfloat lightswitchVerts[] = {
     // Position                // Color              // Texture Coordinates
        (-0.25f - 0.25f) * 4 - 0.25f * 4, 0.75f * 4 + (0.75f * 4 - 0.25f * 4) * 2, 0.0f, 0.8f, 0.8f, 0.8f, 0.0f, 0.0f, // Bottom left back vertex
        (0.25f - 0.25f) * 4 - 0.25f * 4,  0.75f * 4 + (0.75f * 4 - 0.25f * 4) * 2, 0.0f, 0.8f, 0.8f, 0.8f, 1.0f, 0.0f, // Bottom right back vertex
        (0.25f - 0.25f) * 4 - 0.25f * 4,  0.75f * 4 + (0.75f * 4 - 0.25f * 4) * 2, 0.1f * 4, 0.8f, 0.8f, 0.8f, 1.0f, 1.0f, // Bottom front right vertex
        (-0.25f - 0.25f) * 4 - 0.25f * 4, 0.75f * 4 + (0.75f * 4 - 0.25f * 4) * 2, 0.1f * 4, 0.8f, 0.8f, 0.8f, 0.0f, 1.0f, // Bottom front left vertex

        // Top face
        (-0.1875f - 0.25f) * 4 - 0.25f * 4,  0.75f * 4 + (0.75f * 4 - 0.25f * 4) * 2 + 0.1f * 4, (-0.1875f) * 4, 0.8f, 0.8f, 0.8f, 0.0f, 0.0f, // Top left back vertex
        (0.1875f - 0.25f) * 4 - 0.25f * 4,   0.75f * 4 + (0.75f * 4 - 0.25f * 4) * 2 + 0.1f * 4, (-0.1875f) * 4, 0.8f, 0.8f, 0.8f, 1.0f, 0.0f, // Top right back vertex
        (0.1875f - 0.25f) * 4 - 0.25f * 4,   0.75f * 4 + (0.75f * 4 - 0.25f * 4) * 2 + 0.1f * 4, (0.1875f) * 4, 0.8f, 0.8f, 0.8f, 1.0f, 1.0f, // Top front right vertex
        (-0.1875f - 0.25f) * 4 - 0.25f * 4,  0.75f * 4 + (0.75f * 4 - 0.25f * 4) * 2 + 0.1f * 4, (0.1875f) * 4, 0.8f, 0.8f, 0.8f, 0.0f, 1.0f  // Top front left vertex
    };

    GLuint lightswitchIndices[] = {
        0, 1, 2,    // Bottom face
        2, 3, 0,
        4, 5, 6,

    };

    /*
    ==================
    Object Four
    ==================
    */
    // Vertex data for the money tree stems
    GLfloat stemVerts[] = {
        // Stem 1
        -0.05f, 0.75f * 4, -0.05f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, // Bottom left back vertex
         0.05f, 0.75f * 4, -0.05f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, // Bottom right back vertex
         0.05f, 0.20f, -0.05f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, // Bottom front right vertex
         -0.05f, 0.20f, -0.05f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f // Bottom front left vertex


         // Stem 2
          
         -0.15f, 0.75f * 4, -0.15f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, // Bottom left back vertex
         0.15f, 0.75f * 4, -0.15f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, // Bottom right back vertex
         0.15f, 0.20f, -0.15f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, // Bottom front right vertex
         -0.15f, 0.20f, -0.15f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, // Bottom front left vertex

        // Stem 3
        // Adjust the y-coordinates and x-coordinate for the third stem
        -0.05f, 0.75f * 4, 0.05f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, // Bottom left back vertex
        0.05f, 0.75f * 4, 0.05f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, // Bottom right back vertex
        0.05f, 0.20f, 0.05f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, // Bottom front right vertex
        -0.05f, 0.20f, 0.05f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f // Bottom front left vertex
    };
    // Indices for the money tree stems
    GLuint stemIndices[] = {
        // Stem 1
        0, 1, 2,
        2, 3, 0,

        // Stem 2
        4, 5, 6,
        6, 7, 4,

        // Stem 3
        8, 9, 10,
        10, 11, 8
    };
    //Vertex data for the Tree Foilage
    GLfloat foliageVerts[] = {
        // Leaf 1
       -0.075f, 0.25f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
       -0.025f, 0.35f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
       0.0f, 0.40f, 0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f, 0.5f, 1.0f,
       0.025f, 0.35f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
       0.075f, 0.25f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,

        // Leaf 2
       -0.065f, 0.24f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
       -0.015f, 0.34f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
       0.01f, 0.39f, 0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f, 0.5f, 1.0f,
       0.035f, 0.34f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
       0.085f, 0.24f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,

        // Leaf 3
      -0.085f, 0.23f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,0.0f, 0.0f,
      -0.035f, 0.33f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
      0.0f, 0.38f, 0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,  0.5f, 1.0f,
      0.035f, 0.33f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
      0.085f, 0.23f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,

       
       // Leaf 4
      -0.095f, 0.22f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,0.0f, 0.0f,
      -0.045f, 0.32f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
      0.0f, 0.37f, 0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f, 0.5f, 1.0f,
      0.045f, 0.32f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
      0.095f, 0.22f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,

      // Leaf 5
      -0.080f, 0.26f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,0.0f, 0.0f,
      -0.030f, 0.36f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
      0.005f, 0.41f, 0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,  0.5f, 1.0f,
      0.030f, 0.36f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
      0.080f, 0.26f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,

     // Leaf 6
     -0.070f, 0.25f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,0.0f, 0.0f,
     -0.020f, 0.35f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
     0.015f, 0.40f, 0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f, 0.5f, 1.0f,
     0.040f, 0.35f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
     0.090f, 0.25f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,

     // Leaf 7
     -0.090f, 0.24f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,0.0f, 0.0f,
     -0.040f, 0.34f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
     0.005f, 0.39f, 0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,  0.5f, 1.0f,
     0.040f, 0.34f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
     0.090f, 0.24f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,

    // Leaf 8
    -0.100f, 0.23f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,0.0f, 0.0f,
    -0.050f, 0.33f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
    0.000f, 0.38f, 0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,0.5f, 1.0f,
    0.050f, 0.33f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,  1.0f, 1.0f,
    0.100f, 0.23f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,

    // Leaf 9
    -0.085f, 0.24f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,0.0f, 0.0f,
    -0.035f, 0.34f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 0.39f, 0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f, 0.5f, 1.0f,
    0.035f, 0.34f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    0.085f, 0.24f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,

    // Leaf 10
   -0.095f, 0.23f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,0.0f, 0.0f,
   -0.045f, 0.33f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 0.38f, 0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f, 0.5f, 1.0f,
    0.045f, 0.33f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    0.095f, 0.23f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,

    // Leaf 11
    -0.080f, 0.26f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,0.0f, 0.0f,
    -0.030f, 0.36f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
    0.005f, 0.41f, 0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,  0.5f, 1.0f,
    0.030f, 0.36f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    0.080f, 0.26f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,

    // Leaf 12
    -0.070f, 0.25f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,0.0f, 0.0f,
    -0.020f, 0.35f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
    0.015f, 0.40f, 0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,  0.5f, 1.0f,
    0.040f, 0.35f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,1.0f, 1.0f,
    0.090f, 0.25f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,

    // Leaf 13
    -0.090f, 0.24f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,0.0f, 0.0f,
    -0.040f, 0.34f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
    0.005f, 0.39f, 0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,  0.5f, 1.0f,
    0.040f, 0.34f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    0.090f, 0.24f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,

    // Leaf 14
   -0.100f, 0.23f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,0.0f, 0.0f,
   -0.050f, 0.33f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
   0.000f, 0.38f, 0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,  0.5f, 1.0f,
   0.050f, 0.33f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
   0.100f, 0.23f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,

   // Leaf 15
   -0.085f, 0.24f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
   -0.035f, 0.34f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
   0.0f, 0.39f, 0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f, 0.5f, 1.0f,
   0.035f, 0.34f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
   0.085f, 0.24f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,

   // Leaf 16
   -0.095f, 0.23f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
   -0.045f, 0.33f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 0.38f, 0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f, 0.5f, 1.0f,
  0.045f, 0.33f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
   0.095f, 0.23f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,

    };

    GLuint foliageIndices[] = {
        // Leaf 1
        0, 1, 2,
        0, 2, 3,
        0, 3, 4,

        // Leaf 2
        5, 6, 7,
        5, 7, 8,
        5, 8, 9,

        // Leaf 3
        10, 11, 12,
        10, 12, 13,
        10, 13, 14,

        // Leaf 4
        15, 16, 17,
        15, 17, 18,
        15, 18, 19,

        // Leaf 5
        20, 21, 22,
        20, 22, 23,
        20, 23, 24,

        // Leaf 6
        25, 26, 27,
        25, 27, 28,
        25, 28, 29,

        // Leaf 7
        30, 31, 32,
        30, 32, 33,
        30, 33, 34,

        // Leaf 8
        35, 36, 37,
        35, 37, 38,
        35, 38, 39,

        // Leaf 9
        40, 41, 42,
        40, 42, 43,
        40, 43, 44,

        // Leaf 10
        45, 46, 47,
        45, 47, 48,
        45, 48, 49,

        // Leaf 11
        50, 51, 52,
        50, 52, 53,
        50, 53, 54,

        // Leaf 12
        55, 56, 57,
        55, 57, 58,
        55, 58, 59,

        // Leaf 13
        60, 61, 62,
        60, 62, 63,
        60, 63, 64,

        // Leaf 14
        65, 66, 67,
        65, 67, 68,
        65, 68, 69,

        // Leaf 15
        70, 71, 72,
        70, 72, 73,
        70, 73, 74,

        // Leaf 16
        75, 76, 77,
        75, 77, 78,
        75, 78, 79,
    };


    //creating a loop to adjust all the randomized leave structure to match the stems coordinates:

    // Number of stems and leaves
    const int numStems = 3;
    const int numLeavesPerStem = 5;

    // Iterate over each stem and its corresponding leaves
    for (int i = 0; i < numStems; ++i) {
        GLfloat stemX = stemVerts[i * 16];   // stem x coordinate
        GLfloat stemY = stemVerts[i * 16 + 1]; // stem y coordinate
        GLfloat stemZ = stemVerts[i * 16 + 2]; // stem z coordinate

        for (int j = 0; j < numLeavesPerStem; ++j) {
            int leafIndex = i * numLeavesPerStem * 8 + j * 8; // index for leaf

            // Update leaf coordinates to match stem position
            foliageVerts[leafIndex] = stemX + foliageVerts[leafIndex];
            foliageVerts[leafIndex + 1] = stemY + foliageVerts[leafIndex + 1];
            foliageVerts[leafIndex + 2] = stemZ + foliageVerts[leafIndex + 2];
        }
    }


    // Create and set up the Vertex Array Object (VAO), Vertex Buffer Object (VBO), and Element Buffer Object (EBO)
    
    //soundbar
    VAO VAO1;
    VAO1.Bind();
    VBO VBO1(soundbarVerts, sizeof(soundbarVerts));
    EBO EBO1(soundbarIndices, sizeof(soundbarIndices));
    
    //vase
    VAO VAO2;
    VAO2.Bind();
    VBO VBO2(vaseVerts, sizeof(vaseVerts));
    EBO EBO2(vaseIndices, sizeof(vaseIndices));

    //entertainment center
    VAO VAO3;
    VAO3.Bind();
    VBO VBO3(entertainmentCenterVerts, sizeof(entertainmentCenterVerts));
    EBO EBO3(entertainmentCenterIndices, sizeof(entertainmentCenterIndices));

    //wall 
    VAO VAO4;
    VAO4.Bind();
    VBO VBO4(wallVerts, sizeof(wallVerts));
    EBO EBO4(wallIndices, sizeof(wallIndices));

  
    //lightswitch
    VAO VAO5;
    VAO5.Bind();
    VBO VBO5(lightswitchVerts, sizeof(lightswitchVerts));
    EBO EBO5(lightswitchIndices, sizeof(lightswitchIndices));

    //stem
    VAO VAO6;
    VAO6.Bind();
    VBO VBO6(stemVerts, sizeof(stemVerts));
    EBO EBO6(stemIndices, sizeof(stemIndices));

    //foilage
    VAO VAO7;
    VAO7.Bind();
    VBO VBO7(foliageVerts, sizeof(foliageVerts));
    EBO EBO7(foliageIndices, sizeof(foliageIndices));



    // Link vertex attributes
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);  // Coordinates
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));  // Colors
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));  // Texture Coordinates
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();
    VAO2.LinkAttrib(VBO2, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);  // Coordinates
    VAO2.LinkAttrib(VBO2, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));  // Colors
    VAO2.LinkAttrib(VBO2, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));  // Texture Coordinates
    VAO2.Unbind();
    VBO2.Unbind();
    EBO2.Unbind();
    VAO3.LinkAttrib(VBO3, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);  // Coordinates
    VAO3.LinkAttrib(VBO3, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));  // Colors
    VAO3.LinkAttrib(VBO3, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));  // Texture Coordinates
    VAO3.Unbind();
    VBO3.Unbind();
    EBO3.Unbind();
    VAO4.LinkAttrib(VBO4, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);          // Coordinates
    VAO4.LinkAttrib(VBO4, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));    // Colors
    VAO4.LinkAttrib(VBO4, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));    // Texture Coordinates
    VAO4.Unbind();
    VBO4.Unbind();
    EBO4.Unbind();
    VAO5.LinkAttrib(VBO4, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);          // Coordinates
    VAO5.LinkAttrib(VBO4, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));    // Colors
    VAO5.LinkAttrib(VBO4, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));    // Texture Coordinates
    VAO5.Unbind();
    VBO5.Unbind();
    EBO5.Unbind();
    VAO6.LinkAttrib(VBO4, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);          // Coordinates
    VAO6.LinkAttrib(VBO4, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));    // Colors
    VAO6.LinkAttrib(VBO4, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));    // Texture 
    VAO6.Unbind();
    VBO6.Unbind();
    EBO6.Unbind();
    VAO7.LinkAttrib(VBO4, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);          // Coordinates
    VAO7.LinkAttrib(VBO4, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));    // Colors
    VAO7.LinkAttrib(VBO4, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));    // Texture 
    VAO7.Unbind();
    VBO7.Unbind();
    EBO7.Unbind();


    // Load and create the texture for soundbar 
    int widthImg, heightImg, numColCh;
    std::unique_ptr<unsigned char[]> bytes = loadTexture("Recources/soundbar.png", widthImg, heightImg, numColCh);
    if (bytes == nullptr)
    {
        std::cout << "Failed to load texture" << std::endl;
        glfwTerminate();
        return -1;
    }

    GLuint texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthImg, heightImg, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes.get());
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Load and create the texture for the vase
    std::unique_ptr<unsigned char[]> bytesVase = loadTexture("Recources/vase.png", widthImg, heightImg, numColCh);
    if (bytesVase == nullptr)
    {
        std::cout << "Failed to load vase texture" << std::endl;
        glfwTerminate();
        return -1;
    }

    GLuint textureVase;
    glGenTextures(1, &textureVase);
    glActiveTexture(GL_TEXTURE1); // Use a different texture unit for the vase texture (e.g., GL_TEXTURE1)
    glBindTexture(GL_TEXTURE_2D, textureVase);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthImg, heightImg, 0, GL_RGB, GL_UNSIGNED_BYTE, bytesVase.get());
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Load and create the texture for the Entertainment Center
    std::unique_ptr<unsigned char[]> bytesEntertainmentCenter = loadTexture("Recources/entertainmentCenter.png", widthImg, heightImg, numColCh);
    if (bytesVase == nullptr)
    {
        std::cout << "Failed to load Entertianment Center texture" << std::endl;
        glfwTerminate();
        return -1;
    }

    GLuint textureEntertainmentCenter;
    glGenTextures(1, &textureEntertainmentCenter);
    glActiveTexture(GL_TEXTURE2); //  GL_TEXTURE2 is for entertianment center
    glBindTexture(GL_TEXTURE_2D, textureEntertainmentCenter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthImg, heightImg, 0, GL_RGB, GL_UNSIGNED_BYTE, bytesEntertainmentCenter.get());
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Load and create the texture for the wall
    std::unique_ptr<unsigned char[]> bytesWall = loadTexture("Recources/wall.png", widthImg, heightImg, numColCh);
    if (bytesWall == nullptr)
    {
        std::cout << "Failed to load wall texture" << std::endl;
        glfwTerminate();
        return -1;
    }

    GLuint textureWall;
    glGenTextures(1, &textureWall);
    glActiveTexture(GL_TEXTURE3); // GL_TEXTURE3 is for the wall
    glBindTexture(GL_TEXTURE_2D, textureWall);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthImg, heightImg, 0, GL_RGB, GL_UNSIGNED_BYTE, bytesWall.get());
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Load and create the texture for the Lightswitch
    std::unique_ptr<unsigned char[]> bytesLightswitch = loadTexture("Recources/lightSwitch.png", widthImg, heightImg, numColCh);
    if (bytesLightswitch == nullptr)
    {
        std::cout << "Failed to load Lightswitch texture" << std::endl;
        glfwTerminate();
        return -1;
    }

    GLuint textureLightswitch;
    glGenTextures(1, &textureLightswitch);
    glActiveTexture(GL_TEXTURE4); // Use a different texture unit for the lightswitch texture (e.g., GL_TEXTURE4)
    glBindTexture(GL_TEXTURE_2D, textureLightswitch);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthImg, heightImg, 0, GL_RGB, GL_UNSIGNED_BYTE, bytesVase.get());
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);


    // Load and create the texture for the Stem
    std::unique_ptr<unsigned char[]> bytesStem = loadTexture("Recources/stem.png", widthImg, heightImg, numColCh);
    if (bytesStem == nullptr)
    {
        std::cout << "Failed to load Stem texture" << std::endl;
        glfwTerminate();
        return -1;
    }

    GLuint textureStem;
    glGenTextures(1, &textureStem);
    glActiveTexture(GL_TEXTURE5); // Use a different texture unit for the lightswitch texture (e.g., GL_TEXTURE5)
    glBindTexture(GL_TEXTURE_2D, textureStem);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthImg, heightImg, 0, GL_RGB, GL_UNSIGNED_BYTE, bytesStem.get());
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Load and create the texture for the foilage
    std::unique_ptr<unsigned char[]> bytesFoilage = loadTexture("Recources/foilage.png", widthImg, heightImg, numColCh);
    if (bytesFoilage == nullptr)
    {
        std::cout << "Failed to load Foilage texture" << std::endl;
        glfwTerminate();
        return -1;
    }

    GLuint textureFoilage;
    glGenTextures(1, &textureFoilage);
    glActiveTexture(GL_TEXTURE6); // Use a different texture unit for the floiage texture (e.g., GL_TEXTURE6)
    glBindTexture(GL_TEXTURE_2D, textureStem);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthImg, heightImg, 0, GL_RGB, GL_UNSIGNED_BYTE, bytesFoilage.get());
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);


    // Setting the lighting parameters for the objects
    shaderProgram.Activate();
    glm::vec3 lightPos1 = glm::vec3(-1.0f, 2.0f, 0.5f); // Position of  key light
    glm::vec3 lightPos2 = glm::vec3(2.0f, 0.5f, -1.0f); // Position of fill light
    glm::vec3 greenishLightColor = glm::vec3(0.0f, 1.0f, 0.0f); // Greenish color for  key light
    glm::vec3 sunsetLightColor = glm::vec3(1.0f, 0.6f, 0.2f); // Orangeish hue color for the fill light (sunset
    float lightIntensity1 = 1.0f; // Intensity of the key light currently at 100%
    float lightIntensity2 = 0.15f; // Intensity of the fill light currently at 15%

    // Set the texture uniform in the shader for both soundbar and vase
    GLuint tex0Uni = glGetUniformLocation(shaderProgram.ID, "tex0");
    GLuint tex1Uni = glGetUniformLocation(shaderProgram.ID, "tex1"); // For the vase texture

    // Send the lighting data to the shader
    glUniform3fv(glGetUniformLocation(shaderProgram.ID, "lightPos1"), 1, glm::value_ptr(lightPos1));
    glUniform3fv(glGetUniformLocation(shaderProgram.ID, "lightPos2"), 1, glm::value_ptr(lightPos2));
    glUniform3fv(glGetUniformLocation(shaderProgram.ID, "lightColor1"), 1, glm::value_ptr(greenishLightColor));
    glUniform1f(glGetUniformLocation(shaderProgram.ID, "lightIntensity1"), lightIntensity1);
    glUniform1f(glGetUniformLocation(shaderProgram.ID, "lightIntensity2"), lightIntensity2);

    shaderProgram.Activate();
    glUniform1i(tex0Uni, 0); // Set the soundbar texture unit to 0 (GL_TEXTURE0)
    glUniform1i(tex1Uni, 1); // Set the vase texture unit to 1 (GL_TEXTURE1)
    glUniform1i(tex1Uni, 2); // Set the entertianment center texture unit to 2 (GL_TEXTURE2)
    glUniform1i(tex1Uni, 3); // Set the entertianment Wall unit to 3 (GL_TEXTURE3)
    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    // Create the camera
    Camera camera(WINDOW_WIDTH, WINDOW_HEIGHT, glm::vec3(0.0f, 0.0f, 5.0f));

    // Render loop
    while (!glfwWindowShouldClose(window))
    {
        // Clear the screen
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Check for OpenGL errors
        GLenum error;
        while ((error = glGetError()) != GL_NO_ERROR)
        {
            std::cout << "OpenGL Error: " << error << std::endl;
        }

        // Activate the shader program and update the camera
        shaderProgram.Activate();
        camera.Inputs(window);
        camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

        // Bind the texture and render the pyramid
        glBindTexture(GL_TEXTURE_2D, texture);
        VAO1.Bind();
        for (int x = -2; x <= 0; x++)
        {
            for (int z = -2; z <= 0; z++)
            {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, glm::vec3(x * 2.0f, 0.0f, z * 2.0f));
                model = glm::rotate(model, (float)glfwGetTime() * glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
                glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(model));
                glDrawElements(GL_TRIANGLES, sizeof(soundbarIndices) / sizeof(int), GL_UNSIGNED_INT, 0);
            }
        }
        VAO1.Unbind();

        // Swap the buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    VAO2.Delete();
    VBO2.Delete();
    EBO2.Delete();
    VAO3.Delete();
    VBO3.Delete();
    EBO3.Delete();
    VAO4.Delete();
    VBO4.Delete();
    EBO4.Delete();
    VAO5.Delete();
    VBO5.Delete();
    EBO5.Delete();
    VAO6.Delete();
    VBO6.Delete();
    EBO6.Delete();
    VAO7.Delete();
    VBO7.Delete();
    EBO7.Delete();
    shaderProgram.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
