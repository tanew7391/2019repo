/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <iostream>
#include "Robot.h"

#include <frc/commands/Scheduler.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include "networktables/NetworkTableInstance.h"



DrivetrainSub Robot::drivetrainSub;
BallIntakeSub Robot::ballIntakeSub;
HatchSub Robot::hatchSub;
ElevatorSub Robot::elevatorSub;
OI Robot::oi;

void Robot::RobotInit() {
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {

}

/**
 * This function is called once each time the robot enters Disabled mode. You
 * can use it to reset any subsystem information you want to clear when the
 * robot is disabled.
 */
void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() { 
  frc::Scheduler::GetInstance()->Run(); 

  }

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString code to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional commands to the
 * chooser code above (like the commented example) or additional comparisons to
 * the if-else structure below with additional strings & commands.
 */
void Robot::AutonomousInit() {

  nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("camMode", 0);

  nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("ledMode", 3);

  nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("pipeline", 0);

  m_autonomousCommand = m_chooser.GetSelected();

  if (m_autonomousCommand != nullptr) {
    m_autonomousCommand->Start();
  }

}

void Robot::AutonomousPeriodic() { 
  frc::Scheduler::GetInstance()->Run(); 

  }

void Robot::TeleopInit() {
  // This makes sure that the autonomous stops running when
  // teleop starts running. If you want the autonomous to
  // continue until interrupted by another command, remove
  // this line or comment it out.
  if (m_autonomousCommand != nullptr) {
    m_autonomousCommand->Cancel();
    m_autonomousCommand = nullptr;
  }
  
  frc::CameraServer::GetInstance()->StartAutomaticCapture("usbCam1", "/dev/video0");
  frc::CameraServer::GetInstance()->StartAutomaticCapture("usbCam2", "/dev/video1");
//  Robot::m_drivetrainSub.drive(0.25, 0.25);
}

void Robot::TeleopPeriodic() { 
  UpdateSmartDashboard();
  frc::Scheduler::GetInstance()->Run(); 
}

void Robot::TestPeriodic() {
;
}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif

void Robot::UpdateSmartDashboard(){
  frc::SmartDashboard::PutNumber("Left Drive Motor Enc", drivetrainSub.GetLeftEncoder());
  frc::SmartDashboard::PutNumber("Right Drive Motor Enc", drivetrainSub.GetRightEncoder());

  //Limelight Data
  std::shared_ptr<NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
  double targetPerecentArea = table->GetNumber("ta", 0.0);
  double targetSkew = table->GetNumber("ts", 0.0);
  double targetHorizontalOffset = table->GetNumber("tx", 0.0);
  double targetVerticalOffset = table -> GetNumber("ty", 0.0);
  bool foundTarget = table->GetNumber("tv", 0.0);
  double limelightLatency = table->GetNumber("tl", 0.0);
  double targetShort = table->GetNumber("tshort", 0.0);
  double targetLong =table->GetNumber("tlong", 0.0);
  double targetHorizontalLength = table->GetNumber("thoriz", 0.0);
  double targetVerticalLength =  table ->GetNumber("tvert", 0.0);

  frc::SmartDashboard::PutNumber("Target Percent Area", targetPerecentArea);
  frc::SmartDashboard::PutNumber("Target Skew", targetSkew);
  frc::SmartDashboard::PutNumber("Target Horizontal Offset" ,targetHorizontalOffset);
  frc::SmartDashboard::PutNumber("Target Vertical Offset" ,targetVerticalOffset);
  frc::SmartDashboard::PutNumber("Target is in view", foundTarget);
  frc::SmartDashboard::PutNumber("Limelight Latency", limelightLatency);
  frc::SmartDashboard::PutNumber("Target's shortest side of fitted bounding box", targetShort);
  frc::SmartDashboard::PutNumber("Target's longest side of fitted bounding box", targetLong);
  frc::SmartDashboard::PutNumber("Target's horiz. sidelength of rough bounding box", targetHorizontalLength);
  frc::SmartDashboard::PutNumber("Target's vert. sidelength of rough bounding box", targetVerticalLength);





}



double Robot::GetVisionTarget() {
  
  double xAngle = 9001;
  // if over 9000, the vision target is not picking up anything.
  double TargetMarked = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tv", 0.0);

  if (TargetMarked > 0.5) {
    xAngle = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tx", 0.0);
  }

  return xAngle;
}

double Robot::GetDistanceFromVision() {
  double size=nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("thori",0.0);
  double a=0.295;
  double b=-70.6;
  double c=5234;
  return a*size*size+b*size+c;
}

double Robot::GetVisionTargetAngle() {
  double RobotAngle = Robot::drivetrainSub.getAngle();
  double TargetAngle[7] = {-151.25, -90, -21.75, 0, 21.75, 90, 151.25};
  double SmallestAngleDifference = 1000;
  int BestTarget;

  for(int i = 0; i < 7; i++){
    double AngleDifference = fabs(RobotAngle - TargetAngle[i]);
    if(AngleDifference <= SmallestAngleDifference){
      SmallestAngleDifference = AngleDifference;
      BestTarget = i;
    }
  }
  return TargetAngle[BestTarget];
}