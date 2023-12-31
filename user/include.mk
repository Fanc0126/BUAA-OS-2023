lab-ge = $(shell [ "$$(echo $(lab)_ | cut -f1 -d_)" -ge $(1) ] && echo true)

INITAPPS             := test3.x test6.x test7.x test8.x test10.x test11.x test13.x test14.x

USERLIB              := entry.o \
			syscall_wrap.o \
			debugf.o \
			libos.o \
			fork.o \
			syscall_lib.o \
			ipc.o

ifeq ($(call lab-ge,5), true)
	INITAPPS     += devtst.x fstest.x
	USERLIB      += fd.o \
			pageref.o \
			file.o \
			fsipc.o \
			console.o \
			fprintf.o

endif

ifeq ($(call lab-ge,6), true)
	INITAPPS     += icode.x \
			testpipe.x \
			testpiperace.x \
			testptelibrary.x

	USERLIB      += wait.o spawn.o pipe.o
	USERAPPS     := num.b  \
			echo.b \
			halt.b \
			ls.b \
			sh.b  \
			cat.b \
			testpipe.b \
			testpiperace.b \
			testptelibrary.b \
			testarg.b \
			testbss.b \
			testfdsharing.b \
			pingpong.b \
			init.b
endif

USERLIB := $(addprefix lib/, $(USERLIB)) $(wildcard ../lib/*.o)
