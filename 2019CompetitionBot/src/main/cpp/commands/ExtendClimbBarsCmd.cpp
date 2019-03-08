/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ExtendClimbBarsCmd.h"
#include "subsystems/ClimbSub.h"
#include "Robot.h"

ExtendClimbBarsCmd::ExtendClimbBarsCmd() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::climbSub);
}

// Called just before this Command runs the first time
void ExtendClimbBarsCmd::Initialize() {
  Robot::climbSub.SetClimbMotorPower(1);
}

// Called repeatedly when this Command is scheduled to run
void ExtendClimbBarsCmd::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool ExtendClimbBarsCmd::IsFinished() { 
  logger.send(logger.CLIMB, "position = %.1f \n", Robot::climbSub.getClimbPosition());
 
  // return Robot::climbSub.getClimbPosition() > CLIMB_EXTEND_LIMIT_THRESHOLD; 
  if (Robot::climbSub.GetClimbEncoder() >= 400 ) {
    return true;
}
  return false;
}

// Called once after isFinished returns true
void ExtendClimbBarsCmd::End() {
    Robot::climbSub.SetClimbMotorPower(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ExtendClimbBarsCmd::Interrupted() {
    End();
}