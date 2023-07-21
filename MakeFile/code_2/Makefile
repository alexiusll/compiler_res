blah.exe: blah.o # Runs third
	gcc blah.o -o blah 

blah.o: blah.c # Runs second
	gcc -c blah.c -o blah.o 

# Typically blah.c would already exist, but I want to limit any additional required files
blah.c: # Runs first
	echo int main() { return 0; } > blah.c 

clean: #windows 平台指令
	del *.exe *.o 