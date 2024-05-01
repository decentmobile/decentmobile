  #include <LoRa_E220.h>

//  Важно! Удалить EspSoftwareSerial версии 6, установить release 6.15.1 версию или выше
// ----------   WEMOS D1 MINI   --------   LORA МОДУЛЬ ------------
//              GND                        GND
//              D4                         VCC     !!!!!! ВАЖНО !!!!!!!! СОЕДИНИТЬ ПРОВОДОМ С 3V3 !!!!!!!!!!!!!
//              D3                         AUX
//              D2                         TX
//              D1                         RX
//              RX                         M1
//              TX                         M0
// --------------------------------------- настройки репитера ---------------------------------------------------------
#define myname "100"                                                              // имя-номер станции
#define region "RU-KRD"                                                           // регион
// ---------------------------------------------------------------------------------------------------------------------
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <SoftwareSerial.h>
#include <EEPROM.h>
#include <WebSocketsServer.h>
// ---------------------------------------------------------------------------------------------------------------------
#define buflength 15000                                                           // объём памяти под хранение всех сообщений
#define deadline 14000                                                            // граница, по заполнению которой надо очищать память
#define bytestoclear 2000                                                         // объём памяти для очистки
#define idlen                     9                                               // количество знаков в ID
#define lines_in_raw              7                                               // количество строк в исходном сообщении
#define incoming_buffer_size      512                                             // 0.5 кбайт - размер буфера под "сырое" сообщение
#define outgoing_buffer_size      2048                                            // 2 кбайт - размер буфера под все исходящие сообщения
#define message_ids               100                                             // id скольких сообщений хранить
// ------------------------- строки в принятом сообщении --------------------------------------------------------------
#define MESSAGE_SENDER            0                                               // порядковый номер строки
#define MESSAGE_RECIEVER          1                                               // порядковый номер строки
#define MESSAGE_JUMPS             2                                               // порядковый номер строки
#define MESSAGE_TYPE              3                                               // порядковый номер строки
#define MESSAGE_ID                4                                               // порядковый номер строки
#define MESSAGE_REGION            5                                               // порядковый номер строки
#define MESSAGE_TEXT              6                                               // порядковый номер строки
// ---------------------------------- начало и конец сообщения ---------------------------------------------------------
#define terminator                0xFF                                            // символ окончания сообщения - 0xFF
#define startsymbol               0xFE                                            // символ начала сообщения - 0xFE
// ---------------------------------------------------------------------------------------------------------------------
#define DNS_PORT 53                                                               // 53 порт DNS
#define PIN_M0          1                                                         // TX - GPIO1
#define PIN_M1          3                                                         // RX - GPIO3
#define PIN_RXM         5                                                         // D1 - GPIO5
#define PIN_TXM         4                                                         // D2 - GPIO4
#define PIN_AUX         0                                                         // D3 - GPIO0
#define PIN_D4          2                                                         // На D4 надо подать высокий сигнал!
#define store           10                                                        // сигнал о том, что данные модуля уже сохранялись
SoftwareSerial SoftPort(PIN_TXM, PIN_RXM);                                        // Пины RX и TX ESP8266, соответственно TX и RX LoRa-модуля
ESP8266WebServer server;
const char tocompare[] = {0xef,0xbf,0xbf,'\0'};                                   // эти три байта - Unicode-символ разделителя
WebSocketsServer websocket = WebSocketsServer(81);                                // 81 порт
char ssidAP[] = "DECENT mobile";                                                  // SSID
char passwordAP[] = "";
IPAddress local_ip(10,66,66,1);                                                      // ip сервера
IPAddress gateway(10,66,66,1);                                                       // ip шлюза
IPAddress subnet(255,255,255,0);
#include "buildpage.h"                                                            // файл с html-кодом, JS и CSS
char storeddata [buflength] = {0};                                                // буфер сообщений, предназначающихся для отправки в браузер по вебсокету
DNSServer dnsServer;
char data[incoming_buffer_size] = {0};                                            // буфер данных, максимум incoming_buffer_size символов
char data0[incoming_buffer_size] = {0};                                           // буфер данных из com-порта, максимум incoming_buffer_size символов
uint16_t byte_income = 0;                                                         // счётчик принятых символов
uint16_t byte_income0 = 0;                                                        // счётчик принятых символов из com-порта
char outgoing[outgoing_buffer_size] = {0};                                        // буфер исходящих данных, максимум - outgoing_buffer_size символов
uint16_t bytes_to_send = 0;                                                       // счётчик символов исходящих сообщений
int r = 0;                                                                        // произвольное время задержки от получения до отправки
uint32_t id[message_ids];                                                         // массив для хранения ID последних сообщений
int id_id = 0;                                                                    // номер текущего принятого сообщения (используется для массива id)
uint32_t wait_for_send = 0;                                                       // таймер для отправки сообщения
uint32_t myTimer = 0;                                                             // таймер для маяка
uint32_t SignalTimer = 0;                                                         // таймер для показа уровня сигнала (антеннок)
uint16_t parse[lines_in_raw-1];                                                   // массив с адресами переводов строки (6 адресов на 7 строк)
int8_t signal = 0;                                                                // уровень сигнала (антеннок)

