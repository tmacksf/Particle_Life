default_target: all
.PHONY : default_target

Particle_Life: cmake_check_build_system
.PHONY : Particle_Life

.PHONY : clean
clean:
	rm -f *.o

quick:
	g++ main.cpp Engine.cpp Particle.cpp Particles.cpp Quad.cpp -lGL -lglfw -lGLEW -o main
.PHONY : quick
