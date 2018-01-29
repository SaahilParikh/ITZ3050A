#pragma systemFile
void drive(int powerL, int powerR){
	motor[driveBackLeft] = motor[driveFrontLeft] = powerL;
	motor[driveBackRight] = motor[driveFrontRight] = powerR;
}
