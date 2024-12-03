#define GL_GLEXT_PROTOTYPES

#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include "render.h"
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"



GLuint vbo[6];		//identyfikatory buforow wierzcholkow
GLuint vao[3];		//identyfikatory tablic wierzcholkow

GLuint pirb[2];  //piramida bufor
GLuint pira[1];   //element piramidy

GLuint ebo;		//identyfikator bufora elementow

GLuint shaderProgram;
GLint vertexShader;	//identyfikator shadera wierzcholkow
GLint fragmentShader;   //identyfikator shadera fragmentow
GLint posAttrib, colAttrib;	//

glm::mat4 viewMatrix = glm::mat4();
glm::mat4 projectionMatrix = glm::mat4(); //marzerz widoku i rzutowania
GLfloat fi = 0;


//-------------Atrybuty wierzcholkow------------------------------------------

	GLfloat ver_triangle[] = {	//wspolrzedne wierzcholkow trojkata
		 0.0f,  1.0f, 0.0,
		 1.0f,  0.0f, 0.0,
		-1.0f,  0.0f, 0.0
	};

	GLfloat col_triangle[] = {	//kolory wierzcholkow trojkata
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};

	GLfloat ver_rectangle[] = {	//wspolrzedne wierzcholkow prostokata
		-1.0f, -0.2f, 0.0f,
		 1.0f, -0.2f, 0.0f,
		-1.0f, -0.7f, 0.0f,
		 1.0f, -0.7f, 0.0f
	};

	GLfloat col_rectangle[] = {	//kolory wierzcholkow prostokata
		0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f
	};

  GLfloat ver_block[] = {	//wspolrzedne wierzcholkow prostopadlosciana
		0.0f, 0.0f, 0.0f, // vertex 0
		0.0f, 0.0f, -2.0f, // vertex 1
		0.0f, 1.0f, -2.0f, // vertex 2
		0.0f, 1.0f, 0.0f, // vertex 3
    1.0f, 0.0f, 0.0f, // vertex 4
		1.0f, 0.0f, -2.0f, // vertex 5
		1.0f, 1.0f, -2.0f, // vertex 6
		1.0f, 1.0f, 0.0f  // vertex 7
  };

	GLfloat col_block[] = {	//kolory wierzcholkow prostopadlosciana
		0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f
	};

	GLuint elements[] = { //prostopadloscian z 12 trojkatow
		0, 1, 2,		  // trojkat 0
		0, 3, 2,		  // trojkat 1
    0, 4, 7,		  // trojkat 2
		0, 3, 7,		  // trojkat 3
    4, 5, 6,		  // trojkat 4
		4, 7, 6,		  // trojkat 5
    1, 2, 6,		  // trojkat 6
		6, 5, 1,		  // trojkat 7
    3, 2, 6,		  // trojkat 8
		6, 7, 3,		  // trojkat 9
    0, 1, 5,		  // trojkat 10
		0, 4, 5 		  // trojkat 11
  };

  GLfloat ver_pir_1[] = {
    0.0f, 0.0f, 0.0f, // vertex 0
		0.0f, 0.0f, -1.0f, // vertex 1
		0.0f, 1.0f, -1.0f, // vertex 2
		0.0f, 1.0f, 0.0f, // vertex 3
    1.0f, 0.0f, 0.0f, // vertex 4
		1.0f, 0.0f, -1.0f, // vertex 5
		1.0f, 1.0f, -1.0f, // vertex 6
		1.0f, 1.0f, 0.0f  // vertex 7
  };

//----------------------------kod shadera wierzcholkow-----------------------------------------

const GLchar* vShader_string =
{
  "#version 130\n"\

  "in vec3 position;\n"\
  "in vec3 color;\n"\
  "out vec3 Color;\n"\
  "uniform mat4 transformMatrix;\n"\
  "void main(void)\n"\
  "{\n"\
  "  gl_Position = transformMatrix * vec4(position, 1.0);\n"\
  "  Color = color;\n"\
  "}\n"
};

//----------------------------kod shadera fragmentow-------------------------------------------
const GLchar* fShader_string =
{
  "#version 130\n"\
  "in  vec3 Color;\n"\
  "out vec4 outColor;\n"\

  "void main(void)\n"\
  "{\n"\
  "  outColor = vec4(Color, 1.0);\n"\
  "}\n"
};


//------------------------------------------------zmiana rozmiaru okna---------------------------

