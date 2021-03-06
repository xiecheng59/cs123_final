#ifndef MESH_H
#define MESH_H

#include "geometry.h"
#include "common.h"
#include "sceneobject.h"

struct SimpleVertex {
    vec3 position;
    vec3 normal;
    vec2 uv;
};

struct VertexBufferDesc
{
    const void* bufferData;
    uint32_t bufferSize = 0;
    vector<uint8_t> vertexElementSizes;
    uint32_t stride = 0;
};

enum class PrimitiveType 
{
    Points,
    Lines,
    Triangles,
    Patches,
};

typedef vector<uint16_t> IndexBuffer;

class Mesh
{
public:
    Mesh();
    ~Mesh();
    
    void render() const;
    
    // Mesh doesn't own vertex buffer and index buffer, callers are responsible for releasing them
    void setVertexBuffer(const VertexBufferDesc& vertexBuffer,
                         PrimitiveType primitveType);
   
    void setIndexBuffer(const IndexBuffer& indexBuffer);
    
private:
    uint32_t vertexArrayObject_ = 0;
    uint32_t vertexBufferObject_ = 0;
    uint32_t indexBufferObject_ = 0;
    PrimitiveType primitiveType_ = PrimitiveType::Triangles;
    int numElements_ = 0;
};

#endif // MESH_H
