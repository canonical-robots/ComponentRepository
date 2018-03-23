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
// Please do not modify this file. It will be re-generated
// running the code generator.
//--------------------------------------------------------------------------
#include "CdlTaskCore.hh"
#include "SmartCdlServer.hh"

//FIXME: use logging
//#include "smartGlobalLogger.hh"

// include observers

int CdlTaskCore::execute_protected_region()
{
	if(useDefaultState) {
		Smart::StatusCode status = COMP->stateSlave->acquire("moveRobot");
		if(status != Smart::SMART_OK) {
			std::cerr << "CdlTaskCore: ERROR acquiring state active: " << status << std::endl;
			return 0;
		}
	}
	
	// update of comm-objects must be within the protected region to prevent aged comm-object values
	this->updateAllCommObjects();
	
	if(useLogging == true) {
		//FIXME: use logging
		//Smart::LOGGER->log(taskLoggingId, getCurrentUpdateCount(), getPreviousCommObjId());
	}
	
	// this is the user code (should not internally use the state-pattern any more)
	int retval = this->on_execute();
	
	// increment current currentUpdateCount for the next iteration
	currentUpdateCount++;
	
	if(useDefaultState) {
		COMP->stateSlave->release("moveRobot");
	}
	return retval;
}


void CdlTaskCore::updateAllCommObjects()
{
	baseStateClientStatus = COMP->baseStateClientInputTaskTrigger->getUpdate(baseStateClientObject);
	iRClientStatus = COMP->iRClientInputTaskTrigger->getUpdate(iRClientObject);
	laserClientStatus = COMP->laserClientInputTaskTrigger->getUpdate(laserClientObject);
	laserClient2Status = COMP->laserClient2InputTaskTrigger->getUpdate(laserClient2Object);
	navVelSendServerStatus = COMP->navVelSendServerInputTaskTrigger->getUpdate(navVelSendServerObject);
	pathNavigationGoalClientStatus = COMP->pathNavigationGoalClientInputTaskTrigger->getUpdate(pathNavigationGoalClientObject);
	plannerClientStatus = COMP->plannerClientInputTaskTrigger->getUpdate(plannerClientObject);
	trackingClientStatus = COMP->trackingClientInputTaskTrigger->getUpdate(trackingClientObject);
}


// this method is meant to be used in derived classes
Smart::StatusCode CdlTaskCore::goalEventServerPut(CommNavigationObjects::CdlGoalEventState &eventState)
{
	Smart::StatusCode result = COMP->goalEventServer->put(eventState);
	if(useLogging == true) {
		//FIXME: use logging
		//Smart::LOGGER->log(pushLoggingId+1, getCurrentUpdateCount(), getPreviousCommObjId());
	}
	return result;
}
// this method is meant to be used in derived classes
Smart::StatusCode CdlTaskCore::navVelSendClientPut(CommBasicObjects::CommNavigationVelocity &navVelSendClientDataObject)
{
	Smart::StatusCode result = COMP->navVelSendClient->send(navVelSendClientDataObject);
	if(useLogging == true) {
		//FIXME: use logging
		//Smart::LOGGER->log(pushLoggingId+1, getCurrentUpdateCount(), getPreviousCommObjId());
	}
	return result;
}
// this method is meant to be used in derived classes
Smart::StatusCode CdlTaskCore::robotBlockedEventServerPut(CommNavigationObjects::CommCdlRobotBlockedState &eventState)
{
	Smart::StatusCode result = COMP->robotBlockedEventServer->put(eventState);
	if(useLogging == true) {
		//FIXME: use logging
		//Smart::LOGGER->log(pushLoggingId+1, getCurrentUpdateCount(), getPreviousCommObjId());
	}
	return result;
}

void CdlTaskCore::triggerLogEntry(const int& idOffset)
{
	if(useLogging == true) {
		int logId = taskLoggingId + 2*3 + idOffset;
		//FIXME: use logging
		//Smart::LOGGER->log(logId, getCurrentUpdateCount(), getPreviousCommObjId());
	}
}

int CdlTaskCore::getPreviousCommObjId()
{
	// this method needs to be overloaded and implemented in derived classes
	return 0;
}