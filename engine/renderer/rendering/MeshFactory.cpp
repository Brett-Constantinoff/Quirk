#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include "../../core/utils/Utils.hpp"

#include "MeshFactory.hpp"

using namespace Quirk::Engine::Core::Utils;

namespace Quirk::Engine::Renderer::Rendering
{
    void MeshFactory::init()
    {
        m_meshCache.reserve(static_cast<size_t>(MeshTypes::Count));
    }

    void MeshFactory::shutdown()
    {
        m_meshCache.clear();
    }

    std::shared_ptr<MeshComponent> MeshFactory::createMesh(MeshTypes type, const char* path)
    {
        // TODO : Handle custom mesh loading
        return isPrimitiveMesh(type) ? createPrimitiveMesh(type, path) : nullptr;
    }

   void MeshFactory::loadMeshesFromFile(std::shared_ptr<MeshComponent>& mesh, const char* path, bool isPrimitive)
    {
        Assimp::Importer importer{};
        const aiScene* scene{ importer.ReadFile(path,
            aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType) };

        if (!scene || !scene->HasMeshes())
        {
            quirkExit("Failed to load model from - " + std::string{ path });
            return; // the compiler is not smart enough to know that quirkExit will terminate the program
        }

        // TODO: Handle multiple meshes in a single file
        if (isPrimitive)
        {
            const aiMesh* loadedMesh{ scene->mMeshes[0] };

            mesh->vertices.reserve(loadedMesh->mNumVertices);
            for (uint32_t i{ 0 }; i < loadedMesh->mNumVertices; ++i)
            {
                const aiVector3D& vertex{ loadedMesh->mVertices[i] };
                mesh->vertices.emplace_back(vertex.x, vertex.y, vertex.z);
            }

            if (loadedMesh->HasNormals())
            {
                mesh->normals.reserve(loadedMesh->mNumVertices);
                for (uint32_t i{ 0 }; i < loadedMesh->mNumVertices; ++i)
                {
                    const aiVector3D& normal{ loadedMesh->mNormals[i] };
                    mesh->normals.emplace_back(normal.x, normal.y, normal.z);
                }
            }

            mesh->indices.reserve(loadedMesh->mNumFaces * 3);
            for (uint32_t i{ 0 }; i < loadedMesh->mNumFaces; ++i)
            {
                const aiFace& face{ loadedMesh->mFaces[i] };
                mesh->indices.push_back(face.mIndices[0]);
                mesh->indices.push_back(face.mIndices[1]);
                mesh->indices.push_back(face.mIndices[2]);
            }

            mesh->vertexCount = static_cast<uint32_t>(mesh->vertices.size());
            mesh->indexCount = static_cast<uint32_t>(mesh->indices.size());
		}
    }

   bool MeshFactory::isPrimitiveMesh(MeshTypes type)
   {
       switch (type)
       {
           case MeshTypes::Quad:
           case MeshTypes::Sphere:
           case MeshTypes::Cube:
           case MeshTypes::Cylinder:
           case MeshTypes::Cone:
           case MeshTypes::Torus:
               return true;
           default:
               return false;
       }
   }

    std::shared_ptr<MeshComponent> MeshFactory::getMesh(MeshTypes type)
    {
        auto iterator{ m_meshCache.find(type) };
        return (iterator != m_meshCache.end()) ? iterator->second : nullptr;
    }

    std::shared_ptr<MeshComponent> MeshFactory::createPrimitiveMesh(MeshTypes type, const char* path)
    {
        if (type == MeshTypes::Quad)
            return createQuadMesh();

        if (auto mesh{ getMesh(type) })
            return mesh;
        else
        {
            mesh = std::make_shared<MeshComponent>();
            loadMeshesFromFile(mesh, path, true);
            m_meshCache.emplace(type, mesh);
            return mesh;
        }
    }

    std::shared_ptr<MeshComponent> MeshFactory::createQuadMesh()
    {
        if (auto mesh{ getMesh(MeshTypes::Quad)})
            return mesh;
        else
        {
            mesh = std::make_shared<MeshComponent>();

            mesh->vertices = {
                { -0.5f, -0.5f, 0.0f },
                {  0.5f, -0.5f, 0.0f },
                {  0.5f,  0.5f, 0.0f },
                { -0.5f,  0.5f, 0.0f }
            };
            mesh->vertexCount = static_cast<uint32_t>(mesh->vertices.size());

            mesh->indices = {
                0, 1, 2,
                2, 3, 0
            };
            mesh->indexCount = static_cast<uint32_t>(mesh->indices.size());

            m_meshCache.emplace(MeshTypes::Quad, mesh);

            return mesh;
        }
        
    }
} // namespace Quirk::Engine::Renderer::Rendering
