#include "functions.h"

	int driveEncoder;
	int liftEncoder;
task main()
{

	while(1==1)
	{

		setDrive(vexRT[Ch2], vexRT[Ch3]);

		if(vexRT[Btn5U])
			setLiftSpeed(127);
		else if(vexRT[Btn5D])
			setLiftSpeed(-127);
		else
			setLiftSpeed(0);

		if(vexRT[Btn7U] == 1)
		{
			writeDebugStream("drivePID(%d);\r\n", driveEncoder);
			clearDrive();
		}
		if(vexRT[Btn7D] == 1)
		{
			writeDebugStream("liftPID(%d);\r\n", driveLift);
			clearLift();
		}


	}


}
