CXXFLAGS += -std=c++11
GTKFLAGS = `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`

ex: profile.o login.o  main.o
	$(CXX) $(CXXFLAGS) -o login main.o profile.o login.o $(GTKFLAGS)
main.o: main.cpp login.h
	$(CXX) $(CXXFLAGS) -c main.cpp $(GTKFLAGS)
login.o: login.h login.cpp
	$(CXX) $(CXXFLAGS) -c login.cpp $(GTKFLAGS)
profile.o: profile.h profile.cpp
	$(CXX) $(CXXFLAGS) -c profile.cpp $(GTKFLAGS)
