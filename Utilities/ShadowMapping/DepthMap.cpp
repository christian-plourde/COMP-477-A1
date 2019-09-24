#include "DepthMap.h"

DepthMap::~DepthMap()
{
    delete shader;
    delete depth_light;
}

DepthMap::DepthMap() : SHADOW_WIDTH(1024), SHADOW_HEIGHT(1024)
{
    depth_light = new DepthMapLight();
}

DepthMap::DepthMap(GLuint shadow_width, GLuint shadow_height)
{
    depth_light = new DepthMapLight();
    SHADOW_HEIGHT = shadow_height;
    SHADOW_WIDTH = shadow_width;
}

void DepthMap::load()
{
    //when we load a depth map, the first thing we need to do is initialize our framebuffer as well as our
    //depth texture
    GLCall(glGenFramebuffers(1, &frame_buffer));
    GLCall(glGenTextures(1, &depth_tex));
    GLCall(glBindTexture(GL_TEXTURE_2D, depth_tex));
    GLCall(glTexImage2D(GL_TEXTURE_2D, 0,GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0,GL_DEPTH_COMPONENT, GL_FLOAT, NULL));
    GLCall(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer));
    GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth_tex, 0));
    GLCall(glDrawBuffer(GL_NONE));
    GLCall(glReadBuffer(GL_NONE));

}

void DepthMap::setShader(Shader *s)
{
    this -> shader = s;
}

void DepthMap::RenderToTexture(ObjectContainer *o)
{
    //in this method we want to render the scene from the perspective of the depth map
    shader -> use();
    GLCall(glViewport(0,0, SHADOW_WIDTH, SHADOW_HEIGHT));
    BindForWriting();
    GLCall(glClear(GL_DEPTH_BUFFER_BIT));
    for(int i = 0; i < o->size; i++)
    {
        //draw each object using the shader bound to the depth map
        //we need to update the model matrix in the depth map shader so the shadow follows
        shader->setUniformData("model_matrix", o->getObject(i)->getMVP()->getModel());
        o->getObject(i)->Draw(false, false, false);
    }
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

void DepthMap::BindForWriting()
{
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer));
}

void DepthMap::BindForReading()
{
    GLCall(glActiveTexture(texture_slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, depth_tex));
}

GLuint DepthMap::getTexture()
{
    switch(texture_slot)
    {
        case GL_TEXTURE0: return 0;
        case GL_TEXTURE1: return 1;
        case GL_TEXTURE2: return 2;
        case GL_TEXTURE3: return 3;
        case GL_TEXTURE4: return 4;
        case GL_TEXTURE5: return 5;
        case GL_TEXTURE6: return 6;
        case GL_TEXTURE7: return 7;
        case GL_TEXTURE8: return 8;
        case GL_TEXTURE9: return 9;
        case GL_TEXTURE10: return 10;
        case GL_TEXTURE11: return 11;
        case GL_TEXTURE12: return 12;
        case GL_TEXTURE13: return 13;
        case GL_TEXTURE14: return 14;
        case GL_TEXTURE15: return 15;
        case GL_TEXTURE16: return 16;
        case GL_TEXTURE17: return 17;
        case GL_TEXTURE18: return 18;
        case GL_TEXTURE19: return 19;
        case GL_TEXTURE20: return 20;
        case GL_TEXTURE21: return 21;
        case GL_TEXTURE22: return 22;
        case GL_TEXTURE23: return 23;
        case GL_TEXTURE24: return 24;
        case GL_TEXTURE25: return 25;
        case GL_TEXTURE26: return 26;
        case GL_TEXTURE27: return 27;
        case GL_TEXTURE28: return 28;
        case GL_TEXTURE29: return 29;
        case GL_TEXTURE30: return 30;
        case GL_TEXTURE31: return 31;
        default: return 0;
    }
}

