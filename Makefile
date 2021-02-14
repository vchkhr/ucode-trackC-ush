NAME	=	ush

FLAGS	=	-std=c11 $(addprefix -W, all extra error pedantic) -g

INC_DIRECTORY	=	inc
SRC_DIRECTORY	=	src
OBJ_DIRECTORY	=	obj

INC_FILES	=	$(wildcard $(INC_DIRECTORY)/*.h)
SRC_FILES	=	$(wildcard $(SRC_DIRECTORY)/*.c)
OBJ_FILES	=	$(addprefix $(OBJ_DIRECTORY)/, $(notdir $(SRC_FILES:%.c=%.o)))

LIBMX_DIRECTORY	=	libmx
LIBMX_OBJECT:=	$(LIBMX_DIRECTORY)/libmx.a
LIBMX_INC:= $(LIBMX_DIRECTORY)/inc

all: install

install: $(LIBMX_OBJECT) $(NAME)

$(OBJ_DIRECTORY)/%.o: $(SRC_DIRECTORY)/%.c $(INC_FILES)
	@clang $(FLAGS) -c $< -o $@ -I$(INC_DIRECTORY) -I$(LIBMX_INC)

$(OBJ_FILES): | $(OBJ_DIRECTORY)

$(OBJ_DIRECTORY):
	@mkdir -p $@

$(LIBMX_OBJECT):
	@make -sC $(LIBMX_DIRECTORY)

$(NAME): $(OBJ_FILES)
	@clang $(FLAGS) $(OBJ_FILES) -L$(LIBMX_DIRECTORY) -lmx -o $@
	
clean:
	@rm -rf $(OBJ_DIRECTORY)
	@make clean -sC $(LIBMX_DIRECTORY)

uninstall:
	@make -sC $(LIBMX_DIRECTORY) $@
	@rm -rf $(OBJ_DIRECTORY)
	@rm -rf $(NAME)

reinstall: uninstall all
