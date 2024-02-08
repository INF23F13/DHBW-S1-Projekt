#include <gtk/gtk.h>

// Globale Variablen für das Hauptfenster und die Spielobjekte
GtkWidget *window;
GtkWidget *notebook;
GtkWidget *entry;
GtkWidget *user_input_button;
GtkWidget *drawing_area;
GtkWidget *username_label;
GtkWidget *score_label;

int cross_row = 63;
int cross_col = 32; //line 304 > 

gboolean moving_arrow = FALSE; // dürfte nicht mehr gebraucht werden. keine weiteren referenzen

// Struktur für den eingeloggten Benutzer
typedef struct {
    char userName[50]; //pruefen wenn user in datei Load User from fileelse wirte in the file user with point score default
    int userPoints;
    gboolean visible;
} LoggedInUser;

LoggedInUser loggedInUser; 

// Struktur für Zielobjekte
typedef struct {
    int row;
    int col;
    gboolean is_visible;
    char symbol[3];
    gboolean move_down; // Flag für Richtungswechsel
    int points;
} TargetSymbol;

// Struktur für abgefeuerte Raketen
typedef struct {
    int row;
    int col;
    gboolean is_visible;
    char symbol[3];
} FiredRocket;

// Arrays für Zielobjekte und Raketen
FiredRocket firedRockets[100];
TargetSymbol targetEasy[10];
TargetSymbol targetKingpin[5];

// Symbole für Anzeige
char crossSymbol[] = ">||<";
char rocketSymbol[] = "!";
char targetEasySymbol[] = "<>";
char targetKingpinSymbol[] = "<|>";
char arrowSymbol = '^'; // dürfte nicht mehr gebraucht werden. keine weiteren referenzen

gboolean move_symbols(gpointer user_data);
gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer user_data);
gboolean on_draw(GtkWidget *widget, cairo_t *cr, gpointer user_data);
void on_window_destroy(GtkWidget *widget, gpointer user_data);

void start_game(GtkWidget *widget, gpointer user_data);
void update_score(const gchar *username, int points);

gboolean read_user_scores(const gchar *username, int *points);

// Hauptfunktion
int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // Hauptfenster erstellen
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Symbolbewegung");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 800);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(on_window_destroy), NULL);

    // Notebook erstellen (für Tabs)
    notebook = gtk_notebook_new();
    gtk_container_add(GTK_CONTAINER(window), notebook);

    // Erster Tab: Benutzereingabe
    GtkWidget *tab1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), tab1, gtk_label_new("User Input"));

    entry = gtk_entry_new();
    user_input_button = gtk_button_new_with_label("Submit");
    g_signal_connect(G_OBJECT(user_input_button), "clicked", G_CALLBACK(start_game), NULL);

    gtk_box_pack_start(GTK_BOX(tab1), entry, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(tab1), user_input_button, FALSE, FALSE, 5);

    // Zweiter Tab: Spielanzeige
    GtkWidget *tab2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), tab2, gtk_label_new("Game Display"));

    GtkWidget *fixed = gtk_fixed_new();  // Fixed Container für das Drawing Area
    gtk_container_add(GTK_CONTAINER(tab2), fixed);

    drawing_area = gtk_drawing_area_new();
    gtk_widget_set_size_request(drawing_area, 800, 800);  // Größe des Zeichenbereichs
    gtk_fixed_put(GTK_FIXED(fixed), drawing_area, 0, 0);

    GtkWidget *grid = gtk_grid_new();  // Grid für die Anordnung von Widgets
    gtk_container_add(GTK_CONTAINER(tab2), grid);

    username_label = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid), username_label, 0, 0, 1, 1);

    score_label = gtk_label_new("Score: 0");
    gtk_grid_attach(GTK_GRID(grid), score_label, 0, 1, 1, 1);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}

