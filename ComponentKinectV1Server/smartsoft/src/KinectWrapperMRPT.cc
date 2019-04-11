//--------------------------------------------------------------------------
// Code generated by the SmartSoft MDSD Toolchain Version 2.2
// The SmartSoft Toolchain has been developed by:
//
// Christian Schlegel (schlegel@hs-ulm.de)
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
// --------------------------------------------------------------------------
//
//  Copyright (C) 2011, 2017 Matthias Lutz, Dennis Stampfer, Matthias Rollenhagen, Nayabrasul Shaik
//
//      lutz@hs-ulm.de
//      stampfer@hs-ulm.de
//      rollenhagen@hs-ulm.de
//      shaik@hs-ulm.de
//
//      ZAFH Servicerobotic Ulm
//      Christian Schlegel
//      University of Applied Sciences
//      Prittwitzstr. 10
//      89075 Ulm
//      Germany
//
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2.1
//  of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  General Public License for more details.
//
//  You should have received a copy of the GNU General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
//--------------------------------------------------------------------------

#include "KinectWrapperMRPT.hh"

#include "ComponentKinectV1Server.hh"
#define TEXT_COLOR_RESET   "\033[0m"
#define TEXT_COLOR_GREEN   "\033[32m"      /* Green */

//#include <mrpt/hwdrivers.h>
//#include <mrpt/gui.h>
//#include <mrpt/maps.h>

KinectWrapper::KinectWrapper()
{
	imageCounter = 0;
	read_parameters();
	print_parameters();
	int rgb_mode = COMP->getGlobalState().getSettings().getRgb_mode();
	int depth_mode = COMP->getGlobalState().getSettings().getDepth_mode();
	kinect.open(rgb_mode, depth_mode);
}

KinectWrapper::~KinectWrapper()
{
}

void KinectWrapper::start_rgb_depth()
{
	try
	{
		kinect.start_rgb_depth();

	} catch (std::exception& e)
	{
		std::cerr << "[Kinect Wrapper] Error while opening kinect dev : " << e.what() << "\n";
	}

}

void KinectWrapper::get_rgbd_image(DomainVision::CommRGBDImage& image)
{

	DomainVision::CommVideoImage comm_video_image;
	DomainVision::CommDepthImage comm_depth_image;
	bool there_is_obs = true, hard_error = false;
	// Grab new observation from the camera:
	mrpt::obs::CObservation3DRangeScanPtr obs = mrpt::obs::CObservation3DRangeScan::Create(); // Smart pointers to observations

	do
	{
		kinect.getNextObservation(*obs, there_is_obs, hard_error);
		if (!there_is_obs)
		{
			std::cout << "There is no new observation!" << endl;
		}

	} while (!there_is_obs);

	++imageCounter;

	// fill ranges as 2D and rgb
	if (obs->hasRangeImage && obs->hasIntensityImage)
	{
		get_depth_image(comm_depth_image, obs->rangeImage);
		get_video_image(comm_video_image, obs->intensityImage);
		image.setColor_image(comm_video_image);
		image.setDepth_image(comm_depth_image);
		image.setSeq_count(imageCounter);
		image.setIs_valid(true);
		cout << "[KinectWrapperMRPT] is_data_valid : true " <<": Frame Number = "<<imageCounter<< endl;
	}
	else
	{
		image.setSeq_count(imageCounter);
		image.setIs_valid(false);
		if(!obs->hasRangeImage) std::cout<<"[KinectWrapperMRPT] The obs has no RangeImage!"<<std::endl;
		if(!obs->hasIntensityImage) std::cout<<"[KinectWrapperMRPT] The obs has no RangeImage!"<<std::endl;
		cout << "[KinectWrapperMRPT] is_data_valid : false"<<": Frame Number = "<<imageCounter << endl;
	}

}
void KinectWrapper::get_depth_image(DomainVision::CommDepthImage& comm_depth_image, CMatrixFloat& range2D)
{

	unsigned int cols = range2D.getColCount();
	unsigned int rows = range2D.getRowCount();

	std::vector<float> depth(rows*cols);

	for (unsigned int x = 0; x < cols; x++)
	{
		for (unsigned int y = 0; y < rows; y++)
		{

			depth[y * cols + x] = range2D(y, x); //access to matrix in y, x direction!

		}
	}

	comm_depth_image.set_distances(depth, cols, rows);
	comm_depth_image.setWidth(cols);
	comm_depth_image.setHeight(rows);
	comm_depth_image.setFormat(DomainVision::DepthFormatType::FLOAT);
	comm_depth_image.setPixel_size(32);
	comm_depth_image.setSeq_count(imageCounter);
	comm_depth_image.setDistortion_model(DomainVision::ImageDistortionModel::NONE);
	comm_depth_image.set_intrinsic(depth_intrinsics);
	comm_depth_image.set_distortion(depth_distortion);
	comm_depth_image.set_extrinsic(depth_extrinsics);
	comm_depth_image.setIs_valid(true);
}