void setup()
{
  pinMode(PIN_D4, OUTPUT);                                                        // ПИН D4 - обязателен высокий сигнал, к нему же подпаян плюс.
  digitalWrite(PIN_D4, HIGH);                                                     // Так нужно!
  pinMode(PIN_AUX, INPUT);                                                        // Вход AUX
  pinMode(PIN_M0, FUNCTION_3);                                                    // Превращаем пин TX в GPIO
  pinMode(PIN_M1, FUNCTION_3);                                                    // Превращаем пин RX в GPIO
  pinMode(PIN_M0, OUTPUT);                                                        // Это - два пина режима - М0 и М1, оба должны
  pinMode(PIN_M1, OUTPUT);                                                        // быть подтынуты к нулю для приёма-передача и к единице для конфигурирования
  EEPROM.begin(1);                                                                // размер 1 байт
  byte v0 = EEPROM.read(0);                                                       // данные в EEPROM(на самом деле flash) по адресу 0;
  byte v1 = EEPROM.read(1);                                                       // данные в EEPROM(на самом деле flash) по адресу 1;
  byte v2 = EEPROM.read(2);                                                       // данные в EEPROM(на самом деле flash) по адресу 2;
  SoftPort.begin(9600);                                                           // Скорость порта
  if ((v0 != store) && (v1 != store) && (v2 != store)){                           // не конфигурировали - конфигурируем
        digitalWrite(PIN_M0, HIGH);
        digitalWrite(PIN_M1, HIGH);                                               // вход в режим конфигурирования
        delay(1000);                                                              // задержка перед конфигурированием
        byte message[] = {0xC0, 0x00, 0x08, 0xFF, 0xFF, 0x60, 0x40, 0x13, 0x04, 0x00, 0x00};                           // C0 - постоянно, сохранить
        // byte message[] = {0xC2, 0x00, 0x08, 0xFF, 0xFF, 0x64, 0x40, 0x12, 0x04, 0x00, 0x00};                        // C2 - временно
        SoftPort.write(message, sizeof(message));                                 // записали и сохранили параметры в LoRa-модуль
        delay(5000);                                                              // нужна задержка после конфигурации
        EEPROM.write(0, store);                                                   // Запись в EEPROM
        EEPROM.write(1, store);                                                   // Запись в EEPROM
        EEPROM.write(2, store);                                                   // Запись в EEPROM
        EEPROM.commit();                                                          // и сохранение
  }
  digitalWrite(PIN_M0, LOW);                                                      // Включаю режим приёма-передачи
  digitalWrite(PIN_M1, LOW);                                                      // Включаю режим приёма-передачи
  WiFi.mode(WIFI_AP);                                                             // режим точки доступа
  WiFi.hostname("decentmobile");
  delay(1000);                                                                    // нужно подождать
  WiFi.softAPConfig(local_ip, gateway, subnet);
  WiFi.softAP(ssidAP, passwordAP);                                                // инициализация Wi-Fi
  server.begin();                                                                 // инициализация веб-сервера
  server.on("/", base);                                                           // главная страница
  server.on("/generate_204", redirect);                                           // android captive portal redirect
  server.on("/redirect", redirect);                                               // microsoft redirect
  server.on("/hotspot-detect.html", redirect);                                    // apple call home
  server.on("/canonical.html", redirect);                                         // firefox captive portal call home
  server.on("/success.txt", base);                                                // firefox captive portal call home
  server.on("/ncsi.txt", redirect);                                               // windows call home
  server.on("/wifi_client", wifi_form);                                           // страница подключения к wi-fi
  server.on("/wifi_connect", wifi_connect);                                       // обработчик подключения к wi-fi
  server.onNotFound(notfound);
  websocket.begin();                                                              // инициализация WebSocket
  websocket.onEvent(wsEvent);
  dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
  dnsServer.start(DNS_PORT, "*", local_ip);
}

