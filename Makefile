NAME = npuzzle
SRC = main.cpp AStarSolver.cpp
OBJ = $(SRC:.cpp=.o)
FLAGS = -Wall -Wextra -std=c++11

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
