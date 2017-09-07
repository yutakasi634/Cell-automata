CXX = clang++
CXXFLAGS = -std=c++11
OPENGLFLAGS = -lglut -lGLU -lGL -lm

all: test/Ising_system_test test/spin_test test/system_initializer_func_test Ising_model

test/Ising_system_test: test/test_for_Ising_system.cpp
	$(CXX) $(CXXFLAGS) -o test/Ising_system_test test/test_for_Ising_system.cpp

test/spin_test: test/test_for_spin.cpp
	$(CXX) $(CXXFLAGS) -o test/spin_test test/test_for_spin.cpp

test/system_initializer_func_test: test/test_for_system_initializer_func.cpp
	$(CXX) $(CXXFLAGS) -o test/system_initializer_func_test test/test_for_system_initializer_func.cpp

Ising_model: Ising_model.cpp
	$(CXX) $(CXXFLAGS) $(OPENGLFLAGS) -o Ising_model Ising_model.cpp

.PHONY:clean
# clean:
# 	$(RM) *\~ test/Ising_system_test test/spin_test test/system_initializer_func_test Ising_model

clean:
	$(RM) Ising_model
