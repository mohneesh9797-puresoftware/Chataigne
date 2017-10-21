/*
  ==============================================================================

    DMXManager.cpp
    Created: 6 Apr 2017 10:23:15pm
    Author:  Ben

  ==============================================================================
*/

#include "DMXManager.h"

juce_ImplementSingleton(DMXManager)

DMXManager::DMXManager() :
	Thread("ArtNetRead")
{
	artNetUDP.bindToPort(3333);
	startTimer(1000);
	startThread();
}

DMXManager::~DMXManager()
{

	signalThreadShouldExit();
	while (isThreadRunning());
}

void DMXManager::checkForArtNetDevices()
{
	sendArtNetPollRequest(ARTNET_FULL_INFO);
}

void DMXManager::sendArtNetPollRequest(int type)
{
	const char typeData[1]{ (char)type };
	artNetUDP.write(IPAddress::broadcast().toString(), ARTNET_PORT, "ESPP", 4);
	artNetUDP.write(IPAddress::broadcast().toString(), ARTNET_PORT, typeData, 1);
}

void DMXManager::timerCallback()
{
	checkForArtNetDevices();
}

void DMXManager::run()
{
	DBG("Start Artnet Run thread");
	uint8 buffer[600];
	while (threadShouldExit())
	{
		String remoteIP;
		int remotePort;
		int numBytes = artNetUDP.read(buffer, 600, false, remoteIP, remotePort);
		if (numBytes > 0)
		{
			DBG("Received : " << numBytes << "bytes from" << remoteIP << ":" << remotePort);
		}
		sleep(20);
	}
	
}
