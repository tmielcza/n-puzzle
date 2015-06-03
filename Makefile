NAME = npuzzle
SRC = main.cpp \
	AStarSolver.cpp \
	NodePool.cpp \
	Node.cpp \
	Manhattan.cpp \
	Dijkstra.cpp \
	LinearConflict.cpp \
	Parser.cpp

OBJ = $(SRC:.cpp=.o)
FLAGS = -Wall -Wextra -std=c++11 -g -O3

all: $(NAME)

%.o:%.cpp
	g++ $(FLAGS) -c -o $@ $<

$(NAME): $(OBJ)
	g++ $(FLAGS) -o $(NAME) $(OBJ)

clean:
	rm -rf $(OBJ) ./*~ ./#*#

fclean: clean
	rm -f $(NAME)

re: fclean all
