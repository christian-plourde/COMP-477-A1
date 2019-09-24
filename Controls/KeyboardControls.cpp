#include "KeyboardControls.h"
#include "../Loaders/ShaderLoader.h"
#include "../GLM/glm/gtc/type_ptr.hpp"
#include <iostream>

void key_press_o(ObjectContainer* objects)
{
    //when the o key is pressed on the keyboard, we should scale the object up by 10%.
    //this is done by scaling the model matrix in all directions and then resetting the value of the uniform in
    //our shader
    for(int i = 0; i<objects->size; i++)
    {
        if(!objects->getObject(i)->isStatic())
        {
            objects->getObject(i)->getMVP()->setModel(
                    glm::scale(objects->getObject(i) -> getMVP() -> getModel(), glm::vec3(0.9f, 0.9f, 0.9f)));

            objects->getObject(i)-> getShader() -> setUniformData("model_matrix", objects->getObject(i)->getMVP()->getModel());
        }
    }
}

void key_press_p(ObjectContainer* objects)
{
    //when the p key is pressed on the keyboard, we should scale the object down by 10%.
    //this is done by scaling the model matrix in all directions and then resetting the value of the uniform in
    //our shader
    for(int i = 0; i<objects->size; i++)
    {
        if(!objects->getObject(i)->isStatic())
        {
            objects->getObject(i)->getMVP()->setModel(
                    glm::scale(objects->getObject(i) -> getMVP() -> getModel(), glm::vec3(1.1f, 1.1f, 1.1f)));

            objects->getObject(i)-> getShader() -> setUniformData("model_matrix", objects->getObject(i)->getMVP()->getModel());
        }
    }
}

void key_press_b(ObjectContainer* objects)
{
    //when the b key is pressed, the OBJECT itself (not the camera) should be rotated about the x-axis.
    //in order to do this, we want to modify the Model matrix
    for(int i = 0; i<objects->size; i++)
    {
        if(!objects->getObject(i) -> isStatic())
        {
            objects->getObject(i)->getMVP()->setModel(
                    glm::rotate(objects->getObject(i) -> getMVP() -> getModel(),glm::radians(-1.5f), glm::vec3(1,0,0)));

            objects->getObject(i)-> getShader() -> setUniformData("model_matrix", objects->getObject(i)->getMVP()->getModel());
        }
    }
}

void key_press_n(ObjectContainer* objects)
{
    //when the n key is pressed, the OBJECT itself (not the camera) should be rotated about the y-axis.
    //in order to do this, we want to modify the Model matrix
    for(int i = 0; i<objects->size; i++)
    {
        if(!objects->getObject(i) -> isStatic())
        {
            objects->getObject(i)->getMVP()->setModel(
                    glm::rotate(objects->getObject(i) -> getMVP() -> getModel(),glm::radians(1.5f), glm::vec3(0,1,0)));

            objects->getObject(i)-> getShader() -> setUniformData("model_matrix", objects->getObject(i)->getMVP()->getModel());
        }
    }
}

void key_press_e(ObjectContainer* objects)
{
    //when the n key is pressed, the OBJECT itself (not the camera) should be rotated about the z-axis.
    //in order to do this, we want to modify the Model matrix
    for(int i = 0; i<objects->size; i++)
    {
        if(!objects->getObject(i) -> isStatic())
        {
            objects->getObject(i)->getMVP()->setModel(
                    glm::rotate(objects->getObject(i) -> getMVP() -> getModel(),glm::radians(1.5f), glm::vec3(0,0,1)));

            objects->getObject(i)-> getShader() -> setUniformData("model_matrix", objects->getObject(i)->getMVP()->getModel());
        }
    }
}

void key_press_j(ObjectContainer* objects)
{
    //when the j key is pressed, the OBJECT itself (not the camera) should be translated along the x axis
    //in the positive direction
    //in order to do this, we want to modify the Model matrix
    for(int i = 0; i<objects->size; i++)
    {
        if(!objects->getObject(i) -> isStatic())
        {
            objects->getObject(i)->getMVP()->setModel(
                    glm::translate(objects->getObject(i) -> getMVP() -> getModel(), glm::vec3(1,0,0)));

            objects->getObject(i)-> getShader() -> setUniformData("model_matrix", objects->getObject(i)->getMVP()->getModel());
        }
    }
}