// Funktion zum Starten des Spiels
void start_game(GtkWidget *widget, gpointer user_data) {
    const gchar *username = gtk_entry_get_text(GTK_ENTRY(entry));

    // Überprüfen, ob der Benutzername in der Datei vorhanden ist
    int points = 0;
    if (read_user_scores(username, &points)) {
        // Benutzername gefunden, Punktestand aktualisieren
        loggedInUser.userPoints = points;
        update_score(username, points);
    } else {
        // Benutzername nicht gefunden, neuen Benutzer erstellen
        loggedInUser.userPoints = 0;
        update_score(username, 0);
    }

    gtk_label_set_text(GTK_LABEL(username_label), username);
    gtk_label_set_text(GTK_LABEL(score_label), g_strdup_printf("Score: %d", loggedInUser.userPoints));

    gtk_notebook_set_current_page(GTK_NOTEBOOK(notebook), 1);

    // Step 2: Game Start
    GtkWidget *grid = gtk_grid_new();  // Grid für die Anordnung von Widgets
    gtk_container_add(GTK_CONTAINER(notebook), grid);

    GtkWidget *score_label = gtk_label_new("Score: 0");
    gtk_grid_attach(GTK_GRID(grid), score_label, 0, 1, 1, 1);

    g_signal_connect(G_OBJECT(drawing_area), "draw", G_CALLBACK(on_draw), NULL);
    g_signal_connect(G_OBJECT(window), "key-press-event", G_CALLBACK(on_key_press), NULL);

    g_timeout_add(100, (GSourceFunc)move_symbols, NULL);  // Änderung auf 100 Millisekunden

    for (int i = 0; i < 100; i++) {
        firedRockets[i].is_visible = FALSE;
    }

    // Setze die Startpositionen der Symbole vom Typ 3 und Typ 4
    for (int i = 0; i < 10; i++) {
        targetEasy[i].row = 2; //easy target starten auf 2
        targetEasy[i].col = i * 2; // Breiter Abstand
        targetEasy[i].is_visible = TRUE;
        targetEasy[i].move_down = TRUE; // initial direction is down
        strcpy(targetEasy[i].symbol, targetEasySymbol);
        targetEasy[i].points = 10; //hier muesste eigentlich der userPointScore aukualisiert werden
    }

    for (int i = 0; i < 5; i++) {
        targetKingpin[i].row = 1; //kingpin target starten auf 2
        targetKingpin[i].col = i * 2; // Breiterer Abstand
        targetKingpin[i].is_visible = TRUE;
        targetKingpin[i].move_down = TRUE; // initial direction is down
        strcpy(targetKingpin[i].symbol, targetKingpinSymbol);
        targetKingpin[i].points = 20; //hier muesste eigentlich der userPointScore aukualisiert werden
    }

    gtk_widget_show_all(window);

    gtk_main();
}


