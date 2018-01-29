void skills(){

	clearGyro();
	clearDriveEnc();

	mogoDriveDown(); //MobileGoalLiftDown for the first Mogo
	driveKeepHeading(1300, 0 ,-1500); // Drive into the first mogo

	drive(30, 30);
	wait1Msec(500);

	mogoDriveUp();

	driveTurn(targetHeading, 2000, 0.5, 1000, true);

	driveKeepHeading(130); //drive back just infront of starting position

	driveTurn(-450); // turn 45 degrees to line up with starting pole, parrallel.
	clearDriveEnc();

	driveKeepHeading(-750); // bcjkward parellel to bar

	driveTurn(-1350); // perpendic to bar
	clearDriveEnc();

	driveKeepHeading(750); // forward

	mogoDriveDown(); //mogo down

	driveKeepHeading(550); // back alittle

	drive(-30, -30);
	wait1Msec(500);

	mogoDriveUp(); // mogo up

	driveKeepHeading(200); // robot backwards

	driveTurn(targetHeading+900);
	clearDriveEnc();

	driveKeepHeading(-510);

	driveSmoothTurn(-30, targetHeading+450);
	clearDriveEnc();

	driveTurn(targetHeading, 500);
	clearDriveEnc();

	driveKeepHeading(-450); // ram  wall

	clearGyro();
	driveTurn(0);
	clearDriveEnc();

	driveKeepHeading(585);

	driveTurn(450, 4000, 0.3, 80, true);
	clearDriveEnc();

	mogoDriveDown();

	driveKeepHeading(400);

	drive(20, 20);
	wait1Msec(1000);

	mogoDriveUp(); // pick up second mogo

	delay(10);

	driveTurn(targetHeading, 1000, 0.5, 100, true);

	driveKeepHeading(-500);
	driveTurn(targetHeading-1800, 1000, 0.5, 100, true);
	clearDriveEnc();

	driveKeepHeading(200);

	mogoDriveDown();
	driveKeepHeading(-100);
	mogoDriveUp(); //s score second mogo

	//THREE
	driveTurn(targetHeading-900, 2000, 0.3, 1000, true);
	clearDriveEnc();

	driveKeepHeading(-930);

	driveSmoothTurn(-30, targetHeading-450);

	clearDriveEnc();

	/*driveTurn(targetHeading, 500);
	clearDriveEnc();
	*/
	driveKeepHeading(-700); // ram  wall

	clearGyro();
	driveTurn(0);
	clearDriveEnc();

	driveKeepHeading(600);

	driveTurn(-450, 2000, 0.3, 70, true);
	clearDriveEnc();

	mogoDriveDown();

	driveKeepHeading(450);

	drive(20, 20);
	wait1Msec(1000);

	mogoDriveUp(); // pick up 3 mogo

	driveKeepHeading(-300);
	driveTurn(targetHeading+1800);
	clearDriveEnc();

	driveKeepHeading(400);

	mogoDriveDown();
	driveKeepHeading(0);
	mogoDriveUp();

	driveTurn(targetHeading-1800, 2000, 0.3, 40, true);
	clearDriveEnc();

	mogoDriveDown();
	driveKeepHeading(1450);

	drive(20, 20);
	delay(500);
	mogoDriveUp();

	driveKeepHeading(2500);

	driveTurn(targetHeading+900);
	clearDriveEnc();

	driveKeepHeading(500);
	// 4th

	driveTurn(targetHeading-900); // perpendic to bar
	clearDriveEnc();


	driveKeepHeading(750); // forward

	mogoDriveDown(); //mogo down

	driveKeepHeading(550); // back alittle

	mogoDriveUp(); // mogo up

	driveKeepHeading(100); // robot backwards

	driveTurn(targetHeading-900);
	clearDriveEnc();


	driveKeepHeading(-500);

	driveSmoothTurn(-30, targetHeading-450);
	clearDriveEnc();
	driveTurn(targetHeading, 500);
	clearDriveEnc();

	driveKeepHeading(-450); // ram  wall

	clearGyro();
	driveTurn(0);
	clearDriveEnc();

	driveKeepHeading(600);

	driveTurn(-450, 2000, 0.3, 40, true);
	clearDriveEnc();

	mogoDriveDown();

	driveKeepHeading(450);

	drive(20, 20);
	wait1Msec(1000);

	mogoDriveUp(); // pick up 5 mogo

	driveKeepHeading(-300);
	driveTurn(targetHeading+1800);
	clearDriveEnc();

	driveKeepHeading(400);

	mogoDriveDown();
	driveKeepHeading(0);
	mogoDriveUp();

}









