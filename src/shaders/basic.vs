#version 330

layout (location = 0) in vec4 vertex;

void main( void )
{
    gl_Position = vertex;
}
