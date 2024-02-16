# Space Defender - Anwenderdokumentation

## Einführung

Willkommen zur Anwenderdokumentation für das Spiel Space Defender, welches mithilfe von GTK+ entwickelt wurde. 

## Inhaltsverzeichnis

1. [Installation](#installation)
2. [Spielstart](#spielstart)
3. [Spielsteuerung](#spielsteuerung)
4. [Ziel des Spiels](#ziel-des-spiels)
5. [Punkte und Highscore](#punkte-und-highscore)

## Installation

### Anforderungen (benötigte Pakete)
- GTK3.0 + GTK3-Dev
- GCC (GNU Compiler Collection)

#### Ubuntu/Debian
```bash
sudo apt update
sudo apt install libgtk-3-0 libgtk-3-dev build-essential git
sudo apt install libsdl2-dev libsdl2-mixer-dev
```

#### Repo klonen
```bash
git clone https://github.com/INF23F13/DHBW-S1-Projekt
```

#### Kompilierungsbefehl
```bash
gcc -o main main.c -g `pkg-config --cflags --libs gtk+-3.0 sdl2 SDL2_mixer`
```

#### Spiel starten
```bash
./main
```

## Spielstart

Um das Spiel zu starten, geben Sie Ihren Benutzernamen in das Textfeld ein und klicken Sie auf "Submit". Es öffnet sich nun das Spielfeldfenster.

## Spielsteuerung

- **Leertaste:** Feuert eine Rakete vom Raumschiff ab.
- **Pfeiltasten (links/rechts):** Bewegt das Raumschiff des Spielers nach links oder rechts.

## Ziel des Spiels

Das Ziel des Spiels ist es, so viele Gegner wie möglich abzuschießen und dabei Punkte zu sammeln. Es gibt verschiedene Zielobjekte, die unterschiedliche Punkte wert sind.

## Punkte und Highscore

Ihr Punktestand wird oben auf dem Bildschirm angezeigt. Schießen Sie Gegner ab, um Punkte zu sammeln. Der Highscore wird gespeichert und kann in der Datei "userNames_scores.log" nachverfolgt werden.
