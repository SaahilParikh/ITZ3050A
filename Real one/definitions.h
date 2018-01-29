//Mogo Posititions
////////////////////////down   1    2      3    4      5    6     7      8
const int mogoPos[9] = {315, 1550, 1500, 1500, 1600, 1790, 1850, 2380, 2500};
const int armPos[9] = {   0,  420,  395,  350,  350,  350,  350,  335,  310};


#define zeroM 35

#define wheelDiameter 4

#define timeConstDrive (4/wheelDiameter)
#define timeConstLift 1
#define timeConstMogo 1

//Arm Postitions
/////////////////////


int bottom = armPos[0];
#define driverLoadArmPos 150
#define stationaryArmPos 290
#define topArmPos 300

#define potBand 50

#define potDiff 13

#define potR (SensorValue[potRight]-potDiff)
#define potL (SensorValue[potLeft])

#define driveRightEnc SensorValue[encRight]
#define driveLeftEnc SensorValue[encLeft]
#define getHeading SensorValue[gyro]


bool isMove = true;
bool mogoIsFront = false;
bool breaker = false;
bool loopIsRunning = false;
bool doneWithCone = false;

int mogoPosTarget = mogoPos[0];
int armPosTarget= armPos[0];
int drivePosTarget = 0;
int targetHeading = 0;

int coneCount = 1; // how many cones we jave



bool pressMU = false;
bool pressMD = false;
bool inc = false;
bool dec = false;
bool rest = false;
bool isMoveArm = false;
