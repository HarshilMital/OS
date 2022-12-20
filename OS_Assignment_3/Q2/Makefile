all:
	@echo "use 'make a' to run Q2a"
	@echo "use 'make b' to run Q2b"
	@echo "use 'make c' to run Q2c"

a:
	gcc -o 2a_p1 2a_p1.c
	gcc -o 2a_p2 2a_p2.c
	@./2a_p1&
	@sleep 1&
	@./2a_p2
	rm -f 2a_p1
	rm -f 2a_p2
	rm -f /home/harshil/OS/OS_Assignment_3/socket
b:
	gcc -o 2b_p1 2b_p1.c
	gcc -o 2b_p2 2b_p2.c
	@./2b_p1&
	@sleep 1&
	@./2b_p2
	rm -f 2b_p1
	rm -f 2b_p2

c:
	gcc -o 2c_p1 2c_p1.c
	gcc -o 2c_p2 2c_p2.c
	@./2c_p1&
	@sleep 1&
	@./2c_p2
	rm -f 2c_p1
	rm -f 2c_p2