#pragma once

// clang-format off
#define SEND_QUEUE_DATA(Flag) { \
	while(true) { \
		Protocol::Struct_##Flag structData; \
		if(self->Queue_##Flag.try_dequeue(structData)) { \
			uint8_t* data; \
			uint32_t size; \
			self->serializingProtocol.dataToBinary<Protocol::Struct_##Flag>(structData, &data, &size); \
			uint32_t dataSize = htonl(size); \
			self->sendData(&dataSize, sizeof(dataSize)); \
			self->sendData(&structData.flag, sizeof(DataFlag)); \
			self->sendData(data, size); \
			free(data); \
		} else { \
			break; \
		} \
	} \
}
// clang-format on

// clang-format off
// The data is just shoved onto the queue and wxWidgets can read it during idle or something
#define RECIEVE_QUEUE_DATA(Flag) \
	if (self->currentFlag == DataFlag::Flag) { \
		Protocol::Struct_##Flag data; \
		self->serializingProtocol.binaryToData<Protocol::Struct_##Flag>(data, self->dataToRead, self->dataSize); \
		self->Queue_##Flag.enqueue(data); \
	} \
// clang-format on

// clang-format off
#define ADD_QUEUE(Flag) moodycamel::ConcurrentQueue<Protocol::Struct_##Flag> Queue_##Flag;
// clang-format on

// Use this from other parts of the program to send data over the network
// clang-format off
#define ADD_TO_QUEUE(Flag, networkImp, bodyOfCode) { \
	Protocol::Struct_##Flag data; \
	bodyOfCode \
	networkImp->Queue_##Flag.enqueue(data); \
}
// clang-format on

// clang-format off
#define CHECK_QUEUE(networkInstance, Flag, codeBody) { \
	Protocol::Struct_##Flag data; \
	while (networkInstance->Queue_##Flag.try_dequeue(data)) { \
		codeBody \
	} \
}
// clang-format on

// Empties the queue entirely to fix weird segfaults
// clang-format off
#define CLEAN_QUEUE(Flag) { \
	Protocol::Struct_##Flag data; \
	while (Queue_##Flag.try_dequeue(data)) {}; \
}
// clang-format on

#include <atomic>
#include <condition_variable>
#include <errno.h>
#include <memory>
#include <stdio.h>
#include <stdlib.h>
#include <exception>
#include <string.h>
#include <chrono>
#include <thread>
#include <functional>
#include <unistd.h>
#include <unordered_map>

#ifdef __SWITCH__
#include <plog/Log.h>
#endif

#ifdef CLIENT_IMP
#include <wx/wx.h>
#endif

#include "include/zpp.hpp"
#include "include/concurrentqueue.h"

// Active sockets are the client
#ifdef SERVER_IMP
#include "thirdParty/clsocket/PassiveSocket.h"
#endif
#include "thirdParty/clsocket/ActiveSocket.h"
#include "serializeUnserializeData.hpp"
#include "networkingStructures.hpp"

#define SERVER_PORT 6978

#define SOCKET_TIMEOUT_SECONDS 1
#define SOCKET_TIMEOUT_MICROSECONDS 0

class CommunicateWithNetwork {
private:
#ifdef SERVER_IMP
	CPassiveSocket listeningServer;
#endif

	using E = CSimpleSocket::CSocketError;

	std::atomic_bool connectedToSocket;
	std::atomic_bool otherSideDisconnected;

	std::atomic_bool networkError;

	CSimpleSocket::CSocketError lastError;

	std::shared_ptr<std::thread> networkThread;
	std::shared_ptr<std::thread> readThread;

	std::function<void(CommunicateWithNetwork*)> sendQueueDataCallback;
	std::function<void(CommunicateWithNetwork*)> recieveQueueDataCallback;

	std::mutex ipMutex;
	std::condition_variable cv;

#ifdef CLIENT_IMP
	std::string ipAddress;
#endif

	// Whether to keep going
	// this can be set by anybody and will determine if networking continues
	std::atomic_bool keepReading;

	bool handleSocketError(const char* extraMessage);
	void handleFatalError();
#ifdef CLIENT_IMP
	void waitForIPSelection();
#endif

	void readFunc();
	void writeFunc();

	void yieldThread() {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

public:
	// Protcol for serializing
	SerializeProtocol serializingProtocol;
	CActiveSocket* networkConnection;

	ADD_QUEUE(SendFrameData)
	ADD_QUEUE(RecieveGameFramebuffer)
	ADD_QUEUE(RecieveGameInfo)
	ADD_QUEUE(SendFlag)
	ADD_QUEUE(SendLogging)
	ADD_QUEUE(RecieveLogging)
	ADD_QUEUE(RecieveFlag)
	ADD_QUEUE(RecieveApplicationConnected)
	ADD_QUEUE(SendTrackMemoryRegion)
	ADD_QUEUE(SendSetNumControllers)
	ADD_QUEUE(RecieveMemoryRegion)
	ADD_QUEUE(SendAddMemoryRegion)
	ADD_QUEUE(SendStartFinalTas)
	ADD_QUEUE(SendFinalTasChunk)

	CommunicateWithNetwork(std::function<void(CommunicateWithNetwork*)> sendCallback, std::function<void(CommunicateWithNetwork*)> recieveCallback);

#ifdef CLIENT_IMP
	uint8_t attemptConnectionToServer(std::string ip);
#endif

#ifdef SERVER_IMP
	void waitForNetworkConnection();
#endif

	void prepareNetworkConnection();

	// Called in the network thread
	void listenForCommands();

	bool readData(void* data, uint32_t sizeToRead);
	bool sendData(void* data, uint32_t sizeToSend);

	void initNetwork();

	void endNetwork();

	// This returns true ONCE, it sets the flag to false when it returns true
	// This prevents false retriggers
	bool hasOtherSideJustDisconnected();

	bool isConnected() {
		return connectedToSocket;
	}

	std::string getLastErrorMessage() {
		networkConnection->TranslateSocketError();
		CSimpleSocket::CSocketError error = networkConnection->GetSocketError();
		return std::string(networkConnection->DescribeError(error));
	}

#ifdef CLIENT_IMP
	std::string getSwitchIP() {
		return ipAddress;
	}
#endif

	// This stuff needs to be global for callback reasons
	uint32_t dataSize;
	DataFlag currentFlag;
	uint8_t* dataToRead;
};