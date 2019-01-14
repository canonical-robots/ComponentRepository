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
#include "SmartJoystickNavigation.hh"
#include "smartTimedTaskTrigger.h"
//FIXME: implement logging
//#include "smartGlobalLogger.hh"

// the ace port-factory is used as a default port-mapping
#include "SmartJoystickNavigationAcePortFactory.hh"


// initialize static singleton pointer to zero
SmartJoystickNavigation* SmartJoystickNavigation::_smartJoystickNavigation = 0;

// constructor
SmartJoystickNavigation::SmartJoystickNavigation()
{
	std::cout << "constructor of SmartJoystickNavigation\n";
	
	// set all pointer members to NULL
	//coordinationPort = NULL;
	joystickNavTask = NULL;
	joystickNavTaskTrigger = NULL;
	joystickServiceIn = NULL;
	joystickServiceInInputTaskTrigger = NULL;
	joystickServiceInUpcallManager = NULL;
	navVelServiceOut = NULL;
	//smartJoystickNavigationParameters = NULL;
	stateChangeHandler = NULL;
	stateSlave = NULL;
	wiringSlave = NULL;
	param = NULL;
	
	// set default ini parameter values
	connections.component.name = "SmartJoystickNavigation";
	connections.component.initialComponentMode = "Neutral";
	connections.component.defaultScheduler = "DEFAULT";
	connections.component.useLogger = false;
	
	connections.joystickServiceIn.wiringName = "JoystickServiceIn";
	connections.joystickServiceIn.serverName = "unknown";
	connections.joystickServiceIn.serviceName = "unknown";
	connections.joystickServiceIn.interval = 1;
	connections.joystickServiceIn.roboticMiddleware = "ACE_SmartSoft";
	connections.navVelServiceOut.initialConnect = false;
	connections.navVelServiceOut.wiringName = "NavVelServiceOut";
	connections.navVelServiceOut.serverName = "unknown";
	connections.navVelServiceOut.serviceName = "unknown";
	connections.navVelServiceOut.interval = 1;
	connections.navVelServiceOut.roboticMiddleware = "ACE_SmartSoft";
	connections.joystickNavTask.minActFreq = 0.0;
	connections.joystickNavTask.maxActFreq = 0.0;
	connections.joystickNavTask.trigger = "DataTriggered";
	connections.joystickNavTask.inPortRef = "JoystickServiceIn";	
	connections.joystickNavTask.prescale = 1;
	// scheduling default parameters
	connections.joystickNavTask.scheduler = "DEFAULT";
	connections.joystickNavTask.priority = -1;
	connections.joystickNavTask.cpuAffinity = -1;
	
	// initialize members of PlainOpcUaSmartJoystickNavigationExtension
	
}

void SmartJoystickNavigation::addPortFactory(const std::string &name, SmartJoystickNavigationPortFactoryInterface *portFactory)
{
	portFactoryRegistry[name] = portFactory;
}

void SmartJoystickNavigation::addExtension(SmartJoystickNavigationExtension *extension)
{
	componentExtensionRegistry[extension->getName()] = extension;
}

/**
 * Notify the component that setup/initialization is finished.
 * You may call this function from anywhere in the component.
 *
 * Set component's internal lifecycle state automaton (if any) into 
 * Alive mode (from here on the component is ready to provide its services)
 */
void SmartJoystickNavigation::setStartupFinished() {
	stateSlave->setWaitState("Alive");
	std::cout << "ComponentDefinition initialization/startup finished." << std::endl;
}


