#include <GL/glut.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> // Untuk fungsi trigonometri
bool remajaClicked = false;
bool OrangDewasaClicked = false;
bool drawCircle = false;
bool drawGreenCircleClicked = false; // New flag for green circle
bool drawRedCircleClicked = false;   // New flag for red circle

// Variabel global untuk animasi
float x_start = -0.47;
float y_start = 0.0;
float length = 0.094;
int num_zigs = 10;
bool directionUp = true;
float animasiTime = 0.0; // Waktu untuk animasi

/*
//Pola 12 Super Complex

const int UkuranDetakJantungRemaja = 12; //Ukuran Pola Detak Jantung
float PolaDetakJantungRemaja[UkuranDetakJantungRemaja] = {
    0.0, // Baseline
    0.1, // Awal Gelombang P
    0.2, // Puncak Gelombang P
    0.1, // Akhir Gelombang P
    0.0, // Kembali ke Baseline
    -0.1, // Bagian Q Kompleks QRS
    0.5, // Bagian R Kompleks QRS
    -0.3, // Bagian S Kompleks QRS
    0.0, // Kembali ke Baseline
    0.1, // Awal Gelombang T
    0.2, // Puncak Gelombang T
    0.0  // Kembali ke Baseline
}; // Pola detak jantung


*/


//Pola Sederhana
const int UkuranDetakJantungDewasa = 3;
float PolaDetakJantungDewasa[UkuranDetakJantungDewasa] = {
0.0, 0.3, -0.3
}; // Pola detak jantung



//Pola Complex
const int UkuranDetakJantungRemaja = 4;
float PolaDetakJantungRemaja[UkuranDetakJantungRemaja] = {
0.0, 0.3, -0.3, 0.1
}; // Pola detak jantung

const int bpm_remaja = 71; //Nilai Detak Jantung


//float durasiSatuLangkah = 1.0f / (bpm_remaja * UkuranDetakJantungRemaja);
float SiklusDetakJantungRemaja = 1.0f / bpm_remaja; //dalam satuan detik
float animasiStep_Remaja = SiklusDetakJantungRemaja / UkuranDetakJantungRemaja;

const int bpm_dewasa = 77; //Nilai Detak Jantung


//float durasiSatuLangkah = 1.0f / (bpm_remaja * UkuranDetakJantungRemaja);
float SiklusDetakJantungDewasa = 1.0f / bpm_dewasa; //dalam satuan detik
float animasiStep_Dewasa = SiklusDetakJantungDewasa / UkuranDetakJantungDewasa;




void drawText(float x, float y, const char *text, float red, float green, float blue, void *font, int fontSize) {
    glColor3f(red, green, blue);
    glRasterPos2f(x, y);
    for (size_t i = 0; i < strlen(text); i++) {
        glutBitmapCharacter(font, text[i]);
    }
}




void drawButton(float x, float y, float width, float height, float red, float green, float blue) {
    glBegin(GL_QUADS);
    glColor3f(red, green, blue);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

void drawRemaja() {

    drawText(-0.40, -0.500, "REMAJA", 0.0, 0.0, 0.0, GLUT_BITMAP_HELVETICA_12, 12);
    drawText(-0.40, -0.530, "Umur : 17-27", 0.0, 0.0, 0.0, GLUT_BITMAP_HELVETICA_12, 12);
    drawText(-0.40, -0.560, "Berat Badan : 42-55", 0.0, 0.0, 0.0, GLUT_BITMAP_HELVETICA_12, 12);
    drawText(-0.40, -0.590, "Kondisi Badan : Sehat", 0.0, 0.0, 0.0, GLUT_BITMAP_HELVETICA_12, 12);
    drawText(-0.40, -0.620, "Data Detak Jantung Yang Dihasilkan Per Menit : 71 Bpm ", 0.0, 0.0, 0.0, GLUT_BITMAP_HELVETICA_12, 12);
    drawText(-0.40, -0.650, "Kondisi Aktifitas : Kondisi Diam (Sedang Test)", 0.0, 0.0, 0.0, GLUT_BITMAP_HELVETICA_12, 12);
}

void drawOrangDewasa() {

    drawText((0.1 + 0.5) / 3 - 0.1, (-0.7 - 0.8) / 2 + 0.250, "ORANG DEWASA", 0.0, 0.0, 0.0, GLUT_BITMAP_HELVETICA_12, 12);
    drawText((0.1 + 0.5) / 3 - 0.1, (-0.7 - 0.8) / 2 + 0.220, "Umur: 42-61", 0.0, 0.0, 0.0, GLUT_BITMAP_HELVETICA_12, 12);
    drawText((0.1 + 0.5) / 3 - 0.1, (-0.7 - 0.8) / 2 + 0.190, "Berat Badan : 42-55", 0.0, 0.0, 0.0, GLUT_BITMAP_HELVETICA_12, 12);
    drawText((0.1 + 0.5) / 3 - 0.1, (-0.7 - 0.8) / 2 + 0.160, "Kondisi Badan: Sehat", 0.0, 0.0, 0.0, GLUT_BITMAP_HELVETICA_12, 12);
    drawText((0.1 + 0.5) / 3 - 0.1, (-0.7 - 0.8) / 2 + 0.130, "Data Detak Jantung Yang Dihasilkan Per Menit: 77 Bpm", 0.0, 0.0, 0.0, GLUT_BITMAP_HELVETICA_12, 12);
    drawText((0.1 + 0.5) / 3 - 0.1, (-0.7 - 0.8) / 2 + 0.100, "Kondisi Aktifitas: Kondisi Diam (Sedang Test)", 0.0, 0.0, 0.0, GLUT_BITMAP_HELVETICA_12, 12);
}

void drawSmallRedCircle(double x, double y, double radius, int segments) {
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0, 0.0, 0.0);  // Warna merah

    for (int i = 0; i <= segments; i++) {
        double angle = 2.0 * M_PI * i / segments;
        double xPos = x + radius * cos(angle);
        double yPos = y + radius * sin(angle);
        glVertex2d(xPos, yPos);
    }

    glEnd();
    drawText(x - 0.01, y - 0.01, "OFF", 1.0, 1.0, 1.0, GLUT_BITMAP_HELVETICA_12, 12);
    drawCircle = true;
}


