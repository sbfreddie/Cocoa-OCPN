��    I      d  a   �      0     1  	   3     =     C     R     _     l     �     �     �     �     �     �     �     �     �    �     �     	     	     *	     1	     =	     M	     Y	     o	     ~	     �	     �	     �	  	   �	     �	     �	     �	     �	     �	      
  
   
     
     1
     B
  
   R
     ]
  
   i
     t
     �
     �
     �
     �
     �
     �
     �
     �
  
   �
  K       T  	   `     j     s     �     �  ~   �     9     N  
   ]     h     n  	   w     �     �  	   �     �  S  �       	                  "     /     ;  
   O     Z     a     m     |     �     �     �     �  O  �  	             $     2     ;     G     Y     e          �     �     �     �     �     �     �     �     �               5     C     b     r     �     �  
   �     �     �     �     �     �     �               4  
   B  M  M     �  	   �     �     �     �     �  �        �     �     �     �     �  
   �  	         
          '     /   9         G   F   "           =   8   6                 '   A          D         @   3           ;      (         #   >      $   I                                          !   -            +   )             &   
   C          *   E       %                     B   :   	   <       4   2   5   H                ,       7   .   1       0          ?        3 ALARM!!!! About About Watchman Alarm Action Anchor Watch Automatically  Reset Close Command Course Error Current Course Days  Deadman Alarm Degrees Distance to Anchor Donate Each alarm is enabled/disabled with a check box.

Most alarms should be self-explanatory, however the AIS alarm may be only useful in areas where AIS traffic is known to regularly occur, or from a reciever on a ship which also has an active transmitter.  Otherwise an alarm will occur if there are no ships

Alarm action:

Normally a sound is played, however you can execute any command you like.  On linux for example, builtin sound playing can block, so instead consider a command of:
"aplay /usr/local/share/opencpn/sounds/2bells.wav" Enabled GPS fix crosses land in < GPS fix is < Hours  Information Land Distance > LandFall in LandFall not Detected Landfall Alarm Last AIS Sentence Last GPS Update Last activity Latitude Longitude Message Box Minutes  NMEA Data Alarm No AIS for > No GPS for > No NMEA Messages No Updates No User Activity for Off Course Alarm Off Course By > Over Speed Preferences Radius (m) Repeat Alarm after seconds Reset Last Alarm Seconds Select a file Sound Speed Alarm Speed over ground < Speed over ground > Sync to Boat Test Alarm The watchman plugin for opencpn is made to add a range of alarms based on various conditions.

Only a very small fraction of possible alarms are implemented, patches are welcome.

License: GPLv3+

Source Code:
https://github.com/seandepagnier/watchman_pi

Author:
Sean D'Epagnier

Many thanks to all of the translators and testers. Under Speed Watch Man Watchman Watchman Anchor Watch Watchman Information Watchman PlugIn for OpenCPN Watchman PlugIn for OpenCPN
Alarm user of possible dangerous situations. 

The Watchman plugin was written by Sean D'Epagnier
 Watchman Preferences With Course Of degrees(s) knots meter(s) minute(s) minutes nm from coastline second(s) seconds Project-Id-Version: watchman_pi 3.4.64
Report-Msgid-Bugs-To: 
POT-Creation-Date: 2013-11-08 17:15+0100
PO-Revision-Date: 2013-11-08 17:39+0100
Last-Translator: CarCode <carcode@me.com>
Language-Team: de_DE <carcode@me.com>
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
X-Generator: Poedit 1.5.7
 3 ALARM!!!! Über Über Watchman Alarm Aktion Anker Wache Automatischer Reset Schließen Befehl Kurs-Fehler Aktueller Kurs Tage  Totermann Alarm Grad Distanz zum Anker Spenden Jeder Alarm kann mit einer Checkbox aktiviert/deaktiviert werden.

Die meisten Alarme sind selbst-erklärend, der AIS Alarm ist jedoch nur in Gebieten nützlich, wo AIS Verkehr regelmäßig vorkommt oder von einem Receiver im Boot, der auch einen aktiven Transmitter hat. Sonst gibt es einen Alarm, wenn kein Schiff da ist.

Alarm Aktion:

Normalerweise wird ein Ton erzeugt, es kann jedoch jeder beliebige Befehl ausgeführt werden. Bei Linux kann beispielsweise das Tonabspielen blockieren, somit ist stattdessen folgender Befehl denkbar:
"aplay /usr/local/share/opencpn/sounds/2bells.wav" Aktiviert GPS Fix kreuzt Land in < GPS Fix ist < Stunden  Information Land-Entfernung > LandFall in LandFall nicht detektiert Landfall Alarm Letzte AIS Sequenz Letztes GPS Update Letzte Aktivität Breite Länge Nachrichten Box Minuten  NMEA-Daten Alarm Kein AIS für > Kein GPS für > Keine NMEA Nachrichten Keine Updates Keine Anwender Aktivität für Kurs-Abw. Alarm Kurs-Abw. mit > Übergeschw. Einstellungen Radius (m) Wiederhole Alarm nach Sekunden Reset letzten Alarm Sekunden Wähle eine Datei Ton Geschw. Alarm Geschw. über Grund < Geschw. über Grund > Sync zum Boot Test Alarm Das Watchman Plugin für OpenCPN wurde zum Hinzufügen von Alarmen bei verschiedenen Situationen gemacht.

Es sind nur wenige mögliche Alarme implementiert, Erweiterungen sind willkommen.

Lizenz: GPLv3+

Source Code:
https://github.com/seandepagnier/watchman_pi

Author:
Sean D'Epagnier

Vielen Dank allen Übersetzern und Testern. Untergeschw. Watch Man Watchman Watchman Ankerwache Watchman Information Watchman PlugIn für OpenCPN Watchman PlugIn für OpenCPN
Alarmiert Anwender bei möglichen gefährlichen Situationen.
Verschiedene Situationen programmierbar.

Das Watchman Plugin wude geschrieben von Sean D'Epagnier
 Watchman Einstellungen Mit Kurs von Grad Knoten Meter Minute(n)  Minute(n) sm von Küstenlinie Sekunden Sekunden 