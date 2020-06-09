#include "Cube.h"
#include "RenderEngine.h"

namespace Clumsy {

	Cube::Cube(glm::vec3 cubeTranslate, glm::vec3 cubeScale) : m_CubeTranslate(cubeTranslate), m_CubeScale(cubeScale)
	{

		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);


		float cubeVertices[] = {
			// Back face
            -0.5f, -0.5f, -0.5f, 0.0f,  0.0f, -1.0f, // Bottom-left
             0.5f, -0.5f, -0.5f, 0.0f,  0.0f, -1.0f, // bottom-right   
             0.5f,  0.5f, -0.5f, 0.0f,  0.0f, -1.0f, // top-right             
             0.5f,  0.5f, -0.5f, 0.0f,  0.0f, -1.0f, // top-right
            -0.5f,  0.5f, -0.5f, 0.0f,  0.0f, -1.0f, // top-left
            -0.5f, -0.5f, -0.5f, 0.0f,  0.0f, -1.0f, // bottom-left               
            // Front face
            -0.5f, -0.5f,  0.5f, 0.0f,  0.0f, 1.0f, // bottom-left
             0.5f,  0.5f,  0.5f, 0.0f,  0.0f, 1.0f, // top-right
             0.5f, -0.5f,  0.5f, 0.0f,  0.0f, 1.0f, // bottom-right       
             0.5f,  0.5f,  0.5f, 0.0f,  0.0f, 1.0f, // top-right
            -0.5f, -0.5f,  0.5f, 0.0f,  0.0f, 1.0f, // bottom-left
            -0.5f,  0.5f,  0.5f, 0.0f,  0.0f, 1.0f, // top-left       
            // Left face
            -0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  0.0f, // top-right
            -0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  0.0f, // bottom-left
            -0.5f,  0.5f, -0.5f, 1.0f,  0.0f,  0.0f, // top-left      
            -0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  0.0f, // bottom-left
            -0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  0.0f, // top-right
            -0.5f, -0.5f,  0.5f, 1.0f,  0.0f,  0.0f, // bottom-right
            // Right face
             0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  0.0f, // top-left
             0.5f,  0.5f, -0.5f, 1.0f,  0.0f,  0.0f, // top-right     
             0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  0.0f, // bottom-right         
             0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  0.0f, // bottom-right
             0.5f, -0.5f,  0.5f, 1.0f,  0.0f,  0.0f, // bottom-left
             0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  0.0f, // top-left
            // Bottom face      
            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f,  0.0f, // top-right
             0.5f, -0.5f,  0.5f, 0.0f, -1.0f,  0.0f, // bottom-left
             0.5f, -0.5f, -0.5f, 0.0f, -1.0f,  0.0f, // top-left       
             0.5f, -0.5f,  0.5f, 0.0f, -1.0f,  0.0f, // bottom-left
            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f,  0.0f, // top-right
            -0.5f, -0.5f,  0.5f, 0.0f, -1.0f,  0.0f, // bottom-right
            // Top face
            -0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f, // top-left
             0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f, // top-right
             0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f, // bottom-right                
             0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f, // bottom-right
            -0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f, // bottom-left
            -0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f // top-left    
		};

        glGenVertexArrays(1, &cubeVAO);
        glGenBuffers(1, &cubeVBO);
        glBindVertexArray(cubeVAO);
        glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	}


    void Cube::Render(Shader* shaderCube, unsigned int cubemapTexture)
    {
        glFrontFace(GL_CW);

        shaderCube->use();
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, m_CubeTranslate);
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.5f, 0.5f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.2f, 0.4f, 0.0f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.4f, 0.4f));
       // model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 1.0f, 0.0f));

        model = glm::scale(model, m_CubeScale);
        shaderCube->setMat4("model", model);
        shaderCube->setMat4("view", RenderEngine::GetInstance()->getView());
        shaderCube->setMat4("projection", RenderEngine::GetInstance()->getProjection());
        shaderCube->setVec3("cameraPos", RenderEngine::GetInstance()->getCamera()->GetPosition());

        glBindVertexArray(cubeVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
	}


}


