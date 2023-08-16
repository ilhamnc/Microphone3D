#include <windows.h>
#include <GL/glut.h>

// inisialisasi variabel untuk transformasi seperti translasi, rotasi atau scaling
float angle = 0.0f;					// sudut transformasi kamera
float posX = 0.0f, rotX =  0.0f;	// posisi kamera di sumbu X
float posY = 0.0f, rotY =  0.0f;	// posisi kamera di sumbu Y
float posZ = 5.0f, rotZ = -1.0f;	// posisi kamera di sumbu Z

float objectAngleX = 0.0f;			// sudut tranformasi obyek di sumbu X
float objectAngleY = 0.0f;			// sudut tranformasi obyek di sumbu Y
float objectAngleZ = 0.0f;			// sudut tranformasi obyek di sumbu Z

// fungsi untuk menggambar cylinder sama radius atas-bawah
void drawCylinder(float radius, float height, int slices, int stacks)
{
	glPushMatrix();
	GLUquadricObj* cyl = gluNewQuadric();
	
	// buat tutup atas silinder
	glTranslatef(0.0f, -height/2, 0.0f);
	glRotatef(-90, 1.0f, 0.0f, 0.0f);
	gluDisk(cyl, 0.0f, radius, slices, stacks);
	
	// buat badan silinder
	gluCylinder(cyl, radius, radius*1.5, height, slices, stacks);
	
	// buat tutup bawah silinder
	glTranslatef(0.0f, 0.0f, height);
	gluDisk(cyl, 0.0f, radius, slices, stacks);
	glPopMatrix();
}

// fungsi untuk menggambar cylinder beda radius atas-bawah
void drawCyl(float radius, float height, int slices, int stacks)
{
	glPushMatrix();
	GLUquadricObj* cyl = gluNewQuadric();
	
	// buat tutup atas silinder
	glTranslatef(0.0f, -height/2, 0.0f);
	glRotatef(-90, 1.0f, 0.0f, 0.0f);
	gluDisk(cyl, 0.0f, radius, slices, stacks);
	
	// buat badan silinder
	gluCylinder(cyl, radius, radius, height, slices, stacks);
	
	// buat tutup bawah silinder
	glTranslatef(0.0f, 0.0f, height);
	gluDisk(cyl, 0.0f, radius, slices, stacks);
	glPopMatrix();
}

// Fungsi untuk menggambar microphone
void drawMicrophone() {
    // Bagian atas microphone
    glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, 2.0f, 0.0f);
    glutSolidSphere(0.88, 20, 20);
    
    // Pegangan microphone
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, -2.0f, 0.0f);
    drawCylinder(0.4, 5, 20, 20);

    // Kabel di bagian bawah pegangan
    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslatef(0.0f, -2.8f, 0.0f);
    drawCylinder(0.1, 1.0, 100, 100);
    
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, 0.0f);
    drawCyl(0.06, 3.0, 20, 20);
    glPopMatrix();
    
    // Permukaan atas microphone
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslatef(0.0f, 2.0f, 0.0f);
    glRotatef(-90, 2.0f, 0.0f, 0.0f);
    glutWireSphere(0.9, 40, 35);
    glPopMatrix();
    
    // bagian tengah bola microphone
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslatef(0.0f, 2.0f, 0.0f);
    drawCyl(0.92, 0.1, 20, 20);
    glTranslatef(0.0f, -0.8f, 0.0f);
    drawCyl(0.6, 0.2, 20, 20);
    glPopMatrix();
}

// fungsi untuk menggambar obyek
void drawObject()
{
	// obyek bisa dimasukkan diantara glPushMatrix() dan glPopMatrix() 
	// fungsinya agar obyek tidak terpengaruh atau mempengaruhi obyek lain
	// saat diwarnai, ditransformasi dan sebagainya
	glPushMatrix();

	// operasi transformasi rotasi obyek ke arah kanan-kiri
	glRotatef(objectAngleY, 0.0f, 1.0f, 0.0f);

	glPushMatrix();

	// operasi transformasi rotasi obyek ke arah atas-bawah
	glRotatef(objectAngleX, 1.0f, 0.0f, 0.0f);

	drawMicrophone();
	
	glPopMatrix();

	glPopMatrix();
}

