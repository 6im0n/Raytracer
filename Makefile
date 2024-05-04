##
## EPITECH PROJECT, 2024
## Raytracer
## File description:
## Makefile
##

#-------------- Main Variables --------------#

SRC			=	main.cpp								\
				DataRetriever/Parsing.cpp				\
				Graphical/Sdl2.cpp						\
				Math/Ray3D.cpp							\
				Math/Vector3D.cpp						\
				Raytracer/Camera.cpp					\
				Shapes/Material.cpp						\
				Shapes/ShapeList.cpp					\
				Shapes/Sphere.cpp						\
				Core/ClusterManagement.cpp				\

TRUE_SRC 	= 	$(patsubst %,src/%, $(SRC))

OBJ			=	$(TRUE_SRC:.cpp=.o)

NAME		=	raytracer

WARNINGS	=	-Wall -Wextra -Wshadow

INCLUDE		=	-I./src -I.

VALGRIND	=	-g3

LIBS		=	-lconfig++ -lSDL2 -lSDL2_image -lSDL2_ttf

CXXFLAGS	=	$(INCLUDE) $(WARNINGS) $(LIBS) #$(VALGRIND)

#-------------- Tests Variables --------------#

TEST_SRC		=	MainTests.cpp						\
					DataRetriever/ParsingTests.cpp		\

TESTS_LIBS		=	-lcriterion -lconfig++

TESTS_INCLUDE 		= -I./Tests/Include -I./src -I. -I./Interfaces

TESTS_COMPILATION_FLAGS	=	--coverage

TEST_TRUE_SRC	=	$(patsubst %,Tests/src/%, $(TEST_SRC))	\
					$(filter-out src/main.cpp, $(TRUE_SRC))

TESTS_FLAGS		=	$(TESTS_INCLUDE) $(WARNINGS) $(TESTS_LIBS) $(TESTS_COMPILATION_FLAGS)

#-------------- Phony & Silent Rules --------------#

.PHONY: all clean fclean re tests_run tests_compile tests_launch

.SILENT: clean fclean re tests_launch tests_run

#-------------- Rules --------------#

all:	$(NAME)

$(NAME):	$(OBJ)
	g++ -o $(NAME) $(OBJ) $(CXXFLAGS)
	@if [ -f $(NAME) ]; then \
		printf "\033[1;32mCompilation completed ✅\033[0m\n"; \
	else \
		printf "\033[1;31mCompilation failed ❌\033[0m\n"; \
	fi

clean:
	rm -f $(OBJ)
	printf "\033[1;35mObject files removed ✅\033[0m\n"

fclean:	clean
	rm -f $(NAME)
	rm -f unit_tests*
	rm -f *.gc*
	rm -f vgcore*
	rm -f *.so
	printf "\033[1;35mFiles removed ✅\033[0m\n"

re:	fclean all
	printf "\033[1;35mRecompiled ✅\033[0m\n"

#-------------- Tests --------------#

tests_compile: fclean
	g++ -o unit_tests $(TEST_TRUE_SRC) $(TESTS_FLAGS)
	@if [ -f unit_tests ]; then \
		printf "\033[1;32mTests compiled ✅\033[0m\n"; \
	else \
		printf "\033[1;31mTests compilation failed ❌\033[0m\n"; \
	fi

tests_launch:
	./unit_tests
	printf "\033[1;35mTests launched ✅\033[0m\n"
	gcovr --exclude tests/
	gcovr --exclude tests/ --branches
	printf "\033[1;35mCoverage generated ✅\033[0m\n"

tests_run: tests_compile tests_launch
	printf "\033[1;32mTests runned ✅\033[0m\n"
