#ifndef COMMON_H
#define COMMON_H

#include <stdlib.h>
#include <stdio.h>
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <list>
using std::list;
#include <map>
using std::map;
#include <assert.h>
#include <math.h>
#include <memory>
using std::shared_ptr;
using std::unique_ptr;
#include <algorithm>
using std::min;
using std::max;
using std::sort;
#include <iostream>
using std::cout;
using std::endl;
//#include <QColor>
//typedef QColor Color;
#include <QVector3D>
typedef QVector3D Color;

#ifdef QT_DEBUG
    #define DEBUG_LOG(message) printf("-->");printf(message);printf("\n");fflush(stdout);
#else
    #define DEBUG_LOG(message)
#endif

class DrawContext;
class Light;
class Camera;
class SceneObject;
class Scene;
class CameraController;
class Texture;
class MeshRenderer;
class Mesh;


// random number between 0 and 1
inline float randf() {
    return (float)rand() / RAND_MAX;
}

// random number between a and b
inline float randf(float a, float b) {
    return randf() * (b - a) + a; 
}

inline float linear_interpolate(float a, float b, float ratio) {
    return a * (1 - ratio) + b * ratio;
}

#endif // COMMON_H
