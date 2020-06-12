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

//--------------------------------------------------------------------------
//BSD 3-Clause License
//
//  Copyright (C) Servicerobotics Ulm
//  University of Applied Sciences Ulm
//  Prittwitzstr. 10
//  89075 Ulm
//  Germany
//  All rights reserved.
//
//  Author: Nayabrasul Shaik
//
//Redistribution and use in source and binary forms, with or without
//modification, are permitted provided that the following conditions are met:
//
//* Redistributions of source code must retain the above copyright notice, this
//  list of conditions and the following disclaimer.
//
//* Redistributions in binary form must reproduce the above copyright notice,
//  this list of conditions and the following disclaimer in the documentation
//  and/or other materials provided with the distribution.
//
//* Neither the name of the copyright holder nor the names of its
//  contributors may be used to endorse or promote products derived from
//  this software without specific prior written permission.
//
//THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
//DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
//FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
//DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
//SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
//CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
//OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
//OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef _CARTOGRAPHERTASK_HH
#define _CARTOGRAPHERTASK_HH
#include "VisualizationHelper.hh"

#include "CartographerTaskCore.hh"
#include "CommBasicObjects/CommMobileLaserScan.hh"

#include <memory>
#include <chrono>
#include <unordered_map>
#include "cartographer/mapping/map_builder_interface.h"
#include "cartographer/mapping/proto/map_builder_options.pb.h"
#include "cartographer/mapping/map_builder.h"
#include "cartographer/transform/rigid_transform.h"
#include "cartographer/io/submap_painter.h"
//#include "eigen3/Eigen/Core"

using Rigid3d    = cartographer::transform::Rigid3d;
using SensorId   = cartographer::mapping::TrajectoryBuilderInterface::SensorId;
using SensorType = SensorId::SensorType;
using RangeData  = cartographer::sensor::RangeData;
using MapBuilderOptions = cartographer::mapping::proto::MapBuilderOptions;
using MapBuilder = cartographer::mapping::MapBuilder;
using MapBuilderInterface = cartographer::mapping::MapBuilderInterface;
using TrajectoryBuilderOptions = cartographer::mapping::proto::TrajectoryBuilderOptions;
using TrajectoryBuilderInterface = cartographer::mapping::TrajectoryBuilderInterface;
using Time = cartographer::common::Time;
using RangeData = cartographer::sensor::RangeData;
using CGmap     = cartographer::io::PaintSubmapSlicesResult;

class CartographerTask  : public CartographerTaskCore
{
private:
public:
	CartographerTask(SmartACE::SmartComponent *comp);
	virtual ~CartographerTask();
	
	virtual int on_entry();
	virtual int on_execute();
	virtual int on_exit();

	//cartographer stuff

	std::unique_ptr<MapBuilderInterface> map_builder;
	MapBuilderOptions map_builder_options;
	TrajectoryBuilderOptions trajectory_builder_options;
	std::set<SensorId>expected_sensor_ids;
	TrajectoryBuilderInterface* trajectory_builder;
	int trajectory_id;
	static const std::string laser_id;
	static const std::string odometry_id;
	bool use_laser{false};
	bool use_odometry{false};
	uint8_t num_subdivisions_per_laser_scan;
	uint16_t map_id{0};
	uint16_t timer_counter{0};
	uint8_t laser_frequency;
	std::string previous_state_pbstream{""};
	bool enable_visualization;
	bool load_previous_state;
	std::chrono::steady_clock::time_point last;
	CommBasicObjects::CommMobileLaserScan current_laser_scan;

	struct LocalSlamData {
	      Time time;
	      Rigid3d local_pose;
	      RangeData range_data_in_local;
	    };

	enum class CartographerMode{
		Localization,
		Mapping
	};

	CartographerMode cartographer_mode;

	void OnLocalSlamResult(const int trajectory_id,
			               const Time time,
	                       const Rigid3d local_pose,
						   RangeData range_data_in_local);

	std::unordered_map<int, std::shared_ptr<const LocalSlamData>> local_slam_data_;
	void AddSensorData_LaserScanMessage(const CommBasicObjects::CommMobileLaserScan& lasescan);
	void AddSensorData_OdometryMessage(const CommBasicObjects::CommBasePose& odompose, const CommBasicObjects::CommTimeStamp& time_stamp);
	bool FinishTrajectory(const std::string &dirname, const std::string &filename);
	bool savemap(const std::string &dirname, const std::string &filename);
	bool write_to_disk(const CGmap& cg_map,const std::string &dirname, const std::string &filename);
	void send_currentmap(const CGmap& cartographer_map);
	CGmap get_current_map_debug();
	CGmap get_current_map();
	void WriteYaml(const double resolution, const Eigen::Vector2d& origin, const std::string& pgm_filename,::cartographer::io::FileWriter* file_writer);
	void WritePgm(const ::cartographer::io::Image& image, const double resolution, cartographer::io::FileWriter* file_writer);
};
#endif