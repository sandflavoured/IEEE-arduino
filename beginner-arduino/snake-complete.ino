// Including the NeoPixel library and its functions
#include <Adafruit_NeoPixel.h>

// This means: replace "PIN" with 3 
// and "NUMLEDS" with 36 wherever they appear
#define PIN 3
#define NUMLEDS 36

// This is a 6x6 2D array containing integer values.
// It will represent the state of each pixel on the grid.
// 'Unsigned' just means they will not be negative.
unsigned int state[6][6] = {
  {0,0,0,0,0,0},
  {0,0,0,0,0,0},
  {0,0,0,0,0,0},
  {0,0,0,0,0,0},
  {0,0,0,0,0,0},
  {0,0,0,0,0,0}
};

// Declaring an instance of the neopixels called "screen"
// (part of the NeoPixel library)
Adafruit_NeoPixel screen = Adafruit_NeoPixel(NUMLEDS, PIN, NEO_GRB + NEO_KHZ800);

int headLocation[2] = {1,1};
int pastLocations[12][2];
int snakeLength = 3;

// The direction the snake will travel in.
// 0: UP
// 1: RIGHT
// 2: DOWN
// 3: LEFT
int snakeDirection = 1;

void setup()
{
  screen.begin();		// start the neopixels
  
  screen.show();		// turn off all LEDs
    
  pinMode(3, OUTPUT);			// set 3 as output pin
  
  for (int i = 4; i <=7; i++)	// set pins 4 to 7 as inputs
  {
    pinMode(i, INPUT);
  }
  
  /*Serial.begin(9600);*/ 	// The reason this is 9600 is that
  							// the decoding of the data is at
  							// a rate of 9600 baud by default.
  							// Not using it here just to save 
  							// on performance.
}

void loop()
{
  setDirection();
  delay(100);
  moveSnake(headLocation, pastLocations, snakeDirection);
  statesToLights(state);
  screen.show();
  delay(100);
}



void statesToLights(unsigned int state[6][6]) 
{
  for (int i = 0; i <= 5; i++) {
    for (int j = 0; j <= 5; j++) {
      if (state[i][j] == 1) {
        screen.setPixelColor(i*6+j,255,0,0);	// Red
      }
      else if (state[i][j] == 2) {
      	screen.setPixelColor(i*6+j,0,255,0);	// Green
      }
      else if (state[i][j] == 0) {
      	screen.setPixelColor(i*6+j,0,0,0);		// Off
      }
      else {
        screen.setPixelColor(i*6+j,0,0,255);	// Blue
      }
    }
  }
  // ============================
  // || *** Your code here *** ||
  // ============================
  
  // you will need to look at state[][] and
  // set colours on the screen according to this:
  // 0:off, 1:red, 2:green, 3:blue

  // hint: iterate through the rows of state[][]
  // then interate through the columns of state[][]
  // check the value of state[x][y] and set colors accordingly

  
  // some code you may need:

    // for (int i=0; i<=X; i++) --this will repeat code X many times
    // {
    // 	*more code here*
    // }

    // strip.setPixelColor(position,R,G,B);
}

void setDirection()
{
  if (digitalRead(5) == 1) 		// UP
  	snakeDirection = 0;
  else if (digitalRead(4) == 1)	// RIGHT
  	snakeDirection = 1;
  else if (digitalRead(6) == 1)	// DOWN
  	snakeDirection = 2;
  else if (digitalRead(7) == 1)	// LEFT
  	snakeDirection = 3;
}

void moveSnake(int headLocation[2], int pastLocations[12][2], int snakeDirection)
{
  // update pastLocations
  for (int i=11; i>=1; i--)
      {
        pastLocations[i][0] = pastLocations[i-1][0];
        pastLocations[i][1] = pastLocations[i-1][1];
      }
      pastLocations[0][0] = headLocation[0];
      pastLocations[0][1] = headLocation[1];

  // new headLocation
  switch (snakeDirection)
  {
    case 0:		// UP
      headLocation[0] = headLocation[0] - 1;
      break;
    case 1:		// RIGHT
      headLocation[1] = headLocation[1] + 1;
      break;
    case 2:		// DOWN
      headLocation[0] = headLocation[0] +  1;
      break;
    case 3:		// LEFT
      headLocation[1] = headLocation[1] - 1;
      break;    
  }

  // show head
  state[headLocation[0]][headLocation[1]] = 1;

  // delete tail
  for (int j = 11; j >= snakeLength; j--)
  {
    state[pastLocations[j][0]][pastLocations[j][1]] = 0;
  }
}