CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

LDFLAGS= -shared

OBJS =		StepperMotor28BYJ48.o

LIBS = -lwiringPi

TARGET =	libStepperMotor28BYJ48.so

PREFIX=/usr/local

$(TARGET):	$(OBJS)
	$(CXX) -o $@ $(LDFLAGS) $(OBJS) $(LIBS)
	
all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

install: $(TARGET)
	install -m 0755 $(TARGET) $(PREFIX)/lib