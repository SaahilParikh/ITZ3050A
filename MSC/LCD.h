#pragma systemFile            	// eliminates warning for "unreferenced" functions
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

void preAutonBattery()
{
				while(nLCDButtons != centerButton)
					{
						string mainBatteryStatus, backupBatteryStatus, backupBattery;
						sprintf(mainBatteryStatus,"Cortex: %1.2f%c V", nImmediateBatteryLevel/1000.0);
						sprintf(backupBatteryStatus,"Xpander: %1.2f%c V", SensorValue[powerExpander]/280.0);
						displayLCDString(0, 0, mainBatteryStatus);
						displayLCDString(1, 0, backupBatteryStatus);
						if(nLCDButtons == rightButton)
							{
								while(nLCDButtons != centerButton && nLCDButtons != leftButton)
								{
									displayLCDString(1, 0, "Backup: ");
									sprintf(backupBattery, "%1.2f%c", BackupBatteryLevel/1000.0, 'V');	//Build the value to be displayed
									displayNextLCDString(backupBattery);
								}
						}


					}
					waitForRelease();

}

task LCD ();
