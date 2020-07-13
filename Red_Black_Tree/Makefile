#------------------------------------------------------------------------------
#  make                  makes Order
#  make clean            removes all binaries
#  make check2           checks Order for memory leaks on infile
#------------------------------------------------------------------------------

TOP              = Order
TOP_OBJ          = $(TOP).o
TOP_SRC          = $(TOP).c
ADT              = Dictionary
ADT_OBJ          = $(ADT).o
ADT_SRC          = $(ADT).c
ADT_HDR          = $(ADT).h
COMPILE          = gcc -std=c11 -Wall -c
LINK             = gcc -std=c11 -Wall -o 
REMOVE           = rm -f
MEMCHECK         = valgrind --leak-check=full


$(TOP) : $(TOP_OBJ) $(ADT_OBJ)
	$(LINK) $(TOP) $(TOP_OBJ) $(ADT_OBJ)


$(TOP_OBJ) : $(TOP_SRC) $(ADT_HDR)
	$(COMPILE) $(TOP_SRC)



$(ADT_OBJ) : $(ADT_SRC) $(ADT_HDR)
	$(COMPILE) $(ADT_SRC)

clean :
	$(REMOVE) $(TOP) $(TOP_OBJ) $(ADT_OBJ) out1 out2


check2 : $(TOP)
	$(MEMCHECK) $(TOP) in1 out1



