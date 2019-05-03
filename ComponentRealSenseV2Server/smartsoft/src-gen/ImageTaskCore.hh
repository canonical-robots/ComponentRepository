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
#ifndef _IMAGETASK_CORE_HH
#define _IMAGETASK_CORE_HH
	
#include "aceSmartSoft.hh"

// include upcall interface
#include "UrPosePushTimedClientUpcallInterface.hh"
#include "BasePushTimedClientUpcallInterface.hh"
#include "PtuPosePushNewestClientUpcallInterface.hh"

// include communication-objects for output ports
#include <DomainVision/CommVideoImage.hh>
#include <DomainVision/CommDepthImage.hh>
#include <DomainVision/CommRGBDImage.hh>

// include all interaction-observer interfaces
#include <ImageTaskObserverInterface.hh>


class ImageTaskCore
:	public SmartACE::ManagedTask
,	public Smart::TaskTriggerSubject
,	public UrPosePushTimedClientUpcallInterface
,	public BasePushTimedClientUpcallInterface
,	public PtuPosePushNewestClientUpcallInterface
{
private:
	bool useDefaultState; 
	bool useLogging;
	int taskLoggingId;
	unsigned int currentUpdateCount;
	
	Smart::StatusCode urPosePushTimedClientStatus;
	CommManipulatorObjects::CommMobileManipulatorState urPosePushTimedClientObject;
	Smart::StatusCode basePushTimedClientStatus;
	CommBasicObjects::CommBaseState basePushTimedClientObject;
	Smart::StatusCode ptuPosePushNewestClientStatus;
	CommBasicObjects::CommDevicePoseState ptuPosePushNewestClientObject;
	
	
protected:
	virtual int execute_protected_region();
	
	virtual void updateAllCommObjects();
	
	virtual int getPreviousCommObjId();
	
	void triggerLogEntry(const int& idOffset);
	
	
	// overload and implement this method in derived classes to immediately get all incoming updates from UrPosePushTimedClient (as soon as they arrive)
	virtual void on_UrPosePushTimedClient(const CommManipulatorObjects::CommMobileManipulatorState &input) {
		// no-op
	}
	
	// this method can be safely used from the thread in derived classes
	inline Smart::StatusCode urPosePushTimedClientGetUpdate(CommManipulatorObjects::CommMobileManipulatorState &urPosePushTimedClientObject) const
	{
		// copy local object buffer and return the last status code
		urPosePushTimedClientObject = this->urPosePushTimedClientObject;
		return urPosePushTimedClientStatus;
	}
	// overload and implement this method in derived classes to immediately get all incoming updates from basePushTimedClient (as soon as they arrive)
	virtual void on_basePushTimedClient(const CommBasicObjects::CommBaseState &input) {
		// no-op
	}
	
	// this method can be safely used from the thread in derived classes
	inline Smart::StatusCode basePushTimedClientGetUpdate(CommBasicObjects::CommBaseState &basePushTimedClientObject) const
	{
		// copy local object buffer and return the last status code
		basePushTimedClientObject = this->basePushTimedClientObject;
		return basePushTimedClientStatus;
	}
	// overload and implement this method in derived classes to immediately get all incoming updates from ptuPosePushNewestClient (as soon as they arrive)
	virtual void on_ptuPosePushNewestClient(const CommBasicObjects::CommDevicePoseState &input) {
		// no-op
	}
	
	// this method can be safely used from the thread in derived classes
	inline Smart::StatusCode ptuPosePushNewestClientGetUpdate(CommBasicObjects::CommDevicePoseState &ptuPosePushNewestClientObject) const
	{
		// copy local object buffer and return the last status code
		ptuPosePushNewestClientObject = this->ptuPosePushNewestClientObject;
		return ptuPosePushNewestClientStatus;
	}
	
	// this method is meant to be used in derived classes
	Smart::StatusCode colorImagePushNewestServerPut(DomainVision::CommVideoImage &colorImagePushNewestServerDataObject);
	// this method is meant to be used in derived classes
	Smart::StatusCode depthPushNewestServerPut(DomainVision::CommDepthImage &depthPushNewestServerDataObject);
	// this method is meant to be used in derived classes
	Smart::StatusCode imagePushNewestServerPut(DomainVision::CommRGBDImage &imagePushNewestServerDataObject);
	
	
/**
 * Implementation of the Subject part of an InteractionObserver
 */
private:
	std::mutex interaction_observers_mutex;
	std::list<ImageTaskObserverInterface*> interaction_observers;
protected:
	void notify_all_interaction_observers();
public:
	void attach_interaction_observer(ImageTaskObserverInterface *observer);
	void detach_interaction_observer(ImageTaskObserverInterface *observer);

public:
	ImageTaskCore(Smart::IComponent *comp, const bool &useDefaultState=true);
	virtual ~ImageTaskCore();
	
	inline void setUpLogging(const int &taskNbr, const bool &useLogging=true) {
		this->taskLoggingId = taskNbr;
		this->useLogging = useLogging;
	}
	
	inline bool isLoggingActive() const {
		return useLogging;
	}
	
	inline int getLoggingID() const {
		return taskLoggingId;
	}
	
	inline int getCurrentUpdateCount() const {
		return currentUpdateCount;
	}
	
};
#endif