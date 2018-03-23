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
#include "SmartCdlServer.hh"
#include "smartTimedTaskTrigger.h"
//FIXME: implement logging
//#include "smartGlobalLogger.hh"

#include "GoalEventServerEventTestHandler.hh"
#include "RobotBlockedEventServerEventTestHandler.hh"

// constructor
SmartCdlServer::SmartCdlServer()
{
	std::cout << "constructor of SmartCdlServer\n";
	
	component = NULL;
	
	// set all pointer members to NULL
	baseStateClient = NULL;
	baseStateClientInputTaskTrigger = NULL;
	baseStateClientUpcallManager = NULL;
	cdlTask = NULL;
	cdlTaskTrigger = NULL;
	goalEventServer = NULL;
	goalEventServerEventTestHandler = NULL; 
	iRClient = NULL;
	iRClientInputTaskTrigger = NULL;
	iRClientUpcallManager = NULL;
	laserClient = NULL;
	laserClientInputTaskTrigger = NULL;
	laserClientUpcallManager = NULL;
	laserClient2 = NULL;
	laserClient2InputTaskTrigger = NULL;
	laserClient2UpcallManager = NULL;
	navVelSendClient = NULL;
	navVelSendServer = NULL;
	navVelSendServerInputTaskTrigger = NULL;
	navVelSendServerUpcallManager = NULL;
	pathNavigationGoalClient = NULL;
	pathNavigationGoalClientInputTaskTrigger = NULL;
	pathNavigationGoalClientUpcallManager = NULL;
	plannerClient = NULL;
	plannerClientInputTaskTrigger = NULL;
	plannerClientUpcallManager = NULL;
	robotBlockedEventServer = NULL;
	robotBlockedEventServerEventTestHandler = NULL; 
	trackingClient = NULL;
	trackingClientInputTaskTrigger = NULL;
	trackingClientUpcallManager = NULL;
	stateChangeHandler = NULL;
	stateSlave = NULL;
	wiringSlave = NULL;
	param = NULL;
	
	// set default ini parameter values
	connections.component.name = "SmartCdlServer";
	connections.component.initialMainState = "Neutral";
	connections.component.defaultScheduler = "DEFAULT";
	connections.component.useLogger = false;
	
	connections.goalEventServer.serviceName = "GoalEventServer";
	connections.navVelSendServer.serviceName = "NavVelSendServer";
	connections.robotBlockedEventServer.serviceName = "RobotBlockedEventServer";
	connections.baseStateClient.initialConnect = false;
	connections.baseStateClient.serverName = "unknown";
	connections.baseStateClient.serviceName = "unknown";
	connections.baseStateClient.interval = 1;
	connections.iRClient.initialConnect = false;
	connections.iRClient.serverName = "unknown";
	connections.iRClient.serviceName = "unknown";
	connections.iRClient.interval = 1;
	connections.laserClient.serverName = "unknown";
	connections.laserClient.serviceName = "unknown";
	connections.laserClient.interval = 1;
	connections.laserClient2.initialConnect = false;
	connections.laserClient2.serverName = "unknown";
	connections.laserClient2.serviceName = "unknown";
	connections.laserClient2.interval = 1;
	connections.navVelSendClient.initialConnect = false;
	connections.navVelSendClient.serverName = "unknown";
	connections.navVelSendClient.serviceName = "unknown";
	connections.navVelSendClient.interval = 1;
	connections.pathNavigationGoalClient.initialConnect = false;
	connections.pathNavigationGoalClient.serverName = "unknown";
	connections.pathNavigationGoalClient.serviceName = "unknown";
	connections.pathNavigationGoalClient.interval = 1;
	connections.plannerClient.initialConnect = false;
	connections.plannerClient.serverName = "unknown";
	connections.plannerClient.serviceName = "unknown";
	connections.plannerClient.interval = 1;
	connections.trackingClient.initialConnect = false;
	connections.trackingClient.serverName = "unknown";
	connections.trackingClient.serviceName = "unknown";
	connections.trackingClient.interval = 1;
	connections.cdlTask.minActFreq = 5.0;
	connections.cdlTask.maxActFreq = 40.0;
	connections.cdlTask.prescale = 1;
	connections.cdlTask.trigger = "PeriodicTimer";
	connections.cdlTask.periodicActFreq = 20.0;
	// scheduling default parameters
	connections.cdlTask.scheduler = "DEFAULT";
	connections.cdlTask.priority = -1;
	connections.cdlTask.cpuAffinity = -1;
}



