G=g++ -std=c++17
GCC=$(G) -Wall -Werror -Wextra
LIBS=-lgtest -lgtest_main -lpthread

SOURCES = SmartCalc2/Tests/tests.cc SmartCalc2/Model/model.cc

all: install open

tests: clean
	@$(GCC) --coverage $(SOURCES) -o test $(LIBS)
	@./test

leaks:
	@echo .................. testing for leaks ..................
	@$(GCC) $(SOURCES) -lgtest -o leaks -g
	CK_FORK=no leaks --atExit -- ./leaks
	@make clean

style:
	@echo ------------------ style check -----------------------
	clang-format -i SmartCalc2/*/*.cc SmartCalc2/*/*.h
	clang-format -n SmartCalc2/*/*.cc SmartCalc2/*/*.h

install: clean
	mkdir build
	cd SmartCalc2 && qmake && make && make clean && rm Makefile
	cd ..
	mv SmartCalc2/SmartCalc2.pro build
	rm SmartCalc2/.qmake.stash

uninstall:
	 -rm -rf build

dvi: 
	open readme.md

dist:
	@-rm -rf Archive_SmartCalc2/
	@mkdir Archive_SmartCalc2/
	@mkdir Archive_SmartCalc2/src
	@mv ./SmartCalc2/SmartCalc2.app Archive_SmartCalc2/src/
	@tar cvzf Archive_SmartCalc2.tgz Archive_SmartCalc2/
	@-rm -rf Archive_SmartCalc2/
	@-rm -rf build

open:
	cd build/SmartCalc2.app/Contents/MacOS && ./SmartCalc2

clean:
	@-rm -rf test
	@-rm -rf test.info
	@-rm -rf *.gcda
	@-rm -rf *.gcno
	@-rm -rf report
	@-rm -rf leaks*