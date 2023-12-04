all: demo-application

demo-application:  demo-application.o
        g++ demo-application.o -o demo-application

demo-application.o: demo-application.cpp parralel_scheduler.cpp parralel_scheduler.h
        g++ -c demo-application.cpp -pthread

clean:
        rm *.o demo-application
