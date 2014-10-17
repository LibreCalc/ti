#Choix du compilateur.
CP = g++  -g
SDL = `sdl-config --cflags --libs`
#choix des inclusions


ti:obj/charPutter.o obj/main.o obj/yEqualsMenu.o obj/curveViewer.o obj/handlePixels.o obj/mainScreen.o obj/evalFormula.o obj/keyParser.o obj/tiConfig.o  obj/tiString.o obj/tiBasicParser.o obj/83pReadWrite.o obj/menu.o obj/tiVariant.o obj/commandsHandler.o obj/curveRangeEditor.o
	$(CP) $(SDL) $^ -o $@ -lm

obj/main.o: src/main.cpp
	$(CP) src/main.cpp -o $@ -c
obj/charPutter.o: src/charPutter.cpp
	$(CP) src/charPutter.cpp -o $@ -c
obj/yEqualsMenu.o: src/yEqualsMenu.cpp
	$(CP) src/yEqualsMenu.cpp -o $@ -c	
obj/curveViewer.o: src/curveViewer.cpp
	$(CP) src/curveViewer.cpp -o $@ -c
obj/handlePixels.o: src/handlePixels.cpp
	$(CP) src/handlePixels.cpp -o $@ -c	
obj/mainScreen.o: src/mainScreen.cpp
	$(CP) src/mainScreen.cpp -o $@ -c
obj/evalFormula.o: src/evalFormula.cpp
	$(CP) src/evalFormula.cpp -o $@ -c	
obj/keyParser.o: src/keyParser.cpp
	$(CP) src/keyParser.cpp -o $@ -c
obj/tiConfig.o: src/tiConfig.cpp
	$(CP) src/tiConfig.cpp -o $@ -c
obj/tiString.o: src/tiString.cpp
	$(CP) src/tiString.cpp -o $@ -c
obj/tiBasicParser.o: src/tiBasicParser.cpp
	$(CP) src/tiBasicParser.cpp -o $@ -c
obj/83pReadWrite.o: src/83pReadWrite.cpp
	$(CP) src/83pReadWrite.cpp -o $@ -c	
obj/menu.o: src/menu.cpp
	$(CP) src/menu.cpp -o $@ -c	
obj/tiVariant.o: src/tiVariant.cpp
	$(CP) src/tiVariant.cpp -o $@ -c
obj/commandsHandler.o: src/commandsHandler.cpp
	$(CP) src/commandsHandler.cpp -o $@ -c
obj/curveRangeEditor.o: src/curveRangeEditor.cpp
	$(CP) src/curveRangeEditor.cpp -o $@ -c
	
count:
	find . -iname "*.cpp" -exec grep -vE '^#' {} \; | wc -l
	find . -iname "*.h" -exec grep -vE '^#' {} \; | wc -l	
clean:
	rm -vf obj/*
	rm -vf *~
	rm -vf src/*~
	rm -vf sokoban
 
