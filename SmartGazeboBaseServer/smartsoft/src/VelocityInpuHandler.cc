//--------------------------------------------------------------------------
// Code generated by the SmartSoft MDSD Toolchain
// The SmartSoft Toolchain has been developed by:
//  
// Service Robotics Research Center
// University of Applied Sciences Ulm
// Prittwitzstr. 10
// 89075 Ulm (Germany)
//
// Information about the SmartSoft MDSD Toolchain is available at:
// www.servicerobotik-ulm.de
//
// This file is generated once. Modify this file to your needs. 
// If you want the toolchain to re-generate this file, please 
// delete it before running the code generator.
//--------------------------------------------------------------------------
#include "VelocityInpuHandler.hh"

#include "SmartGazeboBaseServer.hh"

#include <iostream>

VelocityInpuHandler::VelocityInpuHandler(Smart::InputSubject<CommBasicObjects::CommNavigationVelocity> *subject, const int &prescaleFactor)
:	VelocityInpuHandlerCore(subject, prescaleFactor)
{
	std::cout << "constructor VelocityInpuHandler\n";
}
VelocityInpuHandler::~VelocityInpuHandler() 
{
	std::cout << "destructor VelocityInpuHandler\n";
}

void VelocityInpuHandler::on_NavVelServiceIn(const CommBasicObjects::CommNavigationVelocity& input)
{
	gazebo::msgs::Vector3d msg;
	gazebo::msgs::Set(&msg, ignition::math::Vector3d(input.get_vX()/1000.0, input.get_vY()/1000.0, input.get_omega()));
	// send command to gazebo topic
	if (COMP->sendVelTopic != NULL) {
		COMP->sendVelTopic->Publish(msg);
	}
	else {
		std::cout << "Gazebo Simulator not yet started !" << std::endl;
	}
}
