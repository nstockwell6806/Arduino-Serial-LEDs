#define totalChannelNum 1
int pins[totalChannelNum][3];
class LedString
{

public:
	int channel;
	LedString(int channelTemp)                                      											//constructor; channelTemp is the input channel
	{
		channel = channelTemp;                                        											//permanently store channel
	}
	char nameChars = {'r', 'g', 'b'};																			//useful for identifying names r,g,b by numbers 1,2,3
	int colors[3][3] = {{pins[channel][0], 15, 15}, {pins[channel][1], 15, 15}, {pins[channel][2], 15, 15}};	//r=0, g=1, b=2 for first index, second index is pin #, val, target val
	float changes[3] = {0, 0, 0};																				//incriments
	void changeVal(int val, char pin)                                                    						//change value of one pin
	{
		switch pin {
			case 'r':
				int q = 0;
				break;
			case 'g':
				int q = 1;
				break;
			case 'b':
				int q = 2;
				break;
		}
		colors[q][1] = val;
		analogWrite(colors[q][0], colors[q][2] = colors[q][1]);
	}
	void changeVal(int val1, char pin1, int val2, char pin2)                             						//change value of two pins
	{
		changeVal(val1, pin1);
		changeVal(val2, pin2);
	}
	void changeVal(int val1, char pin1, int val2, char pin2, int val3, char pin3)        						//change value of three pins
	{
		changeVal(val1, pin1);
		changeVal(val2, pin2);
		changeVal(val3, pin3);
	}
	void fade()
	{
		if(colors[0][1] == colors[0][2] && colors[1][1] == colors[1][2] && colors[2][1] == colors[2][2])		//if all values are at their targets, set new targets
		{
			startFade();
		}
		for(int i = 0; i < 3; i++)																				//cycle through and fade pins one incriment if needed
		{
			if(colors[i][2] != colors[i][1])
			{
				changeVal(colors[i][1] + changes[i], nameChars[i]);
			}
		}
	}
	void flash(int r, int g, int b)
	{
		analogWrite(colors[0][0], r);
		analogWrite(colors[1][0], g);
		analogWrite(colors[2][0], b);
		delay(10);
		analogWrite(colors[0][0], colors[0][1]);
		analogWrite(colors[1][0], colors[1][1]);
		analogWrite(colors[1][0], colors[2][1]);
	}

private:
	void startFade()																							//calculate new targets and incriments
	{
		for(int i = 0; i < 3; i++)
		{
			colors[i][2] = int(random(0,256));																	//set random ints for targets
			changes[i] = ( colors[i][2] - colors[i][1] ) / 256;													//set incriment value
		}
	}
};

void setPins(int channelIn, int pin1, int pin2, int pin3)                    									//set pins on board to a certain channel in the array pins[][]
{
	int pinsIn[3] = { pin1, pin2, pin3 };
	int i;
	for (i = 0; i < 3; i++)
	{
		pins[channelIn][i] = pinsIn[i];
	}
}
