# You need to "sudo apt-get install libgtkmm-3.0-dev" to build the demo_3d binary

all: piQuad

HDRS = helper_3dmath.h I2Cdev.h MPU6050_6Axis_MotionApps20.h MPU6050.h manager.h gnc.h comms.h udp_server.h pi_types.h rpiPWM1.cpp
CMN_OBJS = I2Cdev.o MPU6050.o manager.o gnc.o comms.o udp_server.o rpiPWM1.o
DMP_OBJS = main.o

# Set DMP FIFO rate to 20Hz to avoid overflows on 3d demo.  See comments in
# MPU6050_6Axis_MotionApps20.h for details.

CXXFLAGS = -DDMP_FIFO_RATE=9 -Wall -g -O2 -D DEBUG -std=c++11
EXTRA_FLAGS = -Wextra -Wdouble-promotion # TODO add this when farther along

$(CMN_OBJS) $(DMP_OBJS) $(RAW_OBJS) : $(HDRS)

piQuad: $(CMN_OBJS) $(DMP_OBJS)
	$(CXX) -o $@ $^ -lm -lboost_system -lboost_thread -pthread

clean:
	rm -f $(CMN_OBJS) $(DMP_OBJS) piQuad
