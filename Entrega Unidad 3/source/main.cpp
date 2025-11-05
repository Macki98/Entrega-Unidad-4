#ifndef NDEBUG
#include <vld.h> // Visual Leak Detector, útil en modo Debug para detectar fugas de memoria
#endif

#include "raylib.h"
#include <cstdlib>
#include <time.h>

int main(void)
{
    // Ventana de 1024x768 píxeles con un título personalizado
    InitWindow(1024, 768, "Sprites en accion - Leonel Tomas Mc Cormack");
    
    // Cargamos la imgagen
    Texture2D imagen = LoadTexture("Assets/ship-galaga.png");

    // Aplicamos un filtro bilineal a la textura
    SetTextureFilter(imagen, TEXTURE_FILTER_BILINEAR);

    // Cargamos la textura del cursor, aplicamos filtro y ocultamos el cursor del sistema
    Texture2D cursor = LoadTexture("Assets/crosshair.png");
    SetTextureFilter(cursor, TEXTURE_FILTER_BILINEAR);
    HideCursor();

    // Aplicamos el origen del cursor para que responda a la posicion actual del mouse
    Rectangle cursorRectangle = { 0,0, cursor.width, cursor.height};
    Vector2 cursorCenter = { cursor.width / 2, cursor.height / 2 };


    // Color del fondo
    Color fondo = RAYWHITE;

    // Color del Boton
    Color colorBoton = BLACK;

    // Radio del Boton
    float r = 50;

    // Boton para cambiar de color el fondo
    Vector2 Boton = { 970, 50 };


    // Posicion inicial de la nave 1
    Vector2 posImagen1 = {150, (768 / 2)};

    // velocidad que se le asignara a la nave
    Vector2 velocidad = { 5.0f, 100.0f };

    // Color de la nave 1
    Color colImagen1 = {255,161,0,255};

    // Rotacion de la nave 1 
    float rotImagen1 = 0.0f;
  
    // Escalado de la nave 1
    float escImagen1 = 0.5f;


    // Configuracion framerate
    SetTargetFPS(60);

    // Contador de veces presionada la tecla M para mostrar/ocultar msj de sistema
    int contador = -1;
    
    // Bucle principal del juego (se repite hasta que se cierre la ventana)
    while (!WindowShouldClose())
    {

        // Se establece un tiempo real
        float deltaTime = GetFrameTime();

        // Buffer de teclado que detecta si se presiono la tecla ESC para cerrar la ventana
        if (IsKeyPressed(KEY_ESCAPE)) {
            CloseWindow();
        }

        // Buffer de teclado que reinicia la posicion del personaje al presionar la R
        if (IsKeyPressed(KEY_R)) {
            posImagen1 = { 150, (768 / 2) };
        }

        // Buffer de teclado que muestra y oculta mensaje del sistema
        if (IsKeyPressed(KEY_M)) {
            contador++;
        }

        // Aplicamos movimiento horizontal  (izq y der ) sobre la Nave 1 utilizando flecha izquierda y derecha 
        if (IsKeyDown(KEY_LEFT)) {
            posImagen1.x -= velocidad.x;
        }
        if (IsKeyDown(KEY_RIGHT)) {
            posImagen1.x += velocidad.x;
        }

        // Aplicamos salto simple



        // Captura de eventos del mouse
            
            // Devuelve la posicion del mouse
        Vector2 windowPosition = GetMousePosition();
            // Booleano que chequea la posicion del mouse con la del boton
        bool collision = CheckCollisionPointCircle(windowPosition, Boton, r);
            // Funcion que permite cambiar el color del fondo
        if (collision && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {

            fondo.r = GetRandomValue(0, 255);
            fondo.g = GetRandomValue(0, 255);
            fondo.b = GetRandomValue(0, 255);
            
        }
     
        // Iniciamos la etapa de dibujo
        BeginDrawing();

        // Limpiamos la pantalla 
        ClearBackground(fondo);
        
        // Mensaje de sistema
        if (contador % 2 == 0) {
            DrawText("Nave 1", 2, 0, 25, BLACK);
            DrawText("Haz click izquierdo sobre el circulo negro para cambiar el color del fondo", 2, 25, 15, BLACK);
            DrawText(TextFormat("Posicion: %.1f, %.1f", posImagen1.x, posImagen1.y), 2, 70, 15, BLACK);
            DrawText(TextFormat("Posicion del mouse: X: %.2f Y: %.2f", windowPosition.x, windowPosition.y), 2, 50, 15, BLACK);
        }

        // Dibujamos la imagen para la nave 1 con sus parametros personalizados
        DrawTextureEx(imagen, posImagen1, rotImagen1, escImagen1, colImagen1);

        // Dibujamos el boton para cambiar el color del fondo
        DrawCircle(Boton.x, Boton.y, r, colorBoton);

        // Dibujamos el cursor con la posicion del mouse
        DrawTexturePro(cursor, cursorRectangle, {windowPosition.x, windowPosition.y, cursorRectangle.width, cursorRectangle.height}, cursorCenter, 0, WHITE);


        // Finalizamos el dibujo
        EndDrawing();
    }

    // Descargamos la imagen para liberar recursos
    UnloadTexture(imagen);

    // Cerramos la ventana
    CloseWindow();

    return 0;
}

