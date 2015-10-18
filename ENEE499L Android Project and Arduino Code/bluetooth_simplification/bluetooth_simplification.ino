#include <NewPing.h>
#include <Servo.h>
#include <SoftwareSerial.h>

#define LEFT false
#define RIGHT true

#define STABLE_WALL_UPPER_BOUND 200
#define NUM_SAMPLES_STABLE 10
#define IGNORE_THRESHOLD 200
#define MAX_DISTANCE 200
#define SPEED 100

NewPing sonar[4] = { // Sensor object array.
  NewPing(4, 4, MAX_DISTANCE),
  NewPing(5, 5, MAX_DISTANCE),
  NewPing(7, 7, MAX_DISTANCE),
  NewPing(8, 8, MAX_DISTANCE)
};

// Struct of flags, used for logic
struct flags {
  long duration;
  boolean ondoor;
  boolean heavy;
  boolean pictureflag;
  boolean skipFlag;
  long stable;
}flag[4];

int bluetoothTx = 2;
int bluetoothRx = 3;

long diff;
long stability[4];
int printCtr;
boolean camera;

Servo servo;
Servo motor;
Servo tilt;
Servo rotation;

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);
char inputString = 'a';

void setup()
{
      // Initialization
      servo.attach(9);
      motor.attach(10);
      tilt.attach(11);
      rotation.attach(12);
      
      // bluetooth
      bluetooth.begin(115200);
      bluetooth.print("$$$");
      delay(100);
      bluetooth.println("U,9600,N");
      bluetooth.begin(9600);
      
      // Initialize the flag struct
      for(int i = 0; i < 4; i++)
        {
          //Eric: median of multiple stability values
          flag[i].stable = sonar[i].ping_median(NUM_SAMPLES_STABLE);      
          delay(30);
          flag[i].ondoor = false;
          flag[i].heavy = false;
          flag[i].pictureflag = false;
          flag[i].skipFlag = false;
        }
        

      printCtr = 0;
      while(true)
      {
          if(printCtr > 100000)
            bluetooth.print("WAITING\n");
          printCtr = printCtr > 100000 ? 0 : printCtr+1;
          if(bluetooth.available() && bluetooth.read() == 'O')
            break;
      }
    
      // Initial servo speeds 
      tilt.write(105);
      rotation.write(0);
      motor.write(SPEED);
      servo.write(90);
      // Start 
      camera = LEFT;
      
}
    
