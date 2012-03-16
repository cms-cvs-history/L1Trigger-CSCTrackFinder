opt=-O0
GPP=g++-4 -Wall $(opt) -Wparentheses

all: vpp_cgen joe_sims

vpp_cgen: vpp_generated_constructor.o vpp_generated.o vpp_wrap.o vpp_main.o
	$(GPP) vpp_generated_constructor.o vpp_generated.o vpp_wrap.o vpp_main.o -o vpp_cgen

joe_sims: vpp_generated_constructor.o vpp_generated.o vpp_wrap.o joe_sims.o
	$(GPP) vpp_generated_constructor.o vpp_generated.o vpp_wrap.o joe_sims.o -o joe_sims

vpp_generated_constructor.o: vpp_generated_constructor.cpp vpp_generated.h vpp_tools.h
	$(GPP) -c vpp_generated_constructor.cpp

vpp_generated.o: vpp_generated.cpp vpp_generated.h vpp_tools.h
	$(GPP) -c vpp_generated.cpp

vpp_wrap.o: vpp_wrap.cpp vpp_generated.h vpp_tools.h
	$(GPP) -c vpp_wrap.cpp

vpp_main.o: vpp_main.cpp vpp_generated.h vpp_tools.h
	$(GPP) -c vpp_main.cpp

joe_sims.o: joe_sims.cpp vpp_generated.h vpp_tools.h
	$(GPP) -c joe_sims.cpp

.PHONY:
clean:
	rm -f *.o vpp_cgen joe_sims *~
