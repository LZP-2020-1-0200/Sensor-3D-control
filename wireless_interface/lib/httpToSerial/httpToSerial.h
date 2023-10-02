#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <memory>
#include <WebSockets4WebServer.h>

#pragma once

struct PassthroughRoute {
	const char * const path;
	const char * const command;
	const char * const* const parameters;
	const size_t parameterCount;
	
	template<size_t N>
	static constexpr std::unique_ptr<PassthroughRoute> makeRoute(
		const char* const path,
		const char* const command,
		const char* (&parameters)[N]){
		return std::make_unique<PassthroughRoute>(PassthroughRoute(path, command, parameters, N));
	}
	constexpr PassthroughRoute(const char* path, const char* command, const char** parameters, size_t parameterCount)
		: path(path), command(command), parameters(parameters), parameterCount(parameterCount) {}

	constexpr PassthroughRoute(const char* path, const char* command)
		: path(path), command(command), parameters(nullptr), parameterCount(0) {}


	// template <size_t N>
	// constexpr PassthroughRoute(const char* path, const char* command, const char* (&parameters)[N]);
	
	// delete copy constructor and assignment operator
	PassthroughRoute(const PassthroughRoute&) = delete;
	PassthroughRoute& operator=(const PassthroughRoute&) = delete;
	// default move constructor and assignment operator
	constexpr PassthroughRoute(PassthroughRoute&& other)
		: path(other.path), command(other.command), parameters(other.parameters), parameterCount(other.parameterCount) {}
	PassthroughRoute& operator=(PassthroughRoute&&) = default;
};

class HttpToSerial
{
private:
	HardwareSerial& serial;
	size_t serialBaud;
	size_t httpPort;
	const char* mdnsName;
	ESP8266WebServer server;
	const char* access_user;
	const char* access_password;

	/// @brief web socket server for sending logs
	WebSockets4WebServer webSocketLogServer;

	
	/// @brief web socket server for receiving/sending messages
	WebSockets4WebServer webSocketSerialServer;

	/**
	 * @brief returns true if the user is authorized
	 * @details Responds with a 401 Unauthorized if the user is not authorized.
	 * @todo just return false if the user is not authorized, and let the caller handle the response
	*/
	bool isAuthorized();

	/**
	 * @brief web socket event handler for the log server
	 * generates a closure that can be passed to the webSocketServer function
	*/
	std::function<void(uint8, WStype_t, uint8_t*, size_t)> webSocketLogEvent();

	/**
	 * @brief web socket event handler for the serial server
	 * generates a closure that can be passed to the webSocketSerialServer function
	*/
	std::function<void(uint8, WStype_t, uint8_t*, size_t)> webSocketSerialEvent();
	
	PassthroughRoute* routes;
	size_t routeCount;
	String logBuffer="";
	void log(const String& message);
public:
	HttpToSerial(
		HardwareSerial& serial,
		size_t serialBaud,
		size_t httpPort,
		const char* mdnsName,
		const char* access_user,
		const char* access_password,
		PassthroughRoute* routes,
		size_t routeCount);
	~HttpToSerial();

	// move constructor
	HttpToSerial(HttpToSerial&&) = default;

	/**
	 * @brief Start the server
	 * 
	*/
	void start();

	/**
	 * @brief Loop function, call this in the main loop
	 * Handles all incoming requests, handles mDNS,
	 * handles serial communication
	*/
	void loop();
};


