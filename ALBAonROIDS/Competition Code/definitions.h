//Mogo Posititions
////////////////////////down   1    2      3    4      5    6     7      8
const int mogoPos[9] = {315, 1550, 1500, 1500, 1600, 1790, 1790, 2380, 2500};
const int armPos[9] = {   0,  420,  395,  350,  350,  350,  350,  335,  310};


   #define zeroM 35
#define oneM (bottom + 1300),
#define twoM (bottom + 1400)
#define threeM (bottom + 1500)
#define fourM (bottom + 1600)
#define fiveM (bottom + 1800)
#define sixM (bottom + 2300)
#define sevenM (bottom + 2500)
#define eightM (bottom + 2700)}



//Arm Postitions
/////////////////////

#define zeroA 0
#define oneA 0
#define twoA 0
#define threeA 0
#define fourA 0
#define fiveA 0
#define sixA 0
#define sevenA 0
#define eightA 0

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
