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
#include "AmclTaskCore.hh"
#include "SmartAmcl.hh"

//FIXME: use logging
//#include "smartGlobalLogger.hh"

// include observers

int AmclTaskCore::execute_protected_region()
{
	if(useDefaultState) {
		Smart::StatusCode status = COMP->stateSlave->acquire("active");
		if(status != Smart::SMART_OK) {
			std::cerr << "AmclTaskCore: ERROR acquiring state active: " << status << std::endl;
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
		COMP->stateSlave->release("active");
	}
	return retval;
}


void AmclTaskCore::updateAllCommObjects()
{
	laserServiceInStatus = COMP->laserServiceInInputTaskTrigger->getUpdate(laserServiceInObject);
}


// this method is meant to be used in derived classes
Smart::StatusCode AmclTaskCore::localizationEventServiceOutPut(CommLocalizationObjects::LocalizationEventState &eventState)
{
	Smart::StatusCode result = COMP->localizationEventServiceOut->put(eventState);
	if(useLogging == true) {
		//FIXME: use logging
		//Smart::LOGGER->log(pushLoggingId+1, getCurrentUpdateCount(), getPreviousCommObjId());
	}
	return result;
}
// this method is meant to be used in derived classes
Smart::StatusCode AmclTaskCore::localizationUpdateServiceOutPut(CommBasicObjects::CommBasePositionUpdate &localizationUpdateServiceOutDataObject)
{
	Smart::StatusCode result = COMP->localizationUpdateServiceOut->send(localizationUpdateServiceOutDataObject);
	if(useLogging == true) {
		//FIXME: use logging
		//Smart::LOGGER->log(pushLoggingId+1, getCurrentUpdateCount(), getPreviousCommObjId());
	}
	return result;
}

void AmclTaskCore::triggerLogEntry(const int& idOffset)
{
	if(useLogging == true) {
		int logId = taskLoggingId + 2*2 + idOffset;
		//FIXME: use logging
		//Smart::LOGGER->log(logId, getCurrentUpdateCount(), getPreviousCommObjId());
	}
}

int AmclTaskCore::getPreviousCommObjId()
{
	// this method needs to be overloaded and implemented in derived classes
	return 0;
}