void KinectWrapper::get_video_image(DomainVision::CommVideoImage& comm_video_image, CImage& intensity_image)
{

	intensity_image.swapRB();
	unsigned int cols = intensity_image.getWidth();
	unsigned int rows = intensity_image.getHeight();

	std::cout << "[KinectWrapperMRPT] colorImg size: " << cols << " " << rows << std::endl;
	comm_video_image.setSeq_count(imageCounter);
	comm_video_image.set_parameters(cols, rows, DomainVision::FormatType::RGB24);
	comm_video_image.set_data(intensity_image(0, 0, 0));
	//comm_video_image.set_data(&colorImg[0]);
	comm_video_image.set_intrinsic(color_intrinsics);
	comm_video_image.setDistortion_model(DomainVision::ImageDistortionModel::BROWN_CONRADY);//TODO need to be verified
	comm_video_image.set_distortion(color_distortion);
	comm_video_image.setIs_valid(true);
}

void KinectWrapper::stop_rgb_depth(){
	try{
		kinect.stop_rgb_depth();
	} catch (std::exception& e) {
		std::cerr << "[Kinect Wrapper] Error while closing kinect dev : " << e.what() << "\n";
	}

}

void KinectWrapper::read_parameters()
{


	// Read intrinsic parameters of RGB camera
	color_intrinsics.set_size(4, 4);
	color_intrinsics.zeros();

	TCamera cameraParamsrgb= kinect.getCameraParamsIntensity();
	color_intrinsics(0, 0) = cameraParamsrgb.fx();
	color_intrinsics(1, 1) = cameraParamsrgb.fy();
	color_intrinsics(0, 2) = cameraParamsrgb.cx();
	color_intrinsics(1, 2) = cameraParamsrgb.cy();

	color_intrinsics(2, 2) = 1;
	color_intrinsics(3, 3) = 1;

	color_distortion.set_size(1, 5);
	color_distortion(0,0) = 0;
	color_distortion(0,1) = 0;
	color_distortion(0,2) = 0;
	color_distortion(0,3) = 0;
	color_distortion(0,4) = 0;


	// Read intrinsic parameters of depth camera
	depth_intrinsics.set_size(4, 4);
	depth_intrinsics.zeros();
	TCamera cameraParamsDepth = kinect.getCameraParamsDepth();
	depth_intrinsics(0, 0) = cameraParamsDepth.fx();
	depth_intrinsics(1, 1) = cameraParamsDepth.fy();
	depth_intrinsics(0, 2) = cameraParamsDepth.cx();
	depth_intrinsics(1, 2) = cameraParamsDepth.cy();
	depth_intrinsics(2, 2) = 1;
	depth_intrinsics(3, 3) = 1;

	depth_distortion.set_size(1, 5);
	depth_distortion(0,0) = 0;
	depth_distortion(0,1) = 0;
	depth_distortion(0,2) = 0;
	depth_distortion(0,3) = 0;
	depth_distortion(0,4) = 0;

	depth_extrinsics.set_size(1, 12);
	depth_extrinsics.zeros();


	// Read extrinsic parameters of depth to color
	// libfreenect is giving rgb, depth frames available in same coordinate frame
	depth_extrinsics(0,0) = 1.0;
	depth_extrinsics(0,1) = 0.0;
	depth_extrinsics(0,2) = 0.0;

	depth_extrinsics(0,3) = 0.0;
	depth_extrinsics(0,4) = 1.0;
	depth_extrinsics(0,5) = 0.0;

	depth_extrinsics(0,6) = 0.0;
	depth_extrinsics(0,7) = 0.0;
	depth_extrinsics(0,8) = 1.0;

	depth_extrinsics(0,9)  = 0.0;
	depth_extrinsics(0,10) = 0.0;
	depth_extrinsics(0,11) = 0.0;


}

