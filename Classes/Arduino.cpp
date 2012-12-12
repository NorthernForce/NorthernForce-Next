#include "Arduino.h"

/**
 * @brief Default constructor for the Arduino class.
 * Sets the serial port to run at 9600 baud.
 */
Arduino::Arduino():
	serialConnection(9600),
	baud(9600)
{
	serialConnection.DisableTermination();
}

/**
 * @brief Constructs the Arduino at the desired baud speed
 * @param baudRate the baud rate to open the connection at.
 */
Arduino::Arduino(int baudRate):
		serialConnection(baudRate),
		baud(baudRate)
{
	serialConnection.DisableTermination();
}

/**
 * @brief The destructor for the Arduino class.
 */
Arduino::~Arduino()
{
	delete &serialConnection;
}

/**
 * @brief Gets a string of data from the buffer.
 * @return The string of data.
 */
std::string Arduino::GetData()
{
	char* str;
	serialConnection.Scanf("%s",str);
	return str;
}

/**
 * @brief Sends a string to the Arduino.
 * @param dataString A string of data to send to the robot.
 */
void Arduino::SendData(std::string dataString)
{
	serialConnection.Printf("%s",&dataString);
}

/**
 * @brief Resets the serial connection.
 */
void Arduino::ResetConnection()
{
	serialConnection.Reset();
}
