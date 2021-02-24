#include"libOne.h"
class VEHICLE {
public:
    VEHICLE() {
        Diameter = 50;
        Pos.x = width / 2;
        Pos.y = height / 2;
        Vel.x = 0;
        Vel.y = 0;
        MaxSpeed = 10;
        MaxForce = 1;
    }
    void chase(VECTOR2 targetPos) {
        //-----最終的に加速度を求める-----

        //まず望まれるベクトルを求める
        VECTOR2 desiredVel = targetPos - Pos;
        float distance = length(desiredVel);
        float speed = MaxSpeed;
        if (distance < 100) {
            //（100より近いなら）距離に応じてスピードを遅くする
            speed = MaxSpeed * distance / 100;
        }
        fill(0);
        text(speed, 0, 20);
        //desiredVelを単位ベクトル化してspeedを掛ける
        desiredVel *= speed / distance;
      
        //加速度ベクトルを求める
        Acc = desiredVel - Vel;
        distance = length(Acc);
        text(distance, 0, 40);
        if (distance > MaxForce) {
            Acc *= MaxForce / distance;
        }
        
    }
    void move() {
        Pos += Vel;
        Vel += Acc;
    }
    void draw() {
        fill(255, 255, 60);
        strokeWeight(1);
        rectMode(CENTER);
        rect(Pos.x, Pos.y, 60,100,atan2(-Vel.x,Vel.y));
        strokeWeight(5);
        line(Pos.x, Pos.y, Pos.x + Vel.x*2, Pos.y + Vel.y*2);
    }
private:
    float MaxSpeed;
    float MaxForce;
    VECTOR2 Pos;
    VECTOR2 Vel;
    VECTOR2 Acc;
    float Diameter;
};
void gmain() {
    window(1000, 1000);
    VEHICLE vehicle;
    float deg = 0;
    angleMode(DEGREES);
    while (notQuit) {
        clear(90);
        float x = cos(deg) * 400 + width / 2;
        float y = -sin(deg * 2) * 400 + height / 2;
        deg += 2;
        vehicle.chase(VECTOR2(x, y));
        vehicle.move();
        line(0, height / 2, width, height / 2);
        line(width / 2, 0, width / 2, height);
        vehicle.draw();
        text(130.0 / 1700000, 0, 100);
    }
}

