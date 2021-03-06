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
#include "ImageTask.hh"
#include "ComponentVisualization.hh"

#include <iostream>

ImageTask::ImageTask(SmartACE::SmartComponent *comp) 
:	ImageTaskCore(comp)
{
	std::cout << "constructor ImageTask\n";
}
ImageTask::~ImageTask() 
{
	std::cout << "destructor ImageTask\n";
}

int ImageTask::connectServices(){
	std::cout << "connecting to: " << COMP->connections.imagePushNewestClient.serverName << "; " << COMP->connections.imagePushNewestClient.serviceName << std::endl;
	Smart::StatusCode status = COMP->imagePushNewestClient->connect(COMP->connections.imagePushNewestClient.serverName, COMP->connections.imagePushNewestClient.serviceName);
	while (status != Smart::SMART_OK){
		usleep(500000);
		status = COMP->imagePushNewestClient->connect(COMP->connections.imagePushNewestClient.serverName, COMP->connections.imagePushNewestClient.serviceName);
	}
	std::cout << COMP->connections.imagePushNewestClient.serverName << "; " << COMP->connections.imagePushNewestClient.serviceName << " connected.\n";
	return 0;
}
int ImageTask::disconnectServices(){
	COMP->imagePushNewestClient->disconnect();
	return 0;
}

int ImageTask::on_entry()
{
	// do initialization procedures here, which are called once, each time the task is started
	// it is possible to return != 0 (e.g. when initialization fails) then the task is not executed further
	imageVisualization= new ImageVisualization("Color Image");
	COMP->imagePushNewestClient->subscribe();

	return (imageVisualization !=0)? 0 : 1;
}
int ImageTask::on_execute()
{
	// this method is called from an outside loop,
	// hence, NEVER use an infinite loop (like "while(1)") here inside!!!
	// also do not use blocking calls which do not result from smartsoft kernel
	Smart::StatusCode status = COMP->imagePushNewestClient->getUpdateWait(image);
	if (status == Smart::SMART_OK)
	{
		imageVisualization->displayImage(image);
	} else
	{
		std::cout << "[ImageTask] error while getting new image: " << Smart::StatusCodeConversion(status) << "\n";
	}
	// it is possible to return != 0 (e.g. when the task detects errors), then the outer loop breaks and the task stops
	return 0;
}
int ImageTask::on_exit()
{
	// use this method to clean-up resources which are initialized in on_entry() and needs to be freed before the on_execute() can be called again
	delete imageVisualization;
	COMP->imagePushNewestClient->unsubscribe();
	return 0;
}
