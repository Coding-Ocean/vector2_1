#include"libOne.h"
class VEHICLE {
public:
    VEHICLE() {
        Pos.x = width / 2+10;
        Pos.y = height / 2+10;
        MaxSpeed = 10;
        MaxForce = 0.6f;
    }
    void chase(VECTOR2 targetPos) {
        //-----最終的に加速度を求める-----

        //まず望まれるベクトルを求める
        VECTOR2 desiredVel = targetPos - Pos;
        float distance = length(desiredVel);
        if (distance >= 0.01) {
            float speed = MaxSpeed;
            if (distance < 100) {
                //（100より近いなら）距離に応じてスピードを遅くする
                speed = MaxSpeed * distance / 100;
            }
            //desiredVelを単位ベクトル化してspeedを掛ける
            desiredVel *= speed / distance;

            //加速度ベクトルを求める
            Acc = desiredVel - Vel;
            distance = length(Acc);
            if (distance > MaxForce) {
                Acc *= MaxForce / distance;
            }
        }
        else {
            Acc *= 0;
            Pos = targetPos;
        }
    }
    void move() {
        Vel += Acc;
        Pos += Vel;
        if (Acc.x == 0.0f && Acc.y == 0.0f) {
            fill(255, 0, 0);
        }
        else {
            fill(0);
        }
        text(Acc.x, 0, 20);
        text(Acc.y, 0, 40);
        text(Vel.x, 0, 80);
        text(Vel.y, 0, 100);
        text(Pos.x, 0, 140);
        text(Pos.y, 0, 160);
    }
    void draw() {
        fill(255, 255, 60);
        strokeWeight(1);
        rectMode(CENTER);
        rect(Pos.x, Pos.y, 60,100,atan2(-Vel.x,Vel.y));
        strokeWeight(5);
        line(Pos.x, Pos.y, Pos.x + Vel.x*20, Pos.y + Vel.y*20);
    }
private:
    float MaxSpeed;
    float MaxForce;
    VECTOR2 Pos;
    VECTOR2 Vel;
    VECTOR2 Acc;
};

void gmain() {
    window(1000, 1000);
    VEHICLE vehicle;
    //ターゲットポジションx,y
    float x = width/2, y = height/2;
    angleMode(DEGREES);
    while (notQuit) {
        clear(90);
        if (isTrigger(MOUSE_LBUTTON)) {
            x = mouseX;
            y = mouseY;
        }
        vehicle.chase(VECTOR2(x, y));
        vehicle.move();
        vehicle.draw();
    }
}

