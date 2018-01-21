NAME = libthreadpool.a

ODIR = ./obj
INCDIR = ./includes
SRCDIR = ./sources
HEADNAMES =	threadpool \
			structures
HEADERS = $(patsubst %, $(INCDIR)/%.h, $(HEADNAMES))

FILENAMES =	init_pool \
			errors \
			thread_maintenance \
			testfuncs
CFILES = $(patsubst %, $(SRCDIR)/%.c, $(FILENAMES))
OFILES = $(patsubst %, $(ODIR)/%.o, $(FILENAMES))
FLAGS = -pthread -O3

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

all: $(NAME)

$(NAME): $(ODIR) $(OFILES) $(HEADERS)
	@echo ${CYAN}[Compiling $(NAME)]${NC}
	@ar rc $(NAME) $(OFILES)
	@ranlib $(NAME)
	@echo ${GREEN}"[========| $(NAME) is up to date. |========]"${NC}

$(ODIR)/%.o: $(SRCDIR)/%.c $(HFILES)
	gcc $(FLAGS) -o $@ -c $< -I$(INCDIR)

$(ODIR):
	@mkdir -p $(ODIR)

fclean: clean
	@echo ${RED}[Removing $(NAME)]${NC}
	@/bin/rm -f $(NAME)

clean:
	@echo ${RED}[Removing $(NAME) *.o files]${NC}
	@/bin/rm -rf $(ODIR)

re: fclean all

main: $(NAME)
	gcc -pthread -o e -I $(INCDIR) -L. -lthreadpool main.c