void KinectWrapper::print_parameters()
{
	std::cout<<TEXT_COLOR_RESET<< TEXT_COLOR_GREEN; // make the screen output Green
	std::cout <<"-----------------------------------------------------------------"<<std::endl;
	std::cout <<std::setw(0)<<"Colour Intrinsics"<<std::endl;
	std::cout <<"-----------------------------------------------------------------"<<std::endl;
	std::cout <<std::setw(20)<<  "cx"<<" = " << color_intrinsics(0, 2)<<std::endl;
	std::cout <<std::setw(20)<<  "cy"<<" = " << color_intrinsics(1, 2)<<std::endl;
	std::cout <<std::setw(20)<<  "fx"<<" ="  << color_intrinsics(0, 0)<<std::endl;
	std::cout <<std::setw(20)<<  "fy"<<" ="  << color_intrinsics(1, 1)<<std::endl;

	//std::cout <<std::setw(20)<<  "height"<<" = "  << color_intrinsics.height<<std::endl;
	//std::cout <<std::setw(20)<<  "width" <<" = "  << color_intrinsics.width<<std::endl;

	std::cout <<std::setw(20)<<  "distortion coeffs"<<" = ["<<color_distortion(0,0) << ", "<<color_distortion(0,1) << ", "
			<<color_distortion(0,2) << ", "<<color_distortion(0,3) << ", "<<color_distortion(0,4)<<" ]" <<std::endl;


	std::cout <<"-----------------------------------------------------------------"<<std::endl;
	std::cout <<std::setw(0)<<"Depth Intrinsics"<<std::endl;
	std::cout <<"-----------------------------------------------------------------"<<std::endl;
	std::cout <<std::setw(20)<<  "cx"<<" = " << depth_intrinsics(0, 2)<<std::endl;
	std::cout <<std::setw(20)<<  "cy"<<" = " << depth_intrinsics(1, 2)<<std::endl;
	std::cout <<std::setw(20)<<  "fx"<<" ="  << depth_intrinsics(0, 0)<<std::endl;
	std::cout <<std::setw(20)<<  "fy"<<" ="  << depth_intrinsics(1, 1)<<std::endl;

	//std::cout <<std::setw(20)<<  "height"<<" = "  << depth_intrinsics.height<<std::endl;
	//std::cout <<std::setw(20)<<  "width" <<" = "  << depth_intrinsics.width<<std::endl;

	std::cout <<std::setw(20)<<  "distortion coeffs"<<" = ["<<depth_distortion(0,0) << ", "<<depth_distortion(0,1) << ", "
			<<depth_distortion(0,2) << ", "<<depth_distortion(0,3) << ", "<<depth_distortion(0,4) <<" ]"<<std::endl;

	std::cout <<"-----------------------------------------------------------------"<<std::endl;
	std::cout <<std::setw(0)<<"Depth Exrinsics"<<std::endl;
	std::cout <<"-----------------------------------------------------------------"<<std::endl;

	std::cout <<std::setw(20)<<  "rotation"<<" = "
			<<std::setw( 2)<< "| "<<std::setw(13)<<depth_extrinsics(0,0) <<std::setw(15)<< depth_extrinsics(0,1)<<std::setw(15)<< depth_extrinsics(0,2)<<" |"<<std::endl
			<<std::setw(25)<< "| "<<std::setw(13)<<depth_extrinsics(0,3) <<std::setw(15)<< depth_extrinsics(0,4)<<std::setw(15)<< depth_extrinsics(0,5)<<" |"<<std::endl
			<<std::setw(25)<< "| "<<std::setw(13)<<depth_extrinsics(0,6) <<std::setw(15)<< depth_extrinsics(0,7)<<std::setw(15)<< depth_extrinsics(0,8)<<" |"<<std::endl;

	std::cout <<std::endl;
	std::cout <<std::setw(20)<< "translation"<<" = "<<"[ "<<std::setw(13) << depth_extrinsics(0,9) <<std::setw(13) << depth_extrinsics(0,10)<<std::setw(13) << depth_extrinsics(0,11)<<" ]"<<std::endl;
	std::cout <<std::endl;
	std::cout <<"-----------------------------------------------------------------"<<std::endl;
	std::cout<< TEXT_COLOR_RESET; // make the screen output normal

}

