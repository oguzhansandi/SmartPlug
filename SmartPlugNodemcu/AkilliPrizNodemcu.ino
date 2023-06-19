#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#ifndef STASSID
#define STASSID "Oguzhan 2.4"
#define STAPSK "*****"
#endif
const char* ssid = STASSID;
const char* password = STAPSK;
ESP8266WebServer server(80);

bool prizler[] = { true, true, true, true };
String degerler[] = { "0", "0", "0" };
int sayi = 0;  // Dizi indeksi

#define role1 D5  // !!! DÜZENLE !!!
#define role2 D6  // !!! DÜZENLE !!!
#define role3 D7  // !!! DÜZENLE !!!


char MAIN_page[] PROGMEM = R"=====(
    <!DOCTYPE html>
  <html lang="tr">

  <head>
      <meta charset="UTF-8">
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
      <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0/dist/css/bootstrap.min.css">
      <title>OS SMART PLUGS </title>
      <link rel="icon" href="https://lh3.googleusercontent.com/u/0/drive-viewer/AFGJ81qol8Pdur2ZAb5zA8JIHIjD41i0Mzi2Su04gVi66uqtPxw09RtnhyJSgeJRZm8g8wN0TD3sXFYmLpByZRALg6j4PH0r6Q=w1870-h903" type="image/x-icon">
  </head>

  <body>
   <img src="https://lh3.googleusercontent.com/u/0/drive-viewer/AFGJ81ozLdPsKfFvgQChL9-CR4xPs80h5cCmh-3LA4kXbPkSK5apbEPcgpE43jyztBniR6B5ig_NG62fTs7Nafe-x6T7-KKJqA=w1170-h2532" width = "150" height ="150">
      <center>
          <div class="container" style="margin-top: 10vh;">
              <div class="row">
                  <div class="col-4">Priz 1</div>
                  <div class="col-4">Priz 2</div>
                  <div class="col-4">Priz 3</div>
              </div>
              <div class="row">
                  <div class="col-4"><p class="deger_1 cihaz_1">Bir cihaz bağlayın</p></div>
                  <div class="col-4"><p class="deger_2 cihaz_2">Bir cihaz bağlayın</p></div>
                  <div class="col-4"><p class="deger_3 cihaz_3">Bir cihaz bağlayın</p></div>
              </div>
              <div class="row" style="margin-top: 1vh;">
                  <div class="col-4">
                      <div class="deger_1" style="width: 80%;">
                          <div class="progress">
                              <div class="progress-bar progress-bar-striped deger_1_bar" role="progressbar"
                                  style="width: 0%" aria-valuenow="0" aria-valuemin="0" aria-valuemax="20">0A/20A</div>
                          </div>
                      </div>
                  </div>
                  <div class="col-4">
                      <div class="deger_2" style="width: 80%;">
                          <div class="progress">
                              <div class="progress-bar progress-bar-striped deger_2_bar" role="progressbar"
                                  style="width: 0%" aria-valuenow="0" aria-valuemin="0" aria-valuemax="20">0A/20A</div>
                          </div>
                      </div>
                  </div>
                  <div class="col-4">
                      <div class="deger_3" style="width: 80%;">
                          <div class="progress">
                              <div class="progress-bar progress-bar-striped deger_3_bar" role="progressbar"
                                  style="width: 0%" aria-valuenow="0" aria-valuemin="0" aria-valuemax="5">0.0A/5A</div>
                          </div>
                      </div>
                  </div>
              </div>
              <div class="row" style="margin-top: 1.5vh;">
                  <div class="col-4"><button class="btn btn-primary button_1">Kapat</button></div>
                  <div class="col-4"><button class="btn btn-primary button_2">Kapat</button></div>
                  <div class="col-4"><button class="btn btn-primary button_3">Kapat</button></div>
              </div>
          </div>
      </center>

      <script src="https://code.jquery.com/jquery-3.6.0.min.js"></script>
      <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0/dist/js/bootstrap.bundle.min.js"></script>
      <script>
          var ip_adress = "192.168.1.4";
          $(document).ready(function () {
              $('.button_1').click(function () {
                  var content = $('.deger_1');
                  content.slideToggle();
                  if ($(this).text() == 'Aç') {
                      $(this).text('Kapat');
                      $.get("http://" + ip_adress + "/ac_1", function (data) { });
                  } else {
                      $('.deger_1_bar').html('0A/20A'); 
                      $('.deger_1_bar').attr('style', 'width: 0%')
                      $(this).text('Aç');
                      $.get("http://" + ip_adress + "/kapat_1", function (data) { });
                  }
              });

              $('.button_2').click(function () {
                  var content = $('.deger_2');
                  content.slideToggle();
                  if ($(this).text() == 'Aç') {
                      $(this).text('Kapat');
                      $.get("http://" + ip_adress + "/ac_2", function (data) { });
                  } else {
                      $('.deger_2_bar').html('0A/20A'); 
                      $('.deger_2_bar').attr('style', 'width: 0%');
                      $(this).text('Aç');
                      $.get("http://" + ip_adress + "/kapat_2", function (data) { });
                  }
              });

              $('.button_3').click(function () {
                  var content = $('.deger_3');
                  content.slideToggle();
                  if ($(this).text() == 'Aç') {
                      $(this).text('Kapat');
                      $.get("http://" + ip_adress + "/ac_3", function (data) { });
                  } else {
                      $('.deger_3_bar').html('0A/20A'); 
                      $('.deger_3_bar').attr('style', 'width: 0%');
                      $(this).text('Aç');
                      $.get("http://" + ip_adress + "/kapat_3", function (data) { });
                  }
              });

              $.get("http://" + ip_adress + "/durum_1", function (data, status) {
                  if (data == '0') {
                      $('.button_1').text('Aç');
                      var content = $('.deger_1');
                      content.slideToggle();
                  }
              })

              $.get("http://" + ip_adress + "/durum_2", function (data, status) {
                  if (data == '0') {
                      $('.button_2').text('Aç');
                      var content = $('.deger_2');
                      content.slideToggle();
                  }
              })

              $.get("http://" + ip_adress + "/durum_3", function (data, status) {
                  if (data == '0') {
                      $('.button_3').text('Aç');
                      var content = $('.deger_3');
                      content.slideToggle();
                  }
              })

              setInterval(() => {
                  if ($('.button_1').text() == 'Kapat') $.get("http://" + ip_adress + "/deger_3", function (data, status) {
                      if (data > 2 && data < 3) $('.cihaz_1').html('1.Kademe Fön Makinesi');
                      else if (data > 4.5 && data < 5) $('.cihaz_1').html('2.Kademe Fön Makinesi');
                      else if (data > 8 && data < 9) $('.cihaz_1').html('Kettle');
                      else if (data > 4 && data < 4.5) $('.cihaz_2').html('Kahve Makinesi');
                      else $('.cihaz_1').html('Bir cihaz bağlayın');
                      $('.deger_1_bar').html(data + 'A/20A'); $('.deger_1_bar').attr('style', 'width: ' + (data / (20 / 100)) + '%');
                  });
                  if ($('.button_2').text() == 'Kapat') $.get("http://" + ip_adress + "/deger_2", function (data, status) {
                      if (data > 2 && data < 3) $('.cihaz_2').html('1.Kademe Fön Makinesi');
                      else if (data > 4.5 && data < 5) $('.cihaz_2').html('2.Kademe Fön Makinesi');
                      else if (data > 4 && data < 4.5) $('.cihaz_2').html('Kahve Makinesi');
                      else if (data > 8 && data < 9) $('.cihaz_2').html('Kettle');
                      else $('.cihaz_2').html('Bir cihaz bağlayın');
                      $('.deger_2_bar').html(data + 'A/20A'); $('.deger_2_bar').attr('style', 'width: ' + (data / (20 / 100)) + '%')
                  });
                  if ($('.button_3').text() == 'Kapat') $.get("http://" + ip_adress + "/deger_1", function (data, status) {
                      //if (data < 0.1 && data > 0.25) $('.cihaz_3').html('Ampül');
                      if (data > 0.19 && data < 0.38) $('.cihaz_3').html('Şarj Aleti');
                      else if (data == 2) $('.cihaz_3').html('1.Kademe Fön Makinesi');
                      else if (data == 4) $('.cihaz_3').html('2.Kademe Fön Makinesi');
                      else if (data > 4 && data < 4.5) $('.cihaz_2').html('Kahve Makinesi');
                      else $('.cihaz_3').html('Bir cihaz bağlayın');
                      $('.deger_3_bar').html(data + 'A/5A'); $('.deger_3_bar').attr('style', 'width: ' + (data / (5 / 100)) + '%')
                  });
              }, 1000);

          });
      </script>

  </body>

  </html>
)=====";

