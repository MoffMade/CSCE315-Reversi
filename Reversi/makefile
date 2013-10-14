all: reversiServer reversiClient

reversiClient: gameClient.o clientSocket.o
	g++ -o reversiClient gameClient.o clientSocket.o -lsocket -lnsl

reversiServer: gameServer.o serverSocket.o gameMechanics.o gameAI.o
	g++ -o reversiServer gameServer.o serverSocket.o gameMechanics.o gameAI.o -lsocket -lnsl

gameClient.o: gameClient.cpp gameClient.h stdhf.h 
	g++ -c -g gameClient.cpp 

clientSocket.o: clientSocket.cpp clientSocket.h stdhf.h 
	g++ -c -g clientSocket.cpp -lsocket -lnsl	
	
serverSocket.o: serverSocket.cpp serverSocket.h stdhf.h
	g++ -c -g serverSocket.cpp -lsocket -lnsl
	
gameServer.o: gameServer.cpp gameServer.h stdhf.h
	g++ -c -g gameServer.cpp 	
	
gameMechanics.o: gameMechanics.cpp gameMechanics.h stdhf.h
	g++ -c -g gameMechanics.cpp
	
gameAI.o: gameAI.cpp gameAI.h stdhf.h
	g++ -c -g gameAI.cpp

	