void getuart(){
  // -----------------------------------------------------------------------------------------------------------------------------------
  if (SoftPort.available()) {
//    if(signal == 0){
//      signal = 1;
//    };
    data[byte_income] = SoftPort.read();                                          // заполняем буфер
    if ((byte_income < 3) && (data[byte_income] != startsymbol)){
        memset(data, 0, 3);                                                       // обнуление первых трёх байт
        byte_income = 0;
    } else{
        byte_income = byte_income + 1;                                            // номер следующей ячейки для заполнения.
    }
  }
  // если получили хотя бы 20 байт, три из которых - startsymbol и последние три - terminator, можно парсить
  if (
      (byte_income > 20) 
  and (data[byte_income-1] == terminator) 
  and (data[byte_income - 2] == terminator) 
  and (data[byte_income - 3] == terminator)
  and (data[0] == startsymbol)
  and (data[1] == startsymbol)
  and (data[2] == startsymbol)
  ){
    data[byte_income - 3] = '\0';                                                 // обозначаем конец строки вместо символа terminator
    char* line[lines_in_raw];                                                     // это - массив указателей (каждая линия - новое поле)
    // находим 'lines_in_raw' (6) первых символов NewLine и запоминаем их значения
    uint16_t i = 0;
    boolean formatok = false;                                                     // изначально считаем формат пришедшего сообщения неверным
    for (uint16_t jj = 0; jj < byte_income - 1; jj++){
      if (data[jj] == '\n'){
        data[jj] = '\0';                                                          // вместо символа \n (NewLine) ставим ноль
        parse[i] = jj;                                                            // и запоминаем номер этого символа
        i++;
        if (i == lines_in_raw - 1){                                               // если переводов строк на 1 меньше, чем всего строк - прекращаем парсинг,
          formatok = true;                                                        // поднимаем флаг правильного формата
          break;                                                                  // остальное будем считать самим сообщением
        }
      }
    }
    line[MESSAGE_SENDER] = data+3;                                                // первый элемент начинается с 3 символа 
    for (i = 1; i <= lines_in_raw; i++){                                          // остальные элементы
      line[i] = data + parse[i-1]+1;
    }
    uint32_t temp_id = atoi(line[MESSAGE_ID]);                                    // id данного сообщения в виде числа
    boolean NEW_MESSAGE = true;                                                   // флаг нового сообщения
    for (int iii = 0; iii < id_id; iii++){                                        // пробежали по массиву ID предыдущих сообщений
        if (id[iii] == temp_id){                                                  // и если id уже встречался - 
            NEW_MESSAGE = false;                                                  // помечаем сообщение как "не новое".
            break;
        }
    }
    byte local = false;                                                           // считаем регион "чужим"
    if (!strcmp(line[MESSAGE_REGION], region)){                                   // если полученное сообщение предназначено для "своего" региона
        local = true;
    }
    if (  (!NEW_MESSAGE) and                                                      // если пришедшее сообщение - повтор (не новое сообщение == репитер ответил),
          (temp_id > 0) and                                                       // ID - число
          (formatok == true) and                                                  // формат сообщения верный (есть нужное количество переводов строк)
          (strlen(line[MESSAGE_JUMPS]) == 1)                                      // и количество прыжков - 1 символ
       )  {
          char cloud[23] = {"\0"};                                                // строка для отправки в вебсокет
          strcat(cloud, tocompare);                                               // маркер начала
          strcat(cloud, "cloud\n");                                               // "cloud"
          strcat(cloud, line[MESSAGE_ID]);                                        // ID - номер, например, 123456789
          strcat(cloud, tocompare);                                               // маркер конца
          websocket.broadcastTXT(cloud, strlen(cloud));                           // отправляем в вебсокет...
          if (  (signal < 5)  and  (id[id_id-1] == temp_id)  ){                   // если это - старое сообщение и оно последнее в списке, то   
            signal++;                                                             // увеличиваем количество "антеннок" на 1.
          }
    }
    if (  (NEW_MESSAGE) and                                                       // если пришедшее сообщение идентифицировано как новое
          (temp_id > 0) and                                                       // ID - число
          (formatok == true) and                                                  // формат сообщения верный (есть нужное количество переводов строк)
          (strlen(line[MESSAGE_JUMPS]) == 1)                                      // и количество прыжков - 1 символ
       )  {
        signal = 1;                                                               // новое сообщение -> количество антеннок = 1.
        // ------------------------------------------- готовим сообщение для отправки в WebSocket ----------------------------------------
        // вместо символа '\0' ставим '\n' (NewLine)
        for (byte bb = 0; bb < lines_in_raw - 1; bb++){
          data[parse[bb]] = '\n';                                                          
        };
        // меняем начало и конец сообщения на разделитель для JS - Unicode uffff
        data[0] = 0xef;
        data[1] = 0xbf;
        data[2] = 0xbf;
        data[byte_income - 3] = 0xef;
        data[byte_income - 2] = 0xbf;
        data[byte_income-1] = 0xbf;
        data[byte_income] = '\0';
        if (is_utf8(data)){
          websocket.broadcastTXT(data, strlen(data));                             // отправляем в вебсокет
          strcat(storeddata, data);                                               // добавляем текущее сообщение в массив сообщений
          managememory();                                                         // при необходимости очищаем память
        }
        // ------------------------------------------- преобразуем изменённые байты обратно ----------------------------------------
        // вместо символа '\n' ставим '\0' (конец "строки")
        for (byte bb = 0; bb < lines_in_raw - 1; bb++){
          data[parse[bb]] = '\0';                                                          
        };
        data[byte_income - 3] = '\0';                                             // конец текста тела сообщения
        // меняем начало и конец сообщения с uffff на startsymbolx3 и endsymbol
        data[0] = startsymbol;
        data[1] = startsymbol;
        data[2] = startsymbol;
        //data[byte_income - 3] = endsymbol; // этот символ трогать нельзя!
        data[byte_income - 2] = terminator;
        data[byte_income-1] = terminator;
        // -------------------------------- сообщение преобразовали для дальнейшей обработки -------------------------------------
        byte jump_t = (byte)atoi(line[MESSAGE_JUMPS]);                            // получили количество прыжков (дальность)
        id[id_id]=temp_id;                                                        // занесли в массив "ID" id данного сообщения
        id_id++;                                                                  // и увеличили id_id на 1
        if (id_id >=message_ids){
            id_id = 0;                                                            // обнуляем id_id если произошло переполнение
        }
        if (local){                                                               // если сообщение для домашней сети...
            // работаем как репитер: данное сообщение перенаправляем дальше
            int jump_c = atoi(line[MESSAGE_JUMPS]);
            if (jump_c > 9) {jump_c = 0;}
            if (jump_c > 0){                                                                          
                // если количество прыжков не закончилось
                jump_c = jump_c - 1;
                itoa(jump_c, line[MESSAGE_JUMPS], DEC);
                for (int ii = 0; ii < lines_in_raw-1; ii++){                      // или -2
                    data[parse[ii]] = '\n';
                }
                data[byte_income - 3] = terminator;
                // подготовили Data - можно отправлять дальше
                for(int v = 0; v < byte_income; v++){
                    //Serial.print(data[v]);
                    outgoing[bytes_to_send] = data[v];                            // побайтный перенос в буфер для отправки
                    bytes_to_send++;                                              // инкремент номера следующего байта в буфере отправки
                }                
            }
        } else {
            // сообщение предназначено для другого региона - надо задействовать интернет...
        }
    }
    // операции с сообщением закончены - удаляем принятые байты
    memset(data, 0, incoming_buffer_size);
    memset(parse, 0, lines_in_raw);
    byte_income = 0;                                                              // счётчик принятых символов
  }
}

