#pragma systemFile            	// eliminates warning for unreferenced functions



int numberAutons = 12;
string autonomousMenu[12] = {
	"Team 3050A", //0
	"Skills", //1
	"Red Right 24:", //2
	"Red Right 9:", //3
	"Red left 24", //4
	"Red left 5", //5
	"Blue Right 24", //6
	"Blue Right 9", //7
	"Blue Left 24:", //8
	"Blue Left 9:", //9
	"Blue Right 22", //10
	"Red Right 22" //11
};

string rEncoderString, lEncoderString, gyroString, driveEncoderString, liftPotString, waitString;

#define numOfSettingsPages 5

enum { 	LCD_NO_BUTTONS = 0,
	LCD_LEFT_BUTTON = 1,
	LCD_CENTRE_BUTTON = 2, LCD_CENTER_BUTTON = 2,
	LCD_LEFT_CENTRE_BUTTON = 3, LCD_LEFT_CENTER_BUTTON = 3,
	LCD_RIGHT_BUTTON = 4,
	LCD_LEFT_RIGHT_BUTTON = 5,
	LCD_CENTRE_RIGHT_BUTTON = 6, LCD_CENTER_RIGHT_BUTTON = 6,
	LCD_LEFT_CENTRE_RIGHT_BUTTON = 7, LCD_LEFT_CENTER_RIGHT_BUTTON = 7 };

const short leftButton = 1;
const short centerButton = 2;
const short rightButton = 4;

#warning "clearLCD"
void clearLCD () {
	clearLCDLine(0);
	clearLCDLine(1);
}

void waitForPress()
{
	while(nLCDButtons == 0){}
	wait1Msec(5);
}

void waitForRelease()
{
	while(nLCDButtons != 0){}
	wait1Msec(5);
}

void centerLine ( int lineNumber, string* contents ) {
	string out;
	sprintf(out,"%s",contents);
	displayLCDCenteredString(lineNumber, out);
}

void line( int lineNumber, string* contents ) {
	string out;
	sprintf(out,"%s",contents);
	displayLCDString(lineNumber,0,out);
}

void centerDisplay (string line0, string* line1) {
	centerLine(0, line0);
	centerLine(1, line1);
}

#warning "Pre Auton Battery LCD Display DOO POWER EXPANDER"
void preAutonBattery()
{
	while(nLCDButtons != centerButton)
	{
		clearLCDLine(1);
		string mainBatteryStatus, backupBatteryStatus, backupBattery;
		sprintf(mainBatteryStatus,"Cortex: %1.2f%c V", nImmediateBatteryLevel/1000.0);

		//sprintf(backupBatteryStatus,"Xpander: %1.2f%c V", SensorValue[powerExpander]/280.0);
		displayLCDString(0, 0, mainBatteryStatus);
		displayLCDString(1, 0, backupBatteryStatus);
		delay(25);
		if(nLCDButtons == rightButton)
		{
			clearLCDLine(1);
			while(nLCDButtons != centerButton && nLCDButtons != leftButton)
			{
				displayLCDString(1, 0, "Backup: ");
				sprintf(backupBattery, "%1.2f%c V", BackupBatteryLevel/1000.0);	//Build the value to be displayed
				displayNextLCDString(backupBattery);
				delay(25);
			}
		}


	}
	waitForRelease();
}

void debugDrive()
{
	clearLCD();
	waitForRelease();
	while(nLCDButtons != 2)
	{
		sprintf(driveEncoderString,"L:%d R:%d\r\n", SensorValue[driveLeftEnc], SensorValue[driveRightEnc]);

		if(nLCDButtons == rightButton)
			drive(127, 127);
		else if(nLCDButtons == leftButton)
			drive(-127, -127);
		else
			drive(0,0);

		centerLine(0, driveEncoderString);
		centerLine(1,"-127  Exit  127");
		delay(50);
	}
	waitForRelease();
}

void debugLift()
{
	clearLCD();
	waitForRelease();
	while(nLCDButtons != 2)
	{
		//sprintf(liftPotString,"Pot:%d, Pot:%d\r\n", SensorValue[potLeft], SensorValue[potRight]);

		if(nLCDButtons == rightButton)
			liftMogo(127, 127);
		else if(nLCDButtons == leftButton)
			liftMogo(-127, -127);
		else
			liftMogo(0, 0);

		centerLine(0, liftPotString);
		centerLine(1,"-127  Exit  127");
		delay(50);
	}
	waitForRelease();
}

#warning "Settings"
void settings()
{
	int page = 0;
	while(page < numOfSettingsPages &&page >= 0)
	{

		if(nLCDButtons == rightButton)
		{
			page++;
			waitForRelease();
		}
		else if(nLCDButtons == leftButton)
		{
			page--;
			waitForRelease();
		}

		switch(page)
		{
		case 0:
			centerLine(0,"Drive Debug");
			centerLine(1,"Enter");
			waitForPress();
			if(nLCDButtons == 2)
				debugDrive();

			//sprintf(lEncoderString,"lEncoder:%d\r\n", SensorValue[leftEncoder]);
			//sprintf(rEncoderString,"rEncoder:%d\r\n", SensorValue[rightEncoder]);
			//centerLine(0, lEncoderString);
			//centerLine(1, rEncoderString);
			break;
		case 1:

			centerLine(0,"Lift Debug");
			centerLine(1,"Enter");
			waitForPress();
			if(nLCDButtons == 2)
				debugLift();

			break;
		case 2:
			/*centerLine(0,"Piston State");
			centerLine(1,"Enter");
			waitForPress();
			if(nLCDButtons == 2)
			{
				SensorValue[Piston] = !SensorValue[Piston];
				waitForRelease();
			}*/
			break;
		case 3:
			sprintf(gyroString,"Gyro:%d\r\n", SensorValue[gyro]);
			centerLine(0, gyroString);
			centerLine(1, "clear");
			waitForPress();
				if(nLCDButtons == 2)
					clearGyro();
			break;
		case 4:
			sprintf(waitString,"Wait: %d\r\n", driveLeftEnc);
			centerLine(0, waitString);
			centerLine(1, "Enter");
			waitForPress();
				if(nLCDButtons == 2)
					waitBeforeAuton = abs(driveLeftEnc);
		break;

			delay(70);
		}
	}
}

#warning "Auton Chooser"
int autonChooser()
{
	int choice =0;
	while(nLCDButtons != 2) {
		centerLine(0,autonomousMenu[choice]);
		centerLine(1,"<-- SELECT -->");
		waitForPress();
		if(nLCDButtons == leftButton) {
			choice = choice==0?numberAutons-1:choice-1;
			waitForRelease();
			} else if(nLCDButtons == rightButton) {
			choice = choice==numberAutons-1?0:choice+1;
			waitForRelease();
		}

		delay(50);
	}
	waitForRelease();
	delay(100);

	return choice;
}

#warning "Driver Control LCD"
task batteryLCD() {
	while(true) {
		bLCDBacklight = true;
		string mainBatteryStatus, backupBatteryStatus;
		sprintf(mainBatteryStatus,"Cortex: %1.2f%c V", nImmediateBatteryLevel/1000.0);
		//sprintf(backupBatteryStatus,"Xpander: %1.2f%c V", SensorValue[powerExpander]/280.0);
		displayLCDString(0, 0, mainBatteryStatus);
	//	displayLCDString(1, 0, backupBatteryStatus);
		delay(30000);
	}
}


task LCD ();
