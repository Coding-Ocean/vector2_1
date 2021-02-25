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
        //-----�ŏI�I�ɉ����x�����߂�-----

        //�܂��]�܂��x�N�g�������߂�
        VECTOR2 desiredVel = targetPos - Pos;
        float distance = length(desiredVel);
        if (distance >= 0.01) {
            float speed = MaxSpeed;
            if (distance < 100) {
                //�i100���߂��Ȃ�j�����ɉ����ăX�s�[�h��x������
                speed = MaxSpeed * distance / 100;
            }
            //desiredVel��P�ʃx�N�g��������speed���|����
            desiredVel *= speed / distance;

            //�����x�x�N�g�������߂�
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
    //�^�[�Q�b�g�|�W�V����x,y
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