/*void skillssssss1()
{
	clearGyro();
	clearDriveEnc();
	startTask(drivePID);

	mogoDriveDown(); //MobileGoalLiftDown for the first Mogo
	setDrive(1250); // Drive into the first mogo

	stopTask(drivePID);
	drive(30, 30);
	delay(600);
	mogoDriveUp();
	delay(400);
	startTask(drivePID); //pick up first mogo

	setDrive(200); //drive back just infront of starting position

	setTurn(-450); // turn 45 degrees to line up with starting pole, parrallel.

	setDrive(-850); // bcjkward parellel to bar

	setTurn(targetHeading-900, 3000, 3000); // perpendic to bar

	setDrive(750); // forward

	mogoDriveDown(); //mogo down

	setDrive(600); // back alittle

	mogoDriveUp(); // mogo up

	setDrive(100); // robot backwards

	setTurn(targetHeading+900);

	setDrive(-780);

	setTurn(targetHeading+450);

	setDrive(-450); // ram  wall

	clearGyro();
	setTurn(0);

	setDrive(600);

	setTurn(450);

	mogoDriveDown();

	setDrive(400);

	mogoDriveUp(); // pick up second mogo

	setDrive(-700);

	setDrive(-500, 400);
	setTurn(targetHeading+900);
	setDrive(-700);

	setTurn(targetHeading+900);
	setDrive(300, 1000);

	mogoDriveDown();
	setDrive(-100);
	mogoDriveUp(); //s score second mogo

	//THREE
	setTurn(targetHeading-900);
	setDrive(-765);

	setTurn(targetHeading-450);

	setDrive(-450); // ram  wall

	clearGyro();
	setTurn(0);

	setDrive(600);

	setTurn(-450);

	mogoDriveDown();

	setDrive(400);

	mogoDriveUp(); // pick up second mogo

	setDrive(-300);
	setTurn(targetHeading-1800);
	setDrive(400);

	mogoDriveDown();
	setDrive(0);
	mogoDriveUp();

	setTurn(targetHeading+1800);
	mogoDriveDown();
	setDrive(1450, -5000);
	stopTask(drivePID);
	drive(20, 20);
	delay(500);
	mogoDriveUp();
	startTask(drivePID);
	setDrive(2500);

	setTurn(targetHeading+900);

	setDrive(300);



}



void skillsssssss2()
{
	clearGyro();
	clearDriveEnc();

	mogoDriveDown(); //MobileGoalLiftDown for the first Mogo
	driveKeepHeading(1300); // Drive into the first mogo

	drive(20, 20);
	wait1Msec(300);

	mogoDriveUp(); //pick up first mogo

	driveKeepHeading(200); //drive back just infront of starting position

	driveTurn(-450); // turn 45 degrees to line up with starting pole, parrallel.
	clearDriveEnc();

	driveKeepHeading(-850); // bcjkward parellel to bar

	driveTurn(targetHeading-900); // perpendic to bar
	clearDriveEnc();

	driveKeepHeading(750); // forward

	mogoDriveDown(); //mogo down

	driveKeepHeading(600); // back alittle

	mogoDriveUp(); // mogo up

	driveKeepHeading(100); // robot backwards

	driveTurn(targetHeading+900);
	clearDriveEnc();

	driveKeepHeading(-570);

	driveSmoothTurn(targetHeading+450, -20);
	setTurn(targetHeading, 500);
	clearDriveEnc();

	driveKeepHeading(-450); // ram  wall

	clearGyro();
	driveTurn(0);

	driveKeepHeading(600);

	driveTurn(450);
	clearDriveEnc();


	mogoDriveDown();

	driveKeepHeading(400);

	mogoDriveUp(); // pick up second mogo

	driveKeepHeading(-300);
	driveTurn(targetHeading+900);
	clearDriveEnc();

	driveKeepHeading(-700);

	driveTurn(targetHeading+900);
	clearDriveEnc();

	driveKeepHeading(300, 1000);

	mogoDriveDown();
	driveKeepHeading(0);
	mogoDriveUp(); //s score second mogo

	//THREE
	driveTurn(targetHeading+900);
	driveKeepHeading(-820);

	clearGyro();
	driveTurn(0);

	driveTurn(450);
	driveKeepHeading(-400);

	clearGyro();
	driveTurn(0);


	driveKeepHeading(100,2000);

	driveTurn(targetHeading+900);



}




*/




/*













































































































void skillsOLDDD()
{
clearGyro();
clearDriveEnc();
startTask(drivePID);

mogoDriveDown();
setDrive(1450);// forwad for first mogo
mogoDriveUp();// mogo down for first mogo
setDrive(270,800); // backward for first mogo


setTurn(-450, 500); //turn robot parrallel to bar

clearDriveEnc();

setDrive(-750, 900);	//line up to 20 point

setTurn(-450 + -900, 1000);	//turn to 20 point
clearGyro();
setTurn(0,0);

wait1Msec(1000);
clearDriveEnc();

stopTask(drivePID);

drive(127,127);
wait1Msec(700);
drive(0,0);
wait1Msec(100);
mogoDriveDown();

drive(-80,-80);
wait1Msec(300);
drive(0,0);
wait1Msec(100);
mogoDriveUp();

drive(127,127);
wait1Msec(500);
drive(0,0);
wait1Msec(100);

drivePosTarget = 0;
targetHeading = 0;

clearDriveEnc();
clearGyro();

startTask(drivePID);

setDrive(-500, 2000);
setTurn(-950, 3000);
wait1Msec(3000);
stopTask(drivePID);
drive(-80,-80);
wait1Msec(1500);
drive(0,0);
wait1Msec(100);

mogoDriveUp();
stopTask(drivePID);


//setDrive(-100, 0);	//drive to 20 point


mogodriveUp();
setDrive(700, 300);	// drive out of scoring zone

setDrive(-150, 400);	//drive back from 20 point

setDrive(-600, 1300);	// drive out of scoring zone
clearDriveEnc();
setDrive(0, 300);	// drive out of scoring zone
wait1Msec(1000);



wait1Msec(100000);


}
*/
