
#include "Particle.h"

Particle::Particle() : Particle(0, 0, 0) //3D CLASS
{
    
}

Particle::Particle(float x, float y, float z) 
{
//SET UP
    this->location = ofVec3f(x, y, z);
    this->start_location = ofVec3f(x, y, z);
    this->velocity = ofVec3f(0, 0, 0);
    this->acceleration = ofVec3f(0, 0, 0);
    
    this->max_speed = 200;// max move speed/ if too small the particle can not go back
    this->max_force = 2; //
    this->radius = 200; //shape of the movement is sphere
 // set blue color 
    this->bodycolor.setHsb(ofRandom(100,170), 255, 255,175);
    this->bodysize = 40;
    
}
Particle::~Particle()
{
    
}

void Particle::applyForce(ofVec3f force)
{
    this->acceleration += force; // add acceleration to change the speed
}

// Particles need to stop the movement  when the the leapmotion can not detect my hand
void Particle::seek(ofVec3f target) //target location = start ≠≠=location
{
    //get back  find orginial location
    ofVec3f different = this->location - target;
    float distance =  different.length();
    if (distance < this->radius)// If distance samller than radius, the distances will increase
    {
        float m = ofMap(distance, this->radius, 0, 0, this->max_speed);
        different *= m;
    }
    else
    {
        different *= this->max_speed; //when the distance larger than radius, the particle won't move anymore
    }
    
    ofVec3f steer = this->velocity -  different;
    steer.limit(this->max_force);
    this->applyForce(steer); // apply steer value to force
}


//leap motion control the movement of particles
void Particle::move(ofVec3f target, float power)
{
    ofVec3f  different = this->location - target;  // caculate the distance between location and target (hand)
    float distance =  different.length();
    
    if (distance < power){     // when distance smaller than power, particles move
        float m = ofMap(distance, this->radius, 0, 0, this->max_speed);
         different *= m;
    }
    else
    {
        this->seek(this->start_location); // power *= 1-pinch  pinchstrengh = grabhand is closer to 1, so power is closer to 0 , and particles will keep in the start location , add twist
        return;
    }
    
    ofVec3f steer = this->velocity -  different;
    steer.limit(this->max_force);
    this->applyForce(steer);
}

void Particle::update()
{
    // initialize the value of velocity and aaceleration so that the new movement will not be affected by the last movement.
    this->velocity += this->acceleration;
    this->velocity.limit(max_speed);
    this->location += this->velocity;  // location get closer to start location changes by velocity 
    
    this->acceleration *= 0;
    this->velocity *= 0.95; 
    
}

void Particle::draw()
{
    ofPushMatrix();
    ofTranslate(this->location);
    ofSetColor(this->bodycolor);
    //ofDrawSphere(this->body_size);
    ofBox(this->bodysize);
    ofPopMatrix();
}


