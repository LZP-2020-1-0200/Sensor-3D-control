
#include <httpToSerial.h>
#include <LittleFS.h>




static const String base64_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

String b64_decode(String& str) {
	String decoded;
	decoded.reserve(str.length());
	int bitsWritten = 0;
	uint16_t bits = 0;
	// add a maximum length to avoid infinite loops
	for (size_t i = 0; i < str.length() && i < 500; i++) {
		auto c = str[i];
		auto pos = base64_table.indexOf(c);
		if (pos == -1) {
			continue;
		}
		bits = (bits << 6) | pos;
		bitsWritten += 6;
		if (bitsWritten >= 8) {
			bitsWritten -= 8;
			decoded += (char)(bits >> (bitsWritten));
		}
	}
	return decoded;
}

HttpToSerial::HttpToSerial(
	HardwareSerial& serial,
	size_t serialBaud,
	size_t httpPort,
	const char* mdnsName,
	const char* access_user,
	const char* access_password,
	PassthroughRoute* routes,
	size_t routeCount)
	: serial(serial),
	serialBaud(serialBaud),
	httpPort(httpPort),
	mdnsName(mdnsName),
	server(httpPort),
	access_user(access_user),
	access_password(access_password),
	routes(routes),
	routeCount(routeCount) {
	}

HttpToSerial::~HttpToSerial() {
	server.stop();
}

void HttpToSerial::log(const String& message) {
	if(logBuffer.length() > 1000) {
		logBuffer = logBuffer.substring(500);
	}
	logBuffer += message;
}

void HttpToSerial::start() {
	serial.setTimeout(3000);
	serial.begin(serialBaud);
	serial.readString();
	if (MDNS.begin("esp8266")) {              // Start the mDNS responder for esp8266.local
		//serial.println("mDNS responder started");
	} else {
		//serial.println("Error setting up MDNS responder!");
	}
	//serial.println("Hello World!");
	//serial.flush();

	// Route for root / web page
	server.on("/", HTTP_GET, [this]() {
		if(!isAuthorized()) {
			return;
		}
		//serial.println("HTTP request received");

		File page = LittleFS.open("/pages/index.html", "r");
		server.send(200, "text/html", page);
	});
	
	// send a custom command to the serial device
	server.on("/serial", HTTP_GET, [this]() {
		if(!isAuthorized()) {
			return;
		}
		serial.print("\r\n");
		serial.flush();
		serial.readString();
		auto serialData = server.arg("data");
		String decoded = b64_decode(serialData);
		serial.print(decoded+"\r\n");
		serial.flush();
		String response = serial.readStringUntil('\r');
		server.send(200, "text/plain", response);
	});
	server.on("/log", HTTP_GET, [this]() {
		if(!isAuthorized()) {
			return;
		}
		server.send(200, "text/plain", logBuffer);
		logBuffer.clear();
	});
	// Routes for passthrough commands
	for(size_t j=0; j<routeCount; j++) {
		PassthroughRoute& route = routes[j];
		server.on(route.path, HTTP_GET, [this, &route]() {
			if(!isAuthorized()) {
				return;
			}
			serial.print("\r\n");
			serial.flush();
			serial.readString();
			
			// print command
			serial.print(route.command);

			// print parameters if any
			auto routeParameters = route.parameters;
			for(size_t i=0; i<route.parameterCount; i++) {
				auto parameter = server.arg(routeParameters[i]);
				serial.print(" ");
				serial.print(parameter);
				serial.print("\r\n");
				serial.flush();
				serial.readString();
			}
			
			
			serial.print("\r\n");
			serial.flush();
			log(String(route.command) + " --> ");
			String response = serial.readStringUntil('\r');
			log(response + "\r\n");
			server.send(200, "text/plain", response);
		});
	}

	server.onNotFound([this]() {
		//serial.println("HTTP request received");
		server.send(404, "text/plain", "Not found");
	});
	server.begin();
	
	// Add service to MDNS-SD
	MDNS.addService("http", "tcp", 80);
}

void HttpToSerial::loop() {
	server.handleClient();
	MDNS.update();
}


bool HttpToSerial::isAuthorized() {
	auto authHeader = server.header("Authorization");
	String decoded;
	authHeader.trim();
	if (!authHeader.startsWith("Basic ")) {
		//serial.println("No Authorization header");
		server.sendHeader("WWW-Authenticate", "Basic realm=\"Secure Area\"");
		server.send(401, "text/plain", "Authentication required");
		return false;
	}
	authHeader.remove(0, 6);
	authHeader.trim();
	decoded = b64_decode(authHeader);
	decoded.indexOf(":");
	auto username = decoded.substring(0, decoded.indexOf(":"));
	auto password = decoded.substring(decoded.indexOf(":")+1);
	if(username != access_user || password != access_password) {
		server.sendHeader("WWW-Authenticate", "Basic realm=\"Secure Area\"");
		server.send(401, "text/plain", "Authentication required");
		return false;
	}
	return true;
}