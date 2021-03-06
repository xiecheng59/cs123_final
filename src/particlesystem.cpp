#include "GL/glew.h"
#include "particlesystem.h"
#include "mesh.h"
#include "drawcontext.h"
#include "common.h"
#include "particlematerial.h"

ParticleSystem::ParticleSystem()
{   
    ParticleMaterial* material = new ParticleMaterial;
    setMaterial(material);
    mesh_ = new Mesh;
}

ParticleSystem::~ParticleSystem()
{
    delete mesh_;
}

void ParticleSystem::renderGeometry(DrawContext &context)
{   
    update(context.deltaTime);
    
    if (particles_.size() < 1) {
        return;
    }
    
    Particles particles = particles_;
    
    if (renderingOrder_ == RenderingOrder::Reversed) {
        std::reverse(begin(particles), end(particles));
    }
    else if (renderingOrder_ == RenderingOrder::OldestFirst) {
        std::sort(begin(particles), end(particles), [](const Particle& left, const Particle& right) {
            return left.life > right.life;
        });
    }
    else if (renderingOrder_ == RenderingOrder::YoungestFirst) {
        std::sort(begin(particles), end(particles), [](const Particle& left, const Particle& right) {
            return left.life < right.life;
        });
    }
    
    VertexBufferDesc desc;
    desc.bufferData = particles.data();
    desc.bufferSize = particles.size() * sizeof(Particle);
    desc.vertexElementSizes = {3, 1, 1, 3, 1};
    desc.stride = sizeof(Particle);
          
    mesh_->setVertexBuffer(desc, PrimitiveType::Points);
    
    mesh_->render();
}

void ParticleSystem::setParticleTexture(Texture *texture)
{
    ParticleMaterial* material = static_cast<ParticleMaterial *>(material_);
    material->setTexture(texture);
}

void ParticleSystem::update(float dt)
{   
    timeElapsed_ += dt;
    
    auto it = begin(particles_);
    while (it != end(particles_)) {
        Particle& particle = *it;
        particle.life += dt;
        if (particle.life >= particle.maxLife) {
            particles_.erase(it);
        }
        else {
            this->updateParticle(particle, dt);
            it++;
        }
    }        
    
    float numParticles = emissionRate_ * dt;
    numParticlesToSpawn_ += numParticles;
    
    uint32_t count = 0;
    if (particles_.size() < maxParticleCount_) {
        count = min((int)(maxParticleCount_ - particles_.size()), (int)numParticlesToSpawn_);
    }
    
    numParticlesToSpawn_ -= count;

    for (uint32_t i = 0; i < count; i++) {
        Particle particle;
        this->spawnParticle(&particle);
        particles_.push_back(particle);
    }
}

void ParticleSystem::spawnParticle(Particle *particle)
{
    
}

void ParticleSystem::updateParticle(Particle &particle, float dt)
{
    
}

uint32_t ParticleSystem::emissionRate() const
{
    return emissionRate_;
}

void ParticleSystem::setEmissionRate(int emissionRate)
{
    emissionRate_ = emissionRate;
}

uint32_t ParticleSystem::maxParticleCount() const
{
    return maxParticleCount_;
}

void ParticleSystem::setMaxParticleCount(int maxParticleCount)
{
    maxParticleCount_ = maxParticleCount;
}

RenderingOrder ParticleSystem::renderingOrder() const
{
    return renderingOrder_;
}

void ParticleSystem::setRenderingOrder(RenderingOrder renderingOrder)
{
    renderingOrder_ = renderingOrder;
}