//
void handleRoot() {
  server.send(200, "text/html", MAIN_page);
}
void handleNotFound() {
  String message = "File Not Found ";
  message += "URI: ";
  message += server.uri();
  message += " Method: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += " Arguments: ";
  message += server.args();
  message += " ";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "";
  }
  server.send(404, "text/html", message);
};

void yonlendir() {
  server.sendHeader("Location", String("/"), true);
  server.send(302, "text/plain", "");
}
void ac1() {
  Serial.println("1 Açıldı");
  prizler[1] = true;
  digitalWrite(role1, 1);
  // serial.write("1 Açıldı");
}
void ac2() {
  Serial.println("2 Açıldı");
  prizler[2] = true;
  digitalWrite(role2, 1);
}
void ac3() {
  // Serial.println("3 Açıldı");
  prizler[3] = true;
  digitalWrite(role3, 1);
}
void kapat1() {
  Serial.println("1 Kapatıldı");
  prizler[1] = false;
  digitalWrite(role1, 0);
}
void kapat2() {
  // Serial.println("2 Kapatıldı");
  prizler[2] = false;
  digitalWrite(role2, 0);
}
void kapat3() {
  // Serial.println("3 Kapatıldı");
  prizler[3] = false;
  digitalWrite(role3, 0);
}
void deger1() {
  server.send(200, "text/html", String(degerler[0]));
}
void deger2() {
  server.send(200, "text/html", String(degerler[1]));
}
void deger3() {
  server.send(200, "text/html", String(degerler[2]));
}
void durum1() {
  server.send(200, "text/html", prizler[1] ? "1" : "0");
}
void durum2() {
  server.send(200, "text/html", prizler[2] ? "1" : "0");
}
void durum3() {
  server.send(200, "text/html", prizler[3] ? "1" : "0");
}
//

