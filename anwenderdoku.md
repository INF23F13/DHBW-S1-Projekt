# Space Defender - Anwenderdokumentation

## Einführung

Willkommen zur Anwenderdokumentation für das Spiel Space Defender, welches mithilfe von GTK+ entwickelt wurde. 

## Inhaltsverzeichnis

1. [Spielstart](#spielstart)
2. [Spielsteuerung](#spielsteuerung)
3. [Ziel des Spiels](#ziel-des-spiels)
4. [Punkte und Highscore](#punkte-und-highscore)
5. [Anforderungen](#anforderungen)
6. [Kompilierung und Ausführung](#kompilierung-und-ausführung)

## Spielstart

Um das Spiel zu starten, geben Sie Ihren Benutzernamen in das Textfeld ein und klicken Sie auf "Submit". Es öffnet sich nun das Spielfeldfenster.

## Spielsteuerung

- **Leertaste:** Feuert eine Rakete vom Raumschiff ab.
- **Pfeiltasten (links/rechts):** Bewegt das Raumschiff des Spielers nach links oder rechts.

## Ziel des Spiels

Das Ziel des Spiels ist es, so viele Gegner wie möglich abzuschießen und dabei Punkte zu sammeln. Es gibt verschiedene Zielobjekte, die unterschiedliche Punkte wert sind.

## Punkte und Highscore

Ihr Punktestand wird oben auf dem Bildschirm angezeigt. Schießen Sie Gegner ab, um Punkte zu sammeln. Der Highscore wird gespeichert und kann in der Datei "userNames_scores.log" nachverfolgt werden.

## Anforderungen

- GCC (GNU Compiler Collection)
- GTK+ 3.0-Bibliothek und zugehörige Entwicklungsbibliotheken

## Kompilierung und Ausführung

Verwenden Sie folgenden GCC-Befehl zum Kompilieren des Spiels:

```bash
gcc -o main main.c -g `pkg-config --cflags --libs gtk+-3.0`
