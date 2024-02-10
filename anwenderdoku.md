# Symbolbewegung - Anwenderdokumentation

## Einführung

Willkommen zur Anwenderdokumentation für das Spiel "Symbolbewegung". 
Dieses Spiel wurde mit der GTK+-Bibliothek entwickelt und bietet eine einfache, aber unterhaltsame Benutzeroberfläche.

## Inhaltsverzeichnis

1. [Spielstart](#spielstart)
2. [Spielsteuerung](#spielsteuerung)
3. [Ziel des Spiels](#ziel-des-spiels)
4. [Punkte und Highscore](#punkte-und-highscore) 5. [Anforderungen](#anforderungen) 6. [Kompilierung und Ausführung](#kompilierung-und-ausführung)

## Spielstart

Um das Spiel zu starten, geben Sie Ihren Benutzernamen in das Textfeld ein und klicken Sie auf "Submit". Ihr aktueller Punktestand wird angezeigt, oder falls Sie neu sind, starten Sie mit null Punkten.

## Spielsteuerung

- **Leertaste:** Feuert eine Rakete ab.
- **Pfeiltasten (links/rechts):** Bewegen das Symbol nach links oder rechts.

## Ziel des Spiels

Das Ziel des Spiels ist es, so viele Symbole wie möglich abzuschießen und dabei Punkte zu sammeln. Es gibt verschiedene Zielobjekte, die unterschiedliche Punkte wert sind.

## Punkte und Highscore

Ihr Punktestand wird oben auf dem Bildschirm angezeigt. Schießen Sie Symbole ab, um Punkte zu sammeln. Der Highscore wird gespeichert und kann in der Datei "userNames_scores.log" nachverfolgt werden.

## Anforderungen

Stellen Sie sicher, dass Sie die folgenden Voraussetzungen erfüllen, um das Spiel reibungslos auszuführen:

- GCC (GNU Compiler Collection)
- GTK+ 3.0-Bibliothek und zugehörige Entwicklungsbibliotheken

## Kompilierung und Ausführung

Verwenden Sie den GCC-Befehl zum Kompilieren des Spiels:

```bash
gcc -o main main.c -g `pkg-config --cflags --libs gtk+-3.0`