void key_press_l(ObjectContainer* objects)
{
    //when the l key is pressed, the OBJECT itself (not the camera) should be translated along the x axis
    //in the positive direction
    //in order to do this, we want to modify the Model matrix
    for(int i = 0; i<objects->size; i++)
    {
        if(!objects->getObject(i) -> isStatic())
        {
            objects->getObject(i)->getMVP()->setModel(
                    glm::translate(objects->getObject(i) -> getMVP() -> getModel(), glm::vec3(-1,0,0)));

            objects->getObject(i)-> getShader() -> setUniformData("model_matrix", objects->getObject(i)->getMVP()->getModel());
        }
    }
}

void key_press_i(ObjectContainer* objects)
{
    //when the i key is pressed, the OBJECT itself (not the camera) should be translated along the y axis
    //in the positive direction
    //in order to do this, we want to modify the Model matrix
    for(int i = 0; i<objects->size; i++)
    {
        if(!objects->getObject(i) -> isStatic())
        {
            objects->getObject(i)->getMVP()->setModel(
                    glm::translate(objects->getObject(i) -> getMVP() -> getModel(), glm::vec3(0,1,0)));

            objects->getObject(i)-> getShader() -> setUniformData("model_matrix", objects->getObject(i)->getMVP()->getModel());
        }
    }
}

void key_press_k(ObjectContainer* objects)
{
    //when the k key is pressed, the OBJECT itself (not the camera) should be translated along the y axis
    //in the negative direction
    //in order to do this, we want to modify the Model matrix
    for(int i = 0; i<objects->size; i++)
    {
        if(!objects->getObject(i) -> isStatic())
        {
            objects->getObject(i)->getMVP()->setModel(
                    glm::translate(objects->getObject(i) -> getMVP() -> getModel(), glm::vec3(0,-1,0)));

            objects->getObject(i)-> getShader() -> setUniformData("model_matrix", objects->getObject(i)->getMVP()->getModel());
        }
    }
}

void key_press_pg_up(ObjectContainer* objects)
{
    //when the page up key is pressed, the OBJECT itself (not the camera) should be translated along the z axis
    //in the positive direction
    //in order to do this, we want to modify the Model matrix
    for(int i = 0; i<objects->size; i++)
    {
        if(!objects->getObject(i) -> isStatic())
        {
            objects->getObject(i)->getMVP()->setModel(
                    glm::translate(objects->getObject(i) -> getMVP() -> getModel(), glm::vec3(0,0,1)));

            objects->getObject(i)-> getShader() -> setUniformData("model_matrix", objects->getObject(i)->getMVP()->getModel());
        }
    }
}

void key_press_pg_down(ObjectContainer* objects)
{
    //when the page down key is pressed, the OBJECT itself (not the camera) should be translated along the z axis
    //in the negative direction
    //in order to do this, we want to modify the Model matrix
    for(int i = 0; i<objects->size; i++)
    {
        if(!objects->getObject(i) -> isStatic())
        {
            objects->getObject(i)->getMVP()->setModel(
                    glm::translate(objects->getObject(i) -> getMVP() -> getModel(), glm::vec3(0,0,-1)));

            objects->getObject(i)-> getShader() -> setUniformData("model_matrix", objects->getObject(i)->getMVP()->getModel());
        }
    }
}