void resizeGLScene(unsigned int width, unsigned int height)
{
    if (height == 0) height = 1; // zabezpiecznie dla okna o zerowej wysokosci
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 1.0f, 500.0f);
    glMatrixMode(GL_MODELVIEW);
}


//----------------------------------tworzenie, wczytanie, kompilacja shaderow-------------------------

int initShaders(void)
{
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vShader_string, NULL);
    glCompileShader(vertexShader);
    
    GLint status;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
    if (status == GL_TRUE)
      std::cout << "Kompilacja shadera wierzcholkow powiodla sie!\n";
    else
    {
      std::cout << "Kompilacja shadera wierzcholkow NIE powiodla sie!\n";
      return 0;
     }
     
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fShader_string, NULL); 
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
    if (status == GL_TRUE)
      std::cout << "Kompilacja shadera fragmentow powiodla sie!\n";
    else
    {
      std::cout << "Kompilacja shadera fragmentow NIE powiodla sie!\n";
      return 0;
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    
    //glBindFragDataLocation(shaderProgram, 0, "outColor"); 

    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);
    return 1;
}


void transformVertices(GLuint* vertices, size_t vertexCount, const glm::mat4& transform) {
    for (size_t i = 0; i < vertexCount; ++i) {
        // Extract the x, y, z coordinates
        glm::vec4 vertex(vertices[i * 3], vertices[i * 3 + 1], vertices[i * 3 + 2], 1.0f);
        
        // Apply transformation
        vertex = transform * vertex;

        // Store back transformed coordinates
        vertices[i * 3]     = static_cast<GLuint>(vertex.x);
        vertices[i * 3 + 1] = static_cast<GLuint>(vertex.y);
        vertices[i * 3 + 2] = static_cast<GLuint>(vertex.z);
    }
}


//--------------------------------------------funkcja inicjujaca-------------------------------------
int initGL(void)
{
   
    if(initShaders())
    {   

        glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL); 
	glGenVertexArrays(3, vao); //przypisanie do vao identyfikatorow tablic (ważne!)
	glGenVertexArrays(1, pira); //przypisanie do pira identyfikatorow tablic (ważne!)
	glGenBuffers(6, vbo);	   //przypisanie do vbo identyfikatorow buforow (ważne!)
	glGenBuffers(2, pirb);	   //przypisanie do pirb identyfikatorow buforow (ważne!)
	glGenBuffers(1, &ebo);

	posAttrib = glGetAttribLocation(shaderProgram, "position"); //pobranie indeksu tablicy atrybutow wierzcholkow okreslajacych polozenie
        glEnableVertexAttribArray(posAttrib);
	colAttrib = glGetAttribLocation(shaderProgram, "color");    //pobranie indeksu tablicy atrybutow wierzcholkow okreslajacych kolor
        glEnableVertexAttribArray(colAttrib);
	
	// glBindVertexArray(vao[0]);					//wybor tablicy (ważne!)
		
	// glBindBuffer(GL_ARRAY_BUFFER, vbo[0]); 							//powiazanie bufora z odpowiednim obiektem (wybor bufora) 
	// glBufferData(GL_ARRAY_BUFFER, sizeof(ver_triangle), ver_triangle, GL_STATIC_DRAW); 	//skopiowanie danych do pamieci aktywnego bufora
	// glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);				//okreslenie organizacji danych w tablicy wierzcholkow
	// glEnableVertexAttribArray(posAttrib);							//wlaczenie tablicy
	
	// glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	// glBufferData(GL_ARRAY_BUFFER, sizeof(col_triangle), col_triangle, GL_STATIC_DRAW);
	// glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// glEnableVertexAttribArray(colAttrib);
	
	// glBindVertexArray(vao[1]);

	// glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	// glBufferData(GL_ARRAY_BUFFER, sizeof(ver_rectangle), ver_rectangle, GL_STATIC_DRAW);
	// glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// glEnableVertexAttribArray(posAttrib);

	// glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
	// glBufferData(GL_ARRAY_BUFFER, sizeof(col_rectangle), col_rectangle, GL_STATIC_DRAW);
	// glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// glEnableVertexAttribArray(colAttrib);

  // glBindVertexArray(vao[2]); // prostopadloscian

  // glBindBuffer(GL_ARRAY_BUFFER, vbo[4]);
	// glBufferData(GL_ARRAY_BUFFER, sizeof(ver_block), ver_block, GL_STATIC_DRAW);
	// glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// glEnableVertexAttribArray(posAttrib);

	// glBindBuffer(GL_ARRAY_BUFFER, vbo[5]);
	// glBufferData(GL_ARRAY_BUFFER, sizeof(col_block), col_block, GL_STATIC_DRAW);
	// glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// glEnableVertexAttribArray(colAttrib);

	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	// glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

  	glBindVertexArray(pira[0]);					//wybor tablicy (ważne!)    

    glBindBuffer(GL_ARRAY_BUFFER, pirb[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(ver_pir_1), ver_pir_1, GL_STATIC_DRAW);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(posAttrib);

    glBindBuffer(GL_ARRAY_BUFFER, pirb[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(col_block), col_block, GL_STATIC_DRAW);
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(colAttrib);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

        
	//macierz widoku (okresla polozenie kamery i kierunek w ktorym jest skierowana) 
	viewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 8.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f)); 
	//macierz rzutowania perspektywicznego
	projectionMatrix = glm::perspective(glm::radians(45.0f), 1.0f, 1.0f, 10.0f);		

 	return 1;
    }
    else
	return 0;
}