void drawSmallGreenCircle(double x, double y, double radius, int segments) {
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.0, 1.0, 0.0); // Warna hijau

    for (int i = 0; i <= segments; i++) {
        double angle = 2.0 * M_PI * i / segments;
        double xPos = x + radius * cos(angle);
        double yPos = y + radius * sin(angle);
        glVertex2d(xPos, yPos);
    }

    glEnd();

    // Menambahkan teks "ON" di tengah lingkaran
    drawText(x - 0.01, y - 0.01, "ON", 0.0, 0.0, 0.0, GLUT_BITMAP_HELVETICA_12, 12);
    drawCircle = true;
}

void drawTextCircle(double x, double y, const char *text, float red, float green, float blue, void *font, int fontSize) {
    glColor3f(red, green, blue);
    glRasterPos2d(x, y);
    for (size_t i = 0; i < strlen(text); i++) {
        glutBitmapCharacter(font, text[i]);
    }
}


void GambarDetakJantungRemaja(float x_start, float length, int num_zigs) {
    if (drawCircle && drawGreenCircleClicked) {
        glBegin(GL_LINE_STRIP);
        glColor3f(1.0, 0.0, 0.0); // Warna merah untuk detak jantung

        float x = x_start;
        float y = 0.0;

        for (int i = 0; i < num_zigs; ++i) {
            glVertex2f(x, y); // Titik awal

            int patternIndex = (int)(animasiTime + i) % UkuranDetakJantungRemaja; // Dapatkan indeks pola berdasarkan waktu animasi
            y = PolaDetakJantungRemaja[patternIndex]; // Atur y berdasarkan pola detak jantung

            x += length; // Pindahkan x ke kanan
            glVertex2f(x, y); // Titik akhir
        }

        glEnd();
    }
}


void GambarDetakJantungDewasa(float x_start, float length, int num_zigs) {
    if (drawCircle && drawGreenCircleClicked) {
        glBegin(GL_LINE_STRIP);
        glColor3f(1.0, 0.0, 0.0); // Warna merah untuk detak jantung

        float x = x_start;
        float y = 0.0;

        for (int i = 0; i < num_zigs; ++i) {
            glVertex2f(x, y); // Titik awal

            int patternIndex = (int)(animasiTime + i) % UkuranDetakJantungDewasa; // Dapatkan indeks pola berdasarkan waktu animasi
            y = PolaDetakJantungDewasa[patternIndex]; // Atur y berdasarkan pola detak jantung

            x += length; // Pindahkan x ke kanan
            glVertex2f(x, y); // Titik akhir
        }

        glEnd();
    }
}




void update_remaja(int value) {
    animasiTime -= animasiStep_Remaja; // Kurangi animasiStep_Remaja dari waktu animasi untuk bergerak ke kiri
    if (animasiTime < 0) animasiTime += UkuranDetakJantungRemaja; // Reset animasiTime jika lebih kecil dari 0

    // Redraw
    glutPostRedisplay();
    glutTimerFunc(16, update_remaja, 0); // Panggil update_remaja setiap ~16 ms (untuk ~60FPS)
}

