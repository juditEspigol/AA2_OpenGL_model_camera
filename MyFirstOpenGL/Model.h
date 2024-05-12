#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <GL/glew.h>

class Model 
{
private:

    GLuint VAO, VBO, uvVBO, normalsVBO;
    GLuint colorVBO; 
    unsigned int numVertexs;

public:

    Model(const std::vector<float>& vertexs, const std::vector<float>& uvs = {0,0,0}, const std::vector<float>& normals = { 0,0,0 });

    GLuint GetVAO()
    {
        return VAO;
    }

    GLuint GetVBO()
    {
        return VBO;
    }

    GLuint GetuvVAO()
    {
        return uvVBO;
    }

    unsigned int GetNumVertex()
    {
        return numVertexs;
    }


};

#endif
