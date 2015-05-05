#Choix du compilateur.
CP = g++  -g
SDL = `sdl-config --cflags --libs`
#choix des inclusions


ti:obj/charPutter.o obj/main.o obj/yEqualsMenu.o obj/curveViewer.o obj/handlePixels.o obj/mainScreen.o obj/evalFormula.o obj/keyParser.o obj/tiConfig.o  obj/tiString.o obj/tiBasicParser.o obj/83pReadWrite.o obj/menu.o obj/tiVariant.o obj/commandsHandler.o obj/curveRangeEditor.o obj/tiBasicEditor.o obj/canvas.o
	$(CP) $(SDL) $^ -o $@ -lm

obj/main.o: src/main.cpp
	mkdir -p obj
	$(CP) src/main.cpp -o $@ -c
obj/charPutter.o: src/charPutter.cpp
	mkdir -p obj
	$(CP) src/charPutter.cpp -o $@ -c
obj/yEqualsMenu.o: src/yEqualsMenu.cpp
	mkdir -p obj
	$(CP) src/yEqualsMenu.cpp -o $@ -c	
obj/curveViewer.o: src/curveViewer.cpp
	mkdir -p obj
	$(CP) src/curveViewer.cpp -o $@ -c
obj/handlePixels.o: src/handlePixels.cpp
	mkdir -p obj
	$(CP) src/handlePixels.cpp -o $@ -c	
obj/mainScreen.o: src/mainScreen.cpp
	mkdir -p obj
	$(CP) src/mainScreen.cpp -o $@ -c
obj/evalFormula.o: src/evalFormula.cpp
	mkdir -p obj
	$(CP) src/evalFormula.cpp -o $@ -c	
obj/keyParser.o: src/keyParser.cpp
	mkdir -p obj
	$(CP) src/keyParser.cpp -o $@ -c
obj/tiConfig.o: src/tiConfig.cpp
	mkdir -p obj
	$(CP) src/tiConfig.cpp -o $@ -c
obj/tiString.o: src/tiString.cpp
	mkdir -p obj
	$(CP) src/tiString.cpp -o $@ -c
obj/tiBasicParser.o: src/tiBasicParser.cpp
	mkdir -p obj
	$(CP) src/tiBasicParser.cpp -o $@ -c
obj/83pReadWrite.o: src/83pReadWrite.cpp
	mkdir -p obj
	$(CP) src/83pReadWrite.cpp -o $@ -c	
obj/menu.o: src/menu.cpp
	mkdir -p obj
	$(CP) src/menu.cpp -o $@ -c	
obj/tiVariant.o: src/tiVariant.cpp
	mkdir -p obj
	$(CP) src/tiVariant.cpp -o $@ -c
obj/commandsHandler.o: src/commandsHandler.cpp
	mkdir -p obj
	$(CP) src/commandsHandler.cpp -o $@ -c
obj/curveRangeEditor.o: src/curveRangeEditor.cpp
	mkdir -p obj
	$(CP) src/curveRangeEditor.cpp -o $@ -c
obj/tiBasicEditor.o: src/tiBasicEditor.cpp
	mkdir -p obj
	$(CP) src/tiBasicEditor.cpp -o $@ -c	
obj/canvas.o: src/canvas.cpp
	mkdir -p obj
	$(CP) src/canvas.cpp -o $@ -c		

count:
	find . -iname "*.cpp" -exec grep -vE '^#' {} \; | wc -l
	find . -iname "*.h" -exec grep -vE '^#' {} \; | wc -l	
clean:
	rm -vf obj/*
	rm -vf *~
	rm -vf src/*~
	rm -vf sokoban

