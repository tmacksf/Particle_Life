default_target: all
.PHONY : default_target

Particle_Life:
	g++ -Wall -O2 main.cpp Engine.cpp Particle.cpp Particles.cpp Quad.cpp Shader.cpp -lGL -lglfw -lGLEW -o main
.PHONY : Particle_Life

.PHONY : clean
clean:
	rm -f *.o

quick:
	g++ -Wall main.cpp Engine.cpp Particle.cpp Particles.cpp Quad.cpp Shader.cpp -lGL -lglfw -lGLEW -o main -g
.PHONY : quick
