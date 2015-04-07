CXXFLAGS =	-O2 -g -Wall -fmessage-length=0 -std=c++0x

LDFLAGS= -shared

OBJS =		StepperMotor28BYJ48.o

INCLUDES = StepperMotor28BYJ48.hpp

LIBS = -lwiringPi

TARGET =	libStepperMotor28BYJ48.so

PREFIX=/usr

$(TARGET):	$(OBJS)
	$(CXX) -o $@ $(LDFLAGS) $(OBJS) $(LIBS)
	
all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

install: $(TARGET)
	install -m 0755 $(TARGET) $(PREFIX)/lib
	install -m 0755 $(INCLUDES) $(PREFIX)/include