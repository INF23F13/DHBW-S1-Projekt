# Programmierprojekt 23F, 1. Semester
# Space Defender

## 1. Projektteilnehmer
- Gehl, Torsten 	(T0rstenGeh1)
- Intorre, Francesco 	(frani1611)
- Serban, Daniel 	(OkCool5)
- Biser, Michael 	(WomboCombo53)

Kontakt: inf23187@lehre.dhbw-stuttgart.de (Michael)

## 2. Projektbeschreibung

### 2.1  Beschreibung der Aufgaben- bzw. Problemstellung

### 2.1.1 Beschreibung von Funktionsumfang und Funktionsweise aus Anwendersicht
#### Voraussetzungen
- Linux-System mit GTK3.0 Desktopoberfläche (z.B. Ubuntu Desktop)
- Windows-System ist möglich mithilfe von GTK3.0 + MSYS2; wird jedoch nicht empfohlen.

#### Funktionsumfang
- Es muss eine grafische Benutzeroberflaeche vom Anwender gestartet werden koennen.

- Nach dem Start des Programmes soll der Anwender seinen Anwendernamen eingeben
	- ist der Anwender nicht hinterlegt, muss sein Anwendername erst nach Beendigung des Spieles in die hinterlegte Anwenderliste aufgenommen werden mit Namen, erreichter Punktzahl und Datum des letzten Spieles 

- Nach der Eingabe des Anwendernamens soll ein Highscore-Ranking angezeigt werden von allen Anwendern absteigend sortiert mit Datum des letzen Highscore

- Der Anwender soll dann über einen Button gefragt werden ob er das Spiel beginnen moechte

- Der Anwender muss dann über die Bedingungselemente Pfeiltasten sein "Spaceship" von links nach rehcts navigiren

- Das Spielfeld muss in 64 Reihen und 64 Spalten unterteilt werden.

- Es muss am oberen Rand (row1/row2) Objekte geben, die dem Anwender als "Target Objekte" dienen.
	- Es sollte zwei unterschiedliche Targetklassen mit unterschiedlichen Attributen von Punktanzahl geben 
		- z.B.: KingPin = 10Points, SimpleTarget = 5 Points
	- Die Target-Objekte sollen in einem zeitlichen Intervall von 0.25 Sekunden von Links nach Rechts bewegen.
	- Auf der Zeile 1 (row1) bewegen sich die KinPin-Target-Objekte.
	- Auf der Zeile 2 (row2) bewegen sich die Simple-Target-Objekte.

- Der Anwender muss unter Verwendung der Leertaste ein "Rocket Objekt" von seiner aktuellen Position aus "absetzten" koennen.

- befindet sich das vom Anwender abgesetzte Rocket-Objekte im gleichen Feld wie eines der Target Objekte, muss die dem Target-Objekt zugeordnete Punktzahl auf die aktuelle Punktzahl summieren und das "getroffene" TargetObjekt muss vom Feld geloescht werden.

- der Durchlauf des Programms endet, wenn keine verbleibenden Targetobjekte auf dem Spielfeld verbleiben.

- Zum Ende des Programmdurchlaufs muss der erzielte Punktestand mit dem Datum des Duchlaufs mit dem zugoerigen Anwender erfasst werden.

### 2.1.2  Angestrebte Lösung aus technischer Sicht

1. technisches Erstkonzept 
- Das Programm wird für Windows OS entwickelt.

- Es muss eine GPL3 oder Apache License V2.0 Library für die grafische Benutzer Oberflaeche verwendet werden (vgl. GTK).

- Nach dem Start des Programmes muessen die Daten des Anwenders ueber seinen Anwendernamen aus einer hinterlegten UserInfo.log Datei gelesen werden.
	- Dazu werden typedef struct user, target, spaceship, rocket angelegt

