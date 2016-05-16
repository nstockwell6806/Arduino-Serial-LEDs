




boolean fading = false;
boolean shutDown =  true;
boolean newInstructions = false;







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
    void fade()
    {
      if (not(hasSameSign(pinData[0][2] - pinData[0][1], colorIncriment[0])) && not(hasSameSign(pinData[1][2] - pinData[1][1], colorIncriment[1])) && not(hasSameSign(pinData[2][2] - pinData[2][1], colorIncriment[2])))		//if all values are at or beyond their targets, set new targets
      {
        startFade();
      }
      for (int i = 0; i < 3; i++)																					//cycle through and fade pins one incriment if needed
      {
        if (hasSameSign(pinData[i][2] - pinData[i][1], colorIncriment[i]) || pinData[i][1] + colorIncriment[i] == pinData[i][2])
        {
          changeVal(pinData[i][1] + colorIncriment[i], pinNames[i]);
        }
      }
    }
    void flash(int r, int g, int b)
    {
      changeVal(r, 'r', g, 'g', b, 'b');
      delay(10);
      changeVal(pinData[0][1], 'r', pinData[1][1], 'g', pinData[2][1], 'b');
    }
    void shutDown()
    {
      changeVal(0, 'r', 0, 'g', 0, 'b');
    }
    void dim()
    {
      while (pinData[0][1] < 9 || pinData[0][1] > 11 || pinData[1][1] > 0 || pinData[2][1] > 0)
      {
        if (pinData[0][1] > 11)
        {
          changeVal(pinData[0][1] - 1, 'r');
        }
        else if (pinData[0][1] < 9)
        {
          changeVal(pinData[0][1] + 1, 'r');
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
    bool hasSameSign(float a, float b)
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
          pinData[i][2] = 10 * random(0, 26);																	//set random ints for targets
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
    //    Serial.print("New serial read with returned char: ");
    //    Serial.print(receivedChar);
    //    Serial.print("\n");
    newInstructions = true;
    switch (receivedChar)
    {
      case 'f':
        fading = true;
        //        Serial.println("Setting string to fade");
        break;
      case 'd':
        fading = false;
        shutDown = false;
        break;
      case 'o':
        fading = false;
        shutDown = true;
        //        Serial.println("Setting string to off");
        break;
      default:
        fading = true;
        //        Serial.println("Setting string to fade");
        break;

    }
  }
}
