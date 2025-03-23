#define GLEW_STATIC
#include <Window.h>
#include <iostream>
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


//making variables 
uint32_t shader , XUniform , YUniform , VAO, VBO;

//making the variables for movment
bool direction = true;
float MaxOffset = 0.5f , triincrement = 0.007f , TriOffset = 0.0f;


//setting the position of verticies
float positions[]
{
    -1.0f,-1.0f,0.0f,
     1.0f,-1.0f,0.0f,
     0.0f, 1.0f,0.0f
};
// Vertex Shader code
static const char* vShader = "                                                \n\
#version 330                                                                  \n\
                                                                              \n\
layout (location = 0) in vec3 pos;						                      \n\                                                     \n\
					                                                          \n\
uniform float XMove;					                                      \n\
uniform float YMove;					                                      \n\
					                                                          \n\
					                                                          \n\
void main()                                                                   \n\
{                                                                             \n\
    gl_Position = vec4(0.4 * pos.x + XMove, 0.4 * pos.y +YMove, pos.z, 1.0);  \n\
}";

// Fragment Shader
static const char* fShader = "                                                \n\
#version 330                                                                  \n\
                                                                              \n\
out vec4 colour;                                                               \n\
                                                                              \n\
void main()                                                                   \n\
{                                                                             \n\
    colour = vec4(1.0, 0.0, 0.0, 1.0);                                         \n\
}";


//create triangle (Gen VAO,VBO) , (Bind VAO,VBO)
static void CreateTriangle(float verticies[])
{
    
    // generate and bind VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // generate and bind VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), verticies, GL_STATIC_DRAW);


    // I DON'T KNOW NOW
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // unbind VBO,VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}

// Callback function to handle window resize
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

//Create and Attach Shader to the Program
static void Shader(uint32_t program, const char* ShaderCode, GLenum ShaderType)
{
    //allocate memory to the shader and store id for it
    unsigned int Shader = glCreateShader(ShaderType);

    //take the code length
    int32_t codelength = strlen(ShaderCode);

    // to make it double pointer
    const char** Shadercode = &ShaderCode;

    //attach the source code to the shader program
    glShaderSource(Shader, 1, Shadercode, &codelength);
    // compile the shader program
    glCompileShader(Shader);

    //Error handling for the shader compiltion
    int result = 0;
    glGetShaderiv(Shader, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        if (length > 0)
        {
            char* message = new char[length];
            glGetShaderInfoLog(shader, length, NULL, message);
            std::cout << "[PROGRAM SHADER]: failed to compile the shader:" << ShaderType << message << std::endl;
            delete[] message;
            return;
        }

    }

    //attaching the shader to to program
    glAttachShader(program, Shader);


}

//Create Program and Attach Shader to it (VertexShdaer , FragmentShader)
static void CompileShader()
{
    //Create Program to Attach Shader to it
    shader = glCreateProgram();
    if (!shader)
    {
        printf("[Shader]: can't create shader program!");
        return;
    }

    //Create Shaders and Attach it to the Program
    Shader(shader, vShader, GL_VERTEX_SHADER);
    Shader(shader, fShader, GL_FRAGMENT_SHADER);

    //Link the program after attaching the shaders
    glLinkProgram(shader);
    int result;
    glGetProgramiv(shader, GL_LINK_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &length);
        if (length > 0)
        {
            char* message = new char[length];
            glGetProgramInfoLog(shader, length, NULL, message);
            std::cout << "[PROGRAM SHADER]: failed to link:" << message << std::endl;
            delete[] message;
            return;
        }

    }

    //Validate program to check there is no error
    glValidateProgram(shader);
    glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &length);
        if (length > 0)
        {
            char* message = new char[length];
            glGetProgramInfoLog(shader, length, NULL, message);
            std::cout << "[PROGRAM SHADER]: failed to Validate:" << message << std::endl;
            delete[] message;
            return;
        }

    }

    //getting up the uniform location
    XUniform = glGetUniformLocation(shader, "XMove");
    YUniform = glGetUniformLocation(shader, "YMove");

}


//the main func of the exe
int main() {
    uint16_t m_width = 800, m_height = 600;
   //creating the object mox from the window class to create a window
    Window MOX(m_width, m_height, "MOX", 3,3);
   
    // Set callback for window resizing
    glfwSetFramebufferSizeCallback(MOX.mxGetWindow(), framebuffer_size_callback);
    //setting the viewport
    glViewport(0, 0, m_width, m_height);
    //creating the vbo and vao and shaders
    CreateTriangle(positions);
    CompileShader();
    

    // the main loop for the program
    while (!MOX.mxShouldClose()) 
    {
        MOX.mxPollEvents();

        

        if (direction)
        {
            TriOffset += triincrement;
        }
        else {
            TriOffset -= triincrement;
        }

        if (abs(TriOffset) >= MaxOffset)
        {
            direction = !direction;
        }

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader);

        glUniform1f(XUniform, TriOffset);
        glUniform1f(YUniform, TriOffset);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        glUseProgram(0);

        

        MOX.mxSwapBuffer();
        
    }


    
    return 0;
}

