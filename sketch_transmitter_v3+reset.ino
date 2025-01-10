#include <Ethernet.h> //libreria ethernet
#include <SPI.h> //collabora con la libreria ethernet
#include <String.h> //gestione stringhe
#include <SoftwareSerial.h>
SoftwareSerial HC12(6,7);



byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED}; //indirizzo fisico
byte ip[] = {192, 168, X, X};                     //indirizzo ip locale
byte subnet[] = {255, X, X, X};                 //indirizzo subnet
byte gateway[] = {192, X, X, X};                 //indirizzo gateway
EthernetServer server(80);                         //imposto porta protocollo HTTP

String ascoltatore;
long TIMER1;

int timer(long *t, long millisecondi)
{
    long x;
  
    x=millis();
    if (!*t){
        *t=x;
        return 0;
    }
    else if (x-*t > millisecondi) {
       *t=millis();
       return 1;
    }
    else
      return 0;      
}

void setup() {
  Ethernet.begin(mac, ip, gateway, subnet);        //inizializzo impostazioni di rete
  ascoltatore="";
  HC12.begin(9600);

}
void(* resetFunc) (void) = 0;//declare reset function at address 0


void loop() {
  EthernetClient client = server.available(); //attendo l'arrivo di un client


  
  if(timer(&TIMER1, 64800000) ) //18 ore = 64800000
  {
    resetFunc(); //call reset 
  }


  
  if (client) { //se c'è il cliente deve..
    
    while(client.connected()) {
      if(client.available()) {
        char c = client.read(); //..leggere i caratteri che invia
        ascoltatore.concat(c); //concatena i caratteri del client
        
        if (c == '\n') { //se arrivo a fine riga
          if(ascoltatore.indexOf("acquafresca")>0){
            if(ascoltatore.indexOf("LampioniAccesi")>0){
              HC12.write('A');
            }
            if(ascoltatore.indexOf("LampioniSpenti")>0){
              HC12.write('a');
            }
            if(ascoltatore.indexOf("FarettoAcceso")>0){
              HC12.write('B');
            }
            if(ascoltatore.indexOf("FarettoSpento")>0){
              HC12.write('b');
            }

            
            client.println("HTTP/1.1 200 OK"); //dico al client che è tutt'ok - standard http
            client.println("Content-Type: text/html"); //indico il formato - standard http
            client.println();
            client.println("<html>"); //inizio codice html
            client.println("<head>");
            client.println("<title>Luci di Casa v.2</title>");
            client.println("</head>");
            client.println("<body>");
            client.println("<p align=center><font size=9><b>--------------------Casa v.3--------------------</b></font></p>");
            client.println("<br> <br> <br><br><br>");
            client.println("<p align=center><font size=15>LAMPIONI</font></p>");
            client.println("<p align=center><a href='/?acquafresca/?LampioniAccesi'> <button><font size=9>Accendi</font></button> </a>  <a href='/?acquafresca/?LampioniSpenti'> <button><font size=9>Spegni</font></button> </a></p>");
            client.println("<br><br>");
            client.println("<p align=center><font size=15>FARETTO GIARDINO</font></p>");
            client.println("<p align=center><a href='/?acquafresca/?FarettoAcceso'> <button><font size=9>Accendi</font></button> </a>  <a href='/?acquafresca/?FarettoSpento'> <button><font size=9>Spegni</font></button> </a></p>");
            client.println("</body>");
            client.println("</html>"); //fine codice html
            client.stop(); //stop richieste dal client
            ascoltatore=""; 
          } //fine if controllo password in questo caso "acquafresca"
          else{
            client.println("HTTP/1.1 200 OK"); //dico al client che è tutt'ok - standard http
            client.println("Content-Type: text/html"); //indico il formato - standard http
            client.println(); //necessario            client.println("<html>"); //inizio codice html
            client.println("<head><title>Casa v.3</title> <link rel='shortcut icon' type='image/x-icon' href='http://i44.servimg.com/u/f44/16/84/89/65/23570310.png' /></head>");
            client.println("<body> <p align='center'> <font size=19> Non hai l'autorizzazione per effettuare l'accesso </font> </p> </body>");
            client.println("</html>"); //fine codice html
            client.stop();
            ascoltatore="";
          }
           
        } //fine if c=='\n'
        
      }//fine if client.available
      
    }// fine while client.conected
    
  }// fine if client
}
