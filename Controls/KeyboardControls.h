#ifndef COMP_371_A1_KEYBOARDCONTROLS_H
#define COMP_371_A1_KEYBOARDCONTROLS_H
#endif

#include <glew.h>
#include <GLFW/glfw3.h>
#include "../GLM/glm/matrix.hpp"
#include "../GLM/glm/gtc/matrix_transform.hpp"
#include "../Utilities/Window/Window.h"
#include "../Utilities/Objects/ObjectContainer.h"


/*
 * This method defines what occurs when the o key is pressed on the keyboard. For this assignment, it modifies
 * the size uniformly of the object and so to change this, we need to pass in the View, Projection, and Model
 * matrices, as well as the shader ID since we will need to update the value in the uniform in the shader program
 * once we have recalculated the size of the model.
 */
void key_press_o(ObjectContainer*);

/*
 * This method defines what occurs when the p key is pressed on the keyboard. For this assignment, it modifies
 * the size uniformly of the object and so to change this, we need to pass in the View, Projection, and Model
 * matrices, as well as the shader ID since we will need to update the value in the uniform in the shader program
 * once we have recalculated the size of the model.
 */
void key_press_p(ObjectContainer*);

/*
 * This method defined what happens when b is pressed on the keyboard. When this occurs, the OBJECT (i.e. the model)
 * will be rotated about the x axis in counterclockwise fashion
 */
void key_press_b(ObjectContainer* objects);

/*
 * This method defined what happens when n is pressed on the keyboard. When this occurs, the OBJECT (i.e. the model)
 * will be rotated about the y axis in counterclockwise fashion
 */
void key_press_n(ObjectContainer* objects);

/*
 * This method defined what happens when e is pressed on the keyboard. When this occurs, the OBJECT (i.e. the model)
 * will be rotated about the z axis in counterclockwise fashion
 */
void key_press_e(ObjectContainer* objects);

/*
 * This method defined what happens when j is pressed on the keyboard. When this occurs, the OBJECT (i.e. the model)
 * will be translated along the x axis in the positive direction
 */
void key_press_j(ObjectContainer* objects);

/*
 * This method defined what happens when l is pressed on the keyboard. When this occurs, the OBJECT (i.e. the model)
 * will be translated along the x axis in the negative direction
 */
void key_press_l(ObjectContainer* objects);

/*
 * This method defined what happens when i is pressed on the keyboard. When this occurs, the OBJECT (i.e. the model)
 * will be translated along the y axis in the positive direction
 */
void key_press_i(ObjectContainer* objects);

/*
 * This method defined what happens when k is pressed on the keyboard. When this occurs, the OBJECT (i.e. the model)
 * will be translated along the y axis in the negative direction
 */
void key_press_k(ObjectContainer* objects);

/*
 * This method defined what happens when page up is pressed on the keyboard. When this occurs, the OBJECT (i.e. the model)
 * will be translated along the z axis in the positive direction
 */
void key_press_pg_up(ObjectContainer* objects);

/*
 * This method defines what happens when page down is pressed on the keyboard. When this occurs, the OBJECT (i.e. the model)
 * will be translated along the z axis in the negative direction
 */
void key_press_pg_down(ObjectContainer* objects);

/*
 * This defines what happens when the 'F1' key is pressed. When this occurs, the 4 lights in the scene should be
 * enabled. If the key has not been pressed, then there should only be one light on the scene.
 */
void key_press_F1(ObjectContainer* objects);

/*
 * This defines what occurs when the 'F2' key is pressed. When this occurs, we should render the scene with two-pass
 * shadow mapping. Also, before doing anything, we should set the scene with only the one light.
 */
void key_press_F2(ObjectContainer* objects);