/**
 * Notify the component that setup/initialization is finished.
 * You may call this function from anywhere in the component.
 *
 * Set component's internal lifecycle state automaton (if any) into 
 * Alive mode (from here on the component is ready to provide its services)
 */
void SmartCdlServer::setStartupFinished() {
	stateSlave->setWaitState("Alive");
	std::cout << "ComponentDefinition initialization/startup finished." << std::endl;
}


Smart::StatusCode SmartCdlServer::connectBaseStateClient(const std::string &serverName, const std::string &serviceName) {
	Smart::StatusCode status;
	
	if(connections.baseStateClient.initialConnect == false) {
		return Smart::SMART_OK;
	}
	std::cout << "connecting to: " << serverName << "; " << serviceName << std::endl;
	status = baseStateClient->connect(serverName, serviceName);
	while(status != Smart::SMART_OK)
	{
		ACE_OS::sleep(ACE_Time_Value(0,500000));
		status = COMP->baseStateClient->connect(serverName, serviceName);
	}
	std::cout << "connected.\n";
	baseStateClient->subscribe(connections.baseStateClient.interval);
	return status;
}
Smart::StatusCode SmartCdlServer::connectIRClient(const std::string &serverName, const std::string &serviceName) {
	Smart::StatusCode status;
	
	if(connections.iRClient.initialConnect == false) {
		return Smart::SMART_OK;
	}
	std::cout << "connecting to: " << serverName << "; " << serviceName << std::endl;
	status = iRClient->connect(serverName, serviceName);
	while(status != Smart::SMART_OK)
	{
		ACE_OS::sleep(ACE_Time_Value(0,500000));
		status = COMP->iRClient->connect(serverName, serviceName);
	}
	std::cout << "connected.\n";
	iRClient->subscribe(connections.iRClient.interval);
	return status;
}
Smart::StatusCode SmartCdlServer::connectLaserClient(const std::string &serverName, const std::string &serviceName) {
	Smart::StatusCode status;
	
	std::cout << "connecting to: " << serverName << "; " << serviceName << std::endl;
	status = laserClient->connect(serverName, serviceName);
	while(status != Smart::SMART_OK)
	{
		ACE_OS::sleep(ACE_Time_Value(0,500000));
		status = COMP->laserClient->connect(serverName, serviceName);
	}
	std::cout << "connected.\n";
	laserClient->subscribe(connections.laserClient.interval);
	return status;
}
Smart::StatusCode SmartCdlServer::connectLaserClient2(const std::string &serverName, const std::string &serviceName) {
	Smart::StatusCode status;
	
	if(connections.laserClient2.initialConnect == false) {
		return Smart::SMART_OK;
	}
	std::cout << "connecting to: " << serverName << "; " << serviceName << std::endl;
	status = laserClient2->connect(serverName, serviceName);
	while(status != Smart::SMART_OK)
	{
		ACE_OS::sleep(ACE_Time_Value(0,500000));
		status = COMP->laserClient2->connect(serverName, serviceName);
	}
	std::cout << "connected.\n";
	laserClient2->subscribe(connections.laserClient2.interval);
	return status;
}
Smart::StatusCode SmartCdlServer::connectNavVelSendClient(const std::string &serverName, const std::string &serviceName) {
	Smart::StatusCode status;
	
	if(connections.navVelSendClient.initialConnect == false) {
		return Smart::SMART_OK;
	}
	std::cout << "connecting to: " << serverName << "; " << serviceName << std::endl;
	status = navVelSendClient->connect(serverName, serviceName);
	while(status != Smart::SMART_OK)
	{
		ACE_OS::sleep(ACE_Time_Value(0,500000));
		status = COMP->navVelSendClient->connect(serverName, serviceName);
	}
	std::cout << "connected.\n";
	return status;
}
Smart::StatusCode SmartCdlServer::connectPathNavigationGoalClient(const std::string &serverName, const std::string &serviceName) {
	Smart::StatusCode status;
	
	if(connections.pathNavigationGoalClient.initialConnect == false) {
		return Smart::SMART_OK;
	}
	std::cout << "connecting to: " << serverName << "; " << serviceName << std::endl;
	status = pathNavigationGoalClient->connect(serverName, serviceName);
	while(status != Smart::SMART_OK)
	{
		ACE_OS::sleep(ACE_Time_Value(0,500000));
		status = COMP->pathNavigationGoalClient->connect(serverName, serviceName);
	}
	std::cout << "connected.\n";
	pathNavigationGoalClient->subscribe(connections.pathNavigationGoalClient.interval);
	return status;
}
Smart::StatusCode SmartCdlServer::connectPlannerClient(const std::string &serverName, const std::string &serviceName) {
	Smart::StatusCode status;
	
	if(connections.plannerClient.initialConnect == false) {
		return Smart::SMART_OK;
	}
	std::cout << "connecting to: " << serverName << "; " << serviceName << std::endl;
	status = plannerClient->connect(serverName, serviceName);
	while(status != Smart::SMART_OK)
	{
		ACE_OS::sleep(ACE_Time_Value(0,500000));
		status = COMP->plannerClient->connect(serverName, serviceName);
	}
	std::cout << "connected.\n";
	plannerClient->subscribe(connections.plannerClient.interval);
	return status;
}
Smart::StatusCode SmartCdlServer::connectTrackingClient(const std::string &serverName, const std::string &serviceName) {
	Smart::StatusCode status;
	
	if(connections.trackingClient.initialConnect == false) {
		return Smart::SMART_OK;
	}
	std::cout << "connecting to: " << serverName << "; " << serviceName << std::endl;
	status = trackingClient->connect(serverName, serviceName);
	while(status != Smart::SMART_OK)
	{
		ACE_OS::sleep(ACE_Time_Value(0,500000));
		status = COMP->trackingClient->connect(serverName, serviceName);
	}
	std::cout << "connected.\n";
	trackingClient->subscribe(connections.trackingClient.interval);
	return status;
}


