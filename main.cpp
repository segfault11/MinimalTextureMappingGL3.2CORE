#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <SDL2/SDL.h>
#include "OpenGL.h"

GLuint gProgram;

GLuint gVAO;
GLuint gVBOs[2];
GLuint gTex;
GLint gTexLoc;

void setUpTexture ()
{
	float *data = new float[4*512*512];
	
	std::fill(data, data + 4*512*512, 0.0f);

	for (unsigned int i = 0; i < 512*512; i++)
	{
		if (i % 2)
		{
			data[4*i + 0] = 1.0f;
			data[4*i + 1] = 1.0f;
			data[4*i + 2] = 0.0f;
			data[4*i + 3] = 1.0f;
		}
	}

	glGenTextures(1, &gTex);
	glBindTexture(GL_TEXTURE_2D, gTex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, 512, 512, 0, GL_RGBA, 
		GL_FLOAT, data);
	delete[] data;
}

void init()
{
	glEnable(GL_TEXTURE_2D);
	gProgram = glCreateProgram();
	GL::AttachShader(gProgram, "vertex.glsl", GL_VERTEX_SHADER);
	GL::DumpLog(gProgram);
	GL::AttachShader(gProgram, "fragment.glsl", GL_FRAGMENT_SHADER);
	GL::DumpLog(gProgram);
	GL::BindAttribLocation(gProgram, "position", 0);
	GL::BindAttribLocation(gProgram, "texCoord", 1);
	GL::BindFragDataLocation(gProgram, "fragOutput", 0);
	GL::LinkProgram(gProgram);
	GL::DumpLog(gProgram);
	setUpTexture ();

	gTexLoc = glGetUniformLocation(gProgram, "uTexture");
	glUseProgram(gProgram);
	glUniform1i(gTexLoc, 0);
   	glActiveTexture(GL_TEXTURE0); 
	glBindTexture(GL_TEXTURE_2D, gTex);

}

void createVBO()
{
    float vertexData[] = 
	{
		-1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, -1.0f, 0.0f
	};
    float texData[] = {0.0f, 0.0f, 0.5f, 0.5f, 1.0f, 0.0f};

    glGenVertexArrays(1, &gVAO);
    glBindVertexArray(gVAO);
    glGenBuffers(2, gVBOs);
    glBindBuffer(GL_ARRAY_BUFFER, gVBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, 9*sizeof(float), vertexData, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, gVBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, 6*sizeof(float), texData, GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glBindVertexArray(0);
}

void renderVBO()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(gProgram);
	glBindVertexArray(gVAO);
    glDrawArrays(GL_TRIANGLES, 0, 3); 
}

int main(int argc, const char *argv[])
{
    SDL_Window* mainWindow;
    SDL_GLContext mainContext;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) 
    {
        
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	mainWindow = SDL_CreateWindow("Triangle", SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 512, 512, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
   
	mainContext = SDL_GL_CreateContext(mainWindow);
	SDL_GL_SetSwapInterval(1);
    glewExperimental = GL_TRUE; 
    if (GLEW_OK != glewInit())
    {
        printf("glewInit failed\n");
    }
    else
    {
        printf("glewInit succeded\n");
    }

    init();
	createVBO();
    renderVBO();

    SDL_GL_SwapWindow(mainWindow);
    SDL_Delay(5000);
	SDL_GL_DeleteContext(mainContext);
    SDL_DestroyWindow(mainWindow);
    SDL_Quit();

    return 0;
}

