/*----- PROTECTED REGION ID(DeviceMemLeak.h) ENABLED START -----*/
//=============================================================================
//
// file :        DeviceMemLeak.h
//
// description : Include file for the DeviceMemLeak class
//
// project :     DeviceMemLeak
//
// This file is part of Tango device class.
// 
// Tango is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// Tango is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with Tango.  If not, see <http://www.gnu.org/licenses/>.
// 
//
//
//=============================================================================
//                This file is generated by POGO
//        (Program Obviously used to Generate tango Object)
//=============================================================================


#ifndef DeviceMemLeak_H
#define DeviceMemLeak_H

#include <tango.h>
#include <thread>


/*----- PROTECTED REGION END -----*/	//	DeviceMemLeak.h

/**
 *  DeviceMemLeak class description:
 *    Device class to tests TangoTickets#30
 */

namespace DeviceMemLeak_ns
{
/*----- PROTECTED REGION ID(DeviceMemLeak::Additional Class Declarations) ENABLED START -----*/

//	Additional Class Declarations

/*----- PROTECTED REGION END -----*/	//	DeviceMemLeak::Additional Class Declarations

class DeviceMemLeak : public TANGO_BASE_CLASS
{

/*----- PROTECTED REGION ID(DeviceMemLeak::Data Members) ENABLED START -----*/

//	Add your own data members
private:
	std::thread * push_thread;
	bool stop_requested;

/*----- PROTECTED REGION END -----*/	//	DeviceMemLeak::Data Members

//	Device property data members
public:
	//	ThreadSleepTimeMs:	
	Tango::DevShort	threadSleepTimeMs;

//	Attribute data members
public:
	Tango::DevEncoded	*attr_attr1_read;

//	Constructors and destructors
public:
	/**
	 * Constructs a newly device object.
	 *
	 *	@param cl	Class.
	 *	@param s 	Device Name
	 */
	DeviceMemLeak(Tango::DeviceClass *cl,string &s);
	/**
	 * Constructs a newly device object.
	 *
	 *	@param cl	Class.
	 *	@param s 	Device Name
	 */
	DeviceMemLeak(Tango::DeviceClass *cl,const char *s);
	/**
	 * Constructs a newly device object.
	 *
	 *	@param cl	Class.
	 *	@param s 	Device name
	 *	@param d	Device description.
	 */
	DeviceMemLeak(Tango::DeviceClass *cl,const char *s,const char *d);
	/**
	 * The device object destructor.
	 */
	~DeviceMemLeak() {delete_device();};


//	Miscellaneous methods
public:
	/*
	 *	will be called at device destruction or at init command.
	 */
	void delete_device();
	/*
	 *	Initialize the device
	 */
	virtual void init_device();
	/*
	 *	Read the device properties from database
	 */
	void get_device_property();
	/*
	 *	Always executed method before execution command method.
	 */
	virtual void always_executed_hook();


//	Attribute methods
public:
	//--------------------------------------------------------
	/*
	 *	Method      : DeviceMemLeak::read_attr_hardware()
	 *	Description : Hardware acquisition for attributes.
	 */
	//--------------------------------------------------------
	virtual void read_attr_hardware(vector<long> &attr_list);

/**
 *	Attribute attr1 related methods
 *	Description: 
 *
 *	Data type:	Tango::DevEncoded
 *	Attr type:	Scalar
 */
	virtual void read_attr1(Tango::Attribute &attr);
	virtual bool is_attr1_allowed(Tango::AttReqType type);


	//--------------------------------------------------------
	/**
	 *	Method      : DeviceMemLeak::add_dynamic_attributes()
	 *	Description : Add dynamic attributes if any.
	 */
	//--------------------------------------------------------
	void add_dynamic_attributes();




//	Command related methods
public:
	/**
	 *	Command Start related method
	 *	Description: 
	 *
	 */
	virtual void start();
	virtual bool is_Start_allowed(const CORBA::Any &any);
	/**
	 *	Command Stop related method
	 *	Description: 
	 *
	 */
	virtual void stop();
	virtual bool is_Stop_allowed(const CORBA::Any &any);
	/**
	 *	Command PushEncodedEvent related method
	 *	Description: 
	 *
	 */
	virtual void push_encoded_event();
	virtual bool is_PushEncodedEvent_allowed(const CORBA::Any &any);


	//--------------------------------------------------------
	/**
	 *	Method      : DeviceMemLeak::add_dynamic_commands()
	 *	Description : Add dynamic commands if any.
	 */
	//--------------------------------------------------------
	void add_dynamic_commands();

/*----- PROTECTED REGION ID(DeviceMemLeak::Additional Method prototypes) ENABLED START -----*/

//	Additional Method prototypes
	void push_thread_execution();

/*----- PROTECTED REGION END -----*/	//	DeviceMemLeak::Additional Method prototypes
};

/*----- PROTECTED REGION ID(DeviceMemLeak::Additional Classes Definitions) ENABLED START -----*/

//	Additional Classes Definitions

/*----- PROTECTED REGION END -----*/	//	DeviceMemLeak::Additional Classes Definitions

}	//	End of namespace

#endif   //	DeviceMemLeak_H