/**
 * First connect ALL client ports contained in this component, then start all services:
 * activate state, push, etc...
 */
Smart::StatusCode SmartCdlServer::connectAndStartAllServices() {
	Smart::StatusCode status = Smart::SMART_OK;
	
	status = connectBaseStateClient(connections.baseStateClient.serverName, connections.baseStateClient.serviceName);
	if(status != Smart::SMART_OK) return status;
	status = connectIRClient(connections.iRClient.serverName, connections.iRClient.serviceName);
	if(status != Smart::SMART_OK) return status;
	status = connectLaserClient(connections.laserClient.serverName, connections.laserClient.serviceName);
	if(status != Smart::SMART_OK) return status;
	status = connectLaserClient2(connections.laserClient2.serverName, connections.laserClient2.serviceName);
	if(status != Smart::SMART_OK) return status;
	status = connectNavVelSendClient(connections.navVelSendClient.serverName, connections.navVelSendClient.serviceName);
	if(status != Smart::SMART_OK) return status;
	status = connectPathNavigationGoalClient(connections.pathNavigationGoalClient.serverName, connections.pathNavigationGoalClient.serviceName);
	if(status != Smart::SMART_OK) return status;
	status = connectPlannerClient(connections.plannerClient.serverName, connections.plannerClient.serviceName);
	if(status != Smart::SMART_OK) return status;
	status = connectTrackingClient(connections.trackingClient.serverName, connections.trackingClient.serviceName);
	if(status != Smart::SMART_OK) return status;
	
	return status;
}

/**
 * Start all tasks contained in this component.
 */
void SmartCdlServer::startAllTasks() {
	// start task CdlTask
	if(connections.cdlTask.scheduler != "DEFAULT") {
		ACE_Sched_Params cdlTask_SchedParams(ACE_SCHED_OTHER, ACE_THR_PRI_OTHER_DEF);
		if(connections.cdlTask.scheduler == "FIFO") {
			cdlTask_SchedParams.policy(ACE_SCHED_FIFO);
			cdlTask_SchedParams.priority(ACE_THR_PRI_FIFO_MIN);
		} else if(connections.cdlTask.scheduler == "RR") {
			cdlTask_SchedParams.policy(ACE_SCHED_RR);
			cdlTask_SchedParams.priority(ACE_THR_PRI_RR_MIN);
		}
		cdlTask->start(cdlTask_SchedParams, connections.cdlTask.cpuAffinity);
	} else {
		cdlTask->start();
	}
}

/**
 * Start all timers contained in this component
 */
void SmartCdlServer::startAllTimers() {
}


Smart::TaskTriggerSubject* SmartCdlServer::getInputTaskTriggerFromString(const std::string &client)
{
	if(client == "BaseStateClient") return baseStateClientInputTaskTrigger;
	if(client == "IRClient") return iRClientInputTaskTrigger;
	if(client == "LaserClient") return laserClientInputTaskTrigger;
	if(client == "LaserClient2") return laserClient2InputTaskTrigger;
	if(client == "NavVelSendServer") return navVelSendServerInputTaskTrigger;
	if(client == "PathNavigationGoalClient") return pathNavigationGoalClientInputTaskTrigger;
	if(client == "PlannerClient") return plannerClientInputTaskTrigger;
	if(client == "TrackingClient") return trackingClientInputTaskTrigger;
	
	return NULL;
}


