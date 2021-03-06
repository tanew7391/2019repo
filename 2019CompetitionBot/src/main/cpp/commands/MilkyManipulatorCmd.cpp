/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/MilkyManipulatorCmd.h"
#include "OI.H"
#include "Robot.h"
#include <iostream>

constexpr double JOYSTICK_DEADBAND = 0.01;

MilkyManipulatorCmd::MilkyManipulatorCmd() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::drivetrainSub);
}

// Called just before this Command runs the first time
void MilkyManipulatorCmd::Initialize() {
  //logger.send(logger.CMD_TRACE, "%s : %s\n", __FILE__, __FUNCTION__);
  if (Robot::manipulatorSub.getFlipperAngle() > 0) {
    Robot::visionSub.setManipulatorPipeline(VISION_MODE_NORMAL); 
  }
  else{
    Robot::visionSub.setManipulatorPipeline(VISION_MODE_FLIPPED);
  }
}

// Called repeatedly when this Command is scheduled to run
// USE HATCH VISION COMMAND AND NOT THIS ONE
// THIS ONE DOES NOT DO THE RIGHT THING
//IT IS LOW-KEY CLAPPED SO JUST DON'T
void MilkyManipulatorCmd::Execute() {
  std::shared_ptr<frc::Joystick> driverJoystick = Robot::oi.getDriverController();

  double targetAngle=Robot::visionSub.getVisionTarget(BUMPER_CAMERA);
  
  if(fabs(driverJoystick->GetX()) > JOYSTICK_DEADBAND){
    targetAngle += (driverJoystick->GetX()*20.0);
  }
  

  if (Robot::visionSub.isTargetVisible(MANIPULATOR_CAMERA) ){
    double lSpeed=(0);
    double rSpeed=(0);

    if (Robot::manipulatorSub.getFlipperAngle() > 0) {
      lSpeed=((targetAngle*0.007));
      rSpeed=(-(targetAngle*0.007));
    } else {
      lSpeed=(-(targetAngle*0.007));
      rSpeed=((targetAngle*0.007));
    }
    Robot::drivetrainSub.drive(lSpeed,rSpeed);
  } else {
    Robot::drivetrainSub.drive(0,0);    
  } 
}

// Make this return true when this Command no longer needs to run execute()
bool MilkyManipulatorCmd::IsFinished() { return false; }

// Called once after isFinished returns true
void MilkyManipulatorCmd::End() {
  //MilkyManipulatorCmd.milkyManipulator(0.0);
  Robot::drivetrainSub.drive(0,0);
  Robot::visionSub.setManipulatorPipeline(DRIVER_MODE_NORMAL);

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MilkyManipulatorCmd::Interrupted() {
  End();
}
//Green Milk
//Green Milk
//Green Milk
//Green Milk