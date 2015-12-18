#pragma config(Motor,  port2,           FW1,           tmotorVex393, openLoop)
#pragma config(Motor,  port3,           FW2,           tmotorVex393, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//


// Flywheel consisting of one wheel and 2 motors, no slow-down/speed-up
// To-do: Add preset power values

void Flywheel(int speed)
{
	motor[FW1] = speed;
	motor[FW2] = speed;
}

/* int x = 0;
int f = 127;
int cont = 0; */

task main()
{
	while(true)
	{
		if(vexRT[Btn5U] == 1) // && (motor[FW1] >= 65))
		/*{
			if(vexRT[Btn7U] == 1)
			{
				f = 127;
				Flywheel(f);
			}
			else if(vexRT[Btn7R] == 1)
			{
				f = 107;
				Flywheel(f);
			}
			else if(vexRT[Btn7D] == 1)
			{
				f = 87;
				Flywheel(f);
			}
			else if(vexRT[Btn7L] == 1)
			{
				f = 67;
				Flywheel(f);
			}
			else */
			{
				Flywheel(127);
			}
		else
		{
			Flywheel(0);
			/* f = 127;
			cont = 0; */
		}
	}
}