void SmartCdlServer::init(int argc, char *argv[])
{
	try {
		Smart::StatusCode status;
		
		// load initial parameters from ini-file (if found)
		loadParameter(argc, argv);
		
		// print out the actual parameters which are used to initialize the component
		std::cout << " \nComponentDefinition Initial-Parameters:\n" << COMP->getGlobalState() << std::endl;
		if(connections.component.defaultScheduler != "DEFAULT") {
			ACE_Sched_Params sched_params(ACE_SCHED_OTHER, ACE_THR_PRI_OTHER_DEF);
			if(connections.component.defaultScheduler == "FIFO") {
				sched_params.policy(ACE_SCHED_FIFO);
				sched_params.priority(ACE_THR_PRI_FIFO_MIN);
			} else if(connections.component.defaultScheduler == "RR") {
				sched_params.policy(ACE_SCHED_RR);
				sched_params.priority(ACE_THR_PRI_RR_MIN);
			}
			// create new instance of the SmartSoft component with customized scheuling parameters 
			component = new SmartCdlServerImpl(connections.component.name, argc, argv, sched_params);
		} else {
			// create new instance of the SmartSoft component
			component = new SmartCdlServerImpl(connections.component.name, argc, argv);
		}
		
		
		std::cout << "ComponentDefinition SmartCdlServer is named " << connections.component.name << std::endl;
		
		if(connections.component.useLogger == true) {
			//FIXME: use logging
			//Smart::LOGGER->openLogFileInFolder("data/"+connections.component.name);
			//Smart::LOGGER->startLogging();
		}

		// create event-test handlers (if needed)
		goalEventServerEventTestHandler = new GoalEventServerEventTestHandler();
		robotBlockedEventServerEventTestHandler = new RobotBlockedEventServerEventTestHandler();
		
		// create server ports
		// TODO: set minCycleTime from Ini-file
		goalEventServer = new SmartACE::EventServer<CommNavigationObjects::CommCdlGoalEventParameter, CommNavigationObjects::CommCdlGoalEventResult, CommNavigationObjects::CdlGoalEventState>(component, connections.goalEventServer.serviceName, goalEventServerEventTestHandler);
		navVelSendServer = new SmartACE::SendServer<CommBasicObjects::CommNavigationVelocity>(component, connections.navVelSendServer.serviceName);
		robotBlockedEventServer = new SmartACE::EventServer<CommNavigationObjects::CommCdlRobotBlockedEventParameter, CommNavigationObjects::CommCdlRobotBlockedEventResult, CommNavigationObjects::CommCdlRobotBlockedState>(component, connections.robotBlockedEventServer.serviceName, robotBlockedEventServerEventTestHandler);
		
		// create client ports
		baseStateClient = new SmartACE::PushClient<CommBasicObjects::CommBaseState>(component);
		iRClient = new SmartACE::PushClient<CommBasicObjects::CommMobileIRScan>(component);
		laserClient = new SmartACE::PushClient<CommBasicObjects::CommMobileLaserScan>(component);
		laserClient2 = new SmartACE::PushClient<CommBasicObjects::CommMobileLaserScan>(component);
		navVelSendClient = new SmartACE::SendClient<CommBasicObjects::CommNavigationVelocity>(component);
		pathNavigationGoalClient = new SmartACE::PushClient<CommRobotinoObjects::CommPathNavigationGoal>(component);
		plannerClient = new SmartACE::PushClient<CommNavigationObjects::CommPlannerGoal>(component);
		trackingClient = new SmartACE::PushClient<CommTrackingObjects::CommTrackingGoal>(component);
		
		// create InputTaskTriggers and UpcallManagers
		baseStateClientInputTaskTrigger = new Smart::InputTaskTrigger<CommBasicObjects::CommBaseState>(baseStateClient);
		baseStateClientUpcallManager = new BaseStateClientUpcallManager(baseStateClient);
		iRClientInputTaskTrigger = new Smart::InputTaskTrigger<CommBasicObjects::CommMobileIRScan>(iRClient);
		iRClientUpcallManager = new IRClientUpcallManager(iRClient);
		laserClientInputTaskTrigger = new Smart::InputTaskTrigger<CommBasicObjects::CommMobileLaserScan>(laserClient);
		laserClientUpcallManager = new LaserClientUpcallManager(laserClient);
		laserClient2InputTaskTrigger = new Smart::InputTaskTrigger<CommBasicObjects::CommMobileLaserScan>(laserClient2);
		laserClient2UpcallManager = new LaserClient2UpcallManager(laserClient2);
		navVelSendServerInputTaskTrigger = new Smart::InputTaskTrigger<CommBasicObjects::CommNavigationVelocity>(navVelSendServer);
		navVelSendServerUpcallManager = new NavVelSendServerUpcallManager(navVelSendServer);
		pathNavigationGoalClientInputTaskTrigger = new Smart::InputTaskTrigger<CommRobotinoObjects::CommPathNavigationGoal>(pathNavigationGoalClient);
		pathNavigationGoalClientUpcallManager = new PathNavigationGoalClientUpcallManager(pathNavigationGoalClient);
		plannerClientInputTaskTrigger = new Smart::InputTaskTrigger<CommNavigationObjects::CommPlannerGoal>(plannerClient);
		plannerClientUpcallManager = new PlannerClientUpcallManager(plannerClient);
		trackingClientInputTaskTrigger = new Smart::InputTaskTrigger<CommTrackingObjects::CommTrackingGoal>(trackingClient);
		trackingClientUpcallManager = new TrackingClientUpcallManager(trackingClient);
		
		// create input-handler
		
		// create request-handlers
		
		// create state pattern
		stateChangeHandler = new SmartStateChangeHandler();
		stateSlave = new SmartACE::StateSlave(component, stateChangeHandler);
		if (stateSlave->defineStates("MoveRobot" ,"moveRobot") != Smart::SMART_OK) std::cerr << "ERROR: defining state combinaion MoveRobot.moveRobot" << std::endl;
		if (stateSlave->setUpInitialState(connections.component.initialMainState) != Smart::SMART_OK) std::cerr << "ERROR: setUpInitialState" << std::endl;
		// activate state slave
		status = stateSlave->activate();
		if(status != Smart::SMART_OK) std::cerr << "ERROR: activate state" << std::endl;
		
		wiringSlave = new SmartACE::WiringSlave(component);
		// add client port to wiring slave
		dynamic_cast<SmartACE::PushClient<CommBasicObjects::CommBaseState>*>(baseStateClient)->add(wiringSlave, connections.baseStateClient.wiringName);
		dynamic_cast<SmartACE::PushClient<CommBasicObjects::CommMobileIRScan>*>(iRClient)->add(wiringSlave, connections.iRClient.wiringName);
		dynamic_cast<SmartACE::PushClient<CommBasicObjects::CommMobileLaserScan>*>(laserClient)->add(wiringSlave, connections.laserClient.wiringName);
		dynamic_cast<SmartACE::PushClient<CommBasicObjects::CommMobileLaserScan>*>(laserClient2)->add(wiringSlave, connections.laserClient2.wiringName);
		dynamic_cast<SmartACE::SendClient<CommBasicObjects::CommNavigationVelocity>*>(navVelSendClient)->add(wiringSlave, connections.navVelSendClient.wiringName);
		dynamic_cast<SmartACE::PushClient<CommRobotinoObjects::CommPathNavigationGoal>*>(pathNavigationGoalClient)->add(wiringSlave, connections.pathNavigationGoalClient.wiringName);
		dynamic_cast<SmartACE::PushClient<CommNavigationObjects::CommPlannerGoal>*>(plannerClient)->add(wiringSlave, connections.plannerClient.wiringName);
		dynamic_cast<SmartACE::PushClient<CommTrackingObjects::CommTrackingGoal>*>(trackingClient)->add(wiringSlave, connections.trackingClient.wiringName);
		
		// create parameter slave
		param = new SmartACE::ParameterSlave(component, &paramHandler);
		
		
		// create Task CdlTask
		cdlTask = new CdlTask(component);
		// configure input-links
		baseStateClientUpcallManager->attach(cdlTask);
		iRClientUpcallManager->attach(cdlTask);
		laserClientUpcallManager->attach(cdlTask);
		laserClient2UpcallManager->attach(cdlTask);
		navVelSendServerUpcallManager->attach(cdlTask);
		pathNavigationGoalClientUpcallManager->attach(cdlTask);
		plannerClientUpcallManager->attach(cdlTask);
		trackingClientUpcallManager->attach(cdlTask);
		// configure task-trigger (if task is configurable)
		if(connections.cdlTask.trigger == "PeriodicTimer") {
			// create PeriodicTimerTrigger
			int microseconds = 1000*1000 / connections.cdlTask.periodicActFreq;
			if(microseconds > 0) {
				Smart::TimedTaskTrigger *triggerPtr = new Smart::TimedTaskTrigger();
				triggerPtr->attach(cdlTask);
				component->getTimerManager()->scheduleTimer(triggerPtr, std::chrono::microseconds(microseconds), std::chrono::microseconds(microseconds));
				// store trigger in class member
				cdlTaskTrigger = triggerPtr;
			} else {
				std::cerr << "ERROR: could not set-up Timer with cycle-time " << microseconds << " as activation source for Task CdlTask" << std::endl;
			}
		} else if(connections.cdlTask.trigger == "DataTriggered") {
			cdlTaskTrigger = getInputTaskTriggerFromString(connections.cdlTask.inPortRef);
			if(cdlTaskTrigger != NULL) {
				cdlTaskTrigger->attach(cdlTask, connections.cdlTask.prescale);
			} else {
				std::cerr << "ERROR: could not set-up InPort " << connections.cdlTask.inPortRef << " as activation source for Task CdlTask" << std::endl;
			}
		} else
		{
			// setup default task-trigger as PeriodicTimer
			Smart::TimedTaskTrigger *triggerPtr = new Smart::TimedTaskTrigger();
			int microseconds = 1000*1000 / 20.0;
			if(microseconds > 0) {
				component->getTimerManager()->scheduleTimer(triggerPtr, std::chrono::microseconds(microseconds), std::chrono::microseconds(microseconds));
				triggerPtr->attach(cdlTask);
				// store trigger in class member
				cdlTaskTrigger = triggerPtr;
			} else {
				std::cerr << "ERROR: could not set-up Timer with cycle-time " << microseconds << " as activation source for Task CdlTask" << std::endl;
			}
		}
		
		
		// link observers with subjects
	} catch (const std::exception &ex) {
		std::cerr << "Uncaught std exception" << ex.what() << std::endl;
	} catch (...) {
		std::cerr << "Uncaught exception" << std::endl;
	}
}

