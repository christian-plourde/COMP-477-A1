#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 normals;
layout(location = 2) in vec2 tex_coords;

//information required for lighting
uniform vec3 light_color_1;
uniform vec3 light_position_1;
uniform vec3 view_position;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;

out vec3 fragment_position;
out vec3 normal;
out vec2 tex;

void main()
{
        normal = mat3(model_matrix)*normals;
        fragment_position = mat3(model_matrix)*vertexPosition_modelspace;
        tex = tex_coords;
        gl_Position = projection_matrix*view_matrix*model_matrix*vec4(vertexPosition_modelspace * 5, 1);
}