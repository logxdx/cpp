run: tester.exe
	./tester.exe

tester.exe: tester.cpp qna_tool.cpp Node.cpp
	g++ tester.cpp qna_tool.cpp Node.cpp -o tester.exe

clean:
	rm tester.exe