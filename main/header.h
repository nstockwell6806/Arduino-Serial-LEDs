#define totalChannelNum 1
int pins [totalChannelNum][3];
class LedString
{
  public:
    int channel, rVal, gVal, bVal;
    LedString(int channelTemp)                                      //constructor; channelTemp is the input channel
    {
      channel = channelTemp;                                        //permanently store channel
      analogWrite(pins[channel][0], rVal = 15);
      analogWrite(pins[channel][1], gVal = 15);
      analogWrite(pins[channel][2], bVal = 15);
    }
    void changeVal(int val, char pin)                               //change value of one pin
    {
      switch (pin)
      {
        case 'r' :
          analogWrite(pins[channel][0], rVal = val);
          break;
        case 'g' :
          analogWrite(pins[channel][1], gVal = val);
          break;
        case 'b' :
          analogWrite(pins[channel][2], bVal = val);
          break;
        default :                                                   //catchall to turn LEDS to standby if not r/g/b
          int i;
          for (i = 0; i < 3; i++) {
            digitalWrite(pins[channel][i], 15);
          }
      }
    }
};

void setPins(int channelIn, int pin1, int pin2, int pin3 )                    //set pins on board to a certain channel in the array pins[][]
{
  int pinsIn[3] = {pin1, pin2, pin3};
  int i;
  for(i = 0; i < 3; i++)
  {
    pins[channelIn][i] = pinsIn[i];
  }
}

