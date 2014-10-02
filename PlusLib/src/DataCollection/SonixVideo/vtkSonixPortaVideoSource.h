/*=Plus=header=begin======================================================
  Program: Plus
  Copyright (c) Laboratory for Percutaneous Surgery. All rights reserved.
  See License.txt for details.
=========================================================Plus=header=end*/

/*=========================================================================
The following copyright notice is applicable to parts of this file:
Copyright (c) Elvis Chen, 2008
All rights reserved.
See Copyright.txt or http://www.kitware.com/Copyright.htm for details.
Authors include: Elvis Chen (Queen's University)
=========================================================================*/  

#ifndef __VTKSONIXPORTAVIDEOSOURCE_H__
#define __VTKSONIXPORTAVIDEOSOURCE_H__

#include "PlusConfigure.h"
#include "vtkDataCollectionExport.h"

#include "vtkPlusDevice.h"

class vtkDataCollectionExport vtkSonixPortaVideoSource;
class porta;
struct probeInfo;

/*!
\class vtkSonixPortaVideoSourceCleanup 
\brief Class that cleans up (deletes singleton instance of) vtkSonixPortaVideoSource when destroyed
\ingroup PlusLibDataCollection
*/
class vtkDataCollectionExport vtkSonixPortaVideoSourceCleanup 
{
public:
  vtkSonixPortaVideoSourceCleanup();
  ~vtkSonixPortaVideoSourceCleanup();
};

/*!
  \class vtkSonixPortaVideoSource 
  \brief Class providing VTK video input interface for SonixRP

  vtkSonixPortaVideoSource is a subclass of vtkVideoSource that
  implementes Porta API for importing video directly from the Cine
  buffer of a Sonix RP Ultrasound machine.

  You must call the ReleaseSystemResources() method before the application
  exits.  Otherwise the application might hang while trying to exit.

  the 3D/4D probe should always be connected to port-0

  In order to reduce the number of missing frames the motor speed can be 
  decreased by changing the b frame rate id in the imaging.set.xml file of the
  Porta SDK.

  Usage:
  sonixGrabber = vtkSonixPortaVideoSource::New();
  sonixGrabber->SetPortaSettingPath( "../../dat/" );
  sonixGrabber->SetPortaFirmwarePath( "../../fw/" );
  sonixGrabber->SetPortaLUTPath( "C:/LUTs/" );
  sonixGrabber->SetPortaCineSize( 256*1024*1024 );
  // not needed, defaults 256MB
  sonixGrabber->SetBLineDensity( 128 );
  // line density effect the frame rate
  sonixGrabber->Record();
  imageviewer->SetInputData_vtk5compatible( sonixGrabber->GetOutput() ); 

  \ingroup PlusLibDataCollection
*/ 
class vtkDataCollectionExport vtkSonixPortaVideoSource : public vtkPlusDevice {

  vtkTypeRevisionMacro( vtkSonixPortaVideoSource, vtkPlusDevice );
  void PrintSelf( ostream &os, vtkIndent indent );

  /*! This is a singleton pattern New.  There will only be ONE
   reference to a vtkOutputWindow object per process.  Clients that
   call this must call Delete on the object so that the reference
   counting will work.  The single instance will be unreferenced
   when the program exits. */
  static vtkSonixPortaVideoSource *New();

  /*! return the singleton instance with no reference counting */
  static vtkSonixPortaVideoSource *GetInstance();

  /*! Supply a user defined output window.  Call ->Delete() on the supplied instance after setting it. */
  static void SetInstance( vtkSonixPortaVideoSource *instance );

  //BTX
  /*! use this as a way of memory management when the
   program exits the SmartPointer will be deleted which
   will delete the Instance singleton */
  static vtkSonixPortaVideoSourceCleanup Cleanup;
  //ETX

  /*! Hardware device SDK version. */
  virtual std::string GetSdkVersion();
  /*! Read main configuration from xml data */  virtual PlusStatus ReadConfiguration(vtkXMLDataElement* config); 
  /*! Write main configuration to xml data */
  virtual PlusStatus WriteConfiguration(vtkXMLDataElement* config);

  /* List of parameters which can be set or read in B-mode, other mode parameters not currently implemented*/  
  
  /*! Get/Set the probe name */
  vtkSetStringMacro(PortaProbeName); 
  vtkGetStringMacro(PortaProbeName); 

  /*! Get/Set the probe name */
  vtkSetStringMacro(PortaSettingPath); 
  vtkGetStringMacro(PortaSettingPath); 

  /*! Get/Set the firmware path name */
  vtkSetStringMacro(PortaFirmwarePath); 
  vtkGetStringMacro(PortaFirmwarePath); 

  /*! Get/Set the look-up table path name */
  vtkSetStringMacro(PortaLUTPath); 
  vtkGetStringMacro(PortaLUTPath); 

  /*! Set USM initialization parameter */
  vtkSetMacro(Usm, int);
  /*! Get USM initialization parameter */
  vtkGetMacro(Usm, int);

  /*! Set PCI initialization parameter */
  vtkSetMacro(Pci, int);
  /*! Get PCI initialization parameter */
  vtkGetMacro(Pci, int);

  /*! Set HighVoltage initialization parameter */
  vtkSetMacro(HighVoltage, int);
  /*! Get HighVoltage initialization parameter */
  vtkGetMacro(HighVoltage, int);

  /*! Set Channels initialization parameter */
  vtkSetMacro(Channels, int);
  /*! Get Channels initialization parameter */
  vtkGetMacro(Channels, int);


  /*! Get/Set the look-up table path name */
  vtkSetStringMacro(PortaLicensePath); 
  vtkGetStringMacro(PortaLicensePath); 

  /*! Set ultrasound transmitter frequency (MHz) */
  PlusStatus SetFrequency(int aFrequency);
  /*! Get ultrasound transmitter frequency (MHz) */
  PlusStatus GetFrequency(int& aFrequency);

  /*! Set the depth (mm) of B-mode ultrasound */
  PlusStatus SetDepth(int aDepth);
  /*! Get the depth (mm) of B-mode ultrasound */
  PlusStatus GetDepth(int& aDepth);

  /*! Set the Gain (%) of B-mode ultrasound; valid range: 0-100 */
  PlusStatus SetGain(int aGain);
  /*! Get the Gain (%) of B-mode ultrasound; valid range: 0-100 */
  PlusStatus GetGain(int& aGain);

  /*! Set the Zoom (%) of B-mode ultrasound; valid range: 0-100 */
  PlusStatus SetZoom(int aZoom);
  /*! Get the Zoom (%) of B-mode ultrasound; valid range: 0-100 */
  PlusStatus GetZoom(int& aZoom);

  /*! Set the number of frames per volume */
  PlusStatus SetFramePerVolume(int aFramePerVolume);
  /*! Get the number of frames per volume */
  PlusStatus GetFramePerVolume(int& aFramePerVolume);
  
  /*! Set the number of frames per volume */
  PlusStatus SetStepPerFrame(int aStepPerFrame);
  /*! Get the number of frames per volume */
  PlusStatus GetStepPerFrame(int& aStepPerFrame);
  
  /*! Set the Timeout (ms) value for network function calls. */
  PlusStatus SetTimeout(int aTimeout);

  /*! Set the BMode frame size in pixels. */
  vtkSetVector2Macro(BModeFrameSize,int);

  void SetImagingMode(int mode){ImagingMode = mode;};
  void GetImagingMode(int & mode){mode = ImagingMode;};
  
  /*! set the CineSize, defaults to 256MB, size in bytes */
  void SetPortaCineSize( int size );

  /*! Set the start position */
  PlusStatus SetPortaMotorStartPosition(int aMotorStartPosition);
  /*! Get the Gain (%) of B-mode ultrasound; valid range: 0-100 */
  PlusStatus GetPortaMotorStartPosition(int& aMotorStartPosition);

  /*! Set the start position */
  void SetPortaMotorStartPosition( double v );
  
  /*! Return the start position */
  double GetPortaMotorStartPosition();
  
  /*! Go to the start position */
  double GoToPortaMotorStartPosition();
  
  /*! Moves the motor a certain angle from the home position */
  double GoToPosition( double angle );
  
  /*! Moves the motor clockwise or counter-clockwise by one half-step. */
  double StepPortaMotor( bool cw, int steps );
  
  /*! Return the current motor position */
  double GetPortaMotorPosition();

  /*! Return current frame rate as reported by Porta */
  int GetPortaFrameRate();

  /*! Verify the device is correctly configured */
  virtual PlusStatus NotifyConfigured();
  
protected:
  vtkSonixPortaVideoSource();
  ~vtkSonixPortaVideoSource();

  /*! Connect to device */
  virtual PlusStatus InternalConnect();


  /*! Disconnect from device */
  virtual PlusStatus InternalDisconnect();

  /*! Record incoming video at the specified FrameRate.  The recording */
  // continues indefinitely until StopRecording() is called. 
  virtual PlusStatus InternalStartRecording();

  /*! Stop recording or playing. */
  virtual PlusStatus InternalStopRecording();

  /*! Get the last error string returned by Porta */
  std::string GetLastPortaError();
  
  /*! Pointer to the hardware. Only required for SDK versions prior to 6.0 */  
  porta* Porta;

  /*! Imaging parameters */
  int Depth;
  int Frequency;
  int Gain; 
  int Zoom;   

  int ImagingMode;
  int Timeout; 

  /*! Porta initialization parameters */
  int Usm;
  int Pci;
  int HighVoltage;
  int Channels;
  
  /*! for internal use only */
  PlusStatus AddFrameToBuffer( void *param, int id );

  /*! For internal use only */
  PlusStatus SetParamValue(char* paramId, int paramValue, int &validatedParamValue);
  /*! For internal use only */
  PlusStatus GetParamValue(char* paramId, int& paramValue, int &validatedParamValue);

  virtual bool IsTracker() const { return false; }
        
private:
 
  // data members
  static vtkSonixPortaVideoSource *Instance;
  
  /*! call back whenever a new frame is available */ 
#if (PLUS_ULTRASONIX_SDK_MAJOR_VERSION < 5) || (PLUS_ULTRASONIX_SDK_MAJOR_VERSION == 5 && PLUS_ULTRASONIX_SDK_MINOR_VERSION < 7)
  //  SDK version < 5.7.x 
  static bool vtkSonixPortaVideoSourceNewFrameCallback( void *param, int id );
#elif (PLUS_ULTRASONIX_SDK_MAJOR_VERSION < 6) 
  //  5.7.x <= SDK version < 6.x
  static bool vtkSonixPortaVideoSourceNewFrameCallback( void *param, int id, int header );
#else
  static int vtkSonixPortaVideoSourceNewFrameCallback(void* param, int id, int header);
#endif

  // vtkSonixPortaVideoSource(const vtkSonixPortaVideoSource&);  // Not implemented.
  // void operator=(const vtkSonixPortaVideoSource&);  // Not implemented.              
  
  /*! Update porta parameters */
  PlusStatus vtkSonixPortaVideoSource::UpdateSonixPortaParams();

  /*! Get probe head to transducer center transform */
  std::string GetMotorToMotorRotatedTransform( double MotorAngle );

  // Porta parameters
  /*! The B-mode image width */
  int PortaBModeWidth;

  /*! The B-mode iamge height */
  int PortaBModeHeight;

  /*! 1 if the probe has been selected, 0 otherwise */
  int PortaProbeSelected;

  /*! 1 if the PortaImageMode has been set in the hardware, 0 otherwise */
  int PortaModeSelected;

  /*! name of the probe */
  char *PortaProbeName;

  /*! Path to the Porta Setting directory */
  char *PortaSettingPath;

  /*! Path to the Porta Firmware directory */
  char *PortaFirmwarePath;

  /*! Path to the Porta LUT directory */
  char *PortaLUTPath;

  /*! Path to the licenses text file */
  char *PortaLicensePath;

  /*! Size of the Cine buffer */
  int PortaCineSize;
    
  /*! Size of the BMode frame buffer in pixels */
  int BModeFrameSize[2];

  /*! storage for sonix frame buffer */
  unsigned char *BModeFrameBuffer; 

  /*! the number of frames that will acquired in one sweep of the motor */
  int FramePerVolume;
  
  /*!  The number of steps the motor will move while acuqiring a single frame */
  int StepPerFrame;

  /*! Probe information */
  probeInfo* ProbeInformation;

  /*! Motor rotation per step (in degrees) */
  double MotorRotationPerStepDeg;

  /*! Set to false after first call to AddFramToBuffer */
  bool FirstCallToAddFrameToBuffer;

  /*! Initial angle of the motor where it is positioned at the edge of the user defined field of view */
  double StartMotorAngle;

  /*! Current angle of the motor */
  double CurrentMotorAngle;

  /*! Index keeping track of which frame belongs to which volume */
  int VolumeIndex;

	/*! Keeping track in which direction the probe moves */
	bool IncrementVolumeIndexClockwise;
	bool IncrementVolumeIndexCounterClockwise;

	bool RequireFrameBufferSizeInDeviceSetConfiguration;
  bool RequireAcquisitionRateInDeviceSetConfiguration;
  bool RequireAveragedItemsForFilteringInDeviceSetConfiguration;
  bool RequireLocalTimeOffsetSecInDeviceSetConfiguration;
  bool RequireUsImageOrientationInDeviceSetConfiguration;
  bool RequireRfElementInDeviceSetConfiguration;
	unsigned char* ImageBuffer;
};

#endif // of __VTKSONIXPORTAVIDEOSOURCE_H__