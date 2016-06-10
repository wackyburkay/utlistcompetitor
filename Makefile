CC ?= clang
CFLAGS ?= -std=c99
OUT = utlist_ll

utlist_ll: main.c
	$(CC) $(CFLAGS) -Wall -pedantic -o $(OUT) main.c
	@echo 'Dosya oluşturma tamamlandı. ($@ komutu)'
	@echo 'Dosya adı: $(OUT)'

clean:
	rm -f $(OUT) *.o
