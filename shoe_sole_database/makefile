SEARCHER_FLAGS = -std=c++23 -lpq -O3

searcher:
	g++ backend/src/main/DBSetup.cpp \
	backend/src/main/Directory.cpp \
	backend/src/main/Main.cpp \
	backend/src/main/Query.cpp \
	backend/src/main/Json.cpp \
	-o backend/build/searcher \
	${SEARCHER_FLAGS}

clean:
	rm -f backend/build/searcher