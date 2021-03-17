//***************************************************************************
//***********************************************************************/
#include <Arduino.h>
#include <stdlib.h>


//IO    
#define LEDARRAY_D 2
#define LEDARRAY_C 3
#define LEDARRAY_B 4
#define LEDARRAY_A 5
#define LEDARRAY_G 6
#define LEDARRAY_DI 7
#define LEDARRAY_CLK 8
#define LEDARRAY_LAT 9


unsigned char Display_Buffer[2];

unsigned char screen[1][32] = {
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};
/* For copypasting
unsigned char state[16][16] =
{
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};
*/
unsigned char state[16][16] =
{
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

unsigned char winState[16][16] =
{
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,1,1,1,0,0,1,1,1,0,0,0,0},
  {0,0,0,1,0,0,0,1,1,0,0,0,1,0,0,0},
  {0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0},
  {0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0},
  {0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0},
  {0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0},
  {0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

unsigned char loseState[16][16] =
{
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0},
  {0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0},
  {0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0},
  {0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0},
  {0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0},
  {0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0},
  {0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};



bool isFood = false;
bool isSnake = false;
int snakeLength = 3;
int headLocation[2] = {-1,-1};
int pastLocations[30][2] = {    {-1,-1},
                                {-1,-1},
                                {-1,-1},
                                {-1,-1},
                                {-1,-1},
                                {-1,-1},
                                {-1,-1},
                                {-1,-1},
                                {-1,-1},
                                {-1,-1},
                                {-1,-1},
                                {-1,-1},
                                {-1,-1},
                                {-1,-1},
                                {-1,-1},
                                {-1,-1},
                                {-1,-1},
                                {-1,-1},
                                {-1,-1},
                                {-1,-1},
                                {-1,-1},
                                {-1,-1},
                                {-1,-1},
                                {-1,-1},
                                {-1,-1},
                                {-1,-1},
                                {-1,-1},
                                {-1,-1},
                                {-1,-1},
                                {-1,-1}
};
int foodLocation[2] = {-1,-1};
bool foodEaten = false;
bool Game_Won = false;
int snakeDirection = -1;
bool Game_Lost = false;
unsigned long previousTime = 0;
void(* resetFunc) (void) = 0;

void setup()
{
  Serial.begin(9600);
	pinMode(LEDARRAY_D, OUTPUT); 
	pinMode(LEDARRAY_C, OUTPUT);
	pinMode(LEDARRAY_B, OUTPUT);
	pinMode(LEDARRAY_A, OUTPUT);
	pinMode(LEDARRAY_G, OUTPUT);
	pinMode(LEDARRAY_DI, OUTPUT);
	pinMode(LEDARRAY_CLK, OUTPUT);
	pinMode(LEDARRAY_LAT, OUTPUT);
  randomSeed(analogRead(0));
  Serial.println("Starting...");
}

void loop()
{
  unsigned long currentTime = millis();

  if (Game_Won == false && Game_Lost == false)  // game state
  {    
    if (currentTime - previousTime > 200)   // 0.2s non-blocking timer
    {
      //Serial.println(snakeDirection, DEC);
      //Serial.print(foodLocation[0], DEC);
      //Serial.println(foodLocation[1], DEC);
      //Serial.print(headLocation[0], DEC);
      //Serial.print(", ");
      //Serial.println(headLocation[1], DEC);
      previousTime = currentTime;
      if (isSnake == false)
        spawnSnake(state, &snakeLength, &isSnake, headLocation, pastLocations, &snakeDirection);
      
      while (isFood == false)
        spawnFood(state, &isFood, foodLocation);

      // choose a direction to go in
      decide(&snakeDirection, headLocation, foodLocation);
      // move the snake
      moveSnake(headLocation, pastLocations, snakeDirection);
      // check for food eaten
      checkFoodEaten(headLocation, foodLocation);
      // check for lose condition
      checkLose(headLocation, pastLocations, &Game_Lost);
      
      if (foodEaten)
      {
        addLength(&snakeLength, &foodEaten);
        isFood = false;
        foodLocation[0] = -1;
        foodLocation[1] = -1;
      }
      
      if (snakeLength >= 18)
      {
        Game_Won = true;
        isSnake = false;
      }
    }
    UpdateScreen(screen, state);
    Display(screen);
  }
  else if (Game_Won)                  // win state
  {
    UpdateScreen(screen, winState);
    Display(screen);
    // nonblocking 5 sec pause timer here
    if (currentTime - previousTime > 5000)
    {
      previousTime = currentTime;
      isSnake = false;
      Game_Won  = false;
      Game_Lost = false;
      //Serial.println("Win, Respawning");
      resetFunc();
    }
  }
  else if (Game_Lost)                 // lose state
  {
    UpdateScreen(screen, loseState);
    Display(screen);
    // nonblocking 5 sec pause timer here
    if (currentTime - previousTime > 5000)
    {
      previousTime = currentTime;
//      Serial.print(foodLocation[0], DEC);
//      Serial.print(", ");
//      Serial.println(foodLocation[1], DEC);
//      Serial.println("Loss, Respawning");
      resetFunc();
    }
  }
  
}



//************************************************************

//*************************************************************

void decide(int *snakeDirection, int headLocation[2], int foodLocation[2])
{
  switch (*snakeDirection)
  {
    case 0:     // going up
      if (foodLocation[0] < headLocation[0])    // going the right way, keep going
      {
        break;  
      }
      else if (foodLocation[0] >= headLocation[0])    // have to turn left or right
      {
        if (foodLocation[1] < headLocation[1])  // more left
          turnLeft(snakeDirection);        
        else if (foodLocation[1] >= headLocation[1])   // more right or behind
          turnRight(snakeDirection);           
        break;
      }
    case 1: // going right
      if (foodLocation[1] > headLocation[1])    // going the right way, keep going
      {
        break;  
      }
      else if (foodLocation[1] <= headLocation[1])    // have to turn left or right
      {
        if (foodLocation[0] < headLocation[0])    // more up
          turnLeft(snakeDirection);
        else if (foodLocation[0] >= headLocation[0])  // more down or behind
          turnRight(snakeDirection);
        break;
      }
    case 2: // going down
      if (foodLocation[0] > headLocation[0])    // going the right way, keep going
      {
        break;  
      }
      else if (foodLocation[0] <= headLocation[0])    // have to turn left or right
      {
        if (foodLocation[1] < headLocation[1])    // more left
          turnRight(snakeDirection);
        else if (foodLocation[1] >= headLocation[1])  // more right or behind
          turnLeft(snakeDirection);
        break;
      }
    case 3: // going left
      if (foodLocation[1] < headLocation[1])    // going the right way, keep going
      {
        break;  
      }
      else if (foodLocation[1] >= headLocation[1])    // have to turn left or right
      {
        if (foodLocation[0] < headLocation[0])    // more up
          turnRight(snakeDirection);
        else if (foodLocation[0] >= headLocation[0])  // more down or behind
          turnLeft(snakeDirection);
        break;
      }
  }
}

void turnRight(int *snakeDirection)
{
  //Serial.println("Turn Right!");
  if (*snakeDirection == 3)
  {
    *snakeDirection = 0;
  }
  else *snakeDirection = *snakeDirection + 1;
}

void turnLeft(int *snakeDirection)
{
  //Serial.println("Turn Left!");
  if (*snakeDirection == 0)
    *snakeDirection = 3;
  else *snakeDirection = *snakeDirection - 1;
}

void checkFoodEaten(int headLocation[2], int foodLocation[2])
{
  if (headLocation[0] == foodLocation[0] && headLocation[1] == foodLocation[1])
    foodEaten = true;
}

void checkLose(int headLocation[2], int pastLocations[30][2], bool *Game_Lost)
{
  bool collision = false;                                                                             // dynamic memory allocation --
  for(int i = 0; i < snakeLength; i++)
  {
    if (headLocation[0] == pastLocations[i][0] && headLocation[1] == pastLocations[i][1])
    {
      collision = true;
      Serial.println("Collision");
    }
  }
  
  if (headLocation[0] < 0 || headLocation[0] > 15 || headLocation[1] < 0 || headLocation[1] > 15 || collision == true)
  {
    *Game_Lost = true;
    Serial.println("Failture");
  }
}

// move the snake on each 0.4s interval
void moveSnake(int headLocation[2], int pastLocations[30][2], int snakeDirection)
{
  // update pastLocations
  for (int i=29; i>=1; i--)
      {
        pastLocations[i][0] = pastLocations[i-1][0];
        pastLocations[i][1] = pastLocations[i-1][1];
      }
      pastLocations[0][0] = headLocation[0];
      pastLocations[0][1] = headLocation[1];

  // new headLocation
  switch (snakeDirection)
  {
    case 0:
      headLocation[0] = headLocation[0] - 1;
      break;
    case 1:
      headLocation[1] = headLocation[1] + 1;
      break;
    case 2:
      headLocation[0] = headLocation[0] +  1;
      break;
    case 3:
      headLocation[1] = headLocation[1] - 1;
      break;    
  }

  // show head
  state[headLocation[0]][headLocation[1]] = 1;

  // delete tail
  for (int j = 29; j >= snakeLength; j--)
  {
    state[pastLocations[j][0]][pastLocations[j][1]] = 0;
  }
}

// function to add length for every point
void addLength(int *snakeLength, bool *foodEaten)
{
  *snakeLength = *snakeLength + 1;
  *foodEaten = false;
}

// function that spawns the snake for the first time
void spawnSnake(unsigned char state[16][16], int *snakeLength, bool *isSnake, int headLocation[2], int pastLocations[30][2], int *snakeDirection)
{
  // Set snake location
  headLocation[0] = 4;
  headLocation[1] = 5;
  
  pastLocations[0][0] = 4;
  pastLocations[0][1] = 4;

  pastLocations[1][0] = 4;
  pastLocations[1][1] = 3;

  // show snake location
  state[headLocation[0]][headLocation[1]] = 1;
  state[pastLocations[0][0]][pastLocations[0][1]] = 1;
  state[pastLocations[1][0]][pastLocations[1][1]] = 1;

  // snake facing right, length is 3, snake exists
  *snakeDirection = 1;
  *snakeLength = 3;
  *isSnake = true;
  Serial.println("Spawning a snake!");
}

// function to spawn food at random location, retry if something is already there
void spawnFood(unsigned char state[16][16], bool* isFood, int foodLocation[2])
{
  int x, y;
  x = random(0,16);
  y = random(0,16);
  if (state[x][y] == 1) return;
  foodLocation[0] = x;
  foodLocation[1] = y;
  state[x][y] = 1;
  *isFood = true;
}
void UpdateScreen(unsigned char screen[1][32], unsigned char state[16][16])
{
  int screenMod[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  int n = 0;
  for (int h=0; h<2; h++)
  {
    for (int i=0; i<16; i++)
    {
      for (int j=0; j<8; j++)
      {
        //screenMod[n] += state[i][j + 8*h]/**(ceil(pow(2,7-j)))*/;
        // This is written as a switch instead of the pow() function for better performance
        switch(j)
        {
          case 7:
            screenMod[n] += state[i][j + 8*h];
            break;
          case 6:
            screenMod[n] += state[i][j + 8*h]*2;
            break;
          case 5:
            screenMod[n] += state[i][j + 8*h]*4;
            break;
          case 4:
            screenMod[n] += state[i][j + 8*h]*8;
            break;
          case 3:
            screenMod[n] += state[i][j + 8*h]*16;
            break;
          case 2:
            screenMod[n] += state[i][j + 8*h]*32;
            break;
          case 1:
            screenMod[n] += state[i][j + 8*h]*64;
            break;
          case 0:
            screenMod[n] += state[i][j + 8*h]*128;
            break;
        }
      }
      n++;
    }
  }


  for (int i=0; i<32; i++)
  {
    screen[0][i] = 0xFF - screenMod[i];
  }
};

//****************************************************
//  Any code below this line was not written by me
//****************************************************

void Display(const unsigned char dat[][32])					
{
	unsigned char i;

	for( i = 0 ; i < 16 ; i++ )
	{
		digitalWrite(LEDARRAY_G, HIGH);		
		
		Display_Buffer[0] = dat[0][i];		
		Display_Buffer[1] = dat[0][i+16];

		Send(Display_Buffer[1]);
		Send(Display_Buffer[0]);

		digitalWrite(LEDARRAY_LAT, HIGH);					 
		delayMicroseconds(1);
	
		digitalWrite(LEDARRAY_LAT, LOW);
		delayMicroseconds(1);

		Scan_Line(i);							

		digitalWrite(LEDARRAY_G, LOW);
		
		delayMicroseconds(500);			
	}	
}

//****************************************************

//****************************************************
void Scan_Line( unsigned char m)
{	
	switch(m)
	{
		case 0:			
			digitalWrite(LEDARRAY_D, LOW);digitalWrite(LEDARRAY_C, LOW);digitalWrite(LEDARRAY_B, LOW);digitalWrite(LEDARRAY_A, LOW); 					
			break;
		case 1:					
			digitalWrite(LEDARRAY_D, LOW);digitalWrite(LEDARRAY_C, LOW);digitalWrite(LEDARRAY_B, LOW);digitalWrite(LEDARRAY_A, HIGH); 		
			break;
		case 2:					
			digitalWrite(LEDARRAY_D, LOW);digitalWrite(LEDARRAY_C, LOW);digitalWrite(LEDARRAY_B, HIGH);digitalWrite(LEDARRAY_A, LOW); 		
			break;
		case 3:					
			digitalWrite(LEDARRAY_D, LOW);digitalWrite(LEDARRAY_C, LOW);digitalWrite(LEDARRAY_B, HIGH);digitalWrite(LEDARRAY_A, HIGH); 		
			break;
		case 4:
			digitalWrite(LEDARRAY_D, LOW);digitalWrite(LEDARRAY_C, HIGH);digitalWrite(LEDARRAY_B, LOW);digitalWrite(LEDARRAY_A, LOW); 		
			break;
		case 5:
			digitalWrite(LEDARRAY_D, LOW);digitalWrite(LEDARRAY_C, HIGH);digitalWrite(LEDARRAY_B, LOW);digitalWrite(LEDARRAY_A, HIGH); 		
			break;
		case 6:
			digitalWrite(LEDARRAY_D, LOW);digitalWrite(LEDARRAY_C, HIGH);digitalWrite(LEDARRAY_B, HIGH);digitalWrite(LEDARRAY_A, LOW); 		
			break;
		case 7:
			digitalWrite(LEDARRAY_D, LOW);digitalWrite(LEDARRAY_C, HIGH);digitalWrite(LEDARRAY_B, HIGH);digitalWrite(LEDARRAY_A, HIGH); 		
			break;
		case 8:
			digitalWrite(LEDARRAY_D, HIGH);digitalWrite(LEDARRAY_C, LOW);digitalWrite(LEDARRAY_B, LOW);digitalWrite(LEDARRAY_A, LOW); 		
			break;
		case 9:
			digitalWrite(LEDARRAY_D, HIGH);digitalWrite(LEDARRAY_C, LOW);digitalWrite(LEDARRAY_B, LOW);digitalWrite(LEDARRAY_A, HIGH); 		
			break;	
		case 10:
			digitalWrite(LEDARRAY_D, HIGH);digitalWrite(LEDARRAY_C, LOW);digitalWrite(LEDARRAY_B, HIGH);digitalWrite(LEDARRAY_A, LOW); 		
			break;
		case 11:
			digitalWrite(LEDARRAY_D, HIGH);digitalWrite(LEDARRAY_C, LOW);digitalWrite(LEDARRAY_B, HIGH);digitalWrite(LEDARRAY_A, HIGH); 		
			break;
		case 12:
			digitalWrite(LEDARRAY_D, HIGH);digitalWrite(LEDARRAY_C, HIGH);digitalWrite(LEDARRAY_B, LOW);digitalWrite(LEDARRAY_A, LOW); 		
			break;
		case 13:
			digitalWrite(LEDARRAY_D, HIGH);digitalWrite(LEDARRAY_C, HIGH);digitalWrite(LEDARRAY_B, LOW);digitalWrite(LEDARRAY_A, HIGH); 		
			break;
		case 14:
			digitalWrite(LEDARRAY_D, HIGH);digitalWrite(LEDARRAY_C, HIGH);digitalWrite(LEDARRAY_B, HIGH);digitalWrite(LEDARRAY_A, LOW); 		
			break;
		case 15:
			digitalWrite(LEDARRAY_D, HIGH);digitalWrite(LEDARRAY_C, HIGH);digitalWrite(LEDARRAY_B, HIGH);digitalWrite(LEDARRAY_A, HIGH); 		
			break;
		default : break;	
	}
}

//****************************************************
      
//****************************************************
void Send( unsigned char dat)
{
	unsigned char i;
	digitalWrite(LEDARRAY_CLK, LOW);
	delayMicroseconds(1);	
	digitalWrite(LEDARRAY_LAT, LOW);
	delayMicroseconds(1);

	for( i = 0 ; i < 8 ; i++ )
	{
		if( dat&0x01 )
		{
			digitalWrite(LEDARRAY_DI, HIGH);	
		}
		else
		{
			digitalWrite(LEDARRAY_DI, LOW);
		}

		delayMicroseconds(1);
		digitalWrite(LEDARRAY_CLK, HIGH);				  
			delayMicroseconds(1);
		digitalWrite(LEDARRAY_CLK, LOW);
			delayMicroseconds(1);		
		dat >>= 1;
			
	}			
}
