#pragma config(Sensor, in1,    gyro,           sensorGyro)
#pragma config(Sensor, dgtl1,  RB1,            sensorQuadEncoder)
#pragma config(Motor,  port1,           in1,           tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port2,           DFR,           tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port3,           DBR,           tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port4,           DFL,           tmotorVex393, openLoop)
#pragma config(Motor,  port5,           DBL,           tmotorVex393, openLoop)
#pragma config(Motor,  port6,           FW1,           tmotorVex393, openLoop)
#pragma config(Motor,  port7,           FW2,           tmotorVex393, openLoop)
#pragma config(Motor,  port8,           FW3,           tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port9,           FW4,           tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port10,          in2,           tmotorVex393, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/* 12/22/15

// COMPETITION PROGRAM

// TO DO: Find a way to implement conveyor that will allow the ball to incline up the flywheel
(Power expander and Y-split needed)
HOW TO SET UP PORTS :

FW1 is front left, FW4 IS back right.
(when standing behind flywheel, shooting is front) if yo uneed me, text 562-889-4304 and sign ur name at the end

Holonomic drive: for DFR/DBR/DFL/DBL...
in1 is bottom, in2 is right.

FW3 and FW4 are reversed so flywheel can shoot.
in2 is reversed so intakes move in same direction.
DFR and DBR reversed so robot moves in correct directions. */




#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

/////////////////////////////////////////////////////////////////////////////////////////////
////////// FUNCTIONS ////////////////////////////////////////////////////////////////////////

bool fwmove = false;

void Flywheel(int speed)
{
	motor[FW1] = speed;
	motor[FW2] = speed;
	motor[FW3] = speed;
	motor[FW4] = speed;
}


void intake (int speed)
{
	motor[in1] = speed;
	motor[in2] = speed;
}


void strafe(int speed)
{
	motor[DFR] = 0;
	motor[DBR] = speed;
	motor[DBL] = 0;
	motor[DFL] = speed;
}


void driveRotate(int speed)
{
	motor[DFR] = -speed;
	motor[DBR] = -speed;
	motor[DBL] = speed;
	motor[DFL] = speed;
}

void driveStraight(int speed)
{
	motor[DFR] = speed;
	motor[DBR] = 0;
	motor[DBL] = speed;
	motor[DFL] = 0;
}



void checkSensorValue(int distance, int speed)
{
	while(SensorValue(RB1) < distance)
	{
		driveStraight(speed);
	}
}

void gyroTurn(int degrees)
{
	int gyroDrift = 10;
	while(abs(SensorValue[gyro]) > degrees + gyroDrift || abs(SensorValue[gyro]) < degrees - gyroDrift)
	{
		if(abs(SensorValue[gyro]) > degrees)
		{
			motor[DBR] = 40;
			motor[DBL] = 40;
			motor[DFR] = 40;
			motor[DFL] = 40;
		}
		else
		{

		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////

void pre_auton()
{
	// Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
	// Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
	bStopTasksBetweenModes = true;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is   used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task autonomous()
{

	// Autonomous 0: Spin flywheel at lower power, drive straight for 2 seconds, flywheel at full
	//							power, wait 1 second, intake at full power
	Flywheel(50);
  driveStraight(127);
  wait1Msec(2000);
  driveStraight(0);
  Flywheel(127);
  wait1Msec(1000);
  intake(127);


	/*
	Autonomous 1: Spin flywheel at full power perpetually
	Flywheel(25);
	driveStraight(127);
	wait1Msec(750);
	Flywheel(50);
	driveStraight(0);
	strafe(-127);
	wait1Msec(2000);
	Flywheel(127);
	strafe(0);
	intake(127);
	*/

	/*
	Autonomous 2: Spin the Flywheel, then move
	Flywheel(127);
	//confirm that ball has been launched
	checkSensorValue(some distance, 127);
	*/

	/*
	Autonomous 3: run forward and try to control some of the balls on the floor
	motor[conveyor] = 100;
	checkSensorValue(500,127);
	gyroTurn(420);
	*/
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////



task usercontrol()
{
	int threshold = 20;
	// int x, y, z; <--- used for UDLR drive control (2 wheels at a time)

	// MECANUM DRIVE VARIABLES /////////////////////////////////////////////////////////////////////////
	// [Left joystick, Y-axis] Ch3 = Y1 (Forward/Backward movement)
	// [Left joystick, X-axis] Ch4 = X1 (Srafe)
	// [Right joystick, X-axis] Ch1 = X2 (Rotation)

	int Y1 = 0, X1 = 0, X2 = 0;

	while(true)
	{
		// Flywheel //////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////
		if (fwmove == false)
		{
			if (vexRT[Btn5U] == 1)
			{
				Flywheel(127);
				fwmove = true;
			}
		}


		if (fwmove == true)
		{
			if (vexRT[Btn5U] == 1)
			{
				Flywheel(127);
			}
			if (vexRT[Btn7U] == 1)
			{
				Flywheel(100);
			}
			else if (vexRT[Btn7L] == 1)
			{
				Flywheel(75);
			}
			else if (vexRT[Btn7D] == 1)
			{
				Flywheel(50);
			}
			else if (vexRT[Btn7R] == 1)
			{
				Flywheel(25);
			}
			else if (vexRT[Btn5D] == 1)
			{
				Flywheel(0);
				fwmove = false;
			}
		}


	/* if(abs(vexRT[Ch3]) > threshold)
	{
		x = vexRT[Ch3];
		driveStraight(x);
	}




	if(abs(vexRT[Ch1]) > threshold)
	{
		z = vexRT[Ch1];
		driveRotate(z);
	} */


		// Mecanum Drive /////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////
		if(abs(vexRT[Ch3]) > threshold)
		{
			Y1 = vexRT[Ch3];
		}
		else
		{
			Y1 = 0;
		}

		if(abs(vexRT[Ch4]) > threshold)
		{
			X1 = vexRT[Ch4];
		}
		else
		{
			X1 = 0;
		}

		if(abs(vexRT[Ch1]) > threshold)
		{
			X2 = vexRT[Ch1];
		}
		else
		{
			X2 = 0;
		}
		//Remote Control Commands
		motor[DFR] = Y1 - X2 - X1;
		motor[DBR] =  Y1 - X2 + X1;
		motor[DFL] = Y1 + X2 + X1;
		motor[DBL] =  Y1 + X2 - X1;

		// Intake ////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////
		if(vexRT[Btn6U] == 1)
		{
			intake(127);
		}
		else if(vexRT[Btn6D] == 1)
		{
			intake(-127);
		}
		else
		{
			intake(0);
		}
	}
}
