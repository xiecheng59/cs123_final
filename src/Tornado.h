#ifndef TORNADO_H
#define TORNADO_H

#define NUM_CONTROL_POINTS 15

#include "common.h"
#include "sceneobject.h"
#include "terrain.h"

// This is the logical tornado (not the visual tornado) - change the position of this tornado's
// origin and control points to move the tornado around in the world.
class Tornado
{
public:
    Tornado();
    Tornado(vec3 startOrigin, Terrain* terr);
    virtual ~Tornado();
    float getHeight(){return m_height;} // Allow access to height and age.
    float getAge(){return m_age;}
    vec3 getOrigin(){return m_origin;}  // Fetch the origin and control points for the tornado.
    vec3* getControlPoints(){return m_controlPoints;}
    float getSpeed(){return m_speed;}
    float getForce(){return m_force;}
    void setSpeed(float sp){m_speed = sp;}
    void setForce(float fc){m_force = fc;}
    vec3 interp(float height);          // Get the location of the tornado spine at y-value height.
    vec3 interpLocal(float height);     // Same as interp, but in relation to the tornado's base.
    float interpWidth(float height);    // Get the tornado width at a given local height...
    // Give the tornado somewhere to go! Just x and z taken into account.
    void setDestination(vec3 dest){m_destination = dest;}
    // Use a heightmap for this tornado!
    void setTerrain(Terrain* terr){m_terrain = terr;}
    virtual void update(float dt);

protected:
    Terrain* m_terrain;
    float initWidth(float height);      // Initial width function for the tornado.
    float m_height;
    float m_age;            // How long has this tornado been active? Useful if we want to descend from the sky.
    vec3 m_origin;          // The point where the tornado hits the terrain height map.
    vec3* m_controlPoints;  // An array of the control points needed for the tornado - these are offsets from origin!
    float* m_controlWidths; // The width of the tornado at each step!
    float* m_initWidths;    // The original width of the tornado at each step!
    virtual void init();    // Part of both constructors.
    vec3 m_destination;
    float m_speed;
    float m_force;
private:
    void capControls();     // maintain outer bounds for comtrol points and control widths.
};

#endif // TORNADO_H