// Funktion zur Kollisionsprüfung
void collision_detection() {
    gboolean all_targets_hit = TRUE;

    // Prüfe Kollisionen mit Raketen
    for (int i = 0; i < 100; i++) {
        if (firedRockets[i].is_visible) {
            // Prüfe Kollision mit einfachen Zielobjekten
            for (int j = 0; j < 10; j++) {
                if (targetEasy[j].is_visible && firedRockets[i].row == targetEasy[j].row && firedRockets[i].col == targetEasy[j].col) {
                    // Kollision mit einfachem Zielobjekt
                    firedRockets[i].is_visible = FALSE;
                    targetEasy[j].is_visible = FALSE;
                    loggedInUser.userPoints += targetEasy[j].points;
					printf("User Points: %.2d\n",loggedInUser.userPoints);
                }
            }

            // Prüfe Kollision mit anspruchsvollen Zielobjekten
            for (int j = 0; j < 5; j++) {
                if (targetKingpin[j].is_visible && firedRockets[i].row == targetKingpin[j].row && firedRockets[i].col == targetKingpin[j].col) {
                    // Kollision mit anspruchsvollem Zielobjekt
                    firedRockets[i].is_visible = FALSE;
                    targetKingpin[j].is_visible = FALSE;
                    loggedInUser.userPoints += targetKingpin[j].points;
					printf("User Points: %.2d\n",loggedInUser.userPoints);
                }
            }
        }
    }

    // Prüfe, ob alle Zielobjekte getroffen wurden
    for (int j = 0; j < 10; j++) {
        if (targetEasy[j].is_visible) {
            all_targets_hit = FALSE;
            break;
        }
    }

    for (int j = 0; j < 5; j++) {
        if (targetKingpin[j].is_visible) {
            all_targets_hit = FALSE;
            break;
        }
    }

    // Wenn alle Zielobjekte getroffen wurden, erstelle neue und verdopple die Bewegungsgeschwindigkeit
    if (all_targets_hit) {
        for (int i = 0; i < 10; i++) {
            targetEasy[i].row = 2;
            targetEasy[i].col = i * 2;
            targetEasy[i].is_visible = TRUE;
            targetEasy[i].move_down = TRUE;
            strcpy(targetEasy[i].symbol, targetEasySymbol);
            targetEasy[i].points = 10;
        }

        for (int i = 0; i < 5; i++) {
            targetKingpin[i].row = 1;
            targetKingpin[i].col = i * 12;
            targetKingpin[i].is_visible = TRUE;
            targetKingpin[i].move_down = TRUE;
            strcpy(targetKingpin[i].symbol, targetKingpinSymbol);
            targetKingpin[i].points = 20;
        }

        // Verdopple die Bewegungsgeschwindigkeit
        for (int i = 0; i < 10; i++) {
            targetEasy[i].col += targetEasy[i].move_down ? 2 : -2;
        }

        for (int i = 0; i < 5; i++) {
            targetKingpin[i].col += targetKingpin[i].move_down ? 2 : -2;
        }
    }
}

// Funktion zum Lesen der Punkte des Benutzers aus der Datei
gboolean read_user_scores(const gchar *username, int *points) {
    FILE *file = fopen("userNames_scores.log", "r");
    if (file == NULL) {
        // Die Datei existiert nicht, erstelle sie
        file = fopen("userNames_scores.log", "w");
        if (file == NULL) {
            g_print("Error creating file.\n");
            return FALSE;
        }
        fclose(file);

        // Setze die Punkte auf 0, da der Benutzer neu erstellt wurde
        *points = 0;
        return TRUE;
    }

    gchar buffer[100];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        gchar fileUsername[50];
        int filePoints;
        if (sscanf(buffer, "%s %d", fileUsername, &filePoints) == 2) {
            if (strcmp(username, fileUsername) == 0) {
                *points = filePoints;
                fclose(file);
                return TRUE;
            }
        }
    }

    fclose(file);
    return FALSE;
}

// Funktion zum Aktualisieren des Punktestands des Benutzers in der Datei
void update_score(const gchar *username, int points) {
    FILE *file = fopen("userNames_scores.log", "a");
    if (file != NULL) {
        fprintf(file, "%s %d\n", username, points);
        fclose(file);
    }
}

// Funktion zum Verarbeiten von Tastatureingaben
gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer user_data) {
    switch (event->keyval) {
        case GDK_KEY_space:
            for (int i = 0; i < 100; i++) {
                if (!firedRockets[i].is_visible) {
                    firedRockets[i].row = cross_row;
                    firedRockets[i].col = cross_col;
                    firedRockets[i].is_visible = TRUE;
                    strcpy(firedRockets[i].symbol, rocketSymbol);
                    break;
                }
            }
            break;
        case GDK_KEY_Left:
            cross_col = MAX(1, cross_col - 1);
            break;
        case GDK_KEY_Right:
            cross_col = MIN(64, cross_col + 1);
            break;
        default:
            break;
    }

    gtk_widget_queue_draw(drawing_area);

    return TRUE;
}

