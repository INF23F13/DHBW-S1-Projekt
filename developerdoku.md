# Space Defender - Entwicklerdokumentation

## Einführung
Dies ist eine Anwendung für ein Spiel mit beweglichen Symbolen unter Verwendung der GTK-Bibliothek in C. Die Anwendung zeigt ein Fenster mit zwei Tabs: "User Input" für die Benutzereingabe und "Game Display" für die Spielanzeige.

## Plattform
Die Anwendung wurde auf der GTK-Plattform entwickelt, einer plattformübergreifenden Toolkit-Bibliothek für die Erstellung von grafischen Benutzeroberflächen.

## Lizenzen
Diese Anwendung unterliegt den Lizenzbestimmungen der GTK-Bibliothek, die unter der LGPL (GNU Lesser General Public License) steht. Bitte überprüfen Sie die entsprechenden Lizenzinformationen für die Nutzung und Verteilung.

## Externe Bibliotheken
Die Anwendung verwendet die GTK-Bibliothek in der Version 3.0. Die korrekte Ausführung des Programms wird nur für diese Version gewährleistet.

## Anleitung zum Kompilieren und Ausführen des Spiels

### Anforderungen
- GTK3.0
- GCC (GNU Compiler Collection)

### Kompilierungsbefehl
```bash
gcc -o main main.c -g `pkg-config --cflags --libs gtk+-3.0`
```


## Globale Variablen
- `GtkWidget *window`: Das Hauptfenster der Anwendung.
- `GtkWidget *notebook`: Das Notebook-Widget für die Tabs.
- `GtkWidget *entry`: Das Eingabefeld für den Benutzernamen.
- `GtkWidget *user_input_button`: Die Schaltfläche zum Starten des Spiels.
- `GtkWidget *drawing_area`: Der Zeichenbereich für die Spielanzeige.
- `GtkWidget *username_label`: Das Label zur Anzeige des Benutzernamens.
- `GtkWidget *score_label`: Das Label zur Anzeige des Punktestands.

## Strukturen
- `LoggedInUser`: Struktur für den eingeloggten Benutzer mit `userName`, `userPoints` und `visible` Eigenschaften.
- `TargetSymbol`: Struktur für Zielobjekte mit `row`, `col`, `is_visible`, `symbol`, `move_down`, und `points` Eigenschaften.
- `FiredRocket`: Struktur für abgefeuerte Raketen mit `row`, `col`, `is_visible`, und `symbol` Eigenschaften.

## Arrays
- `firedRockets[100]`: Array für abgefeuerte Raketen.
- `targetEasy[10]`: Array für einfache Zielobjekte.
- `targetKingpin[5]`: Array für anspruchsvolle Zielobjekte.

## Symbole
- `crossSymbol`: Symbol für die Benutzerposition.
- `rocketSymbol`: Symbol für die abgefeuerte Rakete.
- `targetEasySymbol`: Symbol für einfache Zielobjekte.
- `targetKingpinSymbol`: Symbol für anspruchsvolle Zielobjekte.

## Zeiten
- `targetInitialTime`: Startzeit für die Bewegung der Zielobjekte (in ms).
- `rocketMoveDelay`: Zeitliche Verzögerung für die kontinuierliche Bewegung der Raketen (in ms).
- `rocketMoveId`: ID für die Zeitsteuerung der Rocket-Bewegung.

## Funktionen
- `move_symbols`: Funktion zur Bewegung der Symbole (Raketen und Zielobjekte).
- `on_key_press`: Callback-Funktion für Tastenereignisse.
- `on_draw`: Callback-Funktion für das Zeichnen im Zeichenbereich.
- `on_window_destroy`: Callback-Funktion für das Schließen des Hauptfensters.
- `collision_detection`: Funktion zur Kollisionsprüfung zwischen Raketen und Zielobjekten.
- `start_game`: Funktion zum Starten des Spiels und Initialisieren der Spielobjekte.
- `update_score`: Funktion zum Aktualisieren und Speichern des Punktestands.
- `read_user_scores`: Funktion zum Lesen des Punktestands aus einer Datei.

## Hauptfunktion `main`
- Initialisiert GTK.
- Erstellt das Hauptfenster, Tabs, Eingabefelder und Labels.
- Setzt die Callback-Funktionen für Ereignisse.
- Startet die GTK-Hauptschleife.

## Ablauf des Spiels
1. Der Benutzer gibt seinen Namen ein und startet das Spiel.
2. Die Funktion `start_game` initialisiert das Spiel, liest den Punktestand und aktualisiert die Anzeige.
3. Der Zeichenbereich wird für das Spiel konfiguriert.
4. Die Funktion `move_symbols` wird mit einer Zeitverzögerung aufgerufen, um die Symbole zu bewegen.
5. Der Benutzer kann mit den Pfeiltasten die Position ändern und mit der Leertaste Raketen abfeuern.
6. Kollisionen zwischen Raketen und Zielobjekten werden erkannt und der Punktestand aktualisiert.
7. Neue Zielobjekte werden erstellt, wenn alle alten getroffen wurden, und die Bewegungsgeschwindigkeit wird verdoppelt.

## Speichern des Punktestands
- Der Punktestand wird in einer Datei namens "userNames_scores.log" 
gespeichert.
- Beim Schließen des Fensters wird der Punktestand aktualisiert.

## Kollisionsdetektion

Die Funktion `collision_detection()` ist verantwortlich für die Erkennung von Kollisionen zwischen abgefeuerten Raketen und den Zielobjekten im Spiel. Sie spielt eine entscheidende Rolle, um Punkte zu vergeben und den Spielverlauf zu steuern.

### Ablauf der Kollisionsdetektion

1. **Überprüfung von Raketenkollisionen mit Zielobjekten:**
     - Die Funktion durchläuft alle abgefeuerten Raketen.
     - Für jede sichtbare Rakete wird überprüft, ob sie mit einem Zielobjekt kollidiert.
     - Kollisionen werden separat für einfache Zielobjekte (`targetEasy`) und anspruchsvolle Zielobjekte (`targetKingpin`) geprüft.

2. **Verarbeitung von Kollisionen:**
     - Bei einer Kollision zwischen einer Rakete und einem Zielobjekt wird die Sichtbarkeit der Rakete und des Zielobjekts auf "nicht sichtbar" gesetzt.
     - Die Punktzahl des eingeloggten Benutzers wird entsprechend der Art des getroffenen Zielobjekts aktualisiert.
     - Die Gesamtpunktzahl wird auf der Benutzeroberfläche angezeigt.

3. **Überprüfung aller Zielobjekte:**
     - Es wird überprüft, ob alle Zielobjekte getroffen wurden.
     - Wenn alle Zielobjekte getroffen wurden, werden neue Zielobjekte erstellt und die Bewegungsgeschwindigkeit der Objekte verdoppelt.

4. **Aktualisierung der Anzeige:**
     - Nach der Verarbeitung von Kollisionen werden die Anzeigen für Raketen und Zielobjekte auf der Zeichenfläche aktualisiert.
     - Die Benutzeroberfläche wird durch `gtk_widget_queue_draw()` neu gezeichnet.


## Hinweis
- Dies ist eine einfache Anwendung und kann weiter verbessert werden, z.B. durch Hinzufügen von Levels, Soundeffekten oder komplexeren Bewegungsmustern der Symbole.
