#ifndef OBJECT_H
#define OBJECT_H

#include <glew.h>
#include "../../Loaders/ObjectLoader.h"
#include <vector>
#include "glm.hpp"
#include "../ErrorHandling/ErrorHandlingFunctions.h"
#include "../Window/Window.h"
#include "MVP.h"
#include "Triangle.h"

class Object
{
    private:
        std::vector<int> indices;
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> uvs;
        std::vector<Triangle> triangles;
        GLuint VAO;
        GLuint vertex_buffer;
        GLuint normal_buffer;
        GLuint texture_buffer;
        GLuint EBO;
        GLuint mesh_type;
        const char* filepath;
        Shader* shader;
        MVP* mvp;
        bool static_mode;
        int screen_width;
        int screen_height;

    public:
        Object(const char* filepath);
        ~Object();
        bool load();
        void Draw(bool use_textures, bool use_shader, bool transparency_enabled);
        void Draw();
        void setViewPort();
        void Draw(bool use_shader);
        inline std::vector<glm::vec3> getVertices(){return vertices;}
        inline std::vector<glm::vec3> getNormals(){return normals;}
        inline std::vector<glm::vec2> getUVS(){return uvs;}
        inline std::vector<int> getIndices(){return indices;}
        inline std::vector<Triangle> getTriangles(){return triangles;}
        inline void setFilePath(const char* path){filepath = path;}
        inline const char* getFilePath(){return filepath;}
        inline void setMeshType(GLuint mesh){mesh_type = mesh;}
        inline Shader* getShader(){return shader;}
        inline void setShader(Shader* s){shader = s;}
        inline void setMVP(MVP* m){mvp = m;}
        inline MVP* getMVP(){return mvp;}
        inline void setAsStatic(){static_mode = true;}
        inline void setAsDynamic(){static_mode = false;}
        inline bool isStatic(){return static_mode;}
        inline int getScreenWidth(){return screen_width;}
        inline int getScreeHeight(){return screen_height;}
        inline void setScreenWidth(int s){screen_width = s;}
        inline void setScreenHeight(int s){screen_height = s;}
};

#endif