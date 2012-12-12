#ifndef SERIALARDUINO_H
#define SERIALARDUINO_H
/*
 * Description: A class for interfacing with an Arduino. Handles
 * connection over a serial port, defined in the constructor.
 * @author Arthur Lockman
 */
#include <WPILib.h>

class SerialArduino
{
public:
	SerialArduino();
	SerialArduino(int baudRate);
	~SerialArduino();
	
	std::string GetData();
	void SendData(std::string dataString);
	void ResetConnection();
	
private:
	SerialPort serialConnection;
	int baud;
};

#endif