void loop()
{
      //Bluetooth test
      if(printCtr > 10)
        bluetooth.print("WORKING\n");
      printCtr = printCtr > 10 ? 0 : printCtr+1;
  
      for(int i = 0; i < 4; i++)
      {
          flag[i].duration = sonar[i].ping();
          delay(30);    
          
          // out of range
          if(flag[i].duration == 0)
          {
              flag[i].ondoor = true;
              stability[i] = STABLE_WALL_UPPER_BOUND;
              continue; 
          }
          
          /* If the duration is within a certain range of the stable value, we are on a wall */
          stability[i] = flag[i].duration - flag[i].stable;
          flag[i].ondoor = (stability[i] >= STABLE_WALL_UPPER_BOUND);
      }
      
      /* Doorss */
      
      /*Eric: comment - if you accidentally miss the end of a door pictureflag won't update and you will, in turn, miss the start of a door on the same side
              consider setting pictureflag to be some sort of timestamp (millis()) which becomes stale after some time    */
      /* END door, RHS */
      if(flag[0].ondoor == true && flag[1].ondoor == false && flag[0].pictureflag == true)
      {
          motor.write(90);
          takePic(0, false);
      }
      /* BEGIN door, RHS */
      else if(flag[0].ondoor == false && flag[1].ondoor == true && flag[0].pictureflag == false)
      {
          
          motor.write(90);
          // Camera is on the LHS, move to RHS
          if(camera == LEFT)
            {
              for(int r = 105; r > 75; r--)
                {
                  tilt.write(r);
                  delay(10);
                }
              for(int i = 0; i < 180; i++)
                {
                  rotation.write(i);
                  delay(10);
                }
              camera = RIGHT;
            }
          takePic(0, true);
      }  
      /* BEGIN door, LHS */
      else if(flag[2].ondoor == true && flag[3].ondoor == false && flag[3].pictureflag == false)
      {
          motor.write(90);
          // Camera is on the RHS, move to LHS
          if(camera == RIGHT)
          {
            for(int s = 75; s < 105; s++)
              {
                tilt.write(s);
                delay(10);
              }
            for(int j = 180; j > 0; j--)
              {
                rotation.write(j);
                delay(10);
              }
            camera = LEFT;
          }
          takePic(3, true);
      }
      /* END door, LHS */
        else if(flag[2].ondoor == false && flag[3].ondoor == true && flag[3].pictureflag == true)
      {
          motor.write(90);
          takePic(3, false);
      }


      /*Eric: comment - you should check stability values here for sanity - i.e. if you come across a trashcan
        you will have a large negative value for stability on one side, indicating you should set it to what 
        you're reading on another sensor same side */
      
      //Both sensors on the right side reading a trashcan
      if(abs(stability[0]) > IGNORE_THRESHOLD || abs(stability[1]) > IGNORE_THRESHOLD)
      {
          //If left side is reading a trashcan too...
          if(abs(stability[2]) > IGNORE_THRESHOLD || abs(stability[3]) > IGNORE_THRESHOLD)
          {
            // going straight
            servo.write(90);
            motor.write(SPEED);
            return;
          }
          else
          {
            // throw away RHS and stabilize using LHS
            diff = (stability[2] + stability[3]) / 2;
            diff = map(diff, -200, 200, 0, 180);
            servo.write(diff);
            return;
          }
      }
   
      //Same thing for left side
      if(abs(stability[2]) > IGNORE_THRESHOLD || abs(stability[3]) > IGNORE_THRESHOLD)
      {
          //If right side is reading a trashcan too...
          if(abs(stability[0]) > IGNORE_THRESHOLD || abs(stability[1]) > IGNORE_THRESHOLD)
          {
              // Go straight
              servo.write(90);
              motor.write(SPEED);
              return;
          }
          else
          {
             //Throw away LHS readings and stabilize using RHS
             diff = -(stability[0] + stability[1]) / 2;
             diff = map(diff, -200, 200, 0, 180);
             servo.write(diff);
             return;  
          }
      }     
      
      //So if you reach this point, you shouldn't be seeing any odd objects, and stability should be in range (-IGNORE_THRESHOLD, IGNORE_THRESHOLD)
      /* Begin to stabilize */
      if(flag[0].ondoor == false && flag[1].ondoor == false && flag[2].ondoor == false && flag[3].ondoor == false)
      {
          diff = ((stability[2] + stability[3]) - (stability[0] + stability[1])) / 4;
          diff = map(diff, -200, 200, 0, 180);
          servo.write(diff);
      }
 }
 
void takePic(int q, boolean f)
  {
      if(flag[q].skipFlag && f == false)
      {
        flag[q].skipFlag = false;
        flag[q].pictureflag = f;
        motor.write(SPEED);
        return;
      }
      
      delay(2500);
      bluetooth.print("TAKE PICTURE \n");
      while(true)
      {  
        if(bluetooth.available())
          {
            char received = (char)bluetooth.read();
                //Switch
              switch(received)
                {
                   case 'S': 
                   {
                       motor.write(90);
                       delay(1000000);
                       return;
                   }
                   case 'C':
                   {
                       motor.write(SPEED);
                       flag[q].pictureflag = f;
                       return;
                   }
                   case 'K':
                   {
                       motor.write(SPEED);
                       flag[q].pictureflag = f;
                       flag[q].skipFlag = true;
                       return;
                   }
                   default: 
                    {
                      break;
                    }
                }
            } 
      }
  } 
