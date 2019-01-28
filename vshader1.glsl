#version 400

// input variables processed in parallel
layout (location = 0) in vec4 vPosition;

out vec4 v2fcolor;

uniform float scaling;
uniform vec4 translation;
uniform vec4 color;
uniform float length;

void main()
{
   //gl_Position->out builtin variable
   gl_Position = (vPosition * vec4(scaling*length, scaling, scaling, 1)) + translation;
   v2fcolor = color;
}
