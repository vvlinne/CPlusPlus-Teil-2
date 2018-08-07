# C++ Teil_2

Semesterarbeit des C++ Kurses (Teil 2) an der Universität zu Köln, von Viviane Linne (#5966540)
Link zum Github-Repository: https://github.com/vvlinne/CPlusPlus-Teil-2

Was, Wie und Wieso?

Im Folgenden werde ich einen kurze Dokumentation meines Projektes darlegen, in der ich aufzeigen werde was ich gemacht habe (welche Funktionalitäten sind umgesetzt worden), wie ich das gemacht habe, und wieso ich es auf diese Art und Weise gemacht habe.

Das Programm erfüllt den Funktionsumfang der Stufe I, also die Basisaufgabe. Erstellt wurde ein kleines Spiel in dem der Spieler ein kleines Quadrat (Avatar) am unteren Bildrand von links nach rechts bewegen kann um somit random generierten Objekten (Kreise und Quadrate), die sich vom oberen zum unteren Bildrand bewegen, auszuweichen. In dem Spielfeld wird als eine Art UI am oberen Rand ein Punktecounter sowie die Leben des Spielers (drei ausgefüllte Kreise) angezeigt. Der Spieler kann einen Spielstand speichern und diesen zu gewünschter Zeit wieder laden, desweiteren kann er das Spiel starten, pausieren und beenden - diese Funktionen sind jeweils über einen Button am linken Spielfeldrand gesteuert.


Kurze, stichpunktartige Zusammenfassung der Funktionalitäten:

Spielfeld: Das Fenster in dem sich das Spiel öffnet hat eine, in der main.cpp festgehaltene, festgesetzte Größe, damit die Dimensionen des Spielfelds nicht verzerrt werden.

Buttons: Insgesamt gibt es 4 Buttons: Start/Stop, Speichern, Laden Ende. Der Start/Stop Button wird anders behandelt als die anderen, da hier auf einem Button zwei Funktionalitäten realisiert werden. In der meinwidget.h Datei werden die Properties der Klasse definiert, die dann in der meinwidget.cpp genutzt und verändert werden. Hierzu wird ein property increment überprüft, welches bei laufendem Spiel den Wert 1 hat und bei gestopptem Spiel dem Wert 0. Je nach Wert wird die Schrift sowie die Funktionalität des Buttons verändert (entweder startet oder stoppt man das Spiel).
Die restlichen Buttons rufen weitere Funktionen auf (savefile und loadfile in meinwidget.cpp), die Quitfuntkion ist eine QT eigene Funktion die einfach übernommen werden konnte.

Stats: Die Stats zeigen am oberen Rand des Spielfelds zum Einen den Punktestand und zum Anderen die Leben des Spielers an. Ein Stats Objekt enthält die Werte der Punkte sowie die verfügbaren Leben eines Spielers. Dieses Objekt wird in der zeichenfeld.cpp benutzt und bildet dort die zuvor gespeicherten Werte ab. Die Funktion updatePoints erhöht den aktuellen Punktestand pro Sekunde (realisiert durch einen Timer) um 25 Einheiten.

Gegner: Eine Klasse Gegner enthält einen randomisierten Wert (1 oder 2) der darüber entscheidet ob ein Kreis oder ein Quadrat als Gegner abgebildet wird. Diese Gegner werden am oberen Spielfeldrand erzeugt (durch einen gegnerVektor in Zeichenfeld.cpp) und bewegen sich mit einer randomisierten Steprange (diese wird nach jedem Schritt neu und random berechnet) an den unteren Spielfeldrand znd verlassen dort das Spielfeld.

Avatar/Spieler: Ein Quadrat wird am unteren Ende des Spielfelds durch eine

Spielfeld/Fenster:

Im Endeffekt verwaltet die Datei zeichenfeld.cpp die Funktionalitäten dieses Programmes.

Anmerkungen:
Ich habe als Basis des Programmes die Codedateien "meinwidget.h/cpp" sowie "zeichenfeld.h/cpp" aus der Vorlesung benutzt und diese passend für die gestellte Aufgabe erweitert.
