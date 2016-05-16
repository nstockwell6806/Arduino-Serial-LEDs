boolean fading = false;                                               //mode setting for fading
boolean forceUpdate = false;                                          //force fade recalculation when true
boolean shutDown =  true;                                             //mode setting for when not fading whether to dim or shutdown
boolean runFlash = false;
boolean newInstructions = false;                                      //lets functions know whether there are new instructions for pins
int intensity = 100;



class LedString
{
  public:
    int channel;
    char pinNames[3] = {'r', 'g', 'b'};																				              //useful for identifying names r,g,b by numbers 1,2,3
    float colorIncriment[3] = {1, 1, 1};																			              //incriments
    float pinData[3][3] = {{ -1, 15, 20}, { -1, 15, 20}, { -1 , 15, 20}};                   //r=0, g=1, b=2 for first index, second index is pin #, val, target val
    LedString(int channelTemp, int r, int b, int g)                                      		//constructor; channelTemp is the input channel; r, g, and b are pin values
    {
      channel = channelTemp;                                        												//permanently store channel
      pinData[0][0] = r;
      pinData[1][0] = g;
      pinData[2][0] = b;
    }


    void changeVal(float val, char pin)                                                    							//change value of one pin
    {
      int pinAssociation;
      switch (pin) {
        case 'r':
          pinAssociation = 0;
          break;
        case 'g':
          pinAssociation = 1;
          break;
        case 'b':
          pinAssociation = 2;
          break;
        default:
          break;
      }
      pinData[pinAssociation][1] = val;
      analogWrite(pinData[pinAssociation][0], val);
    }
    void changeVal(int val1, char pin1, int val2, char pin2)                             							//change value of two pins
    {
      changeVal(val1, pin1);
      changeVal(val2, pin2);
    }
    void changeVal(int val1, char pin1, int val2, char pin2, int val3, char pin3)        							//change value of three pins
    {
      changeVal(val1, pin1);
      changeVal(val2, pin2);
      changeVal(val3, pin3);
    }

    void fade()                                                   //fade to random colors
    {
      if ((not(hasSameSign(pinData[0][2] - pinData[0][1], colorIncriment[0])) && not(hasSameSign(pinData[1][2] - pinData[1][1], colorIncriment[1])) && not(hasSameSign(pinData[2][2] - pinData[2][1], colorIncriment[2]))) || forceUpdate)		//if all values are at or beyond their targets, set new targets
      {
        startFade();
        if (forceUpdate)
        {
          forceUpdate = false;
        }
      }
      for (int i = 0; i < 3; i++)																					//cycle through and fade pins one incriment if needed
      {
        if (hasSameSign(pinData[i][2] - pinData[i][1], colorIncriment[i]) || pinData[i][1] + colorIncriment[i] == pinData[i][2])
        {
          changeVal(pinData[i][1] + colorIncriment[i], pinNames[i]);
        }
      }
    }

    void flash(int r, int g, int b)                             //flash a certain rgb color for 250 milliseconds and return to the normal values
    {
      int tempStorage[3] = {pinData[0][1], pinData[1][1], pinData[2][1]};
      changeVal(r, 'r', g, 'g', b, 'b');
      delay(250);
      changeVal(tempStorage[0], 'r', tempStorage[1], 'g', tempStorage[2], 'b');
    }

    void shutDown()                                             //turn the LEDs off
    {
      changeVal(0, 'r', 0, 'g', 0, 'b');
    }

    void dim()                                                  //dim the LEDs to r=10, g=0, b=0
    {
      while (pinData[0][1] < 9 || pinData[0][1] > 11 || pinData[1][1] > 0 || pinData[2][1] > 0)       //cycle through the pins (quickly) to reduce values
      {
        if (pinData[0][1] > 11)
        {
          changeVal(pinData[0][1] - 1, 'r');
        }
        else if (pinData[0][1] < 9)
        {
          changeVal(pinData[0][1] + 1, 'r');                                                          //if red is below the target, increase red
        }
        if (pinData[1][1] > 0)
        {
          changeVal(pinData[1][1] - 1, 'g');
        }
        if (pinData[2][1] > 0)
        {
          changeVal(pinData[2][1] - 1, 'b');
        }
        delay(5);
      }
    }

  private:
    bool hasSameSign(float a, float b)                        //Check to see if the values are in the target range. Not ideal but useful
    {
      if (a == b)
      {
        return false;                                         //just for a special case
      }
      if (a > -.5 && a < .5)
      {
        return false;                                         //special case also
      }
      if (a > 0 && b > 0)
      {
        return true;
      }
      else if (a < 0 && b < 0)
      {
        return true;
      }
      else
      {
        return false;
      }
    }

    void startFade()																							//calculate new targets and incriments
    {
      for (int i = 0; i < 3; i++)
      {
        do
        {
          pinData[i][2] = 10 * random(0, (intensity/4)+1);																	//set random targets
        }
        while (pinData[i][2] == pinData[i][1]);
        colorIncriment[i] = ( pinData[i][2] - pinData[i][1] );										//set incriment value
        colorIncriment[i] /= 100;
      }
      fading = true;
    }
};



void readSerial()																								//read serial message if available
{
  if (Serial.available() > 0)
  {
    char receivedChar = Serial.read();
    newInstructions = true;
    switch (receivedChar)
    {
      case 'f':                                                 //fade
        fading = true;
        break;
      case 'd':                                                 //dim
        fading = false;
        shutDown = false;
        break;
      case 'o':                                                 //shutdown: o for off
        fading = false;
        shutDown = true;
        break;
      case 'l':                                                 //flash
        runFlash = true;
        break;
      case 'u':                                                 //force recalculation of fade
        forceUpdate = true;
        break;
        case 'i':                                               //change color intensity
          if(intensity == 10)
          {
            intensity = 110;
          }
          intensity -= 10;
          Serial.println(intensity);
          forceUpdate = true;
      default:                                                  //if unknown character, start fade
        fading = true;
        break;

    }
  }
}
