
#include "../pch.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string> 
#include "Shader.h"
#include "Lighting.h"

namespace Clumsy 
{
    Shader::Shader(const char* vertexPath, const char* fragmentPath, 
		const char* tccontrol, const char* tcevalutaion)
    {
        // 1. retrieve the vertex/fragment source code from filePath
        std::string vertexCode;
        std::string fragmentCode;
		std::string tcControlCode;
		std::string tcEvalutionCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
		std::ifstream ftcControlFile;
		std::ifstream ftcEvalutionFile;
        // ensure ifstream objects can throw exceptions:
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		ftcControlFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		ftcEvalutionFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            // open files
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            // read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            // close file handlers
            vShaderFile.close();
            fShaderFile.close();
            // convert stream into string
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();

			//tc shader control and evaluation
			if (tccontrol != nullptr && tcevalutaion != nullptr)
			{
				ftcControlFile.open(tccontrol);
				ftcEvalutionFile.open(tcevalutaion);
				std::stringstream tcControlShaderStream, tcEvaluationShaderStream;
				tcControlShaderStream << ftcControlFile.rdbuf();
				tcEvaluationShaderStream << ftcEvalutionFile.rdbuf();
				ftcControlFile.close();
				ftcEvalutionFile.close();
				tcControlCode = tcControlShaderStream.str();
				tcEvalutionCode = tcEvaluationShaderStream.str();
			}
        }
        catch (std::ifstream::failure & e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }
        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();
        // 2. compile shaders
        unsigned int vertex, fragment;
        // vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");
        // fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");
		//tc shaders
		unsigned int tcControl, tcEvaluation;
		if (tccontrol != nullptr && tcevalutaion != nullptr)
		{
			const char* tcControlShaderCode = tcControlCode.c_str();
			const char* tcEvaluationShaderCode = tcEvalutionCode.c_str();
			tcControl = glCreateShader(GL_TESS_CONTROL_SHADER);
			tcEvaluation = glCreateShader(GL_TESS_EVALUATION_SHADER);
			glShaderSource(tcControl, 1, &tcControlShaderCode, NULL);
			glShaderSource(tcEvaluation, 1, &tcEvaluationShaderCode, NULL);
			glCompileShader(tcControl);
			glCompileShader(tcEvaluation);
			checkCompileErrors(tcControl, "TC_CONTROL");
			checkCompileErrors(tcEvaluation, "TC_EVALUATION");
		}
        // shader Program
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
		if (tccontrol != nullptr && tcevalutaion != nullptr)
		{
			glAttachShader(ID, tcControl);
			glAttachShader(ID, tcEvaluation);
		}
        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");
        // delete the shaders as they're linked into our program now and no longer necessary
        glDeleteShader(vertex);
        glDeleteShader(fragment);
		if (tccontrol != nullptr && tcevalutaion != nullptr)
		{
			glDeleteShader(tcControl);
			glDeleteShader(tcEvaluation);
		}
    }

    void Shader::use()
    {
        glUseProgram(ID);
    }

    void Shader::setBool(const std::string& name, bool value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }

    void Shader::setInt(const std::string& name, int value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }

    void Shader::setFloat(const std::string& name, float value) const
    {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }

    void Shader::checkCompileErrors(unsigned int shader, std::string type)
    {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }

    void Shader::setMat4(const std::string& name, const glm::mat4& mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

	void Shader::setVec3(const std::string& name, const glm::vec3& value) const
	{
		glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}
	void Shader::setVec3(const std::string& name, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
	}

	//void Shader::setBase(const std::string& uniformName, BaseLight baseLight) const
	//{
	//	setVec3(uniformName + ".color", baseLight.GetColor());
	//	setFloat(uniformName + ".intensity", baseLight.GetIntensity());
	//}

	void Shader::setDirectional(const std::string& uniformName, DirectionalLight* directionalLight) const
	{
		setVec3(uniformName + ".direction", directionalLight->GetDirection());
		setVec3(uniformName + ".base.color", directionalLight->GetColor());
		setFloat(uniformName + ".base.intensity", directionalLight->GetIntensity());
	}
    void Shader::SetDirectionalLight(float intensity, glm::vec3 viewPosition, glm::vec3 lightPos, glm::mat4 lightSpaceMatrix)
    {
        setFloat("intensity", intensity);
		setVec3("viewPos",viewPosition);
		setVec3("lightPos", lightPos);
		setMat4("lightSpaceMatrix", lightSpaceMatrix);
    }
    void Shader::SetSpotLight(glm::vec3 position, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
    {
        setVec3("spotLight.position", position);
        setVec3("spotLight.direction", direction);
        setVec3("spotLight.ambient", ambient);
        setVec3("spotLight.diffuse", diffuse);
        setVec3("spotLight.specular", specular);
        setFloat("spotLight.constant", 1.0f);
        setFloat("spotLight.linear", 0.09);
        setFloat("spotLight.quadratic", 0.032);
        setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
        setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
    }
    void Shader::SetPointLight(std::string number, glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
    {
        setVec3("pointLights[" + number + "].position", position);
        setVec3("pointLights[" + number + "].ambient", ambient);
        setVec3("pointLights[" + number + "].diffuse", diffuse);
        setVec3("pointLights[" + number + "].specular", specular);
        setFloat("pointLights[" + number + "].constant", 1.0f);
        setFloat("pointLights[" + number + "].linear", 0.09);
        setFloat("pointLights[" + number + "].quadratic", 0.032);
    }
}
