
#include <Stepper.h>
#include <IRremote.h>


/*----- Variables, Pins -----*/
#define STEPS  32   // Number of steps per revolution of Internal shaft
int  Steps2Take;  // 2048 = 1 Revolution
int receiver = 6; // Signal Pin of IR receiver to Arduino Digital Pin 6

#define RELAY_ON 0
#define RELAY_OFF 1
#define Relay_1 1
#define INFLATE 0xfda05f
#define UP 0xFF629D
#define DOWN 0xFFA857
#define RIGHT
#define LEFT

/*-----( Declare objects )-----*/
// Setup of proper sequencing for Motor Driver Pins
// In1, In2, In3, In4 in the sequence 1-3-2-4

Stepper small_stepper(STEPS, 8, 10, 9, 11);
IRrecv irrecv(receiver);    // create instance of 'irrecv'
decode_results results;     // create instance of 'decode_results'

void setup()
{ 
  irrecv.enableIRIn(); // Start the receiver
  digitalWrite(Relay_1, RELAY_OFF);
  pinMode(Relay_1, OUTPUT);
  delay(4000);
}

void loop()
{
if (irrecv.decode(&results)) // have we received an IR signal?

  {
    switch(results.value)

    {

      case UP:
                      small_stepper.setSpeed(500); //Max seems to be 700
                      Steps2Take  =  2048;  // Rotate CW
                      small_stepper.step(Steps2Take);
                      delay(2000); 
                      break;

      case DOWN:
                      small_stepper.setSpeed(500);
                      Steps2Take  =  -2048;  // Rotate CCW
                      small_stepper.step(Steps2Take);
                      delay(2000); 
                      break;

      case INFLATE:
                 digitalWrite(Relay_1, RELAY_ON);
                 delay(9000);
                 digitalWrite(Relay_1, RELAY_OFF);    
    }
    
      irrecv.resume();
  }  
}