void loop()
{
    dnsServer.processNextRequest();
    server.handleClient();        // manage HTTP requests
    websocket.loop();         // handle WebSocket
    getuart();
    // ----------------------------------------------------------------------------------------------------------------------------------------
    if (bytes_to_send > 0) {                                                      // если буфер отправки не пустой (есть что отправлять)...
        if (r == 0){                                                              // в первый раз
            wait_for_send = millis();                                             // смотрим на время
            randomSeed(millis());
            r = random(50, 600);                                                  // и придумываем произвольную задержку от 50 до 600 msec
        }
        // ведём передачу не глядя, ведёт ещё кто-то или нет (на практике это не нужно)
        if (millis() - wait_for_send >= r) {                                      // как только время пришло
            for(int d = 0; d < bytes_to_send; d++){
                SoftPort.print(outgoing[d]);                                      // весь буфер - в эфир
            }
            memset(outgoing, 0, bytes_to_send);                                   // очистка всего буфера отправки
            bytes_to_send = 0;                                                    // обнуление номера первого байта буфера отправки
            r = 0;
        }
    }
    // -------------------------------------------------------------------------------------------------------------------------------------------------    
    if (millis() - myTimer >= 5 * 3600 * 1000) {                                  // каждые 5 часов
        myTimer = millis();
        char mayak[] = myname;                                                    // маячок (имя ретранслятора)
        byte l = strlen(myname);                                                  // длина имени ретранслятора
        for(int f = 0; f < l; f++){
            outgoing[bytes_to_send] = mayak[f];                                   // побайтный перенос в буфер для отправки
            bytes_to_send++;                                                      // инкремент номера следующего байта в буфере отправки
        }
    }
    // -------------------------------------------------------------------------------------------------------------------------------------------------
    if (millis() - SignalTimer >= 1500) {                                         // каждые 1.5 секунды
        SignalTimer = millis();
        if (signal >= 0) {
          char tmp[15];                                                           //
          strcat(tmp, tocompare);                                                 // маркер начала
          strcat(tmp, "signal\n");
          char val[2];
          itoa(signal, val, DEC);
          strcat(tmp, val);
          strcat(tmp, tocompare);                                                 // маркер конца
          websocket.broadcastTXT(tmp, strlen(tmp));                               // отправляем в вебсокет...
          //signal--;
        } else {
          websocket.broadcastPing();
        }
    };
}

