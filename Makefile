OBJS=head.o hanshu.o main.o
glimmer:$(OBJS)
	cc $(OBJS) -o glimmer -lreadline -lhistory
main.o:
	cc -c main.c -o main.o
hanshu.o:
	cc -c hanshu.c -o hanshu.o
head.o:
	cc -c head.c -o head.o
.PHONY:clean
clean:
	rm $(OBJS) glimmer	