//------------------------------------------renderowanie sceny-------------------------------------

int drawGLScene(int counter)
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    
    // glm::mat4 translationMatrix = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f));  		//macierz przesuniecia o zadany wektor
    // glm::mat4 rotationMatrix = glm::rotate(glm::mat4(), glm::radians(fi), glm::vec3(0.0f, 1.0f, 0.0f)); //macierz obrotu o dany kat wokol wektora
		
    // glm::mat4 transformMatrix = projectionMatrix * viewMatrix * translationMatrix * rotationMatrix; //wygenerowanie macierzy uwzgledniajacej wszystkie transformacje (ważne!) (viewMatrix do przestawiania kamery)


    // GLint transformMatrixUniformLocation = glGetUniformLocation(shaderProgram, "transformMatrix");  //pobranie polozenia macierzy bedacej zmienna jednorodna shadera
    // glUniformMatrix4fv(transformMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix)); //zapisanie macierzy bedacej zmienna jednorodna shadera wierzcholkow
    

    // glBindVertexArray(vao[0]);
    // glDrawArrays(GL_TRIANGLES, 0, 3); //rysowanie trojkata (ważne!)

    // glBindVertexArray(vao[1]);
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); //rysowanie prostokata (ważne!)

    // glBindVertexArray(vao[2]);
    // glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0); //rysowanie blocku (ważne!)

    int pirN = 7;
    glBindVertexArray(pira[0]);

    for (int i = 0; i < pirN; i++)
    {
      glm::mat4 translationMatrix = glm::translate(glm::mat4(), glm::vec3(0.05f * (7 - i), (float)i - 3.5, -0.05f * (7 - i)));  		//macierz przesuniecia o zadany wektor
      
      glm::mat4 rotationMatrix;
      if(i % 2 == 0){
        rotationMatrix = glm::rotate(glm::mat4(), glm::radians(fi), glm::vec3(0.0f, 0.5f, 0.0f)); //macierz obrotu o dany kat wokol wektora
      } else {
        rotationMatrix = glm::rotate(glm::mat4(), glm::radians(fi), glm::vec3(0.0f, -0.5f, 0.0f)); //macierz obrotu o dany kat wokol wektora
      }
      glm::mat4 scaleMatrix = glm::scale(glm::mat4(), glm::vec3(0.1f * (7 - i), 1.0f , 0.1f * (7 - i))); //macierz przeskalowania
      
      glm::mat4 transformMatrix = projectionMatrix * viewMatrix * translationMatrix * rotationMatrix * scaleMatrix; //wygenerowanie macierzy uwzgledniajacej wszystkie transformacje (ważne!) (viewMatrix do przestawiania kamery)

      GLint transformMatrixUniformLocation = glGetUniformLocation(shaderProgram, "transformMatrix");  //pobranie polozenia macierzy bedacej zmienna jednorodna shadera
      glUniformMatrix4fv(transformMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix)); //zapisanie macierzy bedacej zmienna jednorodna shadera wierzcholkow

      
      glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0); //rysowanie elementu piramidy
    }

    fi += 0.5;
 
    glFlush();

    return 1;    
}

//----------------------------------------------------porzadki--------------------------------------

void deleteAll()
{
    glDeleteProgram(shaderProgram);
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);

    glDeleteBuffers(6, vbo);
    glDeleteBuffers(2, pirb);
    glDeleteBuffers(1, &ebo);
    glDeleteVertexArrays(3, vao);
    glDeleteVertexArrays(1, pira);
}
