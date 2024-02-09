#include <iostream>
#include <string>
#include <thread>

using namespace std;

void typeText(const string& text) {
    for (char c : text) {
        cout << c;
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(10));
    }
}

int obtenerCarta() {
    return rand() % 10 + 1;
}

int obtenerTipoCarta() {
    return rand() % 4;
}

string valores[] = { "As", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jota", "Reina", "Rey" };
string tipos[] = { "Corazones", "Diamantes", "Treboles", "Picas" };

void mostrarCarta(int valor, int tipo) {
    cout << valores[valor - 1] << " de " << tipos[tipo] << " \n";
}

int calcularTotal(int mano[], int numCartas) {
    int total = 0;
    int ases = 0;
    for (int i = 0; i < numCartas; ++i) {
        if (mano[i] == 1) {
            ases++;
            total += 11;
        }
        else {
            total += mano[i];
        }
    }
    while (total > 21 && ases) {
        total -= 10;
        ases--;
    }
    return total;
}

int main() {
    typeText("Bienvenido al casino Billares, el lugar donde puedes disfrutar del emocionante Blackjack con un toque especial\n\n");
    srand(time(0));

    int jugador[5];
    int crupier[5];
    int numCartasJugador = 2;
    int numCartasCrupier = 2;

    for (int i = 0; i < 2; ++i) {
        jugador[i] = obtenerCarta();
        crupier[i] = obtenerCarta();
    }

    cout << "Bienvenido al juego de Blackjack!\n";

    while (true) {
        cout << "Tus cartas son: \n";
        for (int i = 0; i < numCartasJugador; ++i) {
            mostrarCarta(jugador[i], obtenerTipoCarta());
        }
        cout << "\nTotal entre las dos: " << calcularTotal(jugador, numCartasJugador) << "\n";

        char opcion;
        cout << "Quieres otra carta? (s/n): ";
        cin >> opcion;

        if (opcion == 's') {
            jugador[numCartasJugador++] = obtenerCarta();
            this_thread::sleep_for(chrono::milliseconds(500));
        }
        else {
            break;
        }

        if (calcularTotal(jugador, numCartasJugador) > 21) {
            cout << "Te has pasado de 21. Has perdido.\n";
            return 0;
        }
    }

    cout << "Las cartas del crupier son: \n";
    for (int i = 0; i < numCartasCrupier; ++i) {
        mostrarCarta(crupier[i], obtenerTipoCarta());
    }
    cout << "\n";

    while (calcularTotal(crupier, numCartasCrupier) < 17) {
        crupier[numCartasCrupier++] = obtenerCarta();
        cout << "El crupier toma una carta. Las cartas del crupier ahora son: \n";
        for (int i = 0; i < numCartasCrupier; ++i) {
            mostrarCarta(crupier[i], obtenerTipoCarta());
        }
        cout << "\n";
        this_thread::sleep_for(chrono::milliseconds(500));
    }

    cout << "Total del crupier: " << calcularTotal(crupier, numCartasCrupier) << "\n";

    int totalJugador = calcularTotal(jugador, numCartasJugador);
    int totalCrupier = calcularTotal(crupier, numCartasCrupier);

    if (totalJugador > totalCrupier || totalCrupier > 21) {
        cout << "Felicidades! Has ganado.\n";
    }
    else if (totalJugador < totalCrupier) {
        cout << "El crupier gana. Mejor suerte la pr�xima vez.\n";
    }
    else {
        cout << "Es un empate.\n";
    }

    return 0;
}
