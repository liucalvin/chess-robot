#ifndef SERVO_ARM
#define SERVO_ARM

#include <Servo.h>

class ServoArm
{
protected:
  Servo servo;
  int id;
  int pin;
  int current_pos;
  int DEFAULT_POS;
  int MIN_POS;
  int MAX_POS;

public:
  ServoArm();
  void Init(int pin, int id, int default_angle, int min, int max);
  int getCurrentPosition();
  int read();
  virtual void setPosition(int new_pos);
  virtual void resetPosition();
  void moveInParallel(int pos, ServoArm &other, int otherPos);
};

#endif
