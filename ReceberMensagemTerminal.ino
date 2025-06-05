#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <ArduinoJson.h>

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

BLECharacteristic* pCharacteristic;

class BLEMensagemCallback : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic* pChar) override {
    // Recebe o valor enviado via BLE como String do Arduino
    String value = pChar->getValue();

    Serial.println("📨 Mensagem recebida via BLE:");
    Serial.println(value);

    // Tenta interpretar o conteúdo como JSON
    StaticJsonDocument<256> doc;
    DeserializationError error = deserializeJson(doc, value);

    if (error) {
      Serial.print("❌ Erro ao interpretar JSON: ");
      Serial.println(error.c_str());
      return;
    }

    // Exibe os campos do JSON
    Serial.println("🧾 JSON Interpretado:");
    Serial.print("UUID: "); Serial.println(doc["uuid"].as<const char*>());
    Serial.print("Conteúdo: "); Serial.println(doc["conteudo"].as<const char*>());
    Serial.print("Timestamp: "); Serial.println(doc["timestamp"].as<const char*>());
    Serial.print("Origem: "); Serial.println(doc["origin"].as<const char*>());
  }
};

void setup() {
  Serial.begin(115200);
  Serial.println("🔧 Iniciando BLE para leitura...");

  BLEDevice::init("ESP32-RECEPTOR");
  BLEServer* pServer = BLEDevice::createServer();
  BLEService* pService = pServer->createService(SERVICE_UUID);

  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_WRITE
                    );

  pCharacteristic->setCallbacks(new BLEMensagemCallback());
  pCharacteristic->addDescriptor(new BLE2902());

  pService->start();
  BLEAdvertising* pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->start();

  Serial.println("✅ Aguardando mensagens JSON via BLE (use o app nRF Connect)");
}

void loop() {
  delay(1000); // Mantém o loop leve
}
