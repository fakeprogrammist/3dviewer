CC      =gcc
CFLAGS  =-Werror -Wextra -Wall -std=c11
OS_NAME =$(shell uname -s)
BRANCH_INFO       =--rc lcov_branch_coverage=1
REMOVE_DIRECTIVES =clean_mode=1
SRC_DIR           =3DViewer_v1
BUILD_DIR         =build
TEST_DIR          =3DViewer_v1/tests
TEMP_DIR          =3DViewer_v1/tests/temp
REPORT_DIR_GCOV   =3DViewer_v1/tests/report_gcov
REPORT_DIR_LCOV   =3DViewer_v1/tests/report_lcov





ifeq ($(OS_NAME), Linux)
	OPEN        =xdg-open
	TEST_FLAGS  =--coverage $(shell pkg-config --libs check)
	LEAK_CHECK  =valgrind --trace-children=yes --track-fds=yes \
	--track-origins=yes --leak-check=full --show-leak-kinds=all \
	--log-file="report.txt" ./$(TEST_DIR)/tests.out
	CFLAGS_LIBS =-lm -lsubunit -lpthread -lrt
else
	OPEN        =open -a "Google Chrome"
	TEST_FLAGS  =--coverage -lm -lcheck
	LEAK_CHECK  =CK_FORK=no leaks --atExit -- ./$(TEST_DIR)/tests.out
	CFLAGS_LIBS =-lm -L /usr/local/lib #-lcheck
endif


all: install dist

install:
	qmake CONFIG+=release -o $(BUILD_DIR)/Makefile $(SRC_DIR)/3DViewer_v1.pro
	-cd $(BUILD_DIR); make
	-cd $(BUILD_DIR); make clean
	-rm -rf $(BUILD_DIR)/Makefile
	-rm -rf $(BUILD_DIR)/.qmake.stash
	-rm -rf $(BUILD_DIR)/qmake_qmake_qm_files.qrc
	-rm -rf $(BUILD_DIR)/.qm

start:
	open $(BUILD_DIR)/3DViewer_v1.app

uninstall: clean


dist:
	mkdir -p $(BUILD_DIR)
	rm -rf $(BUILD_DIR)/3DViewer_v1.tar.gz
	tar -cvf $(BUILD_DIR)/3DViewer_v1.tar.gz $(SRC_DIR)


dvi:
	mkdir -p $(BUILD_DIR)


test.c:
	@checkmk $(REMOVE_DIRECTIVES) $(TEST_DIR)/tests > $(TEST_DIR)/tests.c

tests: test.c
#	@$(CC) $(FLAGS) --coverage SCalc/*.c $(TEST_DIR)/tests.c -o $(TEST_DIR)/tests.out \
#	-lm -lcheck  $(CFLAGS_LIBS)
#	@$(CC) $(FLAGS) $(SRC_DIR)/*.c $(TEST_DIR)/tests.c --coverage -o $(TEST_DIR)/tests.out \
#	 $(CFLAGS_LIBS)
	@$(CC) $(FLAGS) $(SRC_DIR)/*.c $(TEST_DIR)/tests.c $(TEST_FLAGS) -o $(TEST_DIR)/tests.out
	@./$(TEST_DIR)/tests.out
	@mkdir -p $(TEMP_DIR)
	@mv *.gcda $(TEMP_DIR)
	@mv *.gcno $(TEMP_DIR)

gcov_report: tests
	@mkdir -p $(REPORT_DIR_GCOV)
	@mv $(TEMP_DIR)/*.gcda $(REPORT_DIR_GCOV)
	@mv $(TEMP_DIR)/*.gcno $(REPORT_DIR_GCOV)
	@rm -fR $(TEMP_DIR)
	@gcovr -r $(REPORT_DIR_GCOV) -r . --html-details -o test_report_gcov.html
	@mv test_report_gcov.* $(REPORT_DIR_GCOV)
	open $(REPORT_DIR_GCOV)/test_report_gcov.html

lcov_report: tests
	@mkdir -p $(REPORT_DIR_LCOV)
	@mv $(TEMP_DIR)/*.gcda $(REPORT_DIR_LCOV)
	@mv $(TEMP_DIR)/*.gcno $(REPORT_DIR_LCOV)
	@rm -fR $(TEMP_DIR)
	@lcov -t $(TEST_DIR)/tests.out -o $(REPORT_DIR_LCOV)/t_lcov.info -c -d . \
	$(BRANCH_INFO)
	@genhtml -o $(REPORT_DIR_LCOV) $(REPORT_DIR_LCOV)/t_lcov.info \
	$(BRANCH_INFO)
	open $(REPORT_DIR_LCOV)/index.html


clean: clean_dest clean_debug clean_lib clean_test clean_dvi clean_valgrind clean_QT_build clean_leaks
	@rm -f *.out
	@rm -Rf report
	@rm -f o.o

clean_QT_build:
	@rm -Rf build-3DViewer_v1-Desktop_x86_darwin_generic_mach_o_64bit-Debug

clean_dest:
	@rm -fR $(BUILD_DIR)

clean_debug:
	@rm -fR o.o.dSYM tests.out.dSYM

clean_lib:
	@rm -f *.o *.a

clean_test:
	@rm -rf $(TEST_DIR)/*.gcno $(TEST_DIR)/*.gcda $(TEST_DIR)/tests.c $(TEST_DIR)/tests.out
	@rm -f tests_lcov.info
	@rm -Rf $(TEMP_DIR)
	@rm -Rf $(TEST_DIR)/report_gcov
	@rm -rf $(TEST_DIR)/report_lcov

clean_dvi:
	@rm -fR $(BUILD_DIR)/doc_3DViewer_v1

clean_valgrind:
	@rm -f report.txt

clean_leaks:
	@rm -f *.gcda


check:
	cp ../materials/linters/.clang-format ./
	clang-format -i $(SRC_DIR)/*.c
	clang-format -i $(SRC_DIR)/*.h
	clang-format -n $(SRC_DIR)/*.c
	clang-format -n $(SRC_DIR)/*.h
	rm -f .clang-format

leaks: clean tests
	$(LEAK_CHECK)

cppcheck:
	cppcheck $(SRC_DIR)/*.c $(SRC_DIR)/*.h


vivod:
	echo "Вывод"
	echo "$(OS_NAME)"
	echo "$(BRED)"

view: clean
	@$(CC) $(CFLAGS) $(CFLAGS_LIBS) $(SRC_DIR)/*.c -o o.o -g -lm
	@./o.o

