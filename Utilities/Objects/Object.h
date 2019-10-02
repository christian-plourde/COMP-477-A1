#ifndef OBJECT_H
#define OBJECT_H

#include <glew.h>
#include "../../Loaders/ObjectLoader.h"
#include <vector>
#include "../../GLM/glm/glm.hpp"
#include "../../GLM/glm/matrix.hpp"
#include "../../GLM/glm/gtc/matrix_transform.hpp"
#include "../ErrorHandling/ErrorHandlingFunctions.h"
#include "../Window/Window.h"
#include "MVP.h"
#include "BoundingBox.h"
#include "../../GLM/glm/vec3.hpp"
#include "../Timing/Timestep.h"

const glm::vec3 GRAVITY = glm::vec3(0, -9.81, 0);

class Object
{
    private:
        std::vector<int> indices;
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> uvs;
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
        BoundingBox bounding_box;
        glm::vec3 move_direction;
        bool use_gravity;
        Timestep time_step;
        float mass;
        float friction_factor;
        bool use_friction;
        float energy_efficiency;

    public:
        void collide_with(Object& object);
        Object(const char* filepath);
        ~Object();
        bool load();
        void Draw(bool use_textures, bool use_shader, bool transparency_enabled);
        void Draw();
        void setViewPort();
        void Draw(bool use_shader);
        void scale(float factor);
        void move_to(glm::vec3 location);
        inline std::vector<glm::vec3> getVertices(){return vertices;}
        inline std::vector<glm::vec3> getNormals(){return normals;}
        inline std::vector<glm::vec2> getUVS(){return uvs;}
        inline std::vector<int> getIndices(){return indices;}
        inline void setFilePath(const char* path){filepath = path;}
        inline const char* getFilePath(){return filepath;}
        inline void setMeshType(GLuint mesh){mesh_type = mesh;}
        inline Shader* getShader(){return shader;}
        inline void setShader(Shader* s){shader = s;}
        inline void setMVP(MVP* m){mvp = m; bounding_box.setMVP(m);}
        inline MVP* getMVP(){return mvp;}
        inline void setAsStatic(){static_mode = true;}
        inline void setAsDynamic(){static_mode = false;}
        inline bool isStatic(){return static_mode;}
        inline int getScreenWidth(){return screen_width;}
        inline int getScreeHeight(){return screen_height;}
        inline void setScreenWidth(int s){screen_width = s;}
        inline void setScreenHeight(int s){screen_height = s;}
        inline BoundingBox& getBoundingBox(){return bounding_box;}
        inline void setMoveDirection(glm::vec3 dir){move_direction = dir;}
        inline glm::vec3 getMoveDirection(){return move_direction;}
        inline void enable_gravity(){use_gravity = true;}
        inline void disable_gravity(){use_gravity = false;}
        inline void setTimestep(Timestep& timestep){time_step = timestep;}
        inline Timestep getTimestep(){return time_step;}
        inline float getMass(){return mass;}
        inline void setMass(float mass){this->mass = mass;}
        inline float getFrictionFactor(){return friction_factor;}
        inline void setFrictionFactor(float friction){friction_factor = friction;}
        inline void setEnergyEfficiency(float efficiency){energy_efficiency = efficiency;}
        inline float getEnergyEfficiency(){return energy_efficiency;}
        inline void enable_friction(){use_friction = true;}
        inline void disable_friction(){use_friction = false;}
        void apply_friction();

};

#endif