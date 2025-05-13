#include <Arduino.h>
#include <dxlr01.h>
#include <yydora_message_manager.h>
#include <DHT.h>

#define BAUDRATE 9600
#define DHT11_PIN 4

DXLR01 loraModule(BAUDRATE);
YYDoraMessageManager manager(&loraModule);
DHT dht11(DHT11_PIN, DHT11);

int count = 0;

int getCount() {
	count++;
	if(count > 9999) {
		count = 0;
	}
	return count;
}

void setup() {
	dht11.begin();

}

void loop() {
	float h = dht11.readHumidity();
	float t = dht11.readTemperature();
	// printf("Hello One.\n");
	if(loraModule.isAvailable) {
		// printf("Hello Two.\n");
		char snd[200] = {0};
		sprintf(snd, "H%.1fT%.1f", h, t);
		manager.send(snd);
	}
	delay(2000);
}