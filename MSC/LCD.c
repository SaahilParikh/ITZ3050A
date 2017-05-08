#pragma systemFile            	// eliminates warning for "unreferenced" functions



int numberAutons = 10;
string autonomousMenu[10] = {
	"Team 3050A",
	"Skills",
	"Red Right 1",
	"Red Right 2",
	"Red left 1",
	"Red left 2",
	"Blue Right 1",
	"Blue Right 2",
	"Blue Left 1",
	"Blue Left 2",
};

string rEncoderString, lEncoderString, gyroString;

#define numOfSettingsPages 2

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

#warning "Pre Auton Battery LCD Display"
void preAutonBattery()
{
	while(nLCDButtons != centerButton)
	{
		clearLCDLine(1);
		string mainBatteryStatus, backupBatteryStatus, backupBattery;
		sprintf(mainBatteryStatus,"Cortex: %1.2f%c V", nImmediateBatteryLevel/1000.0);
		sprintf(backupBatteryStatus,"Xpander: %1.2f%c V", SensorValue[powerExpander]/280.0);
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
	while(nLCDButtons != 2)
	{
		sprintf(lEncoderString,"L:%d\r\n", SensorValue[leftEncoder], SensorValue[leftEncoder],"R:%d\r\n", SensorValue[rightEncoder]);
		centerLine(0, lEncoderString);
	}
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
		}
		else if(nLCDButtons == leftButton)
		{
			page--;
		}


		if(page == 0)
		{
			centerLine(0,"Drive Base Motors");
			centerLine(1,"Enter");
			if(nLCDButtons == 2)
			{
				debugDrive();
			}

			sprintf(lEncoderString,"lEncoder:%d\r\n", SensorValue[leftEncoder]);
			sprintf(rEncoderString,"rEncoder:%d\r\n", SensorValue[rightEncoder]);
			centerLine(0, lEncoderString);
			centerLine(1, rEncoderString);
		}
		else if(page == 1)
		{
			sprintf(gyroString,"Gyro:%d\r\n", SensorValue[gyro]);
			centerLine(0, gyroString);
		}
		delay(20);
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
		sprintf(backupBatteryStatus,"Xpander: %1.2f%c V", SensorValue[powerExpander]/280.0);
		displayLCDString(0, 0, mainBatteryStatus);
		displayLCDString(1, 0, backupBatteryStatus);
		delay(30000);
	}
}


task LCD ();