void update_dewasa(int value) {
    animasiTime -= animasiStep_Dewasa; // Kurangi animasiStep_Remaja dari waktu animasi untuk bergerak ke kiri
    if (animasiTime < 0) animasiTime += UkuranDetakJantungDewasa; // Reset animasiTime jika lebih kecil dari 0

    // Redraw
    glutPostRedisplay();
    glutTimerFunc(16, update_dewasa, 0); // Panggil update_remaja setiap ~16 ms (untuk ~60FPS)
}

void display() {

    glClear(GL_COLOR_BUFFER_BIT);

    // Menggambar persegi dengan vertex dan warna kuning pada setiap sudut
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 0.0);  // Warna kuning
    glVertex2f(-0.5, -0.8);   // Vertex kiri bawah (diperlebar)
    glVertex2f(0.55, -0.8);    // Vertex kanan bawah (diperlebar)
    glVertex2f(0.55, 0.6);     // Vertex kanan atas
    glVertex2f(-0.5, 0.6);    // Vertex kiri atas
    glEnd();

// Menggambar lingkaran kecil

    drawSmallRedCircle(0.51, +0.30, 0.03, 1000);

  drawSmallGreenCircle(0.51, 0.40, 0.03, 1000);

    // Menggambar tombol "Remaja"
    drawButton(-0.4, -0.8, 0.4, 0.1, 0.0, 0.0, 1.0);

    drawText(-0.25, -0.765, "REMAJA", 1.0, 1.0, 1.0, GLUT_BITMAP_HELVETICA_12, 12);


    // Menggambar tombol "Orang Tua"
    drawButton(0.1, -0.8, 0.4, 0.1, 0.0, 0.0, 1.0);
    drawText((0.1 + 0.5) / 2 - 0.07, (-0.7 - 0.8) / 2 - 0.01, "ORANG DEWASA", 1.0, 1.0, 1.0, GLUT_BITMAP_HELVETICA_12, 12);


  // Menggambar kotak hitam di tengah (diperbesar)
glBegin(GL_QUADS);
glColor3f(0.0, 0.0, 0.0);  // Warna hitam
glVertex2f(-0.47, -0.47);    // Vertex kiri bawah
glVertex2f(0.47, -0.47);     // Vertex kanan bawah
glVertex2f(0.47, 0.47);      // Vertex kanan atas
glVertex2f(-0.47, 0.47);     // Vertex kiri atas
glEnd();

    glColor3f(1.0, 0.0, 0.0); // Warna merah untuk detak jantung

    if (OrangDewasaClicked) {
             GambarDetakJantungDewasa(x_start, length, num_zigs);
        drawOrangDewasa();
    }


       if (remajaClicked) {
    GambarDetakJantungRemaja(x_start, length, num_zigs);
        drawRemaja();
    }



    glutSwapBuffers();




    glFlush();


}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}

void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        float normalizedX = (float)x / glutGet(GLUT_WINDOW_WIDTH) * 2 - 1;
        float normalizedY = 1 - (float)y / glutGet(GLUT_WINDOW_HEIGHT) * 2;

        float normalizedXI = (float)x / glutGet(GLUT_WINDOW_WIDTH) * 2 - 1;
        float normalizedYI = 1 - (float)y / glutGet(GLUT_WINDOW_HEIGHT) * 2;

        // Check if clicked on "Remaja" button
        if (normalizedX >= -0.4 && normalizedX <= 0 && normalizedY >= -0.8 && normalizedY <= -0.7) {
            remajaClicked = true;
            OrangDewasaClicked = false;
            drawGreenCircleClicked = true;

        }

        // Check if clicked on "Orang Dewasa" button
        if (normalizedX >= 0.1 && normalizedX <= 0.5 && normalizedY >= -0.8 && normalizedY <= -0.7) {
            OrangDewasaClicked = true;
            remajaClicked = false;
            drawGreenCircleClicked = true;
        }

        // Check if clicked on green circle
        if (normalizedXI >= 0.48 && normalizedXI <= 0.54 && normalizedYI >= 0.37 && normalizedYI <= 0.43) {
            remajaClicked = true;
            OrangDewasaClicked = false;
            drawGreenCircleClicked = true;
            drawRedCircleClicked = false;
        }

        // Check if clicked on red circle
        if (normalizedXI >= 0.48 && normalizedXI <= 0.54 && normalizedYI >= 0.27 && normalizedYI <= 0.33) {
            drawRedCircleClicked = true;
            drawGreenCircleClicked = false;
        }

        glutPostRedisplay();
    }
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1600, 900);  // Ukuran layar 1600x900
    glutCreateWindow("EKG");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouseClick);
    glClearColor(1.0, 1.0, 1.0, 1.0); // Warna background putih
    glutTimerFunc(0, update_remaja, 0);
        glutTimerFunc(0, update_dewasa, 0);
       glutMainLoop();

    return 0;
}
