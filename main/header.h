#define totalChannelNum 1
int pins[totalChannelNum][3];
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
	void changeVal(int val, char pin)                                                    //change value of one pin
	{
		switch (pin)
		{
		case 'r':
			analogWrite(pins[channel][0], rVal = val);
			break;
		case 'g':
			analogWrite(pins[channel][1], gVal = val);
			break;
		case 'b':
			analogWrite(pins[channel][2], bVal = val);
			break;
		}
	}
	void changeVal(int val1, char pin1, int val2, char pin2)                             //change value of two pins
	{
		changeVal(val1, pin1);
		changeVal(val2, pin2);
	}
	void changeVal(int val1, char pin1, int val2, char pin2, int val3, char pin3)        //change value of three pins
	{
		changeVal(val1, pin1);
		changeVal(val2, pin2);
		changeVal(val3, pin3);
	}
	void fade(int val, char pin)
	{
		switch pin
			case 'r':
			//startFade();
	}

private:
	void startFade()
	{
	int k = 100 * int(rand(20, 26));
	for (int i = 0; i < k; i++)
	{
		changeVal( int(rand(0,256)), 'r', int(rand(0, 256)), 'g', int(rand(0, 256)), 'b')
	}
	}
};

void setPins(int channelIn, int pin1, int pin2, int pin3)                    //set pins on board to a certain channel in the array pins[][]
{
	int pinsIn[3] = { pin1, pin2, pin3 };
	int i;
	for (i = 0; i < 3; i++)
	{
		pins[channelIn][i] = pinsIn[i];
	}
}

