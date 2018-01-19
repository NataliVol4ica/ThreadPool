EXENAME = ft_contrast

LIBDIR = ./library
ODIR = ./obj

# LIB

LIBNAME = libft_thpool.a

LIBSRCDIR = $(LIBDIR)/sources
LIBINCDIR = $(LIBDIR)/includes

LIBHEADNAMES =	ft_thpool \
				structures
LIBHEADERS = $(patsubst %, $(LIBINCDIR)/%.h, $(HEADNAMES))

LIBFILENAMES =	get_next_line \
				gnl_tools_memory \
				gnl_tools_str \
				tools_trash \
				tools_t_line \
				tools_t_ans_mass \
				contrast \
<<<<<<< HEAD
				iterative \
				ft_contrast
=======
				tools
>>>>>>> 37a201060cbbd90429b3a4b303329c50c02f372f
LIBCFILES = $(patsubst %, $(LIBSRCDIR)/%.c, $(LIBFILENAMES))
LIBOFILES = $(patsubst %, $(ODIR)/%.o, $(LIBFILENAMES))

FLAGS = -Wall -Wextra -Werror #-lpthread

# COLORS

BLACK = '\033[0;30m'
RED = '\033[0;31m'
GREEN = '\033[0;32m'
BROWN = '\033[0;33m'
BLUE = '\033[0;34m'
PURPLE = '\033[0;35m'
CYAN = '\033[0;36m'
LGRAY = '\033[0;37m'
DGRAY = '\033[1;30m'
LRED = '\033[1;31m'
LGREEN = '\033[1;32m'
YELLOW = '\033[1;33m'
LBLUE = '\033[1;34m'
PINK = '\033[1;35m'
LCYAN = '\033[1;36m'
WHITE = '\033[1;37m'
NC = '\033[0m' # No Color

all:
	@make $(LIBNAME)
	@make $(EXENAME)

$(LIBNAME): $(ODIR) $(LIBOFILES) $(LIBHEADERS)
	@echo ${CYAN}[Compiling $(LIBNAME)]${NC}
	@ar rc $(LIBNAME) $(LIBOFILES)
	@ranlib $(LIBNAME)
	@echo ${GREEN}"[$(LIBNAME) is up to date.]"${NC}

$(ODIR)/%.o: $(LIBSRCDIR)/%.c $(LIBHEADERS)
	@gcc $(FLAGS) -o $@ -c $< -I$(LIBINCDIR)

$(ODIR):
	@mkdir -p $(ODIR)
	@mkdir -p $(ODIR)/$(LIBDIR)

$(EXENAME): $(LIBNAME) main.c
	@echo ${CYAN}[Compiling $(EXENAME)]${NC}
	@gcc -o $(EXENAME) -I $(LIBINCDIR) -L. -lft_thpool main.c
	@echo ${GREEN}"[========| $(EXENAME) is up to date. |========]"${NC}

$(EXENAME): $(LIBNAME) iterative.c
	@echo ${CYAN}[Compiling $(EXENAME)]${NC}
	@gcc -o $(EXENAME) -I $(LIBINCDIR) -L. -lft_thpool main2.c
	@echo ${GREEN}"[========| $(EXENAME) is up to date. |========]"${NC}

# CLEANING

clean:
	@echo ${RED}[Removing *.o files]${NC}
	@/bin/rm -rf $(ODIR)

fclean: clean
	@echo ${RED}[Removing $(LIBNAME)]${NC}
	@/bin/rm -f $(LIBNAME)
	@echo ${RED}[Removing $(EXENAME)]${NC}
	@/bin/rm -f $(EXENAME)

re: fclean all
