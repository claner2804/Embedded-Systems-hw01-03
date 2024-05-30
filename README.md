Aufgabe 1.3 "Low-Level" Bibliothek für die Verwendung des Joysticks (20%)
Manchmal macht es Sinn, auf die Arduino-Bibliothek zu verzichten um Overhead einzusparen. Für solche Fälle re-implementieren wir den Gerätetreiber von Aufgabe 1.2, wobei wir auf die Verwendung von Funktionen verzichten, die von der Arduino-Bibliothek bereitgestellt werden. Für den Gerätetreiber soll ausschließlich die von avr-libc bereitgestellte Low-Level Bibliothek verwendet werden.
Die öffentliche Schnittstelle soll die gleiche bleiben. Nur der Klassenname ändert sich zu JoystickLow (und entsprechend auch die Dateinamen).
Schreiben Sie ausserdem ein kleines Programm (in der Datei main.cpp), das die Verwendung ihres Gerätetreibers demonstriert.
![image](https://github.com/claner2804/Embedded-Systems-hw01-03/assets/131294860/a8fa3d89-26e2-4fd3-9626-3d08d137e969)
