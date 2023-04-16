CC=gcc
CFLAGS=-std=c11 -Wall -Werror -Wextra
LIB_NAME=my_matrix.a
CLEAN=rm -rf

# ADDITIONAL
TEST_FLAG=-fsanitize=address -g
ADDITIONAL=#$(TEST_FLAG)

ifeq ($(shell uname), Linux)
	CHECK_LIBS=-lcheck -lm -lpthread -lsubunit -lrt
	LEAKS=valgrind $(BUILD_DIR)/test
else
	CHECK_LIBS=-lcheck -lm -lpthread
	LEAKS=CK_FORK=no leaks --atExit -- $(BUILD_DIR)/test
endif

# FOLDERS
SRC_DIR=.
TEST_DIR=$(SRC_DIR)/../tests
BUILD_DIR=$(SRC_DIR)/../build

# SOURCES
SOURCES=*.c
HEADERS=*.h
OBJ=*.o


# GOALS_START
all: $(LIB_NAME)

rebuild: clean all

$(LIB_NAME): $(SRC_DIR)/$(SOURCES) $(SRC_DIR)/$(HEADERS)
	$(CC) $(CFLAGS) $(ADDITIONAL) -g -c $(SRC_DIR)/$(SOURCES)
	ar rc $(LIB_NAME) *.o
	$(CLEAN) $(OBJ)

# TESTS
test: $(LIB_NAME)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(ADDITIONAL) -g $(TEST_DIR)/tests.c -L. $(LIB_NAME) $(CHECK_LIBS) -o $(BUILD_DIR)/$@
	$(BUILD_DIR)/$@	

# COVERAGE
gcov_report: clean
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(ADDITIONAL) --coverage -c $(SRC_DIR)/$(SOURCES)
	ar rc $(LIB_NAME) $(OBJ)
	$(CC) $(CFLAGS) $(TEST_DIR)/tests.c -L. $(LIB_NAME) $(CHECK_LIBS) -lgcov -o $(BUILD_DIR)/test
	$(CLEAN) $(OBJ)
	$(BUILD_DIR)/test
	gcov *.gcda
	lcov -t "gcov_report" -o gcov_report.info -c -d .
	mkdir -p $(BUILD_DIR)/report
	genhtml -o $(BUILD_DIR)/report gcov_report.info

# CHECK
check: clean leaks cppcheck codestyle

codestyle:
	clang-format -i *.c ./../tests/*.c
	clang-format -i *.h
	clang-format -n *.c ./../tests/*.c
	clang-format -n *.h

cppcheck:
	cppcheck --std=c11 --enable=all --suppress=missingIncludeSystem  --suppress=unusedFunction --suppress=duplicateCondition ./

leaks: clean test
	$(LEAKS)

clean:
	$(CLEAN) $(OBJ) *.a *.gcno *.gcda *.gcov *.info
	$(CLEAN) $(BUILD_DIR)
