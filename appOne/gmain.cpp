#include"libOne.h"
class VEHICLE {
public:
    VEHICLE() {
        MaxSpeed = 10;
        MaxForce = 1;
        Pos.x = random(1000.0f);// % 1000;
        Pos.y = random(1000.0f);// % 1000;
        float deg = random(360.0f);// % 360;
        angleMode(DEGREES);
        Vel.x = cos(deg) * MaxSpeed;
        Vel.y = sin(deg) * MaxSpeed;
        Diameter = 50;
    }
    void chase(VECTOR2 targetPos) {
        VECTOR2 desiredVel = targetPos - Pos;
        float d = length(desiredVel);
        float speed;
        if (d > 100) {
            speed = MaxSpeed;
        }
        else{
            speed = map(d, 0, 100, 0, MaxSpeed);
        }
        //if (d < MaxSpeed) {
        //    speed = 0;
        //}
        desiredVel *= (speed/d);
        //Vel = desiredVel;

        Acc = desiredVel - Vel;
        d = length(Acc);
        if (d > MaxForce) {
            Acc *= (MaxForce/d);
        }
    }
    void move() {
        Pos += Vel;
        Vel += Acc;
        //Acc *= 0;
    }
    void draw() {
        fill(160, 200, 255);
        circle(Pos.x, Pos.y, Diameter);
    }
private:
    float MaxSpeed;
    float MaxForce;
    VECTOR2 Pos;
    VECTOR2 Vel;
    VECTOR2 Acc;
    float Diameter;
};

/*
Vehicle.prototype.behaviors = function() {
    arrive = this.arrive(this.target);
    this.applyForce(arrive);

    mouse = createVector(mouseX, mouseY);
    flee = this.flee(mouse);
    this.applyForce(flee);
}
Vehicle.prototype.arrive = function(target) {
    desired = p5.Vector.sub(target, this.pos);
    d = desired.mag();
    speed = this.maxspeed;
    if (d < 100) {
        speed = map(d, 0, 100, 0, this.maxspeed);
    }
    desired.setMag(speed);
    steer = p5.Vector.sub(desired, this.vel);
    steer.limit(this.maxforce);
    return steer;
}
Vehicle.prototype.flee = function(target) {
    desired = p5.Vector.sub(target, this.pos);
    d = desired.mag();
    //steer.mult(0); 
    if (d < 80) {
        desired.setMag(this.maxspeed);
        desired.mult(-1);
        steer = p5.Vector.sub(desired, this.vel);
        steer.limit(this.maxforce);
        steer.mult(10);
    }
    return steer;
}
Vehicle.prototype.applyForce = function(f) {
    this.acc.add(f);
}

Vehicle.prototype.update = function() {
    this.pos.add(this.vel);
    this.vel.add(this.acc);
    this.acc.mult(0);
}

Vehicle.prototype.show = function() {
    stroke(255);
    strokeWeight(this.r);
    point(this.pos.x, this.pos.y);
}
*/

void gmain() {
    window(1000, 1000);
    VEHICLE vehicle;
    while (notQuit){
        vehicle.chase(VECTOR2(mouseX, mouseY));
        vehicle.move();
        clear(220);
        vehicle.draw();
    }
}