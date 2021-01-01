CC = gcc
NAME = testris
BUILD_DIR = ./build/
SOURCE_FILES = ./src/main.c ./src/testris.c ./src/testrisio.c ./src/testrisutils.c

build : $(SOURCE_FILES)
	@echo "--> building and linking all the source files..."
	mkdir -p $(BUILD_DIR)
	$(CC) -o $(BUILD_DIR)$(NAME)  $(SOURCE_FILES)
	@echo "--> done building!"

install:
	@echo "--> installing testris.."
	cp $(BUILD_DIR)testris /bin/
	@echo "--> installed!"

uninstall:
	@echo "--> uninstalling testris.."
	rm /bin/testris
	@echo "--> uninstaled"

clear:
	@echo "--> removing binaries.."
	rm -rd $(BUILD_DIR)
	@echo "--> binaries removed!"
