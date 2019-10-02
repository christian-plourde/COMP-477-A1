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
    friction_factor = 0;
    energy_efficiency = 1.0;
    use_friction = false;
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

void Object::move_to(glm::vec3 location)
{
    glm::vec3 curr_pos = glm::vec3(mvp->getModel()[3][0], mvp->getModel()[3][1], mvp->getModel()[3][2]);
    mvp->setModel(glm::translate(mvp -> getModel(), location - curr_pos));

    getShader() -> setUniformData("model_matrix", mvp->getModel());
}

void Object::apply_friction()
{
    if(!use_friction || move_direction == glm::vec3(0, 0, 0) || friction_factor == 0)
    {
        return; //no need to continue if object is not moving or there is no friction
    }

    //this function will apply friction to the motion of an object
    //to do this we need to multiply the friction factor by the magnitude of the velocity and
    //then decrease the velocity by this amount
    float factor = friction_factor*sqrtf(powf(move_direction.x, 2) + powf(move_direction.y, 2) + powf(move_direction.z, 2));
    move_direction = move_direction - factor*move_direction;

    //we then check if the move_direction is within a certain interval of being 0 (i.e. stopped)
    //this means that the object should stop, lest it start going backwards
    if(sqrtf(powf(move_direction.x, 2) + powf(move_direction.y, 2) + powf(move_direction.z, 2)) < 0.00001)
    {
        move_direction = glm::vec3(0, 0, 0);
    }

}

void Object::collide_with(Object &object)
{
    CollisionPlane plane;
    bool collision_occurred = false;
    if(bounding_box.collides_with(object.getBoundingBox(), plane))
    {
        collision_occurred = true;
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

    apply_friction();

    if(use_gravity)
    {
        //we will also need to include energy efficiency calculations
        if(collision_occurred) //if there was a collision energy is lost
        {
            //we have that (s1/s0)^2 = energy_effiiciency where s1 is the magnitude of the move vector after the
            //collision and s0 is the magnitude of the move vector before the collision

            //what we need to determine first is the new magnitude
            float new_magnitude = sqrtf(powf(glm::length(move_direction), 2)*energy_efficiency);

            //now we need the realtive weights of each of the components before the collision
            float x_weight = move_direction.x/glm::length(move_direction);
            float y_weight = move_direction.y/glm::length(move_direction);
            float z_weight = move_direction.z/glm::length(move_direction);

            //now the move direction should be a vector composed of the weights multiplied by the new magnitude
            move_direction = glm::vec3(x_weight*new_magnitude, y_weight*new_magnitude, z_weight*new_magnitude);
        }

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