///////////////////////////////////////////////////
// Reprojection of depth points to color image --> for rgb color image correction
///////////////////////////////////////////////////
/*
 const int sizeRangeScan = obs->points3D_x.size();
 const float cx = obs->cameraParamsIntensity.cx();
 const float cy = obs->cameraParamsIntensity.cy();
 const float fx = obs->cameraParamsIntensity.fx();
 const float fy = obs->cameraParamsIntensity.fy();
 unsigned int img_idx_x = 0, img_idx_y = 0;
 size_t imgW=0, imgH=0;
 bool hasValidIntensityImage = false;

 if (obs->hasIntensityImage)
 {
 // assure the size matches?
 if (sizeRangeScan == obs->intensityImage.getWidth() * obs->intensityImage.getHeight() )
 {
 hasValidIntensityImage = true;
 imgW = obs->intensityImage.getWidth();
 imgH = obs->intensityImage.getHeight();
 }
 }



 const bool hasColorIntensityImg = hasValidIntensityImage && obs->intensityImage.isColor();


 std::cout<<"RangeScanSize: "<<sizeRangeScan<<endl;

 for (size_t i=0;i<sizeRangeScan;i++)
 {
 // Valid point?
 if ( obs->points3D_x[i]!=0 && obs->points3D_y[i]!=0 )
 {

 const float scan_x = obs->points3D_x[i];
 const float scan_y = obs->points3D_y[i];
 const float scan_z = obs->points3D_z[i];
 imgW = obs->intensityImage.getWidth();
 imgH = obs->intensityImage.getHeight();
 float	pR=1,pG=1,pB=1;
 const float K_8u = 1.0f/255;

 // Do we have to project the 3D point into the image plane??
 bool hasValidColor = false;


 TPoint3D  pt; // pt_wrt_colorcam;
 obs->relativePoseIntensityWRTDepth.inverseComposePoint(
 scan_x,scan_y,scan_z,
 pt.x,pt.y,pt.z);

 // Project to image plane:
 if (pt.z)
 {
 img_idx_x = cx + fx * pt.x/pt.z;
 img_idx_y = cy + fy * pt.y/pt.z;

 hasValidColor=
 img_idx_x>=0 && img_idx_x<imgW &&
 img_idx_y>=0 && img_idx_y<imgH;
 }


 if (hasValidColor && hasColorIntensityImg)
 {
 const uint8_t *c= obs->intensityImage.get_unsafe(img_idx_x, img_idx_y, 0);
 pR= c[2] * K_8u;
 pG= c[1] * K_8u;
 pB= c[0] * K_8u;

 colorImg[i*3+0]= pR*255;//access to matrix in y, x direction!
 colorImg[i*3+1]= pG*255;
 colorImg[i*3+2]= pB*255;
 }
 }
 }
 image->set_rgb_image(colorImg);
 */