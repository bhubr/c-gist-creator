LDFLAGS=-lcurl -ljansson

main : main.c
	gcc -o main main.c $(LDFLAGS)

clean:
	rm main