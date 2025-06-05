# Conexão Solidária – Códigos para envio e recebimento de mensagens via BLE

Este repositório contém dois códigos para ESP32 utilizando Bluetooth Low Energy (BLE) com formato JSON. Eles fazem parte do projeto **Conexão Solidária**, que propõe uma rede de comunicação offline para situações de emergência.

## 🔄 Contexto

Durante enchentes, deslizamentos, queimadas ou apagões, a comunicação pela internet pode ser interrompida. O projeto utiliza dispositivos BLE (como ESP32) para criar nós de retransmissão e leitura de mensagens, formando uma rede local resiliente.
Os codigos foram rodados no ArduinoIDE e feitos com a placa fisica ESP32
Os arquivos abaixo fazem parte da prova de conceito dessa rede:

---

## 🚨 `EnviarAlertaDefesaCivil.ino`

Este código envia um alerta predefinido através de BLE.

### 🔊 O que ele faz:

* Inicia um servidor BLE com um `serviceUUID` e `characteristicUUID`.
* Envia uma mensagem com estrutura JSON no formato:

```json
{
  "uuid": "msg-esp32",
  "conteudo": "CUIDADO! EVENTOS EXTREMOS NA SUA REGIÃO",
  "timestamp": "2025-06-05T18:00:00Z",
  "origin": "esp32"
}
```

* Essa mensagem pode ser lida por um app mobile da população, usando BLE.

### 📲 Aplicativo

Qualquer aplicativo (como o **Conexão Solidária** ou o **nRF Connect**) pode se conectar ao ESP32 e ler esse alerta automaticamente.

---

## 📃 `ReceberMensagemTerminal.ino`

Este código recebe mensagens via BLE, simulando o funcionamento de um nó BLE intermediário (como um celular).

### 🔊 O que ele faz:

* Escuta uma `characteristic` com permissão de escrita (WRITE)
* Quando uma mensagem em JSON é recebida, ele:

  * Decodifica
  * Imprime no terminal serial a estrutura completa

### ✅ Exemplo de JSON enviado pelo app `nRF Connect`:

```json
{
  "uuid": "teste-123",
  "conteudo": "Mensagem recebida!",
  "timestamp": "2025-06-05T18:15:00Z",
  "origin": "celular"
}
```

### ✅ Resultado no serial:

```
📩 Mensagem recebida via BLE:
{"uuid":"teste-123","conteudo":"Mensagem recebida!","timestamp":"2025-06-05T18:15:00Z","origin":"celular"}
🗒 JSON Interpretado:
UUID: teste-123
Conteúdo: Mensagem recebida!
Timestamp: 2025-06-05T18:15:00Z
Origem: celular
```

---

## 🤝 Integração com o projeto maior

No projeto completo da **Conexão Solidária**, o ESP32 pode ser utilizado como retransmissor fixo (em postes, escolas, abrigos), permitindo que mensagens entre celulares alcancem distâncias maiores.

* O `EnviarAlertaDefesaCivil.ino` representa a **origem de um alerta** vindo da Defesa Civil
* O `ReceberMensagemTerminal.ino` representa a **recepção e validação local de mensagens** do app

---

## 🏡 Requisitos para compilar

* ESP32
* ArduinoJson (via Library Manager)
* Biblioteca BLE nativa da placa ESP32 (instalada ao adicionar ESP32 no Arduino IDE)

---

## 📁 Estrutura

```
conexao-solidaria-ble/
├── EnviarAlertaDefesaCivil.ino         # Envia alerta fixo via BLE
├── ReceberMensagemTerminal.ino        # Recebe mensagens JSON via BLE
└── README.md                          # Este arquivo
```

---

## Grupo:
Lu Vieira Santos, Diego Furigo do Nascimento, Melissa Pereira
