#include "texturecache.h"
#include "texture2d.h"
#include "texturecube.h"

static TextureCache* g_instance = NULL;

TextureCache *TextureCache::getInstance()
{
    if (!g_instance) {
        g_instance = new TextureCache;
    }
    return g_instance;
}

Texture *TextureCache::acquire(string name, TextureType type)
{
    Texture* p = getResource(name);
    if (p) {
        return p;
    }
    
    string filename = "textures/" + name;
    
    if (type == TextureType::Texture2D) {
        p = new Texture2D;
    }
    else if (type == TextureType::TextureCube) {
        p = new TextureCube;
    }
    
    p->load(filename);
    
    addResource(name, p);
    
    return p;
}

TextureCache::~TextureCache()
{
    delete g_instance;
}