void key_press_F1(ObjectContainer* objects)
{
    //when the F1 key is pressed, it should toggle between the scene having the 4 lights or only one
    //in order to do this, we can
    for(int i = 0; i < objects->size; i++)
    {
        if(objects->getObject(i)->getShader()->lightsOn())
        {

            //if the lights are on make them all dark
            objects->getObject(i)->getShader()->setUniformData("light_position_1", glm::vec3(0,0,0));
            objects->getObject(i)->getShader()->setUniformData("light_position_2", glm::vec3(0,0,0));
            objects->getObject(i)->getShader()->setUniformData("light_position_3", glm::vec3(0,0,0));
            objects->getObject(i)->getShader()->setUniformData("light_position_4", glm::vec3(0,0,0));
            objects->getObject(i)-> getShader() -> setUniformData("light_color_1", glm::vec3(0,0,0));
            objects->getObject(i)-> getShader()->setUniformData("light_color_2", glm::vec3(0,0,0));
            objects->getObject(i)-> getShader()->setUniformData("light_color_3", glm::vec3(0,0,0));
            objects->getObject(i)-> getShader()-> setUniformData("light_color_4", glm::vec3(0,0,0));
            objects->getObject(i)->getShader()->setUniformData("spot_light_1_position", glm::vec3(0,0,0));
            objects->getObject(i)->getShader()->setUniformData("spot_light_1_color", glm::vec3(0, 0, 0));
            objects->getObject(i)->getShader()->setUniformData("shadow_map_flag", 0);
            objects->getObject(i)-> getShader() -> setLightsOn(false);
        }

        else
        {
            objects->getObject(i)->getShader()->setUniformData("light_position_1", glm::vec3(0,20,10));
            objects->getObject(i)->getShader()->setUniformData("light_position_2", glm::vec3(-10,15,5));
            objects->getObject(i)->getShader()->setUniformData("light_position_3", glm::vec3(0,15,5));
            objects->getObject(i)->getShader()->setUniformData("light_position_4", glm::vec3(0,0,25));
            objects->getObject(i)-> getShader() -> setUniformData("light_color_1", glm::vec3(0.2,0.05,0.05));
            objects->getObject(i)-> getShader()->setUniformData("light_color_2", glm::vec3(0.05,0.2,0.05));
            objects->getObject(i)-> getShader()->setUniformData("light_color_3", glm::vec3(0.05,0.05,0.2));
            objects->getObject(i)-> getShader()-> setUniformData("light_color_4", glm::vec3(0.05,0.05,0.05));
            objects->getObject(i)->getShader()->setUniformData("spot_light_1_position", glm::vec3(0,0,0));
            objects->getObject(i)->getShader()->setUniformData("spot_light_1_color", glm::vec3(0, 0, 0));
            objects->getObject(i)->getShader()->setUniformData("shadow_map_flag", 0);
            objects->getObject(i)-> getShader() -> setLightsOn(true);
        }
    }
}

void key_press_F2(ObjectContainer* objects)
{
    for(int i = 0; i < objects->size; i++)
    {
        if(objects->getObject(i)->getShader()->lightsOn())
        {
            //if the lights are on make them all dark and move them to the origin
            objects->getObject(i)->getShader()->setUniformData("light_position_1", glm::vec3(0,0,0));
            objects->getObject(i)->getShader()->setUniformData("light_position_2", glm::vec3(0,0,0));
            objects->getObject(i)->getShader()->setUniformData("light_position_3", glm::vec3(0,0,0));
            objects->getObject(i)->getShader()->setUniformData("light_position_4", glm::vec3(0,0,0));
            objects->getObject(i)-> getShader() -> setUniformData("light_color_1", glm::vec3(0,0,0));
            objects->getObject(i)-> getShader()->setUniformData("light_color_2", glm::vec3(0,0,0));
            objects->getObject(i)-> getShader()->setUniformData("light_color_3", glm::vec3(0,0,0));
            objects->getObject(i)-> getShader()-> setUniformData("light_color_4", glm::vec3(0,0,0));
            objects->getObject(i)->getShader()->setUniformData("spot_light_1_position", glm::vec3(0,0,0));
            objects->getObject(i)->getShader()->setUniformData("spot_light_1_color", glm::vec3(0, 0, 0));
            //set the shadow map flag back to false
            objects->getObject(i)->getShader()->setUniformData("shadow_map_flag", 0);

            objects->getObject(i)-> getShader() -> setLightsOn(false);
        }

        else
        {
            //Here we want to turn only the spot light on
            objects->getObject(i)->getShader()->setUniformData("spot_light_1_color", glm::vec3(0.8, 0.2, 0.2));
            objects->getObject(i)->getShader()->setUniformData("spot_light_1_position", glm::vec3(0,20, 10));
            //set the shadow map flag
            objects->getObject(i)->getShader()->setUniformData("shadow_map_flag", 1);

            objects->getObject(i)-> getShader() -> setLightsOn(true);

        }
    }
}