// run the component
void SmartCdlServer::run()
{
	compHandler.onStartup();
	
	// coponent will now start running and will continue (block in the run method) until it is commanded to shutdown (i.e. by a SIGINT signal)
	component->run();
	// component was signalled to shutdown
	// 1) signall all tasks to shutdown as well (and give them 2 seconds time to cooperate)
	// if time exceeds, component is killed without further clean-up
	component->closeAllAssociatedTasks(2);
	
	if(connections.component.useLogger == true) {
		//FIXME: use logging
		//Smart::LOGGER->stopLogging();
	}
	
	compHandler.onShutdown();
	
	// unlink all observers
	
	// destroy all task instances
	// unlink all UpcallManagers
	baseStateClientUpcallManager->detach(cdlTask);
	iRClientUpcallManager->detach(cdlTask);
	laserClientUpcallManager->detach(cdlTask);
	laserClient2UpcallManager->detach(cdlTask);
	navVelSendServerUpcallManager->detach(cdlTask);
	pathNavigationGoalClientUpcallManager->detach(cdlTask);
	plannerClientUpcallManager->detach(cdlTask);
	trackingClientUpcallManager->detach(cdlTask);
	// unlink the TaskTrigger
	cdlTaskTrigger->detach(cdlTask);
	delete cdlTask;

	// destroy all input-handler

	// destroy InputTaskTriggers and UpcallManagers
	delete baseStateClientInputTaskTrigger;
	delete baseStateClientUpcallManager;
	delete iRClientInputTaskTrigger;
	delete iRClientUpcallManager;
	delete laserClientInputTaskTrigger;
	delete laserClientUpcallManager;
	delete laserClient2InputTaskTrigger;
	delete laserClient2UpcallManager;
	delete navVelSendServerInputTaskTrigger;
	delete navVelSendServerUpcallManager;
	delete pathNavigationGoalClientInputTaskTrigger;
	delete pathNavigationGoalClientUpcallManager;
	delete plannerClientInputTaskTrigger;
	delete plannerClientUpcallManager;
	delete trackingClientInputTaskTrigger;
	delete trackingClientUpcallManager;

	// destroy client ports
	delete baseStateClient;
	delete iRClient;
	delete laserClient;
	delete laserClient2;
	delete navVelSendClient;
	delete pathNavigationGoalClient;
	delete plannerClient;
	delete trackingClient;

	// destroy server ports
	delete goalEventServer;
	delete navVelSendServer;
	delete robotBlockedEventServer;
	// destroy event-test handlers (if needed)
	delete goalEventServerEventTestHandler;
	delete robotBlockedEventServerEventTestHandler;
	
	// create request-handlers

	delete stateSlave;
	// delete state-change-handler
	delete stateChangeHandler;
	
	// delete all master/slave ports
	delete wiringSlave;
	delete param;
	

	// clean-up component's internally used resources (internally used communication middleware) 
	component->cleanUpComponentResources();
	
	// finally delete the component itself
	delete component;
}

