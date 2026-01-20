#include <Arduino.h>
#include <WiFi.h>
#include <M5GFX.h>
#include <M5Unified.h>
#include <M5UnitENV.h>
#include <core_http_client.h>
#include <core_http_config.h>

const char *http_server_uri = "httpbin.org";
const int http_server_port = 80;

const char *ssid = "Freebox-27E579";
const char *password = "dztsbq9xdrqk4vcwqvwdsf";

typedef struct NetworkContext
{
  int socket;
} NetworkContext_t;

static int32_t transportSend(NetworkContext_t *pNetworkContext, const void *pBuffer, size_t bytesToSend)
{
  return 0;
}

static int32_t transportRecv(NetworkContext_t *pNetworkContext, void *pBuffer, size_t bytesToRecv)
{
  return 0;
}

static BaseType_t connectToServer(NetworkContext_t *pxNetworkContext)
{
  return pdPASS;
}

static BaseType_t disconnectFromServer(NetworkContext_t *pxNetworkContext)
{
  return pdPASS;
}

static BaseType_t sendHttpRequest(
    const TransportInterface_t *pxTransportInterface,
    const char *pcMethod,
    size_t xMethodLen,
    const char *pcPath,
    size_t xPathLen)
{
  return (BaseType_t)0;
}

static void prvHTTPDemoTask(void *pvParameters)
{
  (void)pvParameters;

  TransportInterface_t xTransportInterface;
  NetworkContext_t xNetworkContext = {0};
  BaseType_t isConnected = pdFALSE;
  BaseType_t xDemoStatus = pdPASS;

  xDemoStatus = connectToServer(&xNetworkContext);

  if (xDemoStatus == pdPASS)
  {
    isConnected = pdTRUE;

    xTransportInterface.pNetworkContext = &xNetworkContext;
    xTransportInterface.send = transportSend;
    xTransportInterface.recv = transportRecv;
  }
  else
  {
    LogError(("Failed to connect to HTTP server."));
  }

  // xDemoStatus = prvSendHttpRequest(&xTransportInterface, HTTP_METHOD_GET, HTTP_METH, , );

  if (xDemoStatus != pdPASS)
  {
    LogError(("HTTP Request failed."));
  }

  if (isConnected == pdTRUE)
  {
    disconnectFromServer(&xNetworkContext);
  }

  if (xDemoStatus == pdPASS)
  {
    LogInfo(("prvHTTPDemoTask() completed successfully. "
             "Total free heap is %u.\r\n",
             xPortGetFreeHeapSize()));
    LogInfo(("Demo completed successfully.\r\n"));
  }
}

void TaskBlue(void *pvParameters)
{
  // variable allouée dans la pile (*stack*) de la tâche et unique pour chaque instance de tâche
  int variable1;
  // boucle infinie (~= loop)
  for (;;)
  {
    Serial.printf("I'm blue and this is my core: %d\n", xPortGetCoreID());
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void setup()
{
  Serial.begin(115200);

  while (!Serial.available())
  {
    delay(100);
  }

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(100);
  }

  Serial.println("\nConnected to the WiFi network");
  Serial.print("Local ESP32 IP: ");
  Serial.println(WiFi.localIP());

  xTaskCreate(TaskBlue, "La tâche bleue", 1000, NULL, 1, NULL);
}

void loop()
{
  vTaskDelay(pdMS_TO_TICKS(1000));
}