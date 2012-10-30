#ifndef CAMERA_H
#define CAMERA_H
#include <WPILib.h>

/**
 * @brief This class is the camera subsystem. It is used
 * to get images and data from the camera, and process 
 * those images so that they're useful to the game. 
 * The class assumes that the camera has the IP 
 * 10.1.72.11. If this is different, be sure to change
 * the IP in the constructor for this class.
 *
 * @author Arthur Lockman, Steve Nutt
 */
 class Camera: public Subsystem {
 private:
 	void ProcessImages();
 	void SaveImage(ImageBase& image, const char* name) const;
	static void ImageProcessingTask(Camera& camera);

	//! The axis camera instance
 	AxisCamera& m_cam;

 	//! The current camera image
 	mutable HSLImage m_image;
 	//! The directory the images are stored in
 	char m_directory[32];
 	//! The unique image number used to generate the image file name
 	unsigned m_imageNo;
 	//! The last image number to capture
 	unsigned m_lastImageNo;
 	//! Controls the saving of the source images
 	bool m_saveSourceImage;
 	//! Controls the saving of the processed images
 	bool m_saveProcessedImages;
 	//! The time it took to process the last frame in ms
 	UINT32 m_frameProcessingTime;
	
	//! The task object used to process camera images
 	Task m_imageProcessingTask;
	//! A semaphore to provide mutual exclusion to the camera data members
 	const SEM_ID m_cameraSemaphore;

 public:
 	Camera();
 	~Camera();

 	void InitDefaultCommand();
 	void SetDirectory(const char* directory, unsigned nextImage = 1);
 	void CaptureImages(unsigned count);

 	UINT32 GetLastFrameProcessingTime() const
 	{
 		return m_frameProcessingTime;
 	}
 };
 #endif

