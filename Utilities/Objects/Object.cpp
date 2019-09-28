#include "Object.h"

Object::Object(const char* filepath) : filepath(filepath)
{
    //when initializing a new object, we will need to generate a new VAO
    GLCall(glGenVertexArrays(1, &VAO));
    GLCall(glBindVertexArray(VAO));
    mesh_type = GL_TRIANGLES;
    static_mode = false;
    move_direction = glm::vec3(0, 0, 0);
    use_gravity = false;
    mass = 0;
}

Object::~Object()
{
    delete mvp;
}

bool Object::load()
{
    //function to load an object into the class
    if(!LoadOBJ(filepath, indices, vertices, normals, uvs))
        return false;

    bounding_box.setVertices(&vertices);

    //once we have loaded the data from the file, we should set the data in our buffers

    //next we will need a buffer for the vertices, normals, and uvs
    GLCall(glGenBuffers(1, &vertex_buffer));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*vertices.size(), &vertices.front(), GL_STATIC_DRAW));

    GLCall(glGenBuffers(1, &normal_buffer));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, normal_buffer));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*normals.size(), &normals.front(), GL_STATIC_DRAW));

    GLCall(glGenBuffers(1, &texture_buffer));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, texture_buffer));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2)*uvs.size(), &uvs.front(), GL_STATIC_DRAW));

    //finally we need an EBO for the indices
    GLCall(glGenBuffers(1, &EBO));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*indices.size(), &indices.front(), GL_STATIC_DRAW));
    return true;
}

void Object::setViewPort()
{
    //reset the viewport
    GLCall(glViewport(0,0,screen_width, screen_height));
    GLCall(glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT));
}

void Object::Draw(bool use_textures, bool use_shader, bool transparency_enabled)
{
    bounding_box.setVertices(&vertices);

    if(use_shader)
        shader -> use();

    //now we can set enable the buffers in our vao
    GLCall(glEnableVertexAttribArray(0));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer));
    GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0));

    GLCall(glEnableVertexAttribArray(1));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, normal_buffer));
    GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0));

    if(use_textures)
    {
        GLCall(glEnableVertexAttribArray(2));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, texture_buffer));
        GLCall(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0));
    }

    GLCall(glDisable(GL_BLEND));
    GLCall(glEnable(GL_CULL_FACE));
    //configuring z-buffer
    GLCall(glEnable(GL_DEPTH_TEST));
    GLCall(glDepthFunc(GL_LESS));

    if(transparency_enabled)
    {
        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        GLCall(glDisable(GL_CULL_FACE));
        GLCall(glDisable(GL_DEPTH_TEST));
    }

    //actual drawing
    GLCall(glDrawArrays(mesh_type, 0, vertices.size()));

    //disable buffers
    GLCall(glDisableVertexAttribArray(0));
    GLCall(glDisableVertexAttribArray(1));

    if(use_textures)
        GLCall(glDisableVertexAttribArray(2));
}

void Object::scale(float factor)
{
    mvp->setModel(glm::scale(mvp->getModel(), glm::vec3(factor, factor, factor)));
    bounding_box.setScaleFactor(factor);
}

void Object::Draw()
{
    Draw(true, true, false);
}

void Object::Draw(bool use_textures)
{
    Draw(true, use_textures, false);
}

void Object::collide_with(Object &object)
{
    CollisionPlane plane;
    if(bounding_box.collides_with(object.getBoundingBox(), plane))
    {
        if(plane == POSITIVE_X || plane == NEGATIVE_X)
            this->setMoveDirection(glm::vec3(this->getMoveDirection().x*(-1),
                    this->getMoveDirection().y, this->getMoveDirection().z));

        if(plane == POSITIVE_Y || plane == NEGATIVE_Y)
            this->setMoveDirection(glm::vec3(this->getMoveDirection().x,
                                             this->getMoveDirection().y*(-1), this->getMoveDirection().z));

        if(plane == POSITIVE_Z || plane == NEGATIVE_Z)
            this->setMoveDirection(glm::vec3(this->getMoveDirection().x,
                                             this->getMoveDirection().y, this->getMoveDirection().z*(-1)));
    }

    if(use_gravity)
    {
        //record the timestep since the last update for our calculations
        time_step.record();

        move_direction = move_direction + (float)time_step.getTimestep()*GRAVITY*mass;
        getMVP()->setModel(glm::translate(getMVP()->getModel(), getMoveDirection()*(float)time_step.getTimestep()));
        getShader() -> setUniformData("model_matrix", getMVP()->getModel());
    }

    else
    {
        getMVP()->setModel(glm::translate(getMVP()->getModel(), getMoveDirection()));
        getShader() -> setUniformData("model_matrix", getMVP()->getModel());
    }
}