void base()                                                                       // отдать стартовую страницу
{
  //server.send (200, "text/html", page);
  server.setContentLength(CONTENT_LENGTH_UNKNOWN);
  server.send(200, "text/html", "");
  server.sendContent_P(page);
}

void wifi_connect()
{
  String ssid = server.arg("ssid");                                               // забираем SSID
  String password = server.arg("password");                                       // ...пароль
  String hostname = server.arg("hostname");                                       // ...и имя хоста

  WiFi.softAPdisconnect(true);                                                    // отключаем точку доступа
  WiFi.hostname(hostname.c_str());                                                // ставим имя хоста
  WiFi.mode(WIFI_STA);                                                            // переключение нашего Wi-Fi модуля в режим клиента
  WiFi.begin(ssid.c_str(), password.c_str());                                     // подключаемся...
  delay(1000);
}

void wifi_form() {
  // рисуем форму для SSID, пароля и хостнейма
  server.send(200, "text/html", "<form action=\"/wifi_connect\" method=\"POST\">SSID: <input type=\"text\" name=\"ssid\"><br>Password: <input type=\"password\" name=\"password\"><br>Hostname: <input type=\"text\" value=\"decentmobile\" name=\"hostname\"><br><input type=\"submit\" value=\"Connect\"></form>");
}


void managememory(){
  if (strlen(storeddata) >= deadline){                                            // если перешли границу
    char *newfirst = strstr(storeddata+bytestoclear, tocompare);                  // нулевой элемент массива, начинающийся с xff, но после 3000 байт
    int startfrom = newfirst - storeddata;                                        // с этого байта начинаем
    for (int i = 0; i < buflength; i++){
      if (i+startfrom < buflength){
        storeddata[i] = storeddata[i+startfrom];                                  // освобождаем память
      } else{                                                                     // оставшееся место
        storeddata[i] = '\0';                                                     // затираем нулями
      }
    };
  }
}

void notfound() {
  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  server.sendHeader("Pragma", "no-cache");
  server.sendHeader("Expires", "-1");
  server.send(404, "text/html", page);
}

void redirect() {
    server.sendHeader("Location", "http://10.66.66.1", true);
    server.send(302, "text/plain", "");   
    server.client().stop(); 
}

void wsEvent(uint8_t num, WStype_t type, uint8_t * message, size_t length)
{
  if(type == WStype_TEXT)                                                         // браузер нам что-то передал...
  {
  // проверяем на количество переводов строк ищем 3-й перевод строки
  boolean formatok = false;
  int positionofID = 0;
  byte ncount = 0;
  char idstr[10];
  for (int u = 0; u < length; u++){
    if (message[u] == '\n') {
      ncount++;
      if (ncount == 4){
        positionofID = u + 1;
      }
    }
    if (ncount > 5){
      formatok = true;
      break;
    }
  }
  // если получили хотя бы 20 байт, три первых и три последних - unicode-последовательность, соответствующая разделителю...
  if (
    (length > 20) 
    and (message[0] == 0xef)
    and (message[1] == 0xbf)
    and (message[2] == 0xbf)
    and (message[length-3] == 0xef)
    and (message[length-2] == 0xbf)
    and (message[length-1] == 0xbf)
    and (formatok)
    and (positionofID > 0)
    ){
      strncpy(idstr, (char*)message+positionofID, 9);                          // сохранили в idstr ID текущего сообщения
      //websocket.broadcastTXT(idstr, strlen(idstr));
      uint32_t temp_id = atoi(idstr);                                          // id данного сообщения в виде числа
      boolean NEW_MESSAGE = true;                                              // флаг нового сообщения
      for (int iii = 0; iii < id_id; iii++){                                   // пробежали по массиву ID предыдущих сообщений
        if (id[iii] == temp_id){                                               // и если id уже встречался - 
          NEW_MESSAGE = false;                                                 // помечаем сообщение как "не новое".
          break;
        }
      }
      if (NEW_MESSAGE){                                                        // если этого сообщения не было ещё...
        signal = 0;                                                            // обнуляем "антеннки"
        id[id_id]=temp_id;                                                     // занесли в массив "ID" id данного сообщения
        id_id++;                                                               // и увеличили id_id на 1
        if (id_id >=message_ids){
            id_id = 0;                                                         // обнуляем id_id если произошло переполнение
        }
        websocket.broadcastTXT(message, length);                               // отправляем это сообщение всем, кто рядом с нами...
        int p = strlen(storeddata);                                            // длина
        for(int i=0; i<length; i++){                                           // strncpy из message в storeddata
          storeddata[p] = message[i];                                          // количество символов length
          p++;                                                                 // strncat(storeddata, (char*)message, length);
        };
        managememory();                                                        // при переполнении буфера часть его очищаем...
      };
      outgoing[bytes_to_send] = startsymbol;                                   // а это пойдёт в эфир...
      outgoing[bytes_to_send+1] = startsymbol;                                 // три символа - маркер
      outgoing[bytes_to_send+2] = startsymbol;                                 // начала сообщения
      strncat(outgoing, (char*)message+3, length - 6);                         // само сообщение
      outgoing[bytes_to_send+length-3] = terminator;                           // и 3 символа - маркер
      outgoing[bytes_to_send+length-2] = terminator;                           // конца
      outgoing[bytes_to_send+length-1] = terminator;                           // сообщения
      bytes_to_send = bytes_to_send + length;                                  // здесь - количество байт для отправки
    };
  }
  if (type == WStype_CONNECTED){
      websocket.sendTXT(num, storeddata);                                         // отправить весь буфер новому подключившемуся
  }
}

bool is_utf8(const char * string)
{
    if (!string)
        return true;
    const unsigned char * bytes = (const unsigned char *)string;
    int num;
    while (*bytes != 0x00)
    {
        if ((*bytes & 0x80) == 0x00)
        {
            // U+0000 to U+007F 
            num = 1;
        }
        else if ((*bytes & 0xE0) == 0xC0)
        {
            // U+0080 to U+07FF 
            num = 2;
        }
        else if ((*bytes & 0xF0) == 0xE0)
        {
            // U+0800 to U+FFFF 
            num = 3;
        }
        else if ((*bytes & 0xF8) == 0xF0)
        {
            // U+10000 to U+10FFFF 
            num = 4;
        }
        else
            return false;
        bytes += 1;
        for (int i = 1; i < num; ++i)
        {
            if ((*bytes & 0xC0) != 0x80)
                return false;
            bytes += 1;
        }
    }
    return true;
}