- Nach der Eingabe des Anwendernamens soll ein Highscore-Ranking angezeigt werden von allen Anwendern absteigend sortiert mit Datum des letzen Highscore.
	- Dazu muessen die ausgelesenen Anwender mit Highscore und Date des Highscores in eine Datenstruktur gelesen und in einem Fenster angezeigt werden.
	- Dies wird mit einer while(1) Kontrollstruktur umgesetzt die eine {if(EOF) break} abgebrochen wird. 


- Der Anwender soll dann über einen Button gefragt werden ob er das Spiel beginnen moechte.
	- dazu wird eine von der verwendeteten Library bereitgestellte Funktion/Methode (noch nicht bekannt, vgl. GTK) umgesetzt.

- Der Anwender muss dann über die Bedingungselemente Pfeiltasten sein "Spaceship" von links nach rehcts navigiren
	- dazu wird eine von der verwendeteten Library bereitgestellte Funktion/Methode (noch nicht bekannt, vgl. GTK) umgesetzt.

- Das Spielfeld muss in 64 Reihen und 64 Spalten unterteilt werden.
	- Es muss geprueft werden, ob es hierzu ebenfalls Methoden/Funktionen in der verwendeten Library gibt

- Es muss am oberen Rand (row1/row2) Objekte geben, die dem Anwender als "Target Objekte" dienen.
        - Es sollte zwei unterschiedliche Targetklassen mit unterschiedlichen Attributen von Punktanzahl geben 
                - typedef struct mit Attribut Points ->  KingPin = 10Points, SimpleTarget = 5 Points
        - Die Target-Objekte sollen in einem zeitlichen Intervall von 0.25 Sekunden von Links nach Rechts bewegen.
		- time.h
        - Auf der Zeile 1 (row1) bewegen sich die KinPin-Target-Objekte.
        - Auf der Zeile 2 (row2) bewegen sich die Simple-Target-Objekte.

- Der Anwender muss unter Verwendung der Leertaste ein "Rocket Objekt" von seiner aktuellen Position aus "absetzten" koennen.
	- Es muss geprueft werden, ob es hierzu ebenfalls Methoden/Funktionen in der verwendeten Library gibt
	- Rocket-Objekt bewegt sich mit 0.25 (Sekunden/Feld) orthogonal (kein Drift) Richtung Row1/Row2
	- die Betaetigung der Leertaste ist gekoppelt mit der Erzeugung eines Reocket-Objektes. Es wird eine Art Eventlistener benoetigt.
	- Startpostion Column = Endpositon Column
	- Startpostion Row = Endpositon (Row - 62/63)

- befindet sich das vom Anwender abgesetzte Rocket-Objekte im gleichen Feld wie eines der Target Objekte, muss die dem Target-Objekt zugeordnete Punktzahl auf die ak>
	- es muss eine Funktion geschrieben werden, welche die Gleichheit der Reihen und Spalten Elemente von Target-Objekt und Rocket-Objekt prueft.
	- bei Gleichheit muss actualPointsscore + Attribut Point vom Target-Obejkt berechnet werden.

- der Durchlauf des Programms endet, wenn keine verbleibenden Targetobjekte auf dem Spielfeld verbleiben.

- Zum Ende des Programmdurchlaufs muss der erzielte Punktestand mit dem Datum des Duchlaufs mit dem zugoerigen Anwender erfasst werden.
	- Dazu wird das typedef struct Objekt User mit Summe der erzielten Punkte in der Datei UserInfo.log mit einer Schleifenkontrollstruktur abgeglichen, wenn Punktzahl hoeher als letze Punkt in Datei geschrieben.

## 3. Termine
- Exposé: **29.01.2024** (Punkte 1. und 2. oben)
	- Einladung Benutzer: https://github.com/jfr609/
- Bearbeitung: 02.02. und 09.02.2024
- Abgabe: **14.02.2024** 
	- Beispielformat: https://github.com/AlexanderMelde/Handlungserkennung
- Präsentation: **16.02.2024** (Präsenz)
