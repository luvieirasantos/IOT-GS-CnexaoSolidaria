#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <ArduinoJson.h>

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

BLECharacteristic* pCharacteristic;
bool notifyEnviado = false;

void setup() {
  Serial.begin(115200);
  Serial.println("🔧 Iniciando BLE...");

  BLEDevice::init("ESP32-SOS");
  BLEServer* pServer = BLEDevice::createServer();
  BLEService* pService = pServer->createService(SERVICE_UUID);

  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_READ |
                      BLECharacteristic::PROPERTY_NOTIFY
                    );

  pCharacteristic->addDescriptor(new BLE2902());

  pService->start();
  BLEAdvertising* pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->start();

  Serial.println("✅ Pronto para enviar alerta via BLE...");
}

void loop() {
  if (!notifyEnviado) {
    StaticJsonDocument<256> doc;
    doc["uuid"] = "msg-esp32";
    doc["conteudo"] = "CUIDADO! EVENTOS EXTREMOS NA SUA REGIÃO";
    doc["timestamp"] = "2025-06-05T18:00:00Z";
    doc["origin"] = "esp32";

    String jsonStr;
    serializeJson(doc, jsonStr);

    pCharacteristic->setValue(jsonStr.c_str());
    pCharacteristic->notify();  // Envia notificação via BLE

    Serial.println("📡 Alerta enviado via BLE:");
    Serial.println(jsonStr);

    notifyEnviado = true;
  }

  delay(5000); // espera antes de terminar o loop
}
