#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <memory>
#include <forward_list>

#pragma once

struct PassthroughRoute {
	const char* path;
	const char* command;
	const char** parameters;
	const size_t parameterCount;
	
	template<size_t N>
	static constexpr PassthroughRoute&& makeRoute(
		const char* path,
		const char* command,
		const char* (&parameters)[N]){
		return PassthroughRoute(path, command, parameters, N);
	}
private:
	constexpr PassthroughRoute(const char* path, const char* command, const char** parameters, size_t parameterCount)
		: path(path), command(command), parameters(parameters), parameterCount(parameterCount) {}

public:
	constexpr PassthroughRoute(const char* path, const char* command)
		: path(path), command(command), parameters(nullptr), parameterCount(0) {}


	// template <size_t N>
	// constexpr PassthroughRoute(const char* path, const char* command, const char* (&parameters)[N]);
	
	// delete copy constructor and assignment operator
	PassthroughRoute(const PassthroughRoute&) = delete;
	PassthroughRoute& operator=(const PassthroughRoute&) = delete;
	// default move constructor and assignment operator
	constexpr PassthroughRoute(PassthroughRoute&& other)
		: path(other.path), command(other.command), parameters(std::move(other.parameters)), parameterCount(other.parameterCount) {}
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
	bool isAuthorized();
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
	void start();
	void loop();
};