Smart::StatusCode SmartJoystickNavigation::connectJoystickServiceIn(const std::string &serverName, const std::string &serviceName) {
	Smart::StatusCode status;
	
	std::cout << "connecting to: " << serverName << "; " << serviceName << std::endl;
	status = joystickServiceIn->connect(serverName, serviceName);
	while(status != Smart::SMART_OK)
	{
		ACE_OS::sleep(ACE_Time_Value(0,500000));
		status = COMP->joystickServiceIn->connect(serverName, serviceName);
	}
	std::cout << "connected.\n";
	joystickServiceIn->subscribe(connections.joystickServiceIn.interval);
	return status;
}
Smart::StatusCode SmartJoystickNavigation::connectNavVelServiceOut(const std::string &serverName, const std::string &serviceName) {
	Smart::StatusCode status;
	
	if(connections.navVelServiceOut.initialConnect == false) {
		return Smart::SMART_OK;
	}
	std::cout << "connecting to: " << serverName << "; " << serviceName << std::endl;
	status = navVelServiceOut->connect(serverName, serviceName);
	while(status != Smart::SMART_OK)
	{
		ACE_OS::sleep(ACE_Time_Value(0,500000));
		status = COMP->navVelServiceOut->connect(serverName, serviceName);
	}
	std::cout << "connected.\n";
	return status;
}


/**
 * First connect ALL client ports contained in this component, then start all services:
 * activate state, push, etc...
 */
Smart::StatusCode SmartJoystickNavigation::connectAndStartAllServices() {
	Smart::StatusCode status = Smart::SMART_OK;
	
	status = connectJoystickServiceIn(connections.joystickServiceIn.serverName, connections.joystickServiceIn.serviceName);
	if(status != Smart::SMART_OK) return status;
	status = connectNavVelServiceOut(connections.navVelServiceOut.serverName, connections.navVelServiceOut.serviceName);
	if(status != Smart::SMART_OK) return status;
	return status;
}

/**
 * Start all tasks contained in this component.
 */
void SmartJoystickNavigation::startAllTasks() {
	// start task JoystickNavTask
	if(connections.joystickNavTask.scheduler != "DEFAULT") {
		ACE_Sched_Params joystickNavTask_SchedParams(ACE_SCHED_OTHER, ACE_THR_PRI_OTHER_DEF);
		if(connections.joystickNavTask.scheduler == "FIFO") {
			joystickNavTask_SchedParams.policy(ACE_SCHED_FIFO);
			joystickNavTask_SchedParams.priority(ACE_THR_PRI_FIFO_MIN);
		} else if(connections.joystickNavTask.scheduler == "RR") {
			joystickNavTask_SchedParams.policy(ACE_SCHED_RR);
			joystickNavTask_SchedParams.priority(ACE_THR_PRI_RR_MIN);
		}
		joystickNavTask->start(joystickNavTask_SchedParams, connections.joystickNavTask.cpuAffinity);
	} else {
		joystickNavTask->start();
	}
}

/**
 * Start all timers contained in this component
 */
void SmartJoystickNavigation::startAllTimers() {
}


Smart::TaskTriggerSubject* SmartJoystickNavigation::getInputTaskTriggerFromString(const std::string &client)
{
	if(client == "JoystickServiceIn") return joystickServiceInInputTaskTrigger;
	
	return NULL;
}