// taruh semua obyek yang akan digambar di fungsi display()
void display()
{
	// bersihkan dan reset layar dan buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	glTranslatef(0.0f, 0.0f, -5.0f);


	// posisikan kamera pandang
	// dalam hal ini sumbu Y ada diatas dan posisi kamera pandang di (posX, posY, posZ)
	gluLookAt(posX, posY, posZ, posX + rotX, posY + rotY, posZ + rotZ, 0.0f, 1.0f, 0.0f);

	// panggil fungsi untuk menggambar obyek
	drawObject();
	
	glFlush();
	glutSwapBuffers();
}

// inisialisasikan variabel, pencahayaan, tekstur dan pengaturan kamera pandang di fungsi init()
void init(void)
{
	// inisialisasi warna latar belakang layar dalam hal ini warna putih (1.0, 1.0, 1.0, 0.0)
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glEnable(GL_DEPTH_TEST);				// mengaktifkan depth buffer
	glMatrixMode(GL_PROJECTION);		
	glLoadIdentity();
	gluPerspective(45.0, 1.0, 1.0, 100.0);	// set proyeksi ke perspektif
	glMatrixMode(GL_MODELVIEW);				
	glLoadIdentity();						
	// inisialisasi kamera pandang
	gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	// enable lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHT0);
}

// fungsi ini digunakan bila layar akan diresize (default)
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

// fungsi untuk mengatur masukan dari keyboard 
// untuk arah kiri, kanan, atas, bawah, PgUp, dan PgDn
void keyboard(int key, int x, int y)
{
	float fraction = 0.1f;

	switch (key) 
	{
	// masukkan perintah disini bila tombol kiri ditekan
	case GLUT_KEY_LEFT:
		// dalam hal ini perintah rotasi obyek ke kiri sebanyak 1 derajat 
		objectAngleY -= 1.0f;
		glutPostRedisplay();	// update obyek
		break;
	// masukkan perintah disini bila tombol kanan ditekan
	case GLUT_KEY_RIGHT:		
		// dalam hal ini perintah rotasi obyek ke kanan sebanyak 1 derajat 
		objectAngleY += 1.0f;
		glutPostRedisplay();	// update obyek
		break;
	// masukkan perintah disini bila tombol atas ditekan
	case GLUT_KEY_UP:		
		// dalam hal ini perintah rotasi obyek ke atas sebanyak 1 derajat 
		objectAngleX -= 1.0f;
		glutPostRedisplay();	// update obyek
		break;
	// masukkan perintah disini bila tombol bawah ditekan
	case GLUT_KEY_DOWN:		
		// dalam hal ini perintah rotasi obyek ke bawah sebanyak 1 derajat 
		objectAngleX += 1.0f;
		glutPostRedisplay();	// update obyek
		break;
	// zoom in
	case GLUT_KEY_PAGE_UP:
		// masukkan perintah disini bila tombol PgUp ditekan
		posX += rotX * fraction;		
		posZ += rotZ * fraction;
		glutPostRedisplay();	// update obyek
		break;
	// zoom out
	case GLUT_KEY_PAGE_DOWN:
		// masukkan perintah disini bila tombol PgDn ditekan
		posX -= rotX * fraction;
		posZ -= rotZ * fraction;
		glutPostRedisplay();	// update obyek
		break;
	}
}


// program utama
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// set ukuran jendela tampilan
	glutInitWindowSize(600, 600);		// besarnya jendela dalam piksel dalam hal ini 300x300
	glutInitWindowPosition(50, 50);	// posisi jendela dilayar komputer dalam piksel
	glutCreateWindow("REPRESENTASI MICROPHONE 3D");
	
	// panggil fungsi init untuk inisialisasi awal
	init();

	// event handler untuk display, reshape dan keyboard
	glutDisplayFunc(display);   // display
	glutReshapeFunc(reshape);   // reshape
	glutSpecialFunc(keyboard);  // keyboard

	// looping
	glutMainLoop();

	return 0;
}
