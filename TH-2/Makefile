all: parralel_scheduler.so demo-application

parralel_scheduler.so: parralel_scheduler.cpp
	g++ -c parralel_scheduler.cpp

demo-application: demo-application.cpp parralel_scheduler.so
	g++ -c demo-application.cpp

clean:
	rm *.o demo-application
