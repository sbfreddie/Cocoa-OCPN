��    g      T  �   �      �  �   �  (   9	  �   b	     �	  I   

  R   T
  .   �
  �   �
  �   �  B   ^  H   �     �            	   "     ,     0     2     6     H  +   Q  #   }     �     �     �      �     �     �     �     �  '     �   8     �       	   
               !     &     -     4     B     J     \  
   c     n     w     |     �  
   �  o   �               &     +     ?     W  "   d     �     �     �     �     �     �     �     �  	   �     �  
   �     �                "  @   .     o  	   v     �     �     �     �     �  �   �  
   h     s     y  �   �     *     2     B  N   H     �     �     �     �     �  "   �  
   �     �             
          �    �   �  /   >  �   n     �  Z     Q   p  .   �  �   �  �   �  C   f  I   �     �            	   ,     6     :     <     @     U  %   [  1   �     �     �     �      �     �     �             -   +  �   Y     %  	   B  
   L     W     ]     d  	   l     v     }     �     �     �     �     �     �     �     �  
   �  e   �     G     ]     j     p     �     �  )   �     �     �     �     �                (     /     4     ;     C  
   P     [     p     �  :   �     �     �     �  	   �     �     �     �  �   �  	   �     �     �  �   �     p      y      �   h   �      !     !  
   !     &!  
   ,!  &   7!  
   ^!     i!     u!     y!     �!     �!             \       I       0         ;   N   e       <   9   ^   )       M   R      O      $                      `         6   #   L   '      X   !          /   b   K       c   (         1   a   Y   E       >       P      D   	   V      @          8   F      S   A   
   4   C   d   5   2                     G             7   T   "   +   Z   H   U   [   B             %   _      .      3                      g   J       W          *              ?       =              ,   -           &   :   f   Q       ]           
Corrected Altitude
CorrectedAltitude = ObservedAltitude - ParallaxCorrection
CorrectedAltitude = %.3f - %.3f
CorrectedAltitude = %.5f
 
Did you forget to install vsop87d.txt?
 
Geographical Position (lat, lon) = %.3f %.3f
GHAAST = %.0f %.3f'
SHA = %.0f %.3f'
GHA = %.0f %.3f'
Dec = %c %.0f %.3f'
SD = %.3f'
HP = %.3f'

 
LimbCorrection = %.5f
 
Magnetic data will not be available for the celestial navigation plugin. 
Moon selected, Limb Correction
SD = %.3f
lc = 180/Pi * asin(Pi/180*SD)
lc = %.3f
 
Moon selected, parallax correction
HP = %.3f
 
Observed Altitude
ObservedAltitude = Measurement - IndexCorrection - EyeHeightCorrection - RefractionCorrection - LimbCorrection
ObservedAltitude = %.3f - %.3f - %.3f - %.3f - %.3f
ObservedAltitude = %.5f
 
Refraction Correction
x = tan(Pi/180*Measurement + 4.848e-2*(Pi/180) / (tan(Pi/180*Measurement) + .028))
x = tan(Pi/180*%.3f + 4.848e-2*(Pi/180) / (tan(Pi/180*%.3f) + .028))
x = %.3f
 
Sun selected, Limb Correction
ra = %.3f, lc = 0.266564/ra = %.3f
 
Sun selected, parallax correction
rad = %.3f, HP = 0.002442/rad = %.3f
           N/A                  N/A             N/A         N/A    .25 0 Alg Almanac Data For  Altitude Are you sure you want to delete all sights? Astrolab failed, data unavailable:
 Azimuth Bearing Body Building bearing Sight Positions Calculations Celcius Celestial Body Celestial Navigation Celestial Navigation PlugIn for OpenCPN Celestial Navigation PlugIn for OpenCPN.
Implements nautical almanac for sun, moon, planets,
and various navigational stars.
Compute position fix from celestial measurements. Celestial Navigation Sights Center Certainty Color Combo! Cone Cone 2 Config Date and Time Degrees Degrees Certainty Delete Delete All Distance Done Edit Error Eye Height Eye Height is %.3f meters
Height Correction Degrees = 1.753*sqrt(%.3f) / 60.0
Height Correction Degrees = %.3f
 Failed to load file:
 Failure Alert Find Find Celestial Body Fix From Visible Sights Fix Position Formulas used to calculate sight

 Go Hours Index Error Index Error is %.4f degrees

 Information Initial Latitude Limb Longitude Lower Lower Limb Magnetic Magnetic Azimuth Magnetic Bearing Measurement Measurement certainty likely set to small, sight may not appear  Meters MilliBars Minutes MyLabel New Nm OpenCPN Alert ParallaxCorrection = -180/Pi * asin( sin(Pi/180 * HP ) * cos(Pi/180 * ObservedAltitude))
ParallaxCorrection = -180/Pi * asin( sin(Pi/180 * %.3f ) * cos(Pi/180 * %.3f))
ParallaxCorrection = %.5f
 Parameters Plane Pressure RefractionCorrection = .267 * Pressure / (x*(Temperature + 273.15)) / 60.0
RefractionCorrection = .267 * %.3f / (x*(%.3f + 273.15)) / 60.0
RefractionCorrection = %.5f
 Seconds Set As Defaults Shift Shifted sights are not used to compute a fix, determine fix visually instead.
 Sight Sight Properties Sphere Sun Temperature The plugin will not work correctly Time (UTC) Transparency Type Upper Upper Limb Warning Project-Id-Version: celestial_navigation_pi 3.4.64
Report-Msgid-Bugs-To: 
POT-Creation-Date: 2014-01-13 22:41+0100
PO-Revision-Date: 2014-01-13 22:43+0100
Last-Translator: CarCode <carcode@me.com>
Language-Team: CarCode <carcode@me.com>
Language: de
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
X-Generator: Poedit 1.6.3
Plural-Forms: nplurals=2; plural=(n != 1);
 
Korrigierte Höhe
Korrigierte Höhe = BeobachteteHöhe - ParallaxKorrektur
Korrigierte Höhe = %.3f - %.3f
Korrigierte Höhe = %.5f
 
Wurde Installation von vsop87d.txt vergessen?
 
Geografische Position (lat, lon) = %.3f %.3f
GHAAST = %.0f %.3f'
SHA = %.0f %.3f'
GHA = %.0f %.3f'
Dec = %c %.0f %.3f'
SD = %.3f'
HP = %.3f'

 
RandKorrektur = %.5f
 
Magnetische Daten werden für das astronomische Navigations Plugin nicht verfügbar sein. 
Mond gewählt, Rand Korrektur
SD = %.3f
lc = 180/Pi * asin(Pi/180*SD)
lc = %.3f
 
Mond gewählt, parallaxe Korrektur
HP = %.3f
 
Beobachtete Höhe
BeobachteteHöhe = Messung - IndexKorrektur - AugenHöheKorrektur - BrechungsKorrektur - RandKorrektur
BeobachteteHöhe = %.3f - %.3f - %.3f - %.3f - %.3f
BeobachteteHöhe = %.5f
 
Brechungskorrektur
x = tan(Pi/180*Messung + 4.848e-2*(Pi/180) / (tan(Pi/180*Messung) + .028))
x = tan(Pi/180*%.3f + 4.848e-2*(Pi/180) / (tan(Pi/180*%.3f) + .028))
x = %.3f
 
Sonne gewählt, Rand Korrektur
ra = %.3f, lc = 0.266564/ra = %.3f
 
Sonne gewählt, Parallax Korrektur
rad = %.3f, HP = 0.002442/rad = %.3f
           N/A                  N/A             N/A         N/A    .25 0 Alg Almanach Daten für  Höhe Sollen alle Sichten gelöscht werden? Astrolab fehlgeschlagen, Daten nicht verfügbar:
 Azimuth Peilung Objekt Erzeuge Peilung Sicht Positionen Berechnungen Celcius Astronomisches Objekt Astronom. Navigation Astronomisches Navigation PlugIn für OpenCPN Astronomisches Navigation PlugIn für OpenCPN.
Implementiert nautischen Almanach für Sonne, Mond, Planeten
und verschiedene navigatorische Sterne.
Berechnet Positions-Fixes aus astronomischen Messungen. Astronom. Navigation Sichten Zentriere Sicherheit Farbe Combo! Konisch Konisch 2 Konfig Datum und Zeit Grad Grad Sicherheit Löschen Lösche alles Distanz Getan Editiere Fehler Augenhöhe Augenhöhe ist %.3f Meter
Höhenkorrektur Grad = 1.753*sqrt(%.3f) / 60.0
Höhenkorrektur Grad = %.3f
 Fehler b. Laden von:
 Fehler-Alarm Finde Finde astronomisches Objekt Fix von sichtbaren Sichten Fix Position Verwendete Formeln zur Sicht-Berechnung

 Los Stunden Index Fehler Index Fehler ist %.4f Grad

 Information Ausgang Breite Rand Länge Unterer Unterer Rand Magnetisch Magnetischer Azimuth Magnetische Peilung Messung Messung sicherlich zu niedrig, Sicht wird nicht erscheinen Meter Millibar Minuten MeinLabel Neu sm OpenCPN Alarm ParallaxKorrektur = -180/Pi * asin( sin(Pi/180 * HP ) * cos(Pi/180 * BeobachteteHöhe))
ParallaxKorrektur = -180/Pi * asin( sin(Pi/180 * %.3f ) * cos(Pi/180 * %.3f))
ParallaxKorrektur = %.5f
 Parameter Plan Druck Brechungskorrektur = .267 * Druck / (x*(Temperatur + 273.15)) / 60.0
Brechungskorrektur = .267 * %.3f / (x*(%.3f + 273.15)) / 60.0
Brechungskorrektur = %.5f
 Sekunden Setze als Standard Verschieben Verschobene Sichten werden zur Fix-Berechnung nicht benutzt, bestimmen Sie stattdessen den Fix visuell.
 Sicht Sicht Eigenschaften Sphärisch Sonne Temperatur Das Plugin wird nicht korrekt arbeiten Zeit (UTC) Transparenz Typ Oberer Oberer Rand Warnung 