#pragma systemFile

int waitBeforeAuton = 0;

#define wheelDiameter 1

const float ticsPerDegree = (37870/36000);

const int slits = 90;
const float wheelDiameterMeters = 0.1016;
const float metersPerTick = wheelDiameterMeters*PI/slits;

const float basewheelcirc = 12.99;

#define testedDriveTimeWaitConst (2)
#define testedTurnTimeWaitConst (2)

#define wheelCircum (wheelDiameter)

#define driveTimeConst round(testedDriveTimeWaitConst*wheelCircum)
#define turnTimeConst round(testedTurnTimeWaitConst*wheelCircum)

#define driveSlowSpeed (127-30)

#define driveRightEnc SensorValue[encRight]
#define driveLeftEnc -SensorValue[encLeft]
#define getHeading SensorValue[gyro]

#define driveStraightStationaryCountThresh 40
#define turnStraightStationaryCountThresh 40

bool isMove = true;
bool mogoIsFront = false;
bool breaker = false;
bool loopIsRunning = false;

int drivePosTarget = 0;
int targetHeading = 0;
