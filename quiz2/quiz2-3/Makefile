CC = gcc

all: quiz2_3 utf8_gen quiz2_3SWAR

quiz2_3: quiz2_3.c
	$(CC) -o $@ quiz2_3.c
quiz2_3SWAR: quiz2_3.c
	$(CC) -o $@ quiz2_3.c -DSWAR

ufg8_gen: utf8_gen.c
	$(CC) -o $@ utf8_gen.c


test: quiz2_3 quiz2_3SWAR utf8_gen
	rm -f output.txt
	for i in $$(seq 10000000 10000000 600000000); \
	do \
		echo -n $$i >> output.txt; \
		echo -n " " >> output.txt; \
		./utf8_gen $$i $$i.txt; \
		./quiz2_3 $$i.txt >> output.txt; \
		echo -n " " >> output.txt; \
		./quiz2_3SWAR $$i.txt >> output.txt; \
		echo >> output.txt; \
		rm $$i.txt; \
	done
	gnuplot plot.gp

clean:
	rm -f utf8_gen quiz2_3 quiz2_3SWAR