// Funktion zum Zeichnen der Spielobjekte
gboolean on_draw(GtkWidget *widget, cairo_t *cr, gpointer user_data) {
    gint width, height;
    gtk_window_get_size(GTK_WINDOW(window), &width, &height);

    gint cell_size = MIN(width / 64, height / 64);

    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 64; j++) {
            cairo_set_source_rgb(cr, 0.9, 0.9, 0.9);
            cairo_rectangle(cr, j * cell_size, i * cell_size, cell_size, cell_size);
            cairo_fill(cr);
        }
    }

    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_set_line_width(cr, 2);

    // Zeichne den Spieler
    cairo_move_to(cr, cross_col * cell_size, cross_row * cell_size);
    cairo_show_text(cr, crossSymbol);

    // Zeichne die abgefeuerten Raketen
    for (int i = 0; i < 100; i++) {
        if (firedRockets[i].is_visible) {
            cairo_move_to(cr, firedRockets[i].col * cell_size, firedRockets[i].row * cell_size);
            cairo_show_text(cr, firedRockets[i].symbol);
        }
    }

    // Zeichne die einfachen Zielobjekte
    for (int i = 0; i < 10; i++) {
        if (targetEasy[i].is_visible) {
            cairo_move_to(cr, targetEasy[i].col * cell_size, targetEasy[i].row * cell_size);
            cairo_show_text(cr, targetEasy[i].symbol);
        }
    }

    // Zeichne die anspruchsvollen Zielobjekte
    for (int i = 0; i < 5; i++) {
        if (targetKingpin[i].is_visible) {
            cairo_move_to(cr, targetKingpin[i].col * cell_size, targetKingpin[i].row * cell_size);
            cairo_show_text(cr, targetKingpin[i].symbol);
        }
    }

    return FALSE;
}

// Funktion zum Bewegen der Spielobjekte
gboolean move_symbols(gpointer user_data) {
    // Bewege die abgefeuerten Raketen nach oben
    for (int i = 0; i < 100; i++) {
        if (firedRockets[i].is_visible) {
            firedRockets[i].row--;

            if (firedRockets[i].row < 0) {
                firedRockets[i].is_visible = FALSE;
            }
        }
    }

    // Hier entferne den Aufruf von check_collisions()
    // check_collisions();

    // Bewege die einfachen Zielobjekte
    for (int i = 0; i < 10; i++) {
        if (targetEasy[i].is_visible) {
            if (targetEasy[i].move_down) {
                targetEasy[i].col++;

                if (targetEasy[i].col >= 63) {
                    targetEasy[i].col = 63;
                    targetEasy[i].move_down = FALSE;
                    targetEasy[i].row++;
                }
            } else {
                targetEasy[i].col--;

                if (targetEasy[i].col <= 0) {
                    targetEasy[i].col = 0;
                    targetEasy[i].move_down = TRUE;
                    targetEasy[i].row++;
                }
            }
        }
    }

    // Hier entferne den Aufruf von check_collisions()
    // check_collisions();

    // Bewege die anspruchsvollen Zielobjekte
    for (int i = 0; i < 5; i++) {
        if (targetKingpin[i].is_visible) {
            if (targetKingpin[i].move_down) {
                targetKingpin[i].col++;

                if (targetKingpin[i].col >= 63) {
                    targetKingpin[i].col = 63;
                    targetKingpin[i].move_down = FALSE;
                    targetKingpin[i].row++;
                }
            } else {
                targetKingpin[i].col--;

                if (targetKingpin[i].col <= 0) {
                    targetKingpin[i].col = 0;
                    targetKingpin[i].move_down = TRUE;
                    targetKingpin[i].row++;
                }
            }
        }
    }

    // Hier entferne den Aufruf von check_collisions()
    // check_collisions();

    // Prüfe Kollisionen
    collision_detection();

    gtk_widget_queue_draw(drawing_area);

    return TRUE;
}


// Funktion zum Behandeln des Zerstörungsereignisses des Hauptfensters
void on_window_destroy(GtkWidget *widget, gpointer user_data) {
    g_source_remove_by_user_data(GUINT_TO_POINTER(1));
    gtk_main_quit();
}