void SmartCdlServer::loadParameter(int argc, char *argv[])
{
	/*
	 Parameters can be specified via command line --filename=<filename> or -f <filename>

	 With this parameter present:
	   - The component will look for the file in the current working directory,
	     a path relative to the current directory or any absolute path
	   - The component will use the default values if the file cannot be found

	 With this parameter absent:
	   - <Name of Component>.ini will be read from current working directory, if found there
	   - $SMART_ROOT/etc/<Name of Component>.ini will be read otherwise
	   - Default values will be used if neither found in working directory or /etc
	 */
	SmartACE::SmartIniParameter parameter;
	std::ifstream parameterfile;
	bool parameterFileFound = false;

	// load parameters
	try
	{
		// if paramfile is given as argument
		if(parameter.tryAddFileFromArgs(argc,argv,"filename", 'f'))
		{
			parameterFileFound = true;
			std::cout << "parameter file is loaded from an argv argument \n";
		} else if(parameter.searchFile("SmartCdlServer.ini", parameterfile)) {
			parameterFileFound = true;
			std::cout << "load SmartCdlServer.ini parameter file\n";
			parameter.addFile(parameterfile);
		} else {
			std::cout << "WARNING: SmartCdlServer.ini parameter file not found! (using default values or command line arguments)\n";
		}
		
		// add command line arguments to allow overwriting of parameters
		// from file
		parameter.addCommandLineArgs(argc,argv,"component");
		
		// initialize the naming service using the command line parameters parsed in the
		// SmartIniParameter class. The naming service parameters are expected to be in
		// the "component" parameter group.
		SmartACE::NAMING::instance()->checkForHelpArg(argc,argv);
		if(parameterFileFound) 
		{
			if(SmartACE::NAMING::instance()->init(parameter.getAllParametersFromGroup("component")) != 0) {
				// initialization of naming service failed
				throw std::logic_error( "<NamingService> Service initialization failed!\nPossible causes could be:\n-> Erroneous configuration.\n-> Naming service not reachable.\n" );
			}
		} else {
			if(SmartACE::NAMING::instance()->init(argc, argv) != 0) {
				// initialization of naming service failed
				throw std::logic_error( "<NamingService> Service initialization failed!\nPossible causes could be:\n-> Erroneous configuration.\n-> Naming service not reachable.\n" );
			}
		}
			
		// print all known parameters
		// parameter.print();
		
		//--- server port // client port // other parameter ---
		// load parameter
		parameter.getString("component", "name", connections.component.name);
		parameter.getString("component", "initialMainState", connections.component.initialMainState);
		if(parameter.checkIfParameterExists("component", "defaultScheduler")) {
			parameter.getString("component", "defaultScheduler", connections.component.defaultScheduler);
		}
		if(parameter.checkIfParameterExists("component", "useLogger")) {
			parameter.getBoolean("component", "useLogger", connections.component.useLogger);
		}
		
		// load parameters for client BaseStateClient
		parameter.getBoolean("baseStateClient", "initialConnect", connections.baseStateClient.initialConnect);
		parameter.getString("baseStateClient", "serviceName", connections.baseStateClient.serviceName);
		parameter.getString("baseStateClient", "serverName", connections.baseStateClient.serverName);
		parameter.getString("baseStateClient", "wiringName", connections.baseStateClient.wiringName);
		parameter.getInteger("baseStateClient", "interval", connections.baseStateClient.interval);
		// load parameters for client IRClient
		parameter.getBoolean("iRClient", "initialConnect", connections.iRClient.initialConnect);
		parameter.getString("iRClient", "serviceName", connections.iRClient.serviceName);
		parameter.getString("iRClient", "serverName", connections.iRClient.serverName);
		parameter.getString("iRClient", "wiringName", connections.iRClient.wiringName);
		parameter.getInteger("iRClient", "interval", connections.iRClient.interval);
		// load parameters for client LaserClient
		parameter.getString("laserClient", "serviceName", connections.laserClient.serviceName);
		parameter.getString("laserClient", "serverName", connections.laserClient.serverName);
		parameter.getString("laserClient", "wiringName", connections.laserClient.wiringName);
		parameter.getInteger("laserClient", "interval", connections.laserClient.interval);
		// load parameters for client LaserClient2
		parameter.getBoolean("laserClient2", "initialConnect", connections.laserClient2.initialConnect);
		parameter.getString("laserClient2", "serviceName", connections.laserClient2.serviceName);
		parameter.getString("laserClient2", "serverName", connections.laserClient2.serverName);
		parameter.getString("laserClient2", "wiringName", connections.laserClient2.wiringName);
		parameter.getInteger("laserClient2", "interval", connections.laserClient2.interval);
		// load parameters for client NavVelSendClient
		parameter.getBoolean("navVelSendClient", "initialConnect", connections.navVelSendClient.initialConnect);
		parameter.getString("navVelSendClient", "serviceName", connections.navVelSendClient.serviceName);
		parameter.getString("navVelSendClient", "serverName", connections.navVelSendClient.serverName);
		parameter.getString("navVelSendClient", "wiringName", connections.navVelSendClient.wiringName);
		// load parameters for client PathNavigationGoalClient
		parameter.getBoolean("pathNavigationGoalClient", "initialConnect", connections.pathNavigationGoalClient.initialConnect);
		parameter.getString("pathNavigationGoalClient", "serviceName", connections.pathNavigationGoalClient.serviceName);
		parameter.getString("pathNavigationGoalClient", "serverName", connections.pathNavigationGoalClient.serverName);
		parameter.getString("pathNavigationGoalClient", "wiringName", connections.pathNavigationGoalClient.wiringName);
		parameter.getInteger("pathNavigationGoalClient", "interval", connections.pathNavigationGoalClient.interval);
		// load parameters for client PlannerClient
		parameter.getBoolean("plannerClient", "initialConnect", connections.plannerClient.initialConnect);
		parameter.getString("plannerClient", "serviceName", connections.plannerClient.serviceName);
		parameter.getString("plannerClient", "serverName", connections.plannerClient.serverName);
		parameter.getString("plannerClient", "wiringName", connections.plannerClient.wiringName);
		parameter.getInteger("plannerClient", "interval", connections.plannerClient.interval);
		// load parameters for client TrackingClient
		parameter.getBoolean("trackingClient", "initialConnect", connections.trackingClient.initialConnect);
		parameter.getString("trackingClient", "serviceName", connections.trackingClient.serviceName);
		parameter.getString("trackingClient", "serverName", connections.trackingClient.serverName);
		parameter.getString("trackingClient", "wiringName", connections.trackingClient.wiringName);
		parameter.getInteger("trackingClient", "interval", connections.trackingClient.interval);
		
		// load parameters for server GoalEventServer
		parameter.getString("goalEventServer", "serviceName", connections.goalEventServer.serviceName);
		// load parameters for server NavVelSendServer
		parameter.getString("navVelSendServer", "serviceName", connections.navVelSendServer.serviceName);
		// load parameters for server RobotBlockedEventServer
		parameter.getString("robotBlockedEventServer", "serviceName", connections.robotBlockedEventServer.serviceName);
		
		// load parameters for task CdlTask
		parameter.getDouble("CdlTask", "minActFreqHz", connections.cdlTask.minActFreq);
		parameter.getDouble("CdlTask", "maxActFreqHz", connections.cdlTask.maxActFreq);
		parameter.getString("CdlTask", "triggerType", connections.cdlTask.trigger);
		if(connections.cdlTask.trigger == "PeriodicTimer") {
			parameter.getDouble("CdlTask", "periodicActFreqHz", connections.cdlTask.periodicActFreq);
		} else if(connections.cdlTask.trigger == "DataTriggered") {
			parameter.getString("CdlTask", "inPortRef", connections.cdlTask.inPortRef);
			parameter.getInteger("CdlTask", "prescale", connections.cdlTask.prescale);
		}
		if(parameter.checkIfParameterExists("CdlTask", "scheduler")) {
			parameter.getString("CdlTask", "scheduler", connections.cdlTask.scheduler);
		}
		if(parameter.checkIfParameterExists("CdlTask", "priority")) {
			parameter.getInteger("CdlTask", "priority", connections.cdlTask.priority);
		}
		if(parameter.checkIfParameterExists("CdlTask", "cpuAffinity")) {
			parameter.getInteger("CdlTask", "cpuAffinity", connections.cdlTask.cpuAffinity);
		}
		
		paramHandler.loadParameter(parameter);
	
	} catch (const SmartACE::IniParameterError & e) {
		std::cerr << e.what() << std::endl;
	} catch (const std::exception &ex) {
		std::cerr << "Uncaught std::exception: " << ex.what() << std::endl;
	} catch (...) {
		std::cerr << "Uncaught exception" << std::endl;
	}
}