void SmartJoystickNavigation::init(int argc, char *argv[])
{
	try {
		Smart::StatusCode status;
		
		// load initial parameters from ini-file (if found)
		loadParameter(argc, argv);
		
		// print out the actual parameters which are used to initialize the component
		std::cout << " \nComponentDefinition Initial-Parameters:\n" << COMP->getGlobalState() << std::endl;
		
		// initializations of PlainOpcUaSmartJoystickNavigationExtension
		
		
		// initialize all registered port-factories
		for(auto portFactory = portFactoryRegistry.begin(); portFactory != portFactoryRegistry.end(); portFactory++) 
		{
			portFactory->second->initialize(this, argc, argv);
		}
		
		// initialize all registered component-extensions
		for(auto extension = componentExtensionRegistry.begin(); extension != componentExtensionRegistry.end(); extension++) 
		{
			extension->second->initialize(this, argc, argv);
		}
		
		SmartJoystickNavigationPortFactoryInterface *acePortFactory = portFactoryRegistry["ACE_SmartSoft"];
		if(acePortFactory == 0) {
			std::cerr << "ERROR: acePortFactory NOT instantiated -> exit(-1)" << std::endl;
			exit(-1);
		}
		
		// this pointer is used for backwards compatibility (deprecated: should be removed as soon as all patterns, including coordination, are moved to port-factory)
		SmartACE::SmartComponent *component = dynamic_cast<SmartJoystickNavigationAcePortFactory*>(acePortFactory)->getComponentImpl();
		
		std::cout << "ComponentDefinition SmartJoystickNavigation is named " << connections.component.name << std::endl;
		
		if(connections.component.useLogger == true) {
			//FIXME: use logging
			//Smart::LOGGER->openLogFileInFolder("data/"+connections.component.name);
			//Smart::LOGGER->startLogging();
		}

		// create event-test handlers (if needed)
		
		// create server ports
		// TODO: set minCycleTime from Ini-file
		
		// create client ports
		joystickServiceIn = portFactoryRegistry[connections.joystickServiceIn.roboticMiddleware]->createJoystickServiceIn();
		navVelServiceOut = portFactoryRegistry[connections.navVelServiceOut.roboticMiddleware]->createNavVelServiceOut();
		
		// create InputTaskTriggers and UpcallManagers
		joystickServiceInInputTaskTrigger = new Smart::InputTaskTrigger<CommBasicObjects::CommJoystick>(joystickServiceIn);
		joystickServiceInUpcallManager = new JoystickServiceInUpcallManager(joystickServiceIn);
		
		// create input-handler
		
		// create request-handlers
		
		// create state pattern
		stateChangeHandler = new SmartStateChangeHandler();
		stateSlave = new SmartACE::StateSlave(component, stateChangeHandler);
		status = stateSlave->setUpInitialState(connections.component.initialComponentMode);
		if (status != Smart::SMART_OK) std::cerr << status << "; failed setting initial ComponentMode: " << connections.component.initialComponentMode << std::endl;
		// activate state slave
		status = stateSlave->activate();
		if(status != Smart::SMART_OK) std::cerr << "ERROR: activate state" << std::endl;
		
		wiringSlave = new SmartACE::WiringSlave(component);
		// add client port to wiring slave
		if(connections.joystickServiceIn.roboticMiddleware == "ACE_SmartSoft") {
			//FIXME: this must also work with other implementations
			dynamic_cast<SmartACE::PushClient<CommBasicObjects::CommJoystick>*>(joystickServiceIn)->add(wiringSlave, connections.joystickServiceIn.wiringName);
		}
		if(connections.navVelServiceOut.roboticMiddleware == "ACE_SmartSoft") {
			//FIXME: this must also work with other implementations
			dynamic_cast<SmartACE::SendClient<CommBasicObjects::CommNavigationVelocity>*>(navVelServiceOut)->add(wiringSlave, connections.navVelServiceOut.wiringName);
		}
		
		// create parameter slave
		param = new SmartACE::ParameterSlave(component, &paramHandler);
		
		
		// create Task JoystickNavTask
		joystickNavTask = new JoystickNavTask(component);
		// configure input-links
		joystickServiceInUpcallManager->attach(joystickNavTask);
		// configure task-trigger (if task is configurable)
		if(connections.joystickNavTask.trigger == "PeriodicTimer") {
			// create PeriodicTimerTrigger
			int microseconds = 1000*1000 / connections.joystickNavTask.periodicActFreq;
			if(microseconds > 0) {
				Smart::TimedTaskTrigger *triggerPtr = new Smart::TimedTaskTrigger();
				triggerPtr->attach(joystickNavTask);
				component->getTimerManager()->scheduleTimer(triggerPtr, std::chrono::microseconds(microseconds), std::chrono::microseconds(microseconds));
				// store trigger in class member
				joystickNavTaskTrigger = triggerPtr;
			} else {
				std::cerr << "ERROR: could not set-up Timer with cycle-time " << microseconds << " as activation source for Task JoystickNavTask" << std::endl;
			}
		} else if(connections.joystickNavTask.trigger == "DataTriggered") {
			joystickNavTaskTrigger = getInputTaskTriggerFromString(connections.joystickNavTask.inPortRef);
			if(joystickNavTaskTrigger != NULL) {
				joystickNavTaskTrigger->attach(joystickNavTask, connections.joystickNavTask.prescale);
			} else {
				std::cerr << "ERROR: could not set-up InPort " << connections.joystickNavTask.inPortRef << " as activation source for Task JoystickNavTask" << std::endl;
			}
		} else
		{
			// setup default task-trigger as InputTrigger
			joystickNavTaskTrigger = getInputTaskTriggerFromString("JoystickServiceIn");
			if(joystickNavTaskTrigger != NULL) {
				joystickNavTaskTrigger->attach(joystickNavTask, connections.joystickNavTask.prescale);
			} else {
				std::cerr << "ERROR: could not set-up InPort JoystickServiceIn as activation source for Task JoystickNavTask" << std::endl;
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
void SmartJoystickNavigation::run()
{
	stateSlave->acquire("init");
	// startup all registered port-factories
	for(auto portFactory = portFactoryRegistry.begin(); portFactory != portFactoryRegistry.end(); portFactory++) 
	{
		portFactory->second->onStartup();
	}
	
	// startup all registered component-extensions
	for(auto extension = componentExtensionRegistry.begin(); extension != componentExtensionRegistry.end(); extension++) 
	{
		extension->second->onStartup();
	}
	stateSlave->release("init");
	
	// do not call this handler within the init state (see above) as this handler internally calls setStartupFinished() (this should be fixed in future)
	compHandler.onStartup();
	
	// this call blocks until the component is commanded to shutdown
	stateSlave->acquire("shutdown");
	
	// shutdown all registered component-extensions
	for(auto extension = componentExtensionRegistry.begin(); extension != componentExtensionRegistry.end(); extension++) 
	{
		extension->second->onShutdown();
	}
	
	// shutdown all registered port-factories
	for(auto portFactory = portFactoryRegistry.begin(); portFactory != portFactoryRegistry.end(); portFactory++) 
	{
		portFactory->second->onShutdown();
	}
	
	if(connections.component.useLogger == true) {
		//FIXME: use logging
		//Smart::LOGGER->stopLogging();
	}
	
	compHandler.onShutdown();
	
	stateSlave->release("shutdown");
}

// clean-up component's resources
void SmartJoystickNavigation::fini()
{
	// unlink all observers
	
	// destroy all task instances
	// unlink all UpcallManagers
	joystickServiceInUpcallManager->detach(joystickNavTask);
	// unlink the TaskTrigger
	joystickNavTaskTrigger->detach(joystickNavTask);
	delete joystickNavTask;

	// destroy all input-handler

	// destroy InputTaskTriggers and UpcallManagers
	delete joystickServiceInInputTaskTrigger;
	delete joystickServiceInUpcallManager;

	// destroy client ports
	delete joystickServiceIn;
	delete navVelServiceOut;

	// destroy server ports
	// destroy event-test handlers (if needed)
	
	// destroy request-handlers
	
	delete stateSlave;
	// destroy state-change-handler
	delete stateChangeHandler;
	
	// destroy all master/slave ports
	delete wiringSlave;
	delete param;
	

	// destroy all registered component-extensions
	for(auto extension = componentExtensionRegistry.begin(); extension != componentExtensionRegistry.end(); extension++) 
	{
		extension->second->destroy();
	}

	// destroy all registered port-factories
	for(auto portFactory = portFactoryRegistry.begin(); portFactory != portFactoryRegistry.end(); portFactory++) 
	{
		portFactory->second->destroy();
	}
	
	// destruction of PlainOpcUaSmartJoystickNavigationExtension
	
}

void SmartJoystickNavigation::loadParameter(int argc, char *argv[])
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
		} else if(parameter.searchFile("SmartJoystickNavigation.ini", parameterfile)) {
			parameterFileFound = true;
			std::cout << "load SmartJoystickNavigation.ini parameter file\n";
			parameter.addFile(parameterfile);
		} else {
			std::cout << "WARNING: SmartJoystickNavigation.ini parameter file not found! (using default values or command line arguments)\n";
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
		parameter.getString("component", "initialComponentMode", connections.component.initialComponentMode);
		if(parameter.checkIfParameterExists("component", "defaultScheduler")) {
			parameter.getString("component", "defaultScheduler", connections.component.defaultScheduler);
		}
		if(parameter.checkIfParameterExists("component", "useLogger")) {
			parameter.getBoolean("component", "useLogger", connections.component.useLogger);
		}
		
		// load parameters for client JoystickServiceIn
		parameter.getString("JoystickServiceIn", "serviceName", connections.joystickServiceIn.serviceName);
		parameter.getString("JoystickServiceIn", "serverName", connections.joystickServiceIn.serverName);
		parameter.getString("JoystickServiceIn", "wiringName", connections.joystickServiceIn.wiringName);
		parameter.getInteger("JoystickServiceIn", "interval", connections.joystickServiceIn.interval);
		if(parameter.checkIfParameterExists("JoystickServiceIn", "roboticMiddleware")) {
			parameter.getString("JoystickServiceIn", "roboticMiddleware", connections.joystickServiceIn.roboticMiddleware);
		}
		// load parameters for client NavVelServiceOut
		parameter.getBoolean("NavVelServiceOut", "initialConnect", connections.navVelServiceOut.initialConnect);
		parameter.getString("NavVelServiceOut", "serviceName", connections.navVelServiceOut.serviceName);
		parameter.getString("NavVelServiceOut", "serverName", connections.navVelServiceOut.serverName);
		parameter.getString("NavVelServiceOut", "wiringName", connections.navVelServiceOut.wiringName);
		if(parameter.checkIfParameterExists("NavVelServiceOut", "roboticMiddleware")) {
			parameter.getString("NavVelServiceOut", "roboticMiddleware", connections.navVelServiceOut.roboticMiddleware);
		}
		
		
		// load parameters for task JoystickNavTask
		parameter.getDouble("JoystickNavTask", "minActFreqHz", connections.joystickNavTask.minActFreq);
		parameter.getDouble("JoystickNavTask", "maxActFreqHz", connections.joystickNavTask.maxActFreq);
		parameter.getString("JoystickNavTask", "triggerType", connections.joystickNavTask.trigger);
		if(connections.joystickNavTask.trigger == "PeriodicTimer") {
			parameter.getDouble("JoystickNavTask", "periodicActFreqHz", connections.joystickNavTask.periodicActFreq);
		} else if(connections.joystickNavTask.trigger == "DataTriggered") {
			parameter.getString("JoystickNavTask", "inPortRef", connections.joystickNavTask.inPortRef);
			parameter.getInteger("JoystickNavTask", "prescale", connections.joystickNavTask.prescale);
		}
		if(parameter.checkIfParameterExists("JoystickNavTask", "scheduler")) {
			parameter.getString("JoystickNavTask", "scheduler", connections.joystickNavTask.scheduler);
		}
		if(parameter.checkIfParameterExists("JoystickNavTask", "priority")) {
			parameter.getInteger("JoystickNavTask", "priority", connections.joystickNavTask.priority);
		}
		if(parameter.checkIfParameterExists("JoystickNavTask", "cpuAffinity")) {
			parameter.getInteger("JoystickNavTask", "cpuAffinity", connections.joystickNavTask.cpuAffinity);
		}
		
		// load parameters for PlainOpcUaSmartJoystickNavigationExtension
		
		
		// load parameters for all registered component-extensions
		for(auto extension = componentExtensionRegistry.begin(); extension != componentExtensionRegistry.end(); extension++) 
		{
			extension->second->loadParameters(parameter);
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
