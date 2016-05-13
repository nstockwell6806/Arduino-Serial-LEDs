#define totalChannelNum 1





int pinMap[totalChannelNum][3];
char serialInput = -1;
boolean fading = true;
boolean shutdown =  false;
boolean newInstructions = false;





class LedString
{
public:
	int channel;
	LedString(int channelTemp)                                      												//constructor; channelTemp is the input channel
	{
		channel = channelTemp;                                        												//permanently store channel
	}
	char pinNames = {'r', 'g', 'b'};																				//useful for identifying names r,g,b by numbers 1,2,3
	int pinData[3][3] = {{pinMap[channel][0], 15, 15}, {pinMap[channel][1], 15, 15}, {pinMap[channel][2], 15, 15}};	//r=0, g=1, b=2 for first index, second index is pin #, val, target val 		MAKE SURE TO RUN setPins() FIRST!
	float colorIncriment[3] = {0, 0, 0};																			//incriments
	void changeVal(int val, char pin)                                                    							//change value of one pin
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
		pinData[q][1] = val;
		analogWrite(pinData[q][0], pinData[q][2] = pinData[q][1]);
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
		if(pinData[0][1] == pinData[0][2] && pinData[1][1] == pinData[1][2] && pinData[2][1] == pinData[2][2])		//if all values are at their targets, set new targets
		{
			startFade();
		}
		for(int i = 0; i < 3; i++)																					//cycle through and fade pins one incriment if needed
		{
			if(pinData[i][2] != pinData[i][1])
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
		changeVal(15, 'r', 15, 'g', 15, 'b');	
	}

private:
	void startFade()																							//calculate new targets and incriments
	{
		for(int i = 0; i < 3; i++)
		{
			pinData[i][2] = int(random(0,256));																	//set random ints for targets
			colorIncriment[i] = ( pinData[i][2] - pinData[i][1] ) / 256;										//set incriment value
		}
	}
}





void setPins(int channelIn, int pin1, int pin2, int pin3)                    									//set pins on board to a certain channel in the array pins[][]
{
	int pinsIn[3] = { pin1, pin2, pin3 };
	for (int i = 0; i < 3; i++)
	{
		pinMap[channelIn][i] = pinsIn[i];
	}
}

void readSerial()																								//read serial message if available
{
	if (Serial.available() > 0)
	{
		serialInput = Serial.read();
		switch (serialInput)
		{
			case "f":
				fading = true;
				newInstructions = true;
				break;
			case "d":
				fading = false;
				shutdown = false;
				newInstructions = true;
				break;
			case "o":
				fading = false;
				shutdown = true;
				newInstructions = true;
				break;
			default:
				fading = true;
				newInstructions = true;
				break;

		}
	}
}

void runInstructions()
{
	if(fading)
	{
		String1.fade();
	}
	else if(shutdown && newInstructions)																		//only run if there are new instructions
	{
		String1.shutdown();
	}
	else if(not(shutdown) && newInstructions)																	//only run if there are new instructions
	{
		String1.dim();
	}
}