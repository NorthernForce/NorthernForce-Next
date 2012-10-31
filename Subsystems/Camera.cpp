#include <vxWorks.h>
#include <usrLib.h>
#include <limits>
#include "Camera.h"
#include "../Robotmap.h"
#include "Vision/BinaryImage.h"
#include "../CommandBase.h"

/** 
 * @brief Private NI function needed to write to the VxWorks target.
 */

IMAQ_FUNC int Priv_SetWriteFileAllowed(UINT32 enable); 

/**
 * @brief Creates the camera subsystem.
 * @author Arthur Lockman
 */
Camera::Camera() :
	Subsystem("Camera"),
	m_cam(AxisCamera::GetInstance("10.1.72.11")),
	m_saveSourceImage(false),
	m_saveProcessedImages(false),
	m_frameProcessingTime(0),
	m_imageProcessingTask("ImageProcessing", (FUNCPTR)Camera::ImageProcessingTask, Task::kDefaultPriority + 10),
	m_cameraSemaphore (semBCreate (SEM_Q_PRIORITY, SEM_FULL))
{
	SetDirectory ("/tmp/Images");
	m_imageProcessingTask.Start (reinterpret_cast<UINT32> (this));
}

/**
 * @brief Destroys the camera subsystem.
 */
Camera::~Camera()
{
	semDelete (m_cameraSemaphore);
}

/**
 * @brief Default class required by CommandBase. Initializes
 * the default command for this subsystem to run. 
 * Does nothing as the camera class takes no commands.
 */
void Camera::InitDefaultCommand() { return; }

/** @brief Sets the directory within which to write the camera images
 *
 * @author Stephen Nutt
 */
void Camera::SetDirectory (
	const char* directory,
	unsigned nextImage)
{
	const Synchronized sync (m_cameraSemaphore);
	strcpy (m_directory, directory);
	Priv_SetWriteFileAllowed(1);
//	mkdir (m_directory); Does this work??
	m_lastImageNo = m_imageNo = nextImage - 1;
}

/** 
 * @brief Static function called when the camera task is started,
 * used to start the ProcessImages function
 */
void Camera::ImageProcessingTask(Camera& camera)
{
	camera.ProcessImages();
}

/** 
 * @brief Process the camera images. This processing task will only
 * process the images if <code>kProcessImages</code> in Robotmap.h 
 * is set to <code>true</code>.
 */
void Camera::ProcessImages()
{
	// Wait for the camera to initialize
	Wait(2.0);
	printf("Setting camera parameters\n");
	m_cam.WriteResolution(AxisCamera::kResolution_320x240);
	m_cam.WriteCompression(20);
	m_cam.WriteBrightness(50);
    m_cam.WriteMaxFPS(30);
	printf("Camera parameters set.\n");

	UINT32 frameStart = GetFPGATime();

	while (kProcessImages)
	{
		// Wait for a new image to be available
		if (m_cam.IsFreshImage() == false)
		{
			taskDelay (2);
			continue;
		}

		m_cam.GetImage (&m_image);
		if (m_saveSourceImage) SaveImage(m_image, "src.jpg");

		//! @TODO: IMAGE PROCCESSING CODE HERE.

		// Update the processing time.  We add 1 to ensure the time
		// is never 0
		const UINT32 now = GetFPGATime();
		m_frameProcessingTime = (now - frameStart) + 1;
		frameStart = now;
	}
}

/** 
 * @brief Writes the image to the file system
 * @author Stephen Nutt
 */
void Camera::SaveImage (
	ImageBase& image,
	const char* name) const
{
	char path[60];
	{
		const Synchronized sync (m_cameraSemaphore);
		sprintf (path, "%s/Img%04d_%s", m_directory, m_imageNo, name);
	}
	image.Write(path);
}

/** 
 * @brief Captures the next n images from the camera
 * @author Stephen Nutt
 */
void Camera::CaptureImages (unsigned count)
{
	const Synchronized sync (m_cameraSemaphore);
	m_lastImageNo = std::min (m_imageNo + count, m_lastImageNo + count);
}
