#include "shaders.hpp"

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/cimport.h>
#include <assimp/version.h>

#include <Window.hpp>
#include <VertexBuffer.hpp>
#include <Shader.hpp>
#include <Camera.hpp>

#include <iostream>

int main()
{
    try
    {
        WindowPtr window = createWindow({800, 600, "Cube"});
        auto [width, height] = window->getFrameBufferSize();
        glViewport(0, 0, width, height);

        glEnable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_POLYGON_OFFSET_LINE);
        glPolygonOffset(-0.1f, -0.1f);

        Shader program{vertex_code, fragment_code};

        const aiScene* scene = aiImportFile("resources/models/monke.gltf", aiProcess_Triangulate);
        if (scene == nullptr || !scene->HasMeshes())
        {
            std::cerr << "Failed to load file" << std::endl;
            return 1;
        }
        std::vector<Vertex> vertices;
        const aiMesh* mesh = scene->mMeshes[0];
        for (size_t i = 0; i < mesh->mNumFaces; i++)
        {
            const aiFace face = mesh->mFaces[i];
            const uint32_t idx[3] = 
            {
                face.mIndices[0],
                face.mIndices[1],
                face.mIndices[2],
            };
            const aiVector3D v1 = mesh->mVertices[idx[0]];
            const aiVector3D v2 = mesh->mVertices[idx[1]];
            const aiVector3D v3 = mesh->mVertices[idx[2]];
            vertices.push_back({{v1.x, v1.y, v1.z}, {1.0f, 0.5f, 0.5f}, {0.0f, 0.0f}});
            vertices.push_back({{v2.x, v2.y, v2.z}, {1.0f, 0.5f, 0.5f}, {0.0f, 0.0f}});
            vertices.push_back({{v3.x, v3.y, v3.z}, {1.0f, 0.5f, 0.5f}, {0.0f, 0.0f}});
        }

        VertexBuffer buffer{vertices};
        CameraParams cameraParams;
        cameraParams.fov = 60.0f;
        cameraParams.aspect = (float)width / height;
        cameraParams.position = {0.0f, 1.0f, -3.0f};
        cameraParams.target = {0.0f, 0.0f, 0.0f};
        Camera camera{cameraParams};

        auto view = camera.getViewMatrix();
        auto projection = camera.getProjectionMatrix();

        struct PerFrameData
        {
            glm::mat4 model;
            glm::mat4 view;
            glm::mat4 projection;
            int isWireframe;
        };

        uint32_t perFrameBuffer;
        glCreateBuffers(1, &perFrameBuffer);
        glNamedBufferStorage(perFrameBuffer, sizeof(PerFrameData), nullptr, GL_DYNAMIC_STORAGE_BIT);
        glBindBufferRange(GL_UNIFORM_BUFFER, 0, perFrameBuffer, 0, sizeof(perFrameBuffer));

        while(!window->isClose())
        {
            window->update();

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            program.bind();
            buffer.bind();

            float angle = (float)glfwGetTime();
            glm::mat4 model{1.0f};
            model = glm::rotate(model, angle, {0, 1, 0});

            PerFrameData data;
            data.model = model;
            data.view = view;
            data.projection = projection;
            data.isWireframe = 0;
            glNamedBufferSubData(perFrameBuffer, 0, sizeof(PerFrameData), &data);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glDrawArrays(GL_TRIANGLES, 0, (GLsizei)buffer.size());

            data.isWireframe = 1;
            glNamedBufferSubData(perFrameBuffer, 0, sizeof(PerFrameData), &data);
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glDrawArrays(GL_TRIANGLES, 0, (GLsizei)buffer.size());

            window->display();
        }
        delete scene;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 0;
    }
    return 0;
}