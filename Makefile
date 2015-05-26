NAME = npuzzle
SRC = main.cpp AStarSolver.cpp NodePool.cpp
OBJ = $(SRC:.cpp=.o)
FLAGS = -Wall -Wextra -Werror -std=c++11 -g -O3

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