void setup(void) {
  Serial.begin(115200);

  pinMode(role1, OUTPUT);
  pinMode(role2, OUTPUT);
  pinMode(role3, OUTPUT);

  digitalWrite(role1, 1);
  digitalWrite(role2, 1);
  digitalWrite(role3, 1);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Baglanilan Ag: ");
  Serial.println(ssid);
  Serial.print("IP addresi: ");
  Serial.println(WiFi.localIP());
  if (MDNS.begin("esp8266")) {
    Serial.println("Hazir");
  }
  Serial.println("\nWiFi bağlandı.");

  server.enableCORS(true);

  server.on("/", handleRoot);
  server.on("/ac_1", ac1);
  server.on("/ac_2", ac2);
  server.on("/ac_3", ac3);
  server.on("/kapat_1", kapat1);
  server.on("/kapat_2", kapat2);
  server.on("/kapat_3", kapat3);
  server.on("/deger_1", deger1);
  server.on("/deger_2", deger2);
  server.on("/deger_3", deger3);
  server.on("/durum_1", durum1);
  server.on("/durum_2", durum2);
  server.on("/durum_3", durum3);


  server.on("/inline", []() {
    server.send(200, "text/plain", "root klasoru calisiyor");
  });

  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server baslatildi");
  delay(3000);
}



void loop(void) {
  server.handleClient();
  MDNS.update();

  String metin = String(Serial.readStringUntil('\n'));
  int diziBoyutu = 0;
  for (int i = 0; i < metin.length(); i++) {
    if (metin.charAt(i) == '-') {
      diziBoyutu++;
    }
  }
  diziBoyutu++;
  int indis = 0;
  String eleman = "";
  for (int i = 0; i < metin.length(); i++) {
    if (metin.charAt(i) == '-') {
      degerler[indis] = eleman;
      eleman = "";
      indis++;
    } else {
      eleman += metin.charAt(i);
    }
  }
  degerler[indis] = eleman;

  Serial.print(degerler[0]);
  Serial.print("-");
  Serial.print(degerler[1]);
  Serial.print("-");
  Serial.println(degerler[2]);
}
