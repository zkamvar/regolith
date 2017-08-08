CFILES := src/add.c \
	src/expand-binomial.c

src/init.c : $(CFILES)
	R --slave -e "cat(tools::package_native_routine_registration_skeleton('.'))" > $@

.PHONY : init